//
// Created by wz on 23-11-21.
//
#include <iostream>
#include <thread>
#include <memory>

#include "boost/asio.hpp"
#include "json/json.h"
#include "json/reader.h"
#include "glog/logging.h"

using namespace std;
using namespace boost::asio::ip;

int constexpr MAX_LENGTH=2048;
int constexpr HEAD_LENGTH=2;
int constexpr HEAD_TOTAL=4;

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr =1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Jsong Client");

  try {
    boost::asio::io_context io_context;
    tcp::endpoint remote_ep(address::from_string("127.0.0.1"),10086);
    tcp::socket sock(io_context);
    boost::system::error_code error = boost::asio::error::host_not_found;
    sock.connect(remote_ep,error);
    if (error) {
      LOG(ERROR) << "connect failed, code is " << error.value() << " error msg is " << error.message();
      return 0;
    }
    Json::Value root;
    root["id"] = 1001;
    root["data"] = "Hello World";
    std::string request = root.toStyledString();
    size_t request_length = request.length();
    char send_data[MAX_LENGTH]={0};
    int msgid = 0;
    int msgid_host = boost::asio::detail::socket_ops::host_to_network_short(msgid);
    std::memcpy(send_data,&msgid_host,2);
    int request_host_length = boost::asio::detail::socket_ops::host_to_network_short(request_length);

    std::memcpy(send_data+2, &request_host_length,2);
    std::memcpy(send_data+4,request.c_str(),request_length);
    boost::asio::write(sock,boost::asio::buffer(send_data,request_length+4));
    LOG(INFO) << "Begin to receive ...";

    char reply_head[HEAD_TOTAL];
    size_t reply_length = boost::asio::read(sock,boost::asio::buffer(reply_head,HEAD_TOTAL));

    msgid = 0;
    std::memcpy(&msgid, reply_head,HEAD_LENGTH);
    short msglen = 0;
    std::memcpy(&msglen,reply_head+2, HEAD_LENGTH);

    msglen = boost::asio::detail::socket_ops::network_to_host_short(msglen);
    msgid = boost::asio::detail::socket_ops::network_to_host_short(msgid);
    char msg[MAX_LENGTH] = {0};
    size_t msg_length = boost::asio::read(sock, boost::asio::buffer(msg,msglen));

    Json::Reader reader;
    reader.parse(std::string(msg, msg_length),root);
    LOG(INFO) << "msg id is " << root["id"] << " msg is " << root["data"];
    ::getchar();
  } catch (std::exception& e) {
    LOG(ERROR) << "Exception is : " << e.what();
  }

  return 0;
}
