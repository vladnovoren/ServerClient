#include "socket.hpp"

void MakeFdNonBlocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    throw std::runtime_error("bad flags");
  }

  if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
    throw std::runtime_error("bad flags\n");
  }
}

Socket::Socket(int domain, int type, int protocol) : fd_(socket(domain, type, protocol)) {
  if (fd_ < 0) {
    throw std::runtime_error("error creating socket");
  }
}

Socket::~Socket() {
  close(fd_);
}

void Socket::SetSockOpt(int level, int optname, const void* optval, socklen_t optlen) {
  assert(optval != nullptr);

  if (setsockopt(fd_, level, optname, optval, optlen) == -1) {
    throw std::runtime_error("setsockopt error");
  }
}

void Socket::Bind(const in_port_t port, const in_addr_t ip) {
  sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = ip;

  if (bind(fd_, (sockaddr *)&addr, sizeof(addr)) < 0) {
    throw std::runtime_error("bind error");
  }
}

void Socket::Listen(const int max_queue_len) {
  if (listen(fd_, max_queue_len) < 0) {
    throw std::runtime_error("listen error");
  }
}

void Socket::Connect(const in_port_t port, const in_addr_t ip) {
  sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = ip;

  if (connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    throw std::runtime_error("connect error");
  }
}

void Socket::Write(const std::string& str) {
  write(fd_, str.c_str(), str.size());
}

int Socket::GetFD() const {
  return fd_;
}

void Socket::MakeNonBlocking() {
  MakeFdNonBlocking(fd_);
}
