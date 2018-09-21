/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#include "Server.hpp"

int test(std::vector<std::string> cmd)
{
    for (auto &it : cmd) {
        std::cout << it;
    }
    std::cout << std::endl;
    return 0;
}

Server::Server(boost::asio::io_service& ios, short port)
	: ios(ios), acceptor(ios, tcp::endpoint(tcp::v4(), port)) {
    std::shared_ptr<Session> session = std::make_shared<Session>(ios);
    // std::cout << "Session" << session->get_socket() << std::endl;
    acceptor.async_accept(session->get_socket(),
                          boost::bind(&Server::handle_accept, this,
                                      session,
                                      boost::asio::placeholders::error));
    _actions["test"] = test;
}

void Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code& err) {
    if (!err) {
        session->start(this);
        boost::system::error_code ignored_error;
        boost::asio::write(session->get_socket(), boost::asio::buffer("Login"), ignored_error);
        _clients.push_back(session);
        std::shared_ptr<Session> session = std::make_shared<Session>(ios);
        acceptor.async_accept(session->get_socket(),
                            boost::bind(&Server::handle_accept, this, session,
                                        boost::asio::placeholders::error));
        displayAllName();
    } else {
      std::cerr << "err: " + err.message() << std::endl;
      session.reset();
    }
}

void Server::removeSession(int id) {
    // TO DO
    // _clients.erase(_clients.begin());
}

void Server::displayAllName() {
    for (auto client : _clients) {
        // parcours tout les session
        //  std::cout << (void*)client.get() << " |" << client->getName() << ", ";
    }
}

void    Server::execActions(const std::string &cmd, Session *session) {
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