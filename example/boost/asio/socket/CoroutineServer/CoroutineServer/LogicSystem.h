//
// Created by wz on 23-11-24.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_LOGICSYSTEM_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_LOGICSYSTEM_H_

#include <queue>
#include <thread>
#include "CSession.h"
#include <queue>
#include <map>
#include <functional>
#include "Const.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

typedef  function<void(shared_ptr<CSession>, const short &msg_id, const string &msg_data)> FunCallBack;
class LogicSystem
{
 public:
  ~LogicSystem();
  void PostMsgToQue(shared_ptr < LogicNode> msg);
  static LogicSystem& GetInstance();
 private:
  LogicSystem();
  void DealMsg();
  void RegisterCallBacks();
  void HelloWordCallBack(shared_ptr<CSession>, const short &msg_id, const string &msg_data);
  std::thread _worker_thread;
  std::queue<shared_ptr<LogicNode>> _msg_que;
  std::mutex _mutex;
  std::condition_variable _consume;
  bool _b_stop;
  std::map<short, FunCallBack> _fun_callbacks;
};

#endif //FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_COROUTINESERVER_COROUTINESERVER_LOGICSYSTEM_H_
