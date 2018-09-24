/*
** EPITECH PROJECT, 2018
** Session
** File description:
** Client
*/

#include "Server.hpp"

Session::Session(boost::asio::io_service& ios)
    : socket(ios), _name(""), _login(false), _ip(socket.remote_endpoint().address().to_string()) {}

tcp::socket& Session::get_socket() {
    return socket;
}

void Session::start(Server *server) {
    socket.async_read_some(
        boost::asio::buffer(data, max_length),
        boost::bind(&Session::handle_read, this,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred, server));
}

void Session::handle_read(std::shared_ptr<Session>& s, const boost::system::error_code& err,
        size_t bytes_transferred, Server *server) {
    if (!err) {
    server->execActions(std::string(data.data()), this);
    boost::system::error_code ignored_error;
    start(server);
    // permet l'envoie de reponse
    //boost::asio::write(socket, boost::asio::buffer("InConnect"), ignored_error);

    } else {
        std::cerr << "err (recv): " << err.message() << std::endl;
        server->displayAllName();
        server->removeSession(3);
    }
}

void    Session::setName(std::string name)
{
    _name = name;
    _login = true;
}

void    Session::writeData(std::string message)
{
    boost::system::error_code ignored_error;

    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
}

void    Session::receiveCall(const std::string &user)
{
    std::cout << user << " is trying to call you" << std::endl;
    writeData(user + " is trying to call you\n");
}