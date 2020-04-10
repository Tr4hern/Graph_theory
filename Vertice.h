//
// Created by Arnaud on 07/04/2020.
//

#ifndef PROJET_VERTICE_H
#define PROJET_VERTICE_H

#include <string>
#include "Edge.h"


class Vertice
{
    private:
        string name;
        bool source;
        bool sink;
        Vertice* next;
        Vertice* prev;
        Edge* edges;

    public:
        Vertice* initializer_vertices(int lenght);

        string getName();
        bool getSource();
        bool getSink();
        Vertice* getNext();
        Vertice* getPrev();
        Edge* getEdges();

        Vertice* readText(char *fileName);
};


#endif //PROJET_VERTICE_H
