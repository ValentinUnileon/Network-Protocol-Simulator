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

        TCP tcpConexion = TCP(nodo1, nodo2, 80);
        Packet packet = tcpConexion.createPacketTCP("hola");
        Channel fiberOptic = Channel(1000.0, 10.0, 0.00001);

        fiberOptic.connectNodes(&nodo1, &nodo2);
        fiberOptic.transmitData(packet);


    }


    return 0;

}


//creamos una clase