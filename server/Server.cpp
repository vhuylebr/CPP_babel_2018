/*
** EPITECH PROJECT, 2018
** Server
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(boost::asio::io_service& ios, short port)
	: ios(ios), acceptor(ios, tcp::endpoint(tcp::v4(), port)) {
    std::shared_ptr<Session> session = std::make_shared<Session>(ios);
    // std::cout << "Session" << session->get_socket() << std::endl;
    acceptor.async_accept(session->get_socket(),
                          boost::bind(&Server::handle_accept, this,
                                      session,
                                      boost::asio::placeholders::error));
}

void Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code& err) {
    if (!err) {
        session->start(this);
        boost::system::error_code ignored_error;
        std::cout << "newSession" << std::endl;
        boost::asio::write(session->get_socket(), boost::asio::buffer("Login"), ignored_error);
        _clients.push_back(std::make_shared<Session>(ios));
        acceptor.async_accept(_clients.back()->get_socket(),
                            boost::bind(&Server::handle_accept, this, _clients.back(),
                                        boost::asio::placeholders::error));
        std::cout << "EndHandleAcept" << std::endl;
    } else {
      std::cerr << "err: " + err.message() << std::endl;
      session.reset();
    }
}

void Server::removeSession(int id) {
    _clients.erase(_clients.begin());
    std::cout << "Remove " << _clients.size() << id << std::endl;
}
