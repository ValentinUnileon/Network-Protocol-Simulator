#include <iostream>
#include "Node.cpp"

using namespace std;

int main(){

    Node nodo1 = Node("190.0", "1");
    nodo1.sendData("datos", "TCP", "192.0", 80);


    return 0;

}