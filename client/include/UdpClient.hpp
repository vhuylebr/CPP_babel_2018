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
    UdpClient(int port, PaStream*);
    ~UdpClient();
    void startCall(const std::string &remoteIp, int);
    void hangUp();
  private:
    void start_sending();
    void start_receive();
    void handle_receive(const boost::system::error_code &error,
                        std::size_t size);
    void handle_send(float *,
                     const boost::system::error_code &error,
                     std::size_t size);
    std::shared_ptr<udp::socket> _socket;
    boost::asio::io_service ioService;
    int         _portHost;
    Audio::VoIPManager _voIP;
    udp::endpoint remote_endpoint_;
    float send_data[480];
    float recv_data[480];
    PaStream *_stream;
};

#endif /* UDPCLIENT_HPP_ */