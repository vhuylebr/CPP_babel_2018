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

Client::Client(boost::asio::io_service &io_service, std::string ip, int port, int portUdpHost)
    : _endpointServer(boost::asio::ip::address::from_string(ip.c_str()), port),
      _ipServer(ip), _portServer(port), _socket(std::make_shared<tcp::socket>(io_service)), _udpClient(portUdpHost)
{
    _actions["toto"] = Client::method1;
    _actions["tata"] = Client::method2;
    _socket->connect(_endpointServer);
    start_receive();
    start_send();
}

void Client::start_send()
{

    _socket->async_send(boost::asio::buffer(send_buf),
    boost::bind(&Client::handle_send, this,
        boost::asio::placeholders::error));
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
    for (int i = 0; i < 1025; i++)
        recv_buf[i] = 0;
    //handle when the server disconnect
    //std::cout << "handling receive: " << error << ": " << error.message() << std::endl;
    // std::cout << cmd << std::endl;
    execActions(cmd);
    start_receive();
}

void Client::execActions(const std::string &cmd)
{
    std::size_t current;
    std::size_t previous = 0;
    std::vector<std::string> info;

    current = cmd.find(' ');
    while (current != std::string::npos)
    {
        info.push_back(cmd.substr(previous, current - previous));
        previous = current + 1;
        current = cmd.find(' ', previous);
    }
    info.push_back(cmd.substr(previous, current - previous));
    /*if (!_actions[info[0]])
        std::cerr << "This command doesn't exist" << std::endl;
    else
        _actions[info[0]](info);*/
}

void Client::handle_send(const boost::system::error_code &error)
{
    std::string cmd;
    char        c;

    while (std::cin.get(c) && c != '\n')
        cmd += c;
    for (int i = 0; i < 256; i++) {
        send_buf[i] = cmd[i];
        send_buf[i + 1] = 0;
    }
    start_send();
}

void Client::sendMessage(std::string message)
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

void Client::call(std::string &remoteIp, int remotePort)
{
    _udpClient.startCall(remoteIp, remotePort);
}