//
// Created by wz on 23-11-7.
//

#include <iostream>
#include "connection.h"
#include "session.h"
#include "glog/logging.h"

int accept_new_connection( ) {
  // The size of the queue containing the pending connection requests.
  constexpr int BACKLOG_SIZE = 30;

  // Step 1. Here we assume that the server application has already obtained the protocol port number.
  unsigned short port_num = 3333;

  // Step 2. Creating a server endpoint.
  boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port_num);
  boost::asio::io_context io_context;

  try {
    // Step 3. Instantiating and opening an acceptor socket.
    boost::asio::ip::tcp::acceptor acceptor(io_context, endpoint.protocol());
    // Step 4. Binding the acceptor socket to the server endpoint.
    acceptor.bind(endpoint);

    // Step 5. Starting to listen for incoming connection
    acceptor.listen(BACKLOG_SIZE);

    // Step 6. Creating an active socket.
    boost::asio::ip::tcp::socket sock(io_context);

    // Step 7. Processing the next connection request and connecting the active socket to the client.
    acceptor.accept(sock);
  } catch (boost::system::system_error& e) {
    LOG(INFO) << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();
    return e.code().value();
  }
  return 0;
}

void use_buffer_str() {
  boost::asio::const_buffers_1 out_buf = boost::asio::buffer("Hello World");
}

void use_buffer_array() {
  constexpr size_t BUF_SIZE_BYTES = 20;
  auto buf = std::make_unique<char[]>(BUF_SIZE_BYTES);
  auto input_buf = boost::asio::buffer(static_cast<void*>(buf.get()), BUF_SIZE_BYTES);
}

void use_const_buffer() {
  std::string buf = "Hello World";
  boost::asio::const_buffer asio_buf(buf.c_str(), buf.length());
  std::vector<boost::asio::const_buffer> buffer_sequence;
  buffer_sequence.push_back(asio_buf);
}

void use_stream_buffer() {
  boost::asio::streambuf buf;
  std::ostream output{&buf};

  // Writing the message to the stream-based buffer.
  output << "Message1 \n Message2";

  // Now we want to read all data from a streambuf until '\n' delimiter.
  std::istream input(&buf);
  std::string message1;
  std::getline(input, message1);
}

void write_to_socket(boost::asio::ip::tcp::socket& sock) {
  std::string buf = "Hello World";
  std::size_t total_bytes_written = 0;

  while (total_bytes_written != buf.length()) {
    total_bytes_written += sock.write_some(boost::asio::buffer(buf.c_str() + total_bytes_written,
                                                               buf.length() - total_bytes_written));
  }
}

int send_data_by_write_some() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address),port_num);
    boost::asio::io_context io_context;

    // Step1. Allocating and opening the socket.
    boost::asio::ip::tcp::socket sock(io_context, ep.protocol());
    sock.connect(ep);
    write_to_socket(sock);
  }
  catch (boost::system::system_error& e) {
    LOG(INFO) << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();
    return e.code().value();
  }
  return 0;
}

int send_data_by_send() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address),port_num);
    boost::asio::io_context io_context;

    // Step 1. Allocating and opening the socket
    boost::asio::ip::tcp::socket sock(io_context, ep.protocol());
    sock.connect(ep);
    std::string buf = "Hello World!";
    int send_length = sock.send(boost::asio::buffer(buf.c_str(),buf.length()));
    if (send_length <= 0) {
      LOG(INFO) << "Send Failed ";
      return 0;
    }
  } catch (boost::system::system_error& e) {
    LOG(WARNING) << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();
    return e.code().value();
  }
  return 0;
}

int send_data_by_write() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
    boost::asio::io_context io_context;

    // Step 1. Allocating and opening the socket
    boost::asio::ip::tcp::socket sock(io_context,ep.protocol());
    sock.connect(ep);
    std::string buf = "Hello World!";
    int send_length =
        boost::asio::write(sock, boost::asio::buffer(buf.c_str(), buf.length()));
    if (send_length <= 0) {
      LOG(ERROR) << "Send Failed";
      return 0;
    }
  } catch (boost::system::system_error& e) {
    LOG(ERROR) << "Error occured! Error code = " << e.code()
                    << ". Message: " << e.what();
    return e.code().value();
  }
  return 0;
}

std::string read_from_socket(boost::asio::ip::tcp::socket& sock) {
  constexpr unsigned char MESSAGE_SIZE = 7;
  char buf[MESSAGE_SIZE];
  size_t total_bytes_read = 0;

  while (total_bytes_read != MESSAGE_SIZE) {
    total_bytes_read += sock.read_some(boost::asio::buffer(buf + total_bytes_read, MESSAGE_SIZE- total_bytes_read));
  }
  return std::string{buf};
}

int read_data_by_read_some() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::socket sock(io_context, ep.protocol());

    sock.connect(ep);
    read_from_socket(sock);
  } catch (boost::system::system_error& e) {
    LOG(ERROR) << "Error occured! Error code = " << e.code()
             << ". Message: " << e.what();

    return e.code().value();
  }
  return 0;
}

int read_data_by_receive() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address),port_num);
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::socket sock(io_context, ep.protocol());
    sock.connect(ep);
    constexpr unsigned char BUFF_SIZE = 7;
    char buffer_receive[BUFF_SIZE];
    std::size_t receive_length = sock.receive(boost::asio::buffer(buffer_receive, BUFF_SIZE));
    if (receive_length <= 0) {
      LOG(ERROR) << "receive failed";
    }
  } catch (boost::system::system_error& e) {
    LOG(ERROR) << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();
    return e.code().value();
  }
  return 0;
}

int read_data_by_read() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address),port_num);
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::socket sock(io_context,ep.protocol());
    sock.connect(ep);
    constexpr unsigned char BUFF_SIZE = 7;
    char buffer_receive[BUFF_SIZE];

    auto receive_length = boost::asio::read(sock,boost::asio::buffer(buffer_receive, BUFF_SIZE));
    if (receive_length <= 0) {
      LOG(ERROR) << "receive failed";
    }
  } catch (boost::system::system_error& e) {
    LOG(ERROR) << "Error occured! Error code = " << e.code()
               << ". Message: " << e.what();
    return e.code().value();
  }
  return 0;
}

std::string read_data_by_until(boost::asio::ip::tcp::socket& sock) {
  boost::asio::streambuf buf;

  // Synchronously read data from the socket until '\n' symbol is encountered.
  boost::asio::read_until(sock,buf, '\n');
  std::string message;

  // Because buffer 'buf' may contain some other data
  // after '\n' symbol, we have to parse the buffer and
  // extract only symbols before the delimiter.
  std::istream input_stream(&buf);
  std::getline(input_stream, message);
  return message;
}

int async_write_data() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;
  try {
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address),
                               port_num);
    boost::asio::io_context iox;
    auto socket_ptr =
        std::make_shared<boost::asio::ip::tcp::socket>(iox, ep.protocol());
    auto session_ptr = std::make_shared<Session>(socket_ptr);
    session_ptr->Connect(ep);
    session_ptr->WriteToSocket("Hello world");
    iox.run();
  } catch (boost::system::system_error& e) {
    std::cout << "Error occured! Error code = " << e.code()
              << " . Message: " << e.what();
    return e.code().value();
  }

  return 0;
}











