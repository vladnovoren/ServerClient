#include "epoll.hpp"

EPoll::EPoll() : fd_(epoll_create1(0)) {
  if (fd_ < 0) {
    throw std::runtime_error("creating epoll error");
  }
}

EPoll::~EPoll() {
  close(fd_);
}

int EPoll::GetFD() const {
  return fd_;
}

int EPoll::Wait() {
  return epoll_wait(fd_, events_, MAX_EPOLL_EVENTS, -1);
}

epoll_event& EPoll::operator[](const size_t index) {
  return events_[index];
}
