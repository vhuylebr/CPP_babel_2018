/*
** EPITECH PROJECT, 2018
** Server.cpp
** File description:
** Server
*/

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>

using boost::asio::ip::tcp;
class Server;

class Session : public std::enable_shared_from_this<Session> {
    public:
      Session(boost::asio::io_service&);
  	  tcp::socket& get_socket();
      void start(Server*);
      void handle_read(std::shared_ptr<Session>&, const boost::system::error_code&,
        size_t, Server*);
private:
  tcp::socket socket;
  enum { max_length = 1024 };
  char data[max_length];
};

class Server {
public:
    Server(boost::asio::io_service&, short);
    void handle_accept(std::shared_ptr<Session>, const boost::system::error_code&);
	void removeSession(int);
private:
  boost::asio::io_service& ios;
  tcp::acceptor acceptor;
  std::vector<std::shared_ptr<Session> >   _clients;
};