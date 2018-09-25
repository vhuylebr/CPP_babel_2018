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
#include <unordered_map>
#include <string>
#include <array>
#include <functional>

using boost::asio::ip::tcp;

class Server;

class Session : public std::enable_shared_from_this<Session> {
    public:
      Session(boost::asio::io_service&);
  	  tcp::socket& get_socket();
      void start(Server*);
      void handle_read(std::shared_ptr<Session>&, const boost::system::error_code&,
        size_t, Server*);
      std::string getIp() {return _ip;};
      std::string getName() {return _name;};
      bool        isLogin() {return _login;};
      void  setName(std::string);
      void  writeData(std::string);
      void  acceptCall();
      void  receiveCall(std::string , std::string, int);
      void  setIsCalling(bool val) {_isCalling = val;};
      void  setIsReceiving(bool val) {_isReceiving = val;};
      void  setUserToCall(std::string val) {_userToCall = val;};
      std::string getUserToCall() {return _userToCall;};
      void  rejectCall();
      void  isRejected();
      void  isAccepted(const std::string &, int);
private:
  tcp::socket       socket;
  enum { max_length = 1024 };
  std::string       _name;
  std::array<char, max_length> data;
  bool              _login;
  std::string       _ip;
  std::string       _ipToCall;
  int               _portToCall;
  std::string       _userToCall;
  bool              _isCalling;
  bool              _isReceiving;
};

class Server {
public:
    Server(boost::asio::io_service&, short);
    void handle_accept(std::shared_ptr<Session>, const boost::system::error_code&);
	  void removeSession(std::string &);
    void  displayAllName();
    std::shared_ptr<Session> getSession(const std::string &);
    void execActions(const std::string &, Session*);

private:
    void        createSession(std::vector<std::string>, Session *);
    void  call(std::vector<std::string>, std::shared_ptr<Session>);
    void  accept(std::vector<std::string>, std::shared_ptr<Session>);
    void  reject(std::shared_ptr<Session>);
    boost::asio::io_service& ios;
    tcp::acceptor acceptor;
    std::vector<std::shared_ptr<Session> >   _clients;
    std::unordered_map<std::string, int>  _convertSwitch;
    //using ptrFunc = std::function<int(std::vector<std::string>, std::shared_ptr<Session>)>;
    //std::unordered_map<std::string, ptrFunc>  _actions;
};
