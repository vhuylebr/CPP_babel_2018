#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "VoIPManager.hpp"

using boost::asio::ip::udp;

#ifndef UDPCLIENT_HPP_
	#define UDPCLIENT_HPP_
class UdpClient
{
  public:
    UdpClient(int port);
    ~UdpClient();
    void startCall(std::string&, int);
    void hangUp();
  private:
    void start_sending();
    void start_receive();
    void handle_receive(const boost::system::error_code &error,
                        std::size_t size);
    void handle_send(boost::shared_ptr<std::string> message,
                     const boost::system::error_code &error,
                     std::size_t size);
    std::shared_ptr<udp::socket> _socket;
    boost::asio::io_service ioService;
    int         _portHost;
    Audio::VoIPManager _voIP;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1024> recv_buffer_;
};

#endif /* UDPCLIENT_HPP_ */