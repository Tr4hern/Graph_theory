#include <iostream>

#include "Vertice.h"

void printVertices(Vertice* tmp)
{
    while(tmp)
    {
        cout << "Name : " << tmp -> getName() << endl;
        tmp = tmp -> getNext();
    }
}


int main()
{
    Vertice* head = new Vertice();
    head -> readText((char*)R"(D:\efrei\cours\s6\graph_theory\projet\txt\01.txt)");
    //printVertices(head);
    return 0;
}
