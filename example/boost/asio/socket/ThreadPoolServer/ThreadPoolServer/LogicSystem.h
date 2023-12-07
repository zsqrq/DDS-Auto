//
// Created by wz on 23-11-22.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_LOGICSYSTEM_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_LOGICSYSTEM_H_
#include "SingleTon.h"
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

using FunCallBack = std::function<void(shared_ptr<CSession>, const short &msg_id, const string &msg_data)>;

class LogicSystem:public SingleTon<LogicSystem> {
  friend class SingleTon<LogicSystem>;
 public:
  ~LogicSystem();
  void PostMsgToQue(LogicNodePtr msg);

 private:
  LogicSystem();
  void DealMsg();
  void RegisterCallBacks();
  void HelloWordCallBack(CSessionPtr , const short &msg_id, const string &msg_data);
  std::thread _worker_thread;
  std::queue<LogicNodePtr> _msg_que;
  std::mutex _mutex;
  std::condition_variable _consume;
  bool _b_stop;
  std::map<short, FunCallBack> _fun_callbacks;
};

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_IOCONTEXTPOOLSERVER_IOCONTEXTPOOLSERVER_LOGICSYSTEM_H_
