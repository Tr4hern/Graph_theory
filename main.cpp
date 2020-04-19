#include <iostream>

#include "Vertice.h"

const char* PATH = R"(..\txt\)";
const char* SAVE = R"(..\traces\)";
int BUFFER = 1000;


int main()
{
    char cont = 'Y';

    do
    {
        int graph = 0;
        char str[BUFFER];

        for(int i = 0; i < BUFFER; i++)
            str[i] = '\0';

        do
        {
            cout << "Which graph do you want to test ? (0 to test all)" << endl;
            cin >> graph;
        }while(graph < 0 || graph > 13);

        if(graph == 0)
        {
            for(int i = 0; i < BUFFER; i++)
                str[i] = '\0';

            for(int graph = 1; graph < 13; graph++)
            {
                cout << "--------------------------------------------------------Graph " << graph << " --------------------------------------------------------" << endl;
                if(graph > 9)
                    sprintf(str, "%s%d%s", PATH, graph, ".txt");
                else
                    sprintf(str, "%s%d%d%s", PATH, 0, graph, ".txt");

                Vertice :: makeGraph(str);
            }
        }
        else
        {
            cout << "--------------------------------------------------------Graph " << graph << " --------------------------------------------------------" << endl;

            if(graph > 9)
                sprintf(str, "%s%d%s", PATH, graph, ".txt");
            else
                sprintf(str, "%s%d%d%s", PATH, 0, graph, ".txt");

            Vertice :: makeGraph(str);

        }

        cout << endl << endl << endl << green << "Press Y to continue" << endl << white;
        cin >> cont;

    }while(cont == 'Y' || cont == 'y');

    return 0;
}
