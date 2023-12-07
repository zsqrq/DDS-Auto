//
// Created by wz on 23-11-24.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_CSESSION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_CSESSION_H_
#include <queue>
#include <mutex>
#include <memory>
#include "boost/asio.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/asio/co_spawn.hpp"
#include "boost/asio/detached.hpp"
#include "Const.h"
#include "MsgNode.h"

using namespace std;
using boost::asio::ip::tcp;
class CServer;
class LogicSystem;

using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::strand;
using boost::asio::io_context;

namespace this_coro = boost::asio::this_coro;

class CSession: public std::enable_shared_from_this<CSession>
{
 public:
  CSession(boost::asio::io_context& io_context, CServer* server);
  ~CSession();
  tcp::socket& GetSocket();
  std::string& GetUuid();
  void Start();
  void Send(const char* msg,  short max_length, short msgid);
  void Send(std::string msg, short msgid);
  void Close();
  std::shared_ptr<CSession> SharedSelf();

 private:
  void HandleWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self);
  tcp::socket _socket;
  std::string _uuid;
  char _data[MAX_LENGTH];
  CServer* _server;
  bool _b_close;
  std::queue<shared_ptr<SendNode> > _send_que;
  std::mutex _send_lock;
  std::shared_ptr<RecvNode> _recv_msg_node;
  bool _b_head_parse;
  std::shared_ptr<MsgNode> _recv_head_node;
  boost::asio::io_context& _io_context;
};

class LogicNode {
  friend class LogicSystem;
 public:
  LogicNode(shared_ptr<CSession>, shared_ptr<RecvNode>);
 private:
  shared_ptr<CSession> _session;
  shared_ptr<RecvNode> _recvnode;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_CSESSION_H_
