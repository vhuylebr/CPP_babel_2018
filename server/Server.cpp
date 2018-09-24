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
    //_actions["call"] = Server::call;
    //_actions["toto"] = Server::test2;
}

void Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code& err) {
    if (!err) {
        session->start(this);
        boost::system::error_code ignored_error;
        _clients.push_back(session);
        session->writeData("Succesfuly connected\n");
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

std::shared_ptr<Session> Server::getSession(const std::string &name) {
    for (auto &it : _clients) {
        if (it->getName() == name)
            return it;
    }
    return nullptr;
}

void    Server::createSession(std::vector<std::string> info, Session *session)
{
    if (info[0] != "login") {
        std::cout << "You need to use login before executing command\n";
        //return session->writeData("You need to use login before executing command\n");
        return ;
    }
    else if (info.size() == 1 || getSession(info[1]) != nullptr) {
        std::cout << "This name already exist\n";
        //return session->writeData("This name already exist\n");
        return ;
    }
    session->setName(info[1]);
    std::cout << "Login succesfully created\n";
    //session->writeData("Login succesfully created\n");
}

void    Server::execActions(const std::string &cmd, Session *session) {
    std::size_t                 current;
    std::size_t                 previous = 0;
    std::vector<std::string>    info;

    std::cout << "receive data: " << cmd << std::endl;
    current = cmd.find(' ');
    while (current != std::string::npos) {
        info.push_back(cmd.substr(previous, current - previous));
        previous = current + 1;
        current = cmd.find(' ', previous);
    }
    info.push_back(cmd.substr(previous, current - previous));
    if (!session->isLogin())
        return createSession(info, session);
    else {
        switch (info[0]) {
            case "call" : return this->call(info, session);
            case "test" : return this->test2(info, session);
            default : std::cout << "This command doesn't exist" << std::endl;
        }
    }
}

int     Server::call(std::vector<std::string> cmd, std::shared_ptr<Session> session)
{
    std::shared_ptr<Session>    dest;

    if (cmd.size() != 3) {
        std::cout << "call Port Name" << std::endl;
        return 1;
    }
    else if (getSession(cmd[2]) == nullptr) {
        std::cout << "The user " << cmd[2] << " doesn't exist\n";
        return 1;
    }
    dest->receiveCall(session->getName());
    return 0;
}

int     Server::test2(std::vector<std::string> cmd, std::shared_ptr<Session> session)
{
    for (auto &it : cmd) {
        std::cout << it;
    }
    std::cout << std::endl;
    return 0;
}