//
// Created by wz on 23-11-20.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_MSGJSONIDSERVER_LOGICSERVER_CSESSION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_MSGJSONIDSERVER_LOGICSERVER_CSESSION_H_
#include <queue>
#include <mutex>
#include <memory>
#include "boost/asio.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "Const.h"
#include "MsgNode.h"

using namespace std;
using boost::asio::ip::tcp;

class CServer;
class CSession;
using CSessionPtr = std::shared_ptr<CSession>;

class CSession : public std::enable_shared_from_this<CSession> {

 public:
  CSession(boost::asio::io_context& io_context, CServer* server);
  ~CSession();
  tcp::socket& GetSocket();
  std::string& GetUuid();
  void Start();
  void Send(char* msg,  short max_length, short msgid);
  void Send(std::string msg, short msgid);
  void Close();
  std::shared_ptr<CSession> SharedSelf();

 private:
  void HandleRead(const boost::system::error_code& error, size_t  bytes_transferred, CSessionPtr shared_self);
  void HandleWrite(const boost::system::error_code& error, CSessionPtr shared_self);
  tcp::socket _socket;
  std::string _uuid;
  char _data[MAX_LENGTH];
  CServer* _server;
  bool _b_close;
  std::queue<MsgNodePtr > _send_que;
  std::mutex _send_lock;
  MsgNodePtr _recv_msg_node;
  bool _b_head_parse;
  MsgNodePtr _recv_head_node;
};

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_MSGJSONIDSERVER_LOGICSERVER_CSESSION_H_
