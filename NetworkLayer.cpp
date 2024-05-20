#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

#include <iostream>
#include <string>

using namespace std;

// En esta capa se añade la cabecera IPV4
class NetworkLayer {
public:
    string version;           // Version (IPv4)
    int headerLength;         // Header length (in 32-bit words)
    int totalLength;          // Total Length
    int ttl;                  // Time to Live
    string protocol;          // Protocol ("TCP" = 6, "UDP" = 17)
    string sourceIP;          // Source IP Address
    string destinationIP;     // Destination IP Address
   

    NetworkLayer(const string& sourceIP, const string& destinationIP, int totalLength, const string& protocol) 
        : version("IPv4"),          // IPv4 or IPV6 - with the second one, parameters woudl change
          headerLength(20),         // Header length in bytes (default 20)
          totalLength(totalLength),
          ttl(64),                  // Default TTL
          protocol(protocol),
          sourceIP(sourceIP),
          destinationIP(destinationIP) {}

    void printInfo() const {
        cout << "Version: " << version << endl;
        cout << "Header Length: " << headerLength << endl;
        cout << "Total Length: " << totalLength << endl;
        cout << "TTL: " << ttl << endl;
        cout << "Protocol: " << protocol << endl;
        cout << "Source IP: " << sourceIP << endl;
        cout << "Destination IP: " << destinationIP << endl;
    }
};

#endif // NETWORK_LAYER_H
