#include "server.hpp"

int main(int argc, const char* argv[]) {
  if (argc < 3) {
    printf("enter port & ip\n");
    return 0;
  }

  const in_addr_t ip   = inet_addr(argv[1]);
  const in_port_t port = htons(atoi(argv[2]));

  try {
    Server server(port, ip);
    server.Exec();
  } catch (std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}