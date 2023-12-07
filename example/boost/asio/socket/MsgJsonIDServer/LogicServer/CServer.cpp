//
// Created by wz on 23-11-20.
//

#include "CServer.h"
#include "glog/logging.h"

CServer::CServer(boost::asio::io_context &io_context, short port):
_io_context(io_context),_port(port),_acceptor(io_context,tcp::endpoint(tcp::v4(),port)){
  LOG(INFO) << "Server start success, listen on port : " << _port;
  StartAccept();
}

void CServer::StartAccept() {
  CSessionPtr new_session = make_shared<CSession>(_io_context, this);
  _acceptor.async_accept(new_session->GetSocket(),
                         std::bind(&CServer::HandleAccept, this, new_session, placeholders::_1));
}

void CServer::HandleAccept(CSessionPtr new_session, const boost::system::error_code& error){
  if (!error) {
    new_session->Start();
    _sessions.insert(make_pair(new_session->GetUuid(), new_session));
  }
  else {
    LOG(ERROR) << "session accept failed, error is " << error.what();
  }

  StartAccept();
}

void CServer::ClearSession(std::string uuid) {
  _sessions.erase(uuid);
}
