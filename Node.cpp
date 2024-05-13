#include <iostream>
#include <string>
#include <vector>
#include "Packet.cpp"

using namespace std;

const string UDP = "UDP";
const string TCP = "TCP"


class Node {

private:
    string ipAddress;
    string uniqueID;
    vector<Packet> receivedPackets;

public:

    Node(const string& ip, const string& id) : ipAddress(ip), uniqueID(id) {}


    void sendData(string data, string protocol, string destIP) { //Packet to send and node to recieve
 
        if(protocol==TCP){

            


        }else if(protocol==UDP){



        }else{
            print("Error: No protocol found.");
        }

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
