// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file LoanableHelloWorldPublisher.cpp
 * This file contains the implementation of the publisher functions.
 *
 * This file was generated by the tool fastddsgen.
 */


#include "LoanableHelloWorldPublisher.h"
#include "LoanableHelloWorldPubSubTypes.h"
#include "glog/logging.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <thread>
#include <chrono>

using namespace eprosima::fastdds::dds;

LoanableHelloWorldPublisher::LoanableHelloWorldPublisher()
    : participant_(nullptr)
    , publisher_(nullptr)
    , topic_(nullptr)
    , writer_(nullptr)
    , type_(new LoanableHelloWorldPubSubType())
{
}

LoanableHelloWorldPublisher::~LoanableHelloWorldPublisher()
{
  if (writer_ != nullptr)
  {
    publisher_->delete_datawriter(writer_);
  }
  if (publisher_ != nullptr)
  {
    participant_->delete_publisher(publisher_);
  }
  if (topic_ != nullptr)
  {
    participant_->delete_topic(topic_);
  }
  DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool LoanableHelloWorldPublisher::init()
{
  /* Initialize data_ here */
  data_ = std::make_shared<LoanableHelloWorld>();
  data_->index(0);
  std::array<char,256> msg{"Hello Loan World Zero Copy"};
  data_->message(std::move(msg));

  //CREATE THE PARTICIPANT
  DomainParticipantQos pqos;
  pqos.name("Participant_pub");
  participant_ = DomainParticipantFactory::get_instance()->create_participant(0, pqos);
  if (participant_ == nullptr)
  {
    return false;
  }

  //REGISTER THE TYPE
  type_.register_type(participant_);

  //CREATE THE PUBLISHER
  publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
  if (publisher_ == nullptr)
  {
    return false;
  }

  //CREATE THE TOPIC
  topic_ = participant_->create_topic(
      "LoanableHelloWorldTopic",
      type_.get_type_name(),
      TOPIC_QOS_DEFAULT);
  if (topic_ == nullptr)
  {
    return false;
  }

  // CREATE THE WRITER
  DataWriterQos wqos = publisher_->get_default_datawriter_qos();
  wqos.history().depth = 10;
  wqos.durability().kind = TRANSIENT_LOCAL_DURABILITY_QOS;
  wqos.data_sharing().automatic();
  writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);
  if (writer_ == nullptr)
  {
    return false;
  }

  LOG(INFO) << "LoanableHelloWorld DataWriter created." ;
  return true;
}

void LoanableHelloWorldPublisher::PubListener::on_publication_matched(
    eprosima::fastdds::dds::DataWriter*,
    const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{
  if (info.current_count_change == 1)
  {
    matched = info.total_count;
    LOG(INFO) << "DataWriter matched.";
  }
  else if (info.current_count_change == -1)
  {
    matched = info.total_count;
    LOG(WARNING) << "DataWriter unmatched.";
  }
  else
  {
    LOG(ERROR) << info.current_count_change
              << " is not a valid value for PublicationMatchedStatus current count change";
  }
}

void LoanableHelloWorldPublisher::run(uint32_t samples, uint32_t sleep) {
  stop = false;
  std::thread thread(&LoanableHelloWorldPublisher::runThread, this, samples,sleep);

  if (samples == 0) {
    LOG(INFO) << "Publisher running. Please press enter to stop the "
                 "Publisher at any time.";
    std::cin.ignore();
    stop = true;
  } else {
    LOG(INFO) << "Publisher running " << samples << " samples.";
  }
  thread.join();
}

void LoanableHelloWorldPublisher::runThread(uint32_t samples, uint32_t sleep) {
  if (samples == 0) {
    while (!stop) {
      if (publish(false)) {
        LOG(INFO) << "Message: " << data_->message().data()
                  << " with index: " << data_->index() << " SENT";
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
  } else {
    for (uint32_t i = 0; i < samples; ++i) {
      if (!publish()) {
        --i;
      } else {
        LOG(INFO) << "Message: " << data_->message().data()
                  << " with index: " << data_->index() << " SENT";
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
  }
}

bool LoanableHelloWorldPublisher::publish(bool waitForListener) {
  if (!waitForListener || listener_.matched > 0) {
    data_->index(data_->index() + 1);
    size_t data_size = data_->message().size();
    std::string s = "LoanableHelloWorld" + std::to_string(data_->index());
    memcpy(data_->message().data(), s.c_str(), s.size() + 1);
    writer_->write(data_.get());

    return true;
  }
  return false;
}

void LoanableHelloWorldPublisher::run()
{
  LOG(INFO) << "LoanableHelloWorld DataWriter waiting for DataReaders.";
  while (listener_.matched == 0)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
  }

  // Publication code

  LoanableHelloWorld st;

  /* Initialize your structure here */

  int msgsent = 0;
  char ch = 'y';
  do
  {
    if (ch == 'y')
    {
      writer_->write(&st);
      ++msgsent;
      std::cout << "Sending sample, count=" << msgsent << ", send another sample?(y-yes,n-stop): ";
    }
    else if (ch == 'n')
    {
      std::cout << "Stopping execution " << std::endl;
      break;
    }
    else
    {
      std::cout << "Command " << ch << " not recognized, please enter \"y/n\":";
    }
  } while (std::cin >> ch);
}