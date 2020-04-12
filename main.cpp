#include <iostream>

#include "Vertice.h"

const char* PATH = R"(D:\efrei\cours\s6\graph_theory\projet\txt\)";
int BUFFER = 1000;


int main()
{
    char cont = 'Y';

    do
    {
        int graph = 0;
        char str[BUFFER];

        do
        {
            cout << "Which graph do you want to test ?" << endl;
            cin >> graph;
        }while(graph < 1 || graph > 13);

        if(graph > 9)
            sprintf(str, "%s%d%s", PATH, graph, ".txt");
        else
            sprintf(str, "%s%d%d%s", PATH, 0, graph, ".txt");


        auto* head = new Vertice();
        auto* rank = new Vertice();

        head = head -> readText(str);
        Vertice :: printVertices(head);

        string** Adjacent = Vertice :: adjacentMatrix(head);
        string** Values = Vertice :: valuesMatrix(head);

        Vertice :: printMatrix(Adjacent, 'A');
        Vertice :: printMatrix(Values, 'V');

        Vertice :: findRanks(Adjacent, head, 0);

        rank = Vertice :: listByRank(head);
        rank -> scheduling(head, rank);

        cout << endl << endl << endl << green << "Press Y to continue" << endl << white;
        cin >> cont;

    }while(cont == 'Y' || cont == 'y');

    return 0;
}
