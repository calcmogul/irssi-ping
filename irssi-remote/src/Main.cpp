#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

#include <cstring>

#include <iostream>
#include <string>
#include <vector>

/* Command line arguments should be IP address of server, file number (2
 * characters) and file extension (3 characters)
 */
int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc + !argc);

    if (args.size() != 3 || args[1].length() != 2 || args[2].length() != 3) {
        std::cout << "Arguments: IP address, file number (2 chars), file extension (3 chars)" << std::endl;
        return 1;
    }

    // Set up sending socket
    sf::UdpSocket sender;

    /* Set up payload storage
     * bytes 1-2: File number in ASCII (01, 20, etc.)
     * bytes 3-5: Audio file extension (mp3, wav, etc.)
     *
     * These are combined to produce the file name (beep-01.mp3, beep-20.wav)
     */
    char payload[5];
    std::memcpy(payload, args[1].c_str(), 2);
    std::memcpy(&payload[2], args[2].c_str(), 3);

    sf::IpAddress remoteIP(args[0]);
    unsigned short remotePort = 14551;

    sender.send(payload, 5, remoteIP, remotePort);
}

