#include <iostream>

#include "Vertice.h"

string PATH = R"(D:\efrei\cours\s6\graph_theory\projet\txt\)";


int main()
{
    Vertice* head = new Vertice();
    Vertice* rank = new Vertice();

    head = head -> readText( (char*) R"(D:\efrei\cours\s6\graph_theory\projet\txt\01.txt)" );

    string** Adjacent = head -> adjacentMatrix(head);
    string** Values = head -> valuesMatrix(head);

    //head -> printMatrix(Adjacent, 'A');
   // head -> printMatrix(Values, 'V');

    head -> findRanks(Adjacent, head, 0);
   // printRank(head);

    rank = rank -> listByRank(head);
    rank -> scheduling(head, rank);

    return 0;
}
