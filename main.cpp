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


void printRank(Vertice* list)
{
    Vertice* tmp = list;

    if(tmp -> getRank() != -1)      // if there is no cycle
    {
        cout << "Vertex ";
        while(tmp)
        {
            cout << tmp -> getName() << " ";
            tmp = tmp -> getNext();
        }

        tmp = list;

        cout << endl << "Rank   ";
        while(tmp)
        {
            cout << tmp -> getRank() << " ";
            tmp = tmp -> getNext();
        }
    }
}


int main()
{
    Vertice* head = new Vertice();

    head = head -> readText( (char*) R"(D:\efrei\cours\s6\graph_theory\projet\txt\02.txt)" );
    //printVertices(head);

    string** Adjacent = head -> adjacentMatrix(head);
    string** Values = head -> valuesMatrix(head);

    head -> printMatrix(Adjacent, 'A');
    head -> printMatrix(Values, 'V');

    head -> findRanks(Adjacent, head, 0);
    printRank(head);

    return 0;
}
