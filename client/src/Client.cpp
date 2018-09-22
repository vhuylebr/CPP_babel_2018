/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client
*/

#include "../include/Client.hpp"

Client::~Client()
{
}

Client::Client(boost::asio::io_service &io_service, std::string ip, int port)
    : _endpoint(boost::asio::ip::address::from_string(ip.c_str()), port),
      _ip(ip), _port(port), _socket(std::make_shared<tcp::socket>(io_service))
{
    _socket->connect(_endpoint);
    start_receive();
}

void Client::start_receive()
{
    _socket->async_receive(boost::asio::buffer(recv_buf),
                           boost::bind(&Client::handle_receive, this,
                                       boost::asio::placeholders::error));
}

void Client::handle_receive(const boost::system::error_code &error)
{
    std::cout << "handling receive: " << error << ": " << error.message() << std::endl;
    std::cout << std::string(recv_buf.data()) << std::endl;
    //fais le pinteur sur fonction ici stp
    send_something("send_somthing");
    start_receive();
}

void Client::send_something(std::string message)
{
    boost::array<char, 128> buf;
    std::copy(message.begin(), message.end(), buf.begin());
    boost::system::error_code error;
    _socket->write_some(boost::asio::buffer(buf, message.size()), error);
}

