#include <iostream>

#include "Vertice.h"

string PATH = R"(D:\efrei\cours\s6\graph_theory\projet\txt\)";

void printVertices(Vertice* tmp)
{

    while(tmp)
    {
        cout << "Name : " << tmp -> getName() << "   Source : " << tmp -> getSource() << "   Sink : " << tmp -> getSink() << endl;

        Edge* t = tmp -> getEdges();
        if(t == nullptr)
            cout << "No transition" << endl;
        else
        {
            while(t != nullptr)
            {

                cout <<  t -> getPrevVert() -> getName() << " " << t -> getNextVert() -> getName() << " " << t -> getWeight() << endl;

                t = t -> getNextEdge();
            }
        }

        cout << endl;
        tmp = tmp -> getNext();
    }
}


int main()
{
    Vertice* head = new Vertice();

    head = head -> readText((char*)R"(D:\efrei\cours\s6\graph_theory\projet\txt\01.txt)");
    printVertices(head);

    string** Adjacent = head -> adjacentMatrix(head);
    string** Values = head -> valuesMatrix(head);
    head -> printMatrix(Adjacent, 'A');
    head -> printMatrix(Values, 'V');

    return 0;
}
