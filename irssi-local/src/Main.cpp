#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

#include <string>

int main() {
    // Set up listening socket
    sf::UdpSocket receiver;
    receiver.bind(14551);
    sf::Socket::Status status;

    /* Set up payload storage
     * bytes 1-2: File number in ASCII (01, 20, etc.)
     * bytes 3-5: Audio file extension (mp3, wav, etc.)
     *
     * These are combined to produce the file name (beep-01.mp3, beep-20.wav)
     */
    char payload[5];
    std::size_t recvSize = 0;
    sf::IpAddress recvIP;
    unsigned short recvPort = 0;

    // Set up audio
    sf::SoundBuffer buffer;
    sf::Sound sound(buffer);

    while (1) {
        status = receiver.receive(payload, 5, recvSize, recvIP, recvPort);
        if (status == sf::Socket::Done) {
            std::string name = "/etc/irssi-local.d/beep-";
            name = name + payload[0] + payload[1] + '.' +
                   std::string(&payload[2], 3);
            buffer.loadFromFile(name);
            sound.play();
        }
    }
}

