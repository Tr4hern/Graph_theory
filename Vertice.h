//
// Created by Arnaud on 07/04/2020.
//

#ifndef PROJET_VERTICE_H
#define PROJET_VERTICE_H



#include "Edge.h"

#include "ConsoleColor.h"


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
        ~Vertice();
        static Vertice* initializer_vertices(int);

        void setName(string str);
        void setSource(bool b);
        void setSink(bool b);
        void setNext(Vertice *v);
        void setPrev(Vertice *v);
        Vertice* setEdges(const vector<string>&, Vertice*);
        Vertice* findSinks(Vertice*);

        string getName();
        bool getSource();
        bool getSink();
        Vertice* getNext();
        Vertice* getPrev();
        Edge* getEdges();


        string **initializer_matrix(char);
        string** adjacentMatrix(Vertice*);
        string **valuesMatrix(Vertice *list);
        void printMatrix(string**, char);


        Vertice* readText(char*);

};


#endif //PROJET_VERTICE_H
