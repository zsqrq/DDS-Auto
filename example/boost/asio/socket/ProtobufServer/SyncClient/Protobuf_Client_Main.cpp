//
// Created by wz on 23-11-16.
//
#include <iostream>
#include <thread>

#include "../Message/msg.pb.h"
#include "glog/logging.h"
#include "boost/asio.hpp"

constexpr int MAX_LENGTH = 1024 * 2;
constexpr int HEAD_LENGTH = 2;
using namespace std;
using namespace boost::asio::ip;

int main(int argc, char** argv) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Protobuf SyncClient");
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

    MsgData msg_data;
    msg_data.set_id(1001);
    msg_data.set_data("Hello boost asio!");

    std::string request;
    msg_data.SerializeToString(&request);
    short request_len = request.length();
    char send_data[MAX_LENGTH] = {0};

    short request_host_len = boost::asio::detail::socket_ops::host_to_network_short(request_len);
    std::memcpy(send_data,&request_host_len,HEAD_LENGTH);
    std::memcpy(send_data+HEAD_LENGTH,request.c_str(),request_len);
    boost::asio::write(sock,boost::asio::buffer(send_data,request_len+HEAD_LENGTH));

    LOG(INFO) << "begin to receive...";
    char reply_head[HEAD_LENGTH];
    size_t reply_length = boost::asio::read(sock, boost::asio::buffer(reply_head,HEAD_LENGTH));
    short msglen = 0;
    std::memcpy(&msglen,reply_head,HEAD_LENGTH);

    msglen = boost::asio::detail::socket_ops::network_to_host_short(msglen);
    char msg[MAX_LENGTH] = {0};
    size_t recv_msg_len = boost::asio::read(sock, boost::asio::buffer(msg,msglen));
    MsgData recv_data;
    recv_data.ParseFromArray(msg,msglen);
    LOG(INFO) << "msg id is " << recv_data.id() << " msg is " << recv_data.data();
    std::getchar();
  }catch (std::exception& e) {
    LOG(ERROR) << "Execptions is :" << e.what();
  }
  return 0;
}
