//
// Created by wz on 23-11-13.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER03_ASYNCSERVER01_CSERVER_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER03_ASYNCSERVER01_CSERVER_H_

#include <boost/asio.hpp>
#include "CSession.h"
#include <memory.h>
#include <map>

class CServer
{
 public:
  CServer(boost::asio::io_context& io_context, short port);
  void ClearSession(std::string);
 private:
  void HandleAccept(shared_ptr<CSession>, const boost::system::error_code & error);
  void StartAccept();
  boost::asio::io_context &_io_context;
  short _port;
  boost::asio::ip::tcp::acceptor _acceptor;
  std::map<std::string, CSessionPtr> _sessions;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_ASYNCSERVER03_ASYNCSERVER01_CSERVER_H_
