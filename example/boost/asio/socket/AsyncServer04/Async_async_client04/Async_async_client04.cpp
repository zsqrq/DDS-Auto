// SyncClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <boost/asio.hpp>
#include <thread>

#include "glog/logging.h"
using namespace std;
using namespace boost::asio::ip;
const int MAX_LENGTH = 1024 * 2;
const int HEAD_LENGTH = 2;
int main()
{
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging("Client");
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

    thread send_thread([&sock] {
      for (;;) {
        this_thread::sleep_for(std::chrono::milliseconds(200));
        const char* request = "Hello Debbrin, I am Wang Zhe !";
        short request_length = strlen(request);
        char send_data[MAX_LENGTH] = { 0 };
        //转为网络字节序
        short request_host_length = boost::asio::detail::socket_ops::host_to_network_short(request_length);
        memcpy(send_data, &request_host_length, 2);
        memcpy(send_data + 2, request, request_length);
        boost::asio::write(sock, boost::asio::buffer(send_data, request_length + 2));
      }
    });

    thread recv_thread([&sock] {
      for (;;) {
        this_thread::sleep_for(std::chrono::milliseconds(200));
        LOG(INFO) << "begin to receive..." ;
        char reply_head[HEAD_LENGTH];
        size_t reply_length = boost::asio::read(sock, boost::asio::buffer(reply_head, HEAD_LENGTH));
        short msglen = 0;
        memcpy(&msglen, reply_head, HEAD_LENGTH);
        //转为本地字节序
        msglen = boost::asio::detail::socket_ops::network_to_host_short(msglen);
        char msg[MAX_LENGTH] = { 0 };
        size_t  msg_length = boost::asio::read(sock, boost::asio::buffer(msg, msglen));

        LOG(INFO)<< "Reply is: ";
        LOG(INFO) << msg;
//        std::cout.write(msg, msglen) << endl;
        LOG(INFO) << "Reply len is :" << msglen;
        LOG(INFO) << msglen;
//        std::cout << "\n";
      }
    });

    send_thread.join();
    recv_thread.join();
  }
  catch (std::exception& e) {
    LOG(ERROR)<< "Exception: " << e.what() ;
  }
  return 0;
}


