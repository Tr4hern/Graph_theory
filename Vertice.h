//
// Created by Arnaud on 07/04/2020.
//

#ifndef PROJET_VERTICE_H
#define PROJET_VERTICE_H

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
        Vertice();
        Vertice(const Vertice &);
        Vertice& operator=(const Vertice&);
        static Vertice* initializer_vertices(int);

        Vertice* setEdges(const vector<string>&, Vertice*);

        string getName();
        bool getSource();
        bool getSink();
        Vertice* getNext();
        Vertice* getPrev();
        Edge* getEdges();

        Vertice* readText(char*);
};


#endif //PROJET_VERTICE_H
