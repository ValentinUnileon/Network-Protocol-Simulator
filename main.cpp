#include <iostream>
#include "NodeDevice.cpp"
#include "TCP.cpp"
#include "Channel.cpp"

using namespace std;

int main(){

    NodeDevice nodo1 = NodeDevice("190.0", "1");
    NodeDevice nodo2 = NodeDevice("192.0", "2");


    string protocol="TCP";

    if(protocol=="TCP"){

        //3 handshake connexion

        TCP tcpConexion = TCP(nodo1, nodo2, 80);
        Packet packetSYN = tcpConexion.createPacketTCP("SYN");
        Channel fiberOptic = Channel(1000.0, 10.0, 0.00001);

        fiberOptic.connectNodes(&nodo1, &nodo2);
        bool success = false;

        while(!success){ //if the packet is lost, then there will be another try
            success = fiberOptic.transmitData(packetSYN);                              //SYN packet

        }

        Packet packetSYNACK = tcpConexion.createPacketTCP("SYN+ACK");
        
        

        fiberOptic.connectNodes(&nodo2, &nodo1);




    }


    return 0;

}


//creamos una clase