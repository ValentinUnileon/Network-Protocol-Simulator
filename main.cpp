#include <iostream>
#include "NodeDevice.cpp"
#include "TCP.cpp"
#include "UDP.cpp"
#include "Channel.cpp"

using namespace std;

int main(){

    NodeDevice node1 = NodeDevice("190.0", "1");
    NodeDevice node2 = NodeDevice("192.0", "2");


    string protocol="TCP";

    if(protocol=="TCP"){

        //3 handshake connexion

        TCP tcpConexion = TCP(node1, node2, 80);
        Packet packetSYN = tcpConexion.encapsulatePacketTCP("SYN");
        Channel fiberOptic = Channel(1000.0, 10.0, 0.00001);

        fiberOptic.connectNodes(&node1, &node2);
        bool success = false;
        int successSYN_ACK=-1;
        int successACK=-1;

        //if the packet is lost, then there will be another try

        while(!success){ 
            success = fiberOptic.transmitData(packetSYN);                              //SYN packet
        }

        //then we send the SYN+ACK packet

        Packet packetSYNACK = tcpConexion.encapsulatePacketTCP("SYN+ACK");
        fiberOptic.connectNodes(&node2, &node1);

        //RETRANSMISSION

        while(successSYN_ACK==-1){

            while(!success==-1){ 
                cout << "retransmission of the packet";
                success = fiberOptic.transmitData(packetSYN);                              //SYN packet
            }

            successSYN_ACK = fiberOptic.transmitData(packetSYNACK);

        }

        fiberOptic.connectNodes(&node1, &node2);

        Packet packetACK = tcpConexion.encapsulatePacketTCP("ACK");

        while(successACK==-1){
            successACK=fiberOptic.transmitData(packetACK);
        }

        int successMessage=-1;

        string message="Hello world";

        Packet packetMessage = tcpConexion.encapsulatePacketTCP(message);

        while(successMessage==-1){
            successMessage=fiberOptic.transmitData(packetMessage);
        }


        bool inputAccepted = true;
        string input;
        int ackPacket;

        while(inputAccepted){

            cout << "Enter text to send throw TCP protocol: (or exit)\n";
            cin >> input;

            if(input == "exit"){
                break;
            }

            Packet packetCommunication = tcpConexion.encapsulatePacketTCP(input);
            ackPacket = fiberOptic.transmitData(packetCommunication);
            tcpConexion.congestionControl(ackPacket, packetCommunication, fiberOptic);


        }




        


        //**podemos meterle desencapsulacion tambien aunque es algo tonteria porque seria repetitivo pero podemos poder mensaje tipo 
        //deencapsulation()
        //** desencapsulacion finalizada**

        //3 - handshake finished

        //ahora se tienen que transmitir los paquetes normales de informacion
        //Para ello habria que utilizar el mecanismo de flow congestion
        //Si me da tiempo lo implementaria de la siguente manera:
        //  -en el main tendria una lista de paqueten que tendria que enviar
        //  -esa lista se la paso a un metodo de la clase TCP llamdado retransmissionFLowControl()
        //  -desde ese metodo voy enviando todos los paquete de la manera mas optima y utilizando mecanismos como el fast recovery

    }else if(protocol=="UDP"){

        UDP udpConexion = UDP(node1, node2, 80, 80);
        Packet packetUDP = udpConexion.createPacketUDP("Testing connection");
        Channel fiberOptic = Channel(1000.0, 10.0, 0.00001);

        fiberOptic.connectNodes(&node1, &node2);

        //In UDP we cant confirm the reception of the data
        fiberOptic.transmitData(packetUDP);

        bool inputAccepted = true;
        string input;

        while(inputAccepted){
            cout << "Enter text to send throw UDP protocol: (or exit)\n";
            cin >> input;

            if(input == "exit"){
                break;
            }

            Packet packetUDP = udpConexion.createPacketUDP(input);
            fiberOptic.transmitData(packetUDP);




        }



    }


    return 0;

}

