#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class UdpCall
{
public:
  UdpCall(boost::asio::io_service &io_service, int port, int remotePort)
      : socket_(io_service, udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), port)),
        remote_endpoint_(udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), remotePort))
  {
      start_receive();
      start_sending();
  }

private:
  void start_sending()
  {
    std::cout << "start sending" << std::endl;
    boost::shared_ptr<std::string> message(
        new std::string(make_daytime_string()));
    socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                          boost::bind(&UdpCall::handle_send, this, message,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
  }
  void start_receive()
  {
    std::cout << "start receive" << std::endl;
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&UdpCall::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive(const boost::system::error_code &error,
                      std::size_t size)
  {
    if (!error || error == boost::asio::error::message_size)
    {
      std::cout << "Receive data " << std::string(recv_buffer_.data()) << " size: " << size << std::endl;
    }
    start_receive();
  }

  void handle_send(boost::shared_ptr<std::string> message,
                   const boost::system::error_code &error,
                   std::size_t size)
  {
    if (!error || error == boost::asio::error::message_size)
    {
      std::cout << message->c_str() << std::endl;
    }
    start_sending();
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 1024> recv_buffer_;
};

int main(int ac, char **ar)
{
  try
  {
    boost::asio::io_service io_service;
    UdpCall server(io_service, std::stoi(ar[1]), std::stoi(ar[2]));
    io_service.run();
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
// #include "../include/Client.hpp"

// int main()
// {
// 	boost::asio::io_service io_service;
// 	Client client(io_service, "127.0.0.1", 8080);
// 	io_service.run();
// 	return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <boost/thread.hpp>
// #include "portaudio.h"
// #include "../include/PortAudio.hpp"
// #include "../include/VoIPManager.hpp"

// PaStream	*startRecord(PaStream *stream, paTestData &data) {
// 	if ((stream = voIP.startRecordInput(data)) == NULL) {
// 		std::cout << "An error occured" << std::endl;
// 		exit(84);
// 	}
// }

// PaStream	*playRecord(PaStream *stream, paTestData &data)
// {
// 	if ((stream = voIP.playRecordOutput(data)) == NULL) {
// 		std::cout << "An error occured" << std::endl;
// 		exit(84);
// 	}
// }

// int	main()
// {
// 	Audio::VoIPManager  voIP;
// 	Audio::PortAudio  portA;
// 	PaStream*           stream;
// 	paTestData          data;
// 	using namespace boost;
//     thread thread_1 = thread(startRecord, stream, data);
//     thread thread_2 = thread(playRecord, stream, data);
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include "portaudio.h"
// #include "../include/PortAudio.hpp"
// #include "../include/VoIPManager.hpp"

// int	main()
// {
// 	Audio::VoIPManager  voIP;
// 	PaStream*           stream;
// 	paTestData          data;

// 	while (1) {
// 		if ((stream = voIP.startRecordInput(data)) == NULL) {
// 			std::cout << "An error occured" << std::endl;
// 			exit(84);
// 		}
// 		if ((stream = voIP.playRecordOutput(data)) == NULL) {
// 			std::cout << "An error occured" << std::endl;
// 			exit(84);
// 		}
// 	}
// }
