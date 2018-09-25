/*
** EPITECH PROJECT, 2018
** babel
** File description:
** UdpClient
*/

#include "../include/UdpClient.hpp"

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

UdpClient::~UdpClient()
{
}

UdpClient::UdpClient(int port)
    : _portHost(port)
{
    std::cout << "init udpClient" << std::endl;
}

void UdpClient::hangUp() {
    _socket->close();
}

void UdpClient::startCall(const std::string &remoteIp, int remotePort) {
    _socket = std::make_shared<udp::socket>(ioService, udp::endpoint(udp::v4(), _portHost)),
    remote_endpoint_ = udp::endpoint(boost::asio::ip::address::from_string(remoteIp.c_str()), remotePort);
    start_receive();
    start_sending();
    ioService.run();
}

void UdpClient::start_sending()
{
    std::cout << "start sending" << std::endl;
    boost::shared_ptr<std::string> message(
        new std::string(make_daytime_string()));
    _socket->async_send_to(boost::asio::buffer(send_data), remote_endpoint_,
                          boost::bind(&UdpClient::handle_send, this, message,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}
void UdpClient::start_receive()
{
    std::cout << "start receive" << std::endl;
    _socket->async_receive_from(
        boost::asio::buffer(recv_data), remote_endpoint_,
        boost::bind(&UdpClient::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void UdpClient::handle_receive(const boost::system::error_code &error,
                               std::size_t size)
{
    if (!error || error == boost::asio::error::message_size)
    {
        // std::cout << "Receive data " << std::string(recv_data.data()) << " size: " << size << std::endl;
        // recv_data
    }

    if ((_voIP.playRecordOutput(recv_data[0])) == NULL) {
	    std::cout << "An error occured" << std::endl;
	    exit(84);
	}
    start_receive();
}

void UdpClient::handle_send(boost::shared_ptr<std::string> message,
                            const boost::system::error_code &error,
                            std::size_t size)
{

	if ((_voIP.startRecordInput(send_data[0])) == NULL) {
		std::cout << "An error occured" << std::endl;
		exit(84);
	}
    // if (!error || error == boost::asio::error::message_size)
    // {
    //     std::cout << message->c_str() << std::endl;
    // }
    start_sending();
}
