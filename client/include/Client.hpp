/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client
*/

#include <unordered_map>
#include "UdpClient.hpp"

using boost::asio::ip::tcp;

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

class Client
{
public:
  Client(boost::asio::io_service &io_service, std::string, int, int);
  ~Client();
  void call(std::string&, int);

private:
  int _portServer;
  std::string _ipServer;
  tcp::endpoint _endpointServer;
  std::array<char, 1024> recv_buf;
  std::shared_ptr<tcp::socket> _socket;
  using ptrFunc = std::function<int(std::vector<std::string>)>;
  std::unordered_map<std::string, ptrFunc> _actions;
  UdpClient _udpClient;

  void start_receive();
  void send_something(std::string message);
  void handle_receive(const boost::system::error_code &error);
  static int method1(std::vector<std::string>);
  static int method2(std::vector<std::string>);
  void execActions(const std::string &);
};

#endif /* !CLIENT_HPP_ */
