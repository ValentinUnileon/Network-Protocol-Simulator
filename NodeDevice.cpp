#ifndef NODE_H
#define NODE_H


#include <iostream>
#include <string>
#include <vector>

#include "Packet.cpp"


using namespace std;

//Node origin, Node destination, int originPort, int destinationPort

class NodeDevice {

public:

    string ipAddress;
    string uniqueID;
    vector<Packet> receivedPackets;


    NodeDevice(const string& ip, const string& id) : ipAddress(ip), uniqueID(id) {}


    void receivePacket(const Packet& packet) {

        receivedPackets.push_back(packet);
    }


    string getIPAddress() const {
        return ipAddress;
    }


    string getUniqueID() const {
        return uniqueID;
    }

    void printInfo() const {
        cout << "Node ID: " << uniqueID << endl;
        cout << "IP Address: " << ipAddress << endl;
        cout << "Received Packets:" << endl;
        for (const auto& packet : receivedPackets) {
            packet.printInfo();
        }
    }
};

#endif 