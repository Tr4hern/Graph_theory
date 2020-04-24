//
// Created by Arnaud on 07/04/2020.
//

#ifndef PROJET_VERTICE_H
#define PROJET_VERTICE_H

#include "Int2-1-Edge.h"
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
        Int2* edges;

    public:
        Vertice();
        Vertice(const Vertice &);
        Vertice& operator=(const Vertice &);
        ~Vertice();
        static Vertice* initializer_vertices(int);

        static void printVertices(Vertice *);

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
        static Vertice* listByRank(Vertice *);
        static void printRank(Vertice *);

        static bool checkScheduling(Vertice *, char *);
        static void scheduling(Vertice *, Vertice *, char *);

        static void makeGraph(char *, char *);
        static Vertice* readText(char *);

        static void matSaves(char *, string **, char);
        static void rankSaves(char *, Vertice *);
        static void errorSaves(char *);
        static void timeSaves(char *, int *, Vertice *, char c);
        static void shortSaves(char *, string *, Vertice *);
        static void initSaves(char *, int);
};


#endif //PROJET_VERTICE_H
