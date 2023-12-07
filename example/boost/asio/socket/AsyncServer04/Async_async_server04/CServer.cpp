//
// Created by wz on 23-11-15.
//
#include "CServer.h"
#include "glog/logging.h"

#include <iostream>
CServer::CServer(boost::asio::io_context& io_context, short port)
    : _io_context(io_context),
      _port(port),
      _acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {
  LOG(INFO) << "Server start success, listen on port : " << _port;
  StartAccept();
}

void CServer::HandleAccept(shared_ptr<CSession> new_session,
                           const boost::system::error_code& error) {
  if (!error) {
    new_session->Start();
    _sessions.insert(make_pair(new_session->GetUuid(), new_session));
  } else {
    LOG(ERROR) << "session accept failed, error is " << error.what();
  }

  StartAccept();
}

void CServer::StartAccept() {
  shared_ptr<CSession> new_session = make_shared<CSession>(_io_context, this);
  _acceptor.async_accept(
      new_session->GetSocket(),
      std::bind(&CServer::HandleAccept, this, new_session, placeholders::_1));
}

void CServer::ClearSession(std::string uuid) { _sessions.erase(uuid); }

