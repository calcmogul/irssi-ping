#include <print>
#include <string>
#include <vector>

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

// Command line arguments should be IP address of server, file number (2
// characters) and file extension (3 characters)
int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc + !argc};

  if (args.size() != 3 || args[1].size() != 2 || args[2].size() != 3) {
    std::println("irssi-remote IP_ADDR FILE_NUM (2 chars) FILE_EXT (3 chars)");
    return 1;
  }

  // Payload storage:
  //
  //   bytes 0-1: File number in ASCII (01, 20, etc.)
  //   bytes 2-4: Audio file extension (mp3, wav, etc.)
  //
  // These are combined to produce the file name (e.g., beep-01.mp3,
  // beep-20.wav).
  char payload[5] = {args[1][0], args[1][1], args[2][0], args[2][1],
                     args[2][2]};

  sf::UdpSocket sender;
  if (sender.send(payload, 5, sf::IpAddress::resolve(args[0]).value(), 14551) !=
      sf::Socket::Status::Done) {
    return 1;
  }
}
