//
// Created by wz on 23-11-10.
//
#include <iostream>
#include "CServer.h"

CServer::CServer(boost::asio::io_context &io_context, short port)
: m_io_context(io_context), m_port(port),
m_acceptor(io_context,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port)){
  StartAccept();
}

void CServer::HandleAccept(CSessionPtr new_sessions, const boost::system::error_code &error) {
  if (!error) {
    new_sessions->Start();
    m_sessions.emplace(std::make_pair(new_sessions->GetUuid(), new_sessions));
  } else {
    LOG(INFO) << "session accept failed, error is " << error.what();
  }
  StartAccept();
}

void CServer::StartAccept() {
  CSessionPtr new_session = std::make_shared<CSession>(m_io_context, this);
  m_acceptor.async_accept(new_session->GetSocket(),
                          std::bind(&CServer::HandleAccept, this, new_session, std::placeholders::_1));
}

void CServer::ClearSession(std::string uuid) {
  m_sessions.erase(uuid);
}