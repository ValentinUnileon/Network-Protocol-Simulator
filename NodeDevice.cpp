#ifndef NODE_H
#define NODE_H


#include <iostream>
#include <string>
#include <vector>
#include "Packet.cpp"

using namespace std;

class NodeDevice {

public:

    string ipAddress;
    string uniqueID;
    string MAC_Address;

    NodeDevice(string ip, string MAC, string id) : ipAddress(ip), MAC_Address(MAC), uniqueID(id) {}

    string getIPAddress() const {
        return ipAddress;
    }

    string getUniqueID() const {
        return uniqueID;
    }


};

#endif 