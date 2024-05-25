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
        bool successSYN_ACK = false;
        bool successACK = false;

        //if the packet is lost, then there will be another try

        while(!success){ 
            success = fiberOptic.transmitData(packetSYN);                              //SYN packet
        }

        //then we send the SYN+ACK packet

        Packet packetSYNACK = tcpConexion.createPacketTCP("SYN+ACK");
        fiberOptic.connectNodes(&nodo2, &nodo1);

        //RETRANSMISSION

        while(!successSYN_ACK){

            while(!success){ 
                cout << "retransmission of the packet";
                success = fiberOptic.transmitData(packetSYN);                              //SYN packet
            }

            successSYN_ACK = fiberOptic.transmitData(packetSYNACK);

        }

        fiberOptic.connectNodes(&nodo1, &nodo2);

        Packet packetACK = tcpConexion.createPacketTCP("ACK");

        while(!successACK){
            successACK=fiberOptic.transmitData(packetACK);
        }

        bool successMessage=false;

        string message="Hello world";

        Packet packetMessage = tcpConexion.createPacketTCP(message);

        while(!successMessage){
            successMessage=fiberOptic.transmitData(packetMessage);
        }


        //3 - handshake finished

        //ahora se tienen que transmitir los paquetes normales de informacion
        //Para ello habria que utilizar el mecanismo de flow congestion
        //Si me da tiempo lo implementaria de la siguente manera:
        //  -en el main tendria una lista de paqueten que tendria que enviar
        //  -esa lista se la paso a un metodo de la clase TCP llamdado retransmissionFLowControl()
        //  -desde ese metodo voy enviando todos los paquete de la manera mas optima y utilizando mecanismos como el fast recovery

    }else if(protocol=="UDP"){


    }


    return 0;

}

