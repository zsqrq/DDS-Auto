#include <iostream>

#include "boost/array.hpp"
#include "boost/asio.hpp"
#include "boost/bind/bind.hpp"

using boost::asio::ip::udp;

class async_udp_client {
 public:
  async_udp_client(boost::asio::io_context& io_context, const std::string& host,
				   const std::string& port)
	  : io_context_(io_context),
		socket_(io_context, udp::endpoint(udp::v4(), 0)),
		resolver_(io_context) {
	udp::resolver::query query(udp::v4(), host, port);
	receiver_endpoint_ = *resolver_.resolve(query);
	start_send();
  }

  void start_send() {
	std::string message = "Hello from the async UDP client!";
	socket_.async_send_to(
		boost::asio::buffer(message), receiver_endpoint_,
		boost::bind(&async_udp_client::handle_send, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
  }

  void handle_send(const boost::system::error_code&, std::size_t) {
	start_receive();
  }

  void start_receive() {
	socket_.async_receive_from(
		boost::asio::buffer(recv_buf_), sender_endpoint_,
		boost::bind(&async_udp_client::handle_receive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive(const boost::system::error_code& error,
					  std::size_t bytes_transferred) {
	if (!error) {
	  std::cout.write(recv_buf_.data(), bytes_transferred);
	  std::cout << std::endl;
	  start_send();
	}
  }

 private:
  boost::asio::io_context& io_context_;
  udp::socket socket_;
  udp::resolver resolver_;
  udp::endpoint receiver_endpoint_;
  boost::array<char, 128> recv_buf_;
  udp::endpoint sender_endpoint_;
};

int main(int argc, char* argv[]) {
  if (argc != 3) {
	std::cerr << "Usage : client <host> " << std::endl;
	return 1;
  }

  try {
	boost::asio::io_context io_context;
	async_udp_client client(io_context, argv[1], argv[2]);
	io_context.run();
  } catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
  }

  return 0;
}