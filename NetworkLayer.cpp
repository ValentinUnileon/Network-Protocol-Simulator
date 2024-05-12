#include <iostream>
#include <string>
using namespace std;

class NetworkLayer {
public:
    string sourceIP;
    string destinationIP;
    int ttl;
    string protocol;
    string payload;
};