#include <iostream>
#include <string>
#include <vector>
#include "Packet.cpp"

using namespace std;


// Clase para representar los nodos de la red
class Node {
private:
    string ipAddress;
    string uniqueID;
    vector<Packet> receivedPackets;

public:

    Node(const string& ip, const string& id) : ipAddress(ip), uniqueID(id) {}


    void sendPacket(const Packet& packet, Node& recipient) {

        cout << "Enviando paquete desde el nodo " << uniqueID << " a " << recipient.getUniqueID() << endl;

        recipient.receivePacket(packet);
    }


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
