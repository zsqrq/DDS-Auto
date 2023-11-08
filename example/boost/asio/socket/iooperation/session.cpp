//
// Created by wz on 23-11-8.
//

#include "session.h"
#include "glog/logging.h"

using namespace boost;

Session::Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
: _socket(socket), _send_pending(false), _recv_pending(false){}

void Session::Connect(const boost::asio::ip::tcp::endpoint &ep) {
  _socket->connect(ep);
}

void Session::WriteCallBack(const boost::system::error_code &ec, std::size_t bytes_transferred) {
  if (ec.value() != 0) {
    LOG(ERROR) << "Error , code is " << ec.value() << " . Message is " << ec.message();
    return;
  }
  auto & send_data = _send_queue.front();
  send_data->cur_len_ += bytes_transferred;

  if (send_data->cur_len_ < send_data->total_len_) {
    this->_socket->async_write_some(boost::asio::buffer(send_data->msg_ + send_data->cur_len_,
                                                        send_data->total_len_ - send_data->cur_len_),
                                    std::bind(&Session::WriteCallBack, this,std::placeholders::_1,std::placeholders::_2));
    return;
  }
  _send_queue.pop();
  if (_send_queue.empty()) {
    _send_pending = false;
  }
  if (!_send_queue.empty()) {
    auto& send_data = _send_queue.front();
    this->_socket->async_write_some(boost::asio::buffer(send_data->msg_ + send_data->cur_len_, send_data->total_len_ - send_data->cur_len_),
                                    std::bind(&Session::WriteCallBack,
                                              this, std::placeholders::_1, std::placeholders::_2));
  }
}

void Session::WriteToSocket(const std::string &buf) {
  _send_queue.emplace(new MsgNode(buf.c_str(), buf.length()));
  if (_send_pending) {
    return;
  }
  this->_socket->async_write_some(boost::asio::buffer(buf),
                                  std::bind(&Session::WriteCallBack,this,
                                            std::placeholders::_1, std::placeholders::_2));
  _send_pending = true;
}

void Session::WriteAllCallBack(const boost::system::error_code &ec, std::size_t bytes_transferred) {
  if (ec.value() != 0) {
    LOG(ERROR)<< "Error occured! Error code = "
              << ec.value()
              << ". Message: " << ec.message();
    return;
  }
  _send_queue.pop();

  if (_send_queue.empty()) {
    _send_pending = false;
  }

  if (!_send_queue.empty()) {
    auto& send_data = _send_queue.front();
    this->_socket->async_send(asio::buffer(send_data->msg_ + send_data->cur_len_, send_data->total_len_ - send_data->cur_len_),
                              std::bind(&Session::WriteAllCallBack,
                                        this, std::placeholders::_1, std::placeholders::_2));
  }
}

void Session::ReadFromSocket() {
  if (_recv_pending) {
    return;
  }
  /*auto _recv_nodez = std::make_unique<MsgNode>(RECVSIZE);
  _recv_node = _recv_nodez;*/
  _recv_node = std::make_shared<MsgNode>(RECVSIZE);
  _socket->async_read_some(asio::buffer(_recv_node->msg_, _recv_node->total_len_),
                           std::bind(&Session::ReadCallBack, this,
                                     std::placeholders::_1, std::placeholders::_2));
  _recv_pending = true;
}

void Session::ReadCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred){
  _recv_node->cur_len_ += bytes_transferred;
  if (_recv_node->cur_len_ < _recv_node->total_len_) {
    _socket->async_read_some(asio::buffer(_recv_node->msg_+_recv_node->cur_len_,
                                          _recv_node->total_len_ - _recv_node->cur_len_),
                             std::bind(&Session::ReadCallBack, this,
                                       std::placeholders::_1, std::placeholders::_2));
    return;
  }
  _recv_pending = false;
  _recv_node = nullptr;
}

void Session::ReadAllCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred) {
  _recv_node->cur_len_ += bytes_transferred;
  _recv_pending = false;
  _recv_node = nullptr;
}

void Session::WriteCallBackErr(const boost::system::error_code& ec,
                               std::size_t bytes_transferred, std::shared_ptr<MsgNode> msg_node) {
  if (bytes_transferred + msg_node->cur_len_
      < msg_node->total_len_) {
    _send_node->cur_len_ += bytes_transferred;
    this->_socket->async_write_some(asio::buffer(_send_node->msg_+_send_node->cur_len_,
                                                 _send_node->total_len_-_send_node->cur_len_),
                                    std::bind(&Session::WriteCallBackErr,
                                              this, std::placeholders::_1, std::placeholders::_2, _send_node));
  }
}

void Session::WriteToSocketErr(const std::string& buf) {
  _send_node = std::make_shared<MsgNode>(buf.c_str(), buf.length());

  this->_socket->async_write_some(asio::buffer(_send_node->msg_,
                                               _send_node->total_len_),
                                  std::bind(&Session::WriteCallBackErr,
                                            this, std::placeholders::_1, std::placeholders::_2, _send_node));
}
