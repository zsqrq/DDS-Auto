//
// Created by wz on 23-11-22.
//

#include "CServer.h"
#include <iostream>
#include "glog/logging.h"
#include "AsioThreadPool.h"

CServer::CServer(boost::asio::io_context& io_context, short port)
:_io_context(io_context), _port(port),_acceptor(io_context, tcp::endpoint(tcp::v4(),port))
{
  LOG(INFO) << "Server start success, listen on port : " << _port ;
  StartAccept();
}

CServer::~CServer() {
  LOG(INFO) << "Server destruct listen on port : " << _port;
}

void CServer::HandleAccept(shared_ptr<CSession> new_session, const boost::system::error_code& error){
  if (!error) {
    new_session->Start();
    lock_guard<mutex> lock(_mutex);
    _sessions.insert(make_pair(new_session->GetUuid(), new_session));
  }
  else {
    LOG(ERROR) << "session accept failed, error is " << error.what();
  }

  StartAccept();
}

void CServer::StartAccept() {
  CSessionPtr new_session = make_shared<CSession>(_io_context, this);
  _acceptor.async_accept(new_session->GetSocket(),
                         std::bind(&CServer::HandleAccept, this,
                                   new_session, placeholders::_1));
}

void CServer::ClearSession(std::string uuid) {
  lock_guard<mutex> lock(_mutex);
  _sessions.erase(uuid);
}
