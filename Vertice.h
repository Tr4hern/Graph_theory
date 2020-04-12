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

        void setSource(bool);
        static Vertice* setEdges(const vector<string> &, Vertice *);
        static Vertice* findSinks(Vertice *);

        string getName();
        Vertice* getNext();
        int getRank();

        static string** initializer_matrix(char);
        static string** adjacentMatrix(Vertice *);
        static string** valuesMatrix(Vertice *);
        static void printMatrix(string **, char);

        static Vertice* findRanks(string **, Vertice *, int);
        static Vertice* listByRank(Vertice*);
        static void printRank(Vertice *list);

        static bool checkScheduling(Vertice *list);
        static void scheduling(Vertice*, Vertice*);

        static void printVertices(Vertice *list);

        static Vertice* readText(char *);
};


#endif //PROJET_VERTICE_H
