#ifndef NODE_H
#define NODE_H


#include <iostream>
#include <string>
#include <vector>

#include "Packet.cpp"
#include "TCP.cpp"

using namespace std;


class Node {

public:

    string ipAddress;
    string uniqueID;
    vector<Packet> receivedPackets;


    Node(const string& ip, const string& id) : ipAddress(ip), uniqueID(id) {}


    void sendData(string data, string protocol, string destIP, int port) { //Packet to send and node to recieve
 
        if(protocol=="TCP"){

            //crear objeto TCP y llamar a metodo - sendThrowTCP
            //hay que asegurarse de que exista el nodo de recepcion para poder entrar aqui
            TCP tcpConexion = TCP(ipAddress, destIP, uniqueID, port, data);
            tcpConexion.createPacketTCP();






        }else if(protocol=="UDP"){



        }else{
            cout << "Error: No protocol found.";
        }

        //recipient.receivePacket(packet);
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

#endif 