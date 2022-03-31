#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <cassert>
#include <fcntl.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <string>

void MakeFdNonBlocking(int fd);

class Socket {
 public:
  Socket(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
  ~Socket();

  void SetSockOpt(int level, int optname, const void* optval, socklen_t optlen);

  void Bind(const in_port_t port, const in_addr_t ip);
  void Listen(const int max_queue_len);

  void Connect(const in_port_t port, const in_addr_t ip);

  void Write(const std::string& str);

  int GetFD() const;

  void MakeNonBlocking();

 private:
  int fd_;

};



#endif /* socket.hpp */
