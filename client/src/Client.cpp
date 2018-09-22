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
    _actions["toto"] = Client::method1;
    _actions["tata"] = Client::method2;
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
    std::string cmd = std::string(recv_buf.data());

    std::cout << "handling receive: " << error << ": " << error.message() << std::endl;
    std::cout << cmd << std::endl;
    execActions(cmd);
    send_something("send_somthing");
    start_receive();
}

void    Client::execActions(const std::string &cmd) {
    std::size_t                 current;
    std::size_t                 previous = 0;
    std::vector<std::string>    info;

    current = cmd.find(' ');
    while (current != std::string::npos) {
        info.push_back(cmd.substr(previous, current - previous));
        previous = current + 1;
        current = cmd.find(' ', previous);
    }
    info.push_back(cmd.substr(previous, current - previous));
    if (!_actions[info[0]])
        std::cerr << "This command doesn't exist" << std::endl;
    else
        _actions[info[0]](info);
}

void Client::send_something(std::string message)
{
    boost::array<char, 128> buf;
    std::copy(message.begin(), message.end(), buf.begin());
    boost::system::error_code error;
    _socket->write_some(boost::asio::buffer(buf, message.size()), error);
}

int Client::method1(std::vector<std::string> cmd)
{
    return 0;
}

int Client::method2(std::vector<std::string> cmd)
{
    return 0;
}