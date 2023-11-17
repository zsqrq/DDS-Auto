//
// Created by wz on 23-11-16.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_PROTOBUFSERVER_ASYNCSERVER_CSESSION_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_PROTOBUFSERVER_ASYNCSERVER_CSESSION_H_
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <queue>
#include <mutex>
#include <memory>
#include "Const.h"
using namespace std;

using boost::asio::ip::tcp;
class CServer;
class CSession;

class MsgNode
{
  friend class CSession;
 public:
  MsgNode(const char * msg, short max_len):_total_len(max_len + HEAD_LENGTH),_cur_len(0){
    _data = new char[_total_len+1]();
    //תΪ�����ֽ���
    unsigned short max_len_host = boost::asio::detail::socket_ops::host_to_network_short(max_len);
    memcpy(_data, &max_len_host, HEAD_LENGTH);
    memcpy(_data+ HEAD_LENGTH, msg, max_len);
    _data[_total_len] = '\0';
  }

  MsgNode(short max_len):_total_len(max_len),_cur_len(0) {
    _data = new char[_total_len +1]();
  }

  ~MsgNode() {
    delete[] _data;
  }

  void Clear() {
    ::memset(_data, 0, _total_len);
    _cur_len = 0;
  }
 private:
  short _cur_len;
  short _total_len;
  char* _data;
};
using MsgNodePtr = std::shared_ptr<MsgNode>;
using CSessionPtr = std::shared_ptr<CSession>;

class CSession: public std::enable_shared_from_this<CSession>
{
 public:
  CSession(boost::asio::io_context& io_context, CServer* server);
  ~CSession();
  tcp::socket& GetSocket();
  std::string& GetUuid();
  void Start();
  void Send(char* msg,  int max_length);
  void Send(std::string msg);
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

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_PROTOBUFSERVER_ASYNCSERVER_CSESSION_H_
