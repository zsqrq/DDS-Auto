//
// Created by wz on 23-11-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_CSERVER_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_CSERVER_H_
#include <memory>
#include <mutex>
#include <map>
#include "boost/asio.hpp"
#include "CSession.h"

class CServer {
 public:
  CServer(boost::asio::io_context& io_context, short port);
  ~CServer();
  void ClearSession(std::string);
 private:
  void HandleAccept(shared_ptr<CSession>, const boost::system::error_code & error);
  void StartAccept();
  boost::asio::io_context &_io_context;
  short _port;
  tcp::acceptor _acceptor;
  std::map<std::string, shared_ptr<CSession>> _sessions;
  std::mutex _mutex;
};
#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_CSERVER_H_
