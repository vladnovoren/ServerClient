#include "socket.hpp"

int main(int argc, const char* argv[]) {
  if (argc < 3) {
    printf("enter ip & port\n");
    return 0;
  }

  const in_addr_t ip   = inet_addr(argv[1]);
  const in_port_t port = htons(atoi(argv[2]));

  try {
    Socket socket;
    socket.Connect(port, ip);

    std::string str;
    while (true) {
      getline(std::cin, str);
      if (str == "q") {
          break;
      }
      str += '\n';
      socket.Write(str);
    }
  } catch (std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}