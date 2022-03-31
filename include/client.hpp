#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>

class Client {
 public:
  Client(const in_port_t port, const in_addr_t ip);
  ~Client();

 private:
  int socket_fd_ = -1;
  
};

#endif /* client.hpp */
