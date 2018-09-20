/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** main
*/

#include "Server.hpp"

int main(int argc, char *argv[])
{
  try {
    boost::asio::io_service ios;
    Server s(ios, 8080);
    ios.run();
  } catch(std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
