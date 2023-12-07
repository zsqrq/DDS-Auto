//
// Created by wz on 23-11-10.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER02_CSESSION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER02_CSESSION_H_
#include <queue>
#include <mutex>
#include <memory>
#include <iostream>

#include "glog/logging.h"
#include "boost/asio.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"

#define MAX_LENGTH 1024

class CServer;
class CSession;

class MsgNoe {
  friend class CSession;
 public:
  MsgNoe(char* msg, int max_len) {
    m_data = new char[max_len];
    memmove(m_data, msg, max_len);
  }

  ~MsgNoe() {
    delete[] m_data;
  }

 private:
  int m_cur_len;
  int m_max_len;
  char* m_data;
};

typedef std::shared_ptr<CServer> CServerPtr;
typedef std::shared_ptr<MsgNoe> MsgNoePtr;
using CSessionPtr = std::shared_ptr<CSession>;

class CSession : public std::enable_shared_from_this<CSession> {
 public:
  CSession(boost::asio::io_context& io_context, CServer* server);
  ~CSession() {
    LOG(INFO)<< "Ssession destruct";
  }
  boost::asio::ip::tcp::socket& GetSocket();
  std::string& GetUuid();
  void Start();
  void Send(char* msg, int max_length);

 private:
  void HandleRead(const boost::system::error_code& error, size_t bytes_transferred,
                  CSessionPtr _self_shared);
  void HandleWrite(const boost::system::error_code& error, CSessionPtr _self_shared);

  boost::asio::ip::tcp::socket m_socket;
  std::string m_uuid;
  char m_data[MAX_LENGTH];
  CServer* m_server;
  std::queue<MsgNoePtr> m_send_queue;
  std::mutex m_send_lock;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER02_CSESSION_H_
