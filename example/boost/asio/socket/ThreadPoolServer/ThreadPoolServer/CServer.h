//
// Created by wz on 23-11-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_THREADPOOLSERVER_THREADPOOLSERVER_CSERVER_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_THREADPOOLSERVER_THREADPOOLSERVER_CSERVER_H_

#include <boost/asio.hpp>
#include "CSession.h"
#include <memory.h>
#include <map>
#include <mutex>
using namespace std;
using boost::asio::ip::tcp;
class CServer
{
 public:
  CServer(boost::asio::io_context& io_context, short port);
  ~CServer();
  void ClearSession(std::string);
 private:
  void HandleAccept(CSessionPtr , const boost::system::error_code & error);
  void StartAccept();
  boost::asio::io_context &_io_context;
  short _port;
  tcp::acceptor _acceptor;
  std::map<std::string, CSessionPtr> _sessions;
  std::mutex _mutex;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_THREADPOOLSERVER_THREADPOOLSERVER_CSERVER_H_
