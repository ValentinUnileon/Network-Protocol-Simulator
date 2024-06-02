#include <iostream>
#include "NodeDevice.cpp"
#include "TCP.cpp"
#include "UDP.cpp"
#include "Channel.cpp"

using namespace std;

int main(){

    NodeDevice node1 = NodeDevice("190.168.100.35", "00:1A:2B:3C:4D:5E", "1");
    NodeDevice node2 = NodeDevice("192.168.220.24","00:1A:2B:3C:4D:5E", "2");


    string protocol;

    cout << "Choose the protocol"<<endl;
    cin >> protocol;

    if(protocol != "TCP" && protocol != "UDP") {
        cout << "Protocol not valid";
    }

    if(protocol=="TCP"){

        //3 handshake connexion

        TCP tcpConexion = TCP(node1, node2, 80);
        Packet packetSYN = tcpConexion.encapsulatePacketTCP("SYN");
        Channel fiberOptic = Channel(1000.0, 10.0, 0.5);            //high rate of errors to prove it
        Channel fiberOptic1 = Channel(1000.0, 10.0, 0.5);  

        fiberOptic.connectNodes(&node1, &node2);
        int success = -1;
        int successSYN_ACK=-1;
        int successACK=-1;

        //if the packet is lost, then there will be another try

        while(success==-1){ 
            success = fiberOptic.transmitData(packetSYN);                              //SYN packet
        }

        //then we send the SYN+ACK packet

        Packet packetSYNACK = tcpConexion.encapsulatePacketTCP("SYN+ACK");             //SYN+ACK packet
        fiberOptic1.connectNodes(&node2, &node1);

        //RETRANSMISSION if the SYN+ACK packet is lost

        while(successSYN_ACK==-1){

            while(!success==-1){ 
                cout << "retransmission of the packet";
                success = fiberOptic1.transmitData(packetSYN);                           //SYN packet
            }

            successSYN_ACK = fiberOptic1.transmitData(packetSYNACK);

        }

        //the receptor send the confirmation ACK

        fiberOptic.connectNodes(&node1, &node2);

        Packet packetACK = tcpConexion.encapsulatePacketTCP("ACK");                     //ACK packet

        //RETRANSMISSION if the ACK packet is lost
        while(successACK==-1){
            successACK=fiberOptic.transmitData(packetACK);
        }

        //Normal transmission of data

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
            // congestion control al reliable data transfer 
            tcpConexion.congestionControl(ackPacket, packetCommunication, fiberOptic);


        }

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

