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
        int rank;
        Edge* edges;

    public:
        Vertice();
        Vertice(const Vertice &);
        Vertice& operator=(const Vertice &);
        ~Vertice();
        static Vertice* initializer_vertices(int);

        void setName(string);
        void setSource(bool);
        void setSink(bool);
        void setNext(Vertice *);
        void setPrev(Vertice *);
        void setRank(int);
        Vertice* setEdges(const vector<string> &, Vertice *);
        Vertice* findSinks(Vertice *);

        string getName();
        bool getSource();
        bool getSink();
        Vertice* getNext();
        Vertice* getPrev();
        int getRank();
        Edge* getEdges();


        string **initializer_matrix(char);
        string** adjacentMatrix(Vertice *);
        string **valuesMatrix(Vertice *);
        void printMatrix(string **, char);


        Vertice* readText(char *);

        Vertice* findRanks(string **, Vertice *, int);
};


#endif //PROJET_VERTICE_H
