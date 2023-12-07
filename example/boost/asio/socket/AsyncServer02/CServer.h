//
// Created by wz on 23-11-10.

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER02_CSERVER_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER02_CSERVER_H_
#include <memory>
#include <map>

#include "boost/asio.hpp"
#include "CSession.h"

class CServer {
 public:
  CServer(boost::asio::io_context& io_context, short  port);
  void ClearSession(std::string);
 private:
  void HandleAccept(CSessionPtr, const boost::system::error_code& error);
  void StartAccept();
  boost::asio::io_context& m_io_context;
  short m_port;
  boost::asio::ip::tcp::acceptor m_acceptor;
  std::map<std::string, CSessionPtr> m_sessions;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER02_CSERVER_H_
