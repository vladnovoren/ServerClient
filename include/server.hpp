#ifndef SERVER_HPP
#define SERVER_HPP

#include "epoll.hpp"

static const size_t MAX_QUEUE_LEN = 1024;

class Server {
 public:
  Server(const in_port_t port, const in_addr_t ip);
  ~Server();

  void EPollInit();
  void EventLoop();

  void Exec();

  void AddClient();

 private:
  Socket socket_;
  EPoll  epoll_;

};

#endif /* server.hpp */
