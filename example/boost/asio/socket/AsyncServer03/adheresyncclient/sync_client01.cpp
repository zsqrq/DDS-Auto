//
// Created by wz on 23-11-13.
//
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "glog/logging.h"
using namespace std;
using namespace boost::asio::ip;
const int MAX_LENGTH = 1024*2;
const int HEAD_LENGTH = 2;
int main()
{
  FLAGS_alsologtostderr = true;
  FLAGS_minloglevel = 0;
  try {
    //创建上下文服务
    boost::asio::io_context   ioc;
    //构造endpoint
    tcp::endpoint  remote_ep(address::from_string("127.0.0.1"), 10086);
    tcp::socket  sock(ioc);
    boost::system::error_code   error = boost::asio::error::host_not_found; ;
    sock.connect(remote_ep, error);
    if (error) {
      LOG(ERROR) << "connect failed, code is " << error.value() << " error msg is " << error.message();
      return 0;
    }

    std::thread send_thread([&sock] {
      for(;;) {
        this_thread::sleep_for(std::chrono::milliseconds(2));
        const char* request = "hello world!";
        size_t request_length = strlen(request);
        char send_data[MAX_LENGTH] = { 0 };
        memcpy(send_data, &request_length, 2);
        memcpy(send_data + 2, request, request_length);
        boost::asio::write(sock, boost::asio::buffer(send_data, request_length + 2));
      }
    });
    std::thread recv_thread([&sock] {
      for (;;) {
        this_thread::sleep_for(std::chrono::milliseconds(2));
        LOG(INFO) <<" Beging to receive .... ";
        char reply_head[HEAD_LENGTH];
        size_t reply_length = boost::asio::read(sock, boost::asio::buffer(reply_head, HEAD_LENGTH));
        short msg_len = 0;
        ::memcpy(&msg_len, reply_head, HEAD_LENGTH);
        char msg[MAX_LENGTH]= {0};
        size_t msglen = boost::asio::read(sock, boost::asio::buffer(msg, msg_len));

        LOG(INFO) << "Reply is : ";
        LOG(INFO) << msg;
        LOG(INFO) << "Reply lenth is : " <<msg_len << "\n";
      }
    });

    send_thread.join();
    recv_thread.join();
  }
  catch (std::exception& e) {
    LOG(ERROR)<< "Exception: " << e.what();
  }
  return 0;
}