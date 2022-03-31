#ifndef EPOLL_HPP
#define EPOLL_HPP

#include "socket.hpp"
static const size_t MAX_EPOLL_EVENTS = 1024;

class EPoll {
 public:
  EPoll();
  ~EPoll();

  int GetFD() const;

  int Wait();

  epoll_event& operator[](const size_t index);

 private:
  int fd_;

  epoll_event events_[MAX_EPOLL_EVENTS] = {0};

};

#endif /* epoll.hpp */
