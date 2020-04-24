#include <iostream>

#include "Int2-1-Vertice.h"

const char* PATH = R"(..\Int2-1-graph)";
const char* SAVE = R"(..\Int2-1-trace)";
int BUFFER = 1000;


int main()
{
    char cont = 'Y';

    do
    {
        int graph = 0;
        char str[BUFFER];
        char save[BUFFER];

        for(int i = 0; i < BUFFER; i++)
        {
            str[i] = '\0';
            save[i] = '\0';
        }

        for(int i = 1; i < 13; i++)
        {
            if(i > 9)
                sprintf(str, "%s%d%s", SAVE, i, ".txt");
            else
                sprintf(str, "%s%d%d%s", SAVE, 0, i, ".txt");
            Vertice :: initSaves(str, i);
        }

        for(int i = 0; i < BUFFER; i++)
        {
            str[i] = '\0';
            save[i] = '\0';
        }

        do
        {
            cout << "Which graph do you want to test ? (0 to test all)" << endl;
            cin >> graph;
        }while(graph < 0 || graph > 12);

        if(graph == 0)
        {
            for(int i = 0; i < BUFFER; i++)
            {
                str[i] = '\0';
                save[i] = '\0';
            }

            for(int graph = 1; graph < 13; graph++)
            {
                cout << "--------------------------------------------------------Graph " << graph << " --------------------------------------------------------" << endl;
                if(graph > 9)
                {
                    sprintf(str, "%s%d%s", PATH, graph, ".txt");
                    sprintf(save, "%s%d%s", SAVE, graph, ".txt");
                }
                else
                {
                    sprintf(str, "%s%d%d%s", PATH, 0, graph, ".txt");
                    sprintf(save, "%s%d%d%s", SAVE, 0, graph, ".txt");
                }

                Vertice :: makeGraph(str, save);
            }
        }

        else
        {
            cout << "--------------------------------------------------------Graph " << graph << " --------------------------------------------------------" << endl;

            if(graph > 9)
            {
                sprintf(str, "%s%d%s", PATH, graph, ".txt");
                sprintf(save, "%s%d%s", SAVE, graph, ".txt");
            }
            else
            {
                sprintf(str, "%s%d%d%s", PATH, 0, graph, ".txt");
                sprintf(save, "%s%d%d%s", SAVE, 0, graph, ".txt");
            }

            Vertice :: makeGraph(str, save);

        }

        cout << endl << endl << endl << green << "Press Y to continue" << endl << white;
        cin >> cont;

    }while(cont == 'Y' || cont == 'y');

    return 0;
}
