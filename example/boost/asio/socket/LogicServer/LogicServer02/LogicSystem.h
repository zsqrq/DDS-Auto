//
// Created by wz on 23-11-21.
//

#ifndef FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_LOGICSYSTEM_H_
#define FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_LOGICSYSTEM_H_
#include <queue>
#include <thread>
#include <map>
#include <functional>

#include "boost/asio.hpp"
#include "Singleton.h"
#include "CSession.h"
#include "const.h"
#include "json/json.h"
#include "json/reader.h"
#include "json/value.h"

using FunCallBack = std::function<void(CSessionPtr, short msg_id,std::string msg_data)>;

class LogicSystem : public Singleton<LogicSystem> {
  friend class Singleton<LogicSystem>;
 public:
  ~LogicSystem();
  void PostMsgToQue(std::shared_ptr<LogicNode> msg);
 private:

  LogicSystem();
  void DealMsg();
  void RegisterCallBacks();
  void HelloWorldCallBack(CSessionPtr, short ,string);
  std::thread _worker_thread;
  std::queue<std::shared_ptr<LogicNode>> _msg_que;
  std::mutex _mutex;
  std::condition_variable _consume;
  bool _b_stop;
  std::map<short, FunCallBack> _fun_callbacks;
};

#endif  // FAST_DDS_EXAMPLE_EXAMPLE_BOOST_ASIO_SOCKET_LOGICSERVER_LOGICSERVER01_LOGICSYSTEM_H_
