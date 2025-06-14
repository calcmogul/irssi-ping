#include <format>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

int main() {
  sf::UdpSocket receiver;
  if (receiver.bind(14551) != sf::Socket::Status::Done) {
    return 1;
  }

  // Payload storage:
  //
  //   bytes 0-1: File number in ASCII (01, 20, etc.)
  //   bytes 2-4: Audio file extension (mp3, wav, etc.)
  //
  // These are combined to produce the file name (e.g., beep-01.mp3,
  // beep-20.wav).
  char payload[5];

  sf::SoundBuffer buffer;
  sf::Sound sound{buffer};

  while (1) {
    size_t recv_size = 0;
    std::optional<sf::IpAddress> recv_ip;
    uint16_t recv_port = 0;
    if (receiver.receive(payload, 5, recv_size, recv_ip, recv_port) !=
        sf::Socket::Status::Done) {
      continue;
    }

    if (!buffer.loadFromFile(std::format("/etc/irssi-local.d/beep-{}{}.{}",
                                         payload[0], payload[1],
                                         std::string_view{&payload[2], 3}))) {
      continue;
    }

    sound.play();
  }
}
