#include "server.hpp"

Server::Server(const in_port_t port, const in_addr_t ip) {
  int reuse = 1;
  socket_.SetSockOpt(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  socket_.Bind(port, ip);
  socket_.Listen(MAX_QUEUE_LEN);
  socket_.MakeNonBlocking();
  EPollInit();
}

Server::~Server() {
}

void Server::EPollInit() {
  struct epoll_event ep_ev;
  ep_ev.data.fd = socket_.GetFD();
  ep_ev.events = EPOLLIN ;
  if (epoll_ctl(epoll_.GetFD(), EPOLL_CTL_ADD, socket_.GetFD(), &ep_ev) < 0) {
    throw std::runtime_error("bad epoll_ctl\n");
  }
}

void Server::EventLoop() {
  while (true) {
    int events_cnt = epoll_.Wait();
    for (int i = 0; i < events_cnt; ++i) {
      int event_fd = epoll_[i].data.fd;
      if (event_fd == socket_.GetFD()) {
        AddClient();
      } else {
        while (true) {
          char buff = -1;
          int ret = read(event_fd, &buff, 1);
          if(ret > 0){
              printf("%c", buff);
          }
          if(buff == '\n'){
              break;
          }
          else if (ret == 0){
            close(event_fd);
            epoll_ctl(epoll_.GetFD(), EPOLL_CTL_DEL, event_fd, NULL);
            break;
          }
          else if (ret < 0){
              printf("read error.\n");
              break;
          }
        }
      }
    }
  }
}

void Server::Exec() {
  EventLoop();
}

void Server::AddClient() {
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int connfd = accept(socket_.GetFD(), (struct sockaddr *)&client_addr, &client_addr_len);
  MakeFdNonBlocking(connfd);

  struct epoll_event ev;
  ev.data.fd = connfd;
  ev.events = EPOLLIN;
  if (epoll_ctl(epoll_.GetFD(), EPOLL_CTL_ADD, connfd, &ev) < 0){
    throw std::runtime_error("epoll_ctl error");
  }
}
