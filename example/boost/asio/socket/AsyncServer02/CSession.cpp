//
// Created by wz on 23-11-10.
//
#include <iostream>
#include "CSession.h"
#include "CServer.h"

CSession::CSession(boost::asio::io_context &io_context, CServer *server)
: m_socket(io_context), m_server(server){
  boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
  m_uuid = boost::uuids::to_string(a_uuid);
}

boost::asio::ip::tcp::socket& CSession::GetSocket() {
  return m_socket;
}

std::string& CSession::GetUuid() {
  return m_uuid;
}

void CSession::Start() {
  memset(m_data, 0, MAX_LENGTH);
  m_socket.async_read_some(boost::asio::buffer(m_data, MAX_LENGTH),
                           std::bind(&CSession::HandleRead, this,
                                     std::placeholders::_1,
                                     std::placeholders::_2,
                                     shared_from_this()));
}

void CSession::Send(char *msg, int max_length) {
  bool pending = false;
  std::lock_guard<std::mutex> lock(m_send_lock);
  if (m_send_queue.size() > 0) {
    pending = true;
  }
  m_send_queue.push(std::make_shared<MsgNoe>(msg, max_length));
  if (pending) { return;}
  boost::asio::async_write(m_socket, boost::asio::buffer(msg, max_length),
                           std::bind(&CSession::HandleWrite, this,
                                     std::placeholders::_1, shared_from_this()));
}

void CSession::HandleWrite(const boost::system::error_code &error, CSessionPtr _self_shared) {
  if (!error) {
    std::lock_guard<std::mutex> lock(m_send_lock);
    m_send_queue.pop();
    if (!m_send_queue.empty()) {
      auto& msgnode = m_send_queue.front();
      boost::asio::async_write(m_socket, boost::asio::buffer(msgnode->m_data,
                                                             msgnode->m_max_len),
                               std::bind(&CSession::HandleWrite, this, std::placeholders::_1, _self_shared));
    }
  } else {
    LOG(ERROR) << "Handle Write Failed, Error Is : " << error.what();
    m_server->ClearSession(m_uuid);
  }
}

void CSession::HandleRead(const boost::system::error_code &error, size_t bytes_transferred, CSessionPtr _self_shared) {
  if (!error) {
    LOG(INFO) << "Read Data is : " << m_data;
    Send(m_data, bytes_transferred);
    memset(m_data, 0, MAX_LENGTH);
    m_socket.async_read_some(boost::asio::buffer(m_data, MAX_LENGTH),
                             std::bind(&CSession::HandleRead, this,
                                       std::placeholders::_1, std::placeholders::_2, _self_shared));
  } else {
    LOG(ERROR) << "handle read failed, error is " << error.what();
    m_server->ClearSession(m_uuid);
  }
}

