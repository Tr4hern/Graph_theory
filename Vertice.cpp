//
// Created by Arnaud on 07/04/2020.
//
#include <iostream>
#include <sstream>
#include <iterator>

#include <cstring>
#include <cstdio>
#include <vector>

#include "Vertice.h"


Vertice :: Vertice() : name(), source(false), sink(false), next(nullptr), prev(nullptr), edges(nullptr) {}
Vertice :: Vertice(const Vertice & v) : name(v.name), source(v.source), sink(v.sink), next(v.next), prev(v.prev), edges(v.edges) {}
Vertice& Vertice :: operator=(const Vertice & v)
{
    name = v.name;
    source = v.source;
    sink = v.sink;
    next = v.next;
    prev = v.prev;
    edges = v.edges;
    return *this;
}

Vertice* Vertice :: initializer_vertices(int lenght)
{
    Vertice *node = nullptr, *tmp = nullptr, *head = nullptr;
    for(int i = 0; i < lenght; i++)
    {
        node = new Vertice;
        node -> name = to_string(i);

        if(tmp != nullptr)
        {
            tmp -> next = node;
            node -> prev = tmp;
        }

        tmp = node;

        if(i == 0)
            head = node;
    }
    return head;
}


/*-----------------------------------------SET------------------------------------------------------------------------*/



Vertice* Vertice :: setEdges(const vector<string> &vectors, Vertice* list)
{
    Vertice* tmp = list;
    Edge* newEdge = new Edge;
    Edge* t = nullptr;

    newEdge -> setWeight((stoi(vectors[2]) ) );        // convert string to int

    /* find the ingoing vertex in the list */
    while( (tmp -> name).compare(vectors[1]) != 0 )
        tmp = tmp -> next;
    newEdge -> setNextVert(tmp);

    tmp = list;         // make sure we start at the beginning again

    /* find the outgoing vertex in the list */
    while( (tmp -> name).compare(vectors[0]) != 0)
        tmp = tmp -> next;
    newEdge -> setPrevVert(tmp);

    // we do it in this order to keep the vertex we are adding on the edge


    // make a list of the edges

    if( (tmp -> edges) == nullptr)
        tmp -> edges = newEdge;
    else
    {
        t = tmp -> edges;
        while( (t -> getNextEdge() ) != nullptr )
        {
            t =  t -> getNextEdge();
        }

        newEdge -> setPrevEdge(t);
        t -> setNextEdge(newEdge);
    }

/*
    if( (tmp -> edges) == nullptr)
        tmp -> edges = newEdge;
    else
    {
        while( (tmp -> edges -> getNextEdge() ) != nullptr )
        {
            tmp -> edges =  tmp -> edges -> getNextEdge();
        }

        newEdge -> setPrevEdge(tmp -> edges);
        tmp -> edges -> setNextEdge(newEdge);
    }

    */
/*
    t = tmp -> edges;
    while(t != nullptr)
    {
        cout <<  t -> getPrevVert() -> getName() << " " << t -> getNextVert() -> getName() << " " << t -> getWeight() << endl;
        t =  t -> getNextEdge();
    }
    cout << endl;
*/

    return list;
}



/*-----------------------------------------GET------------------------------------------------------------------------*/


string Vertice :: getName() {return name;}
bool Vertice :: getSink() {return sink;}
bool Vertice :: getSource() {return source;}
Vertice* Vertice :: getNext() {return next;}
Vertice* Vertice :: getPrev() {return prev;}
Edge* Vertice :: getEdges() {return edges;}


/*-------------------------------------READ TEXT----------------------------------------------------------------------*/

vector<string> Split(const string& txt)
{
    istringstream iss(txt);
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
    return tokens;
}


void printVector(const vector<string>& vectors)
{
    for(const auto & vector : vectors)
    {
        cout << vector << ' ';
    }
    cout << endl;
}


Vertice* Vertice :: readText(char *fileName)
{
    vector<string> vector;

    int NumberOfVertices = 0;
    int NumberOfEdges = 0;
    char str[32] = {'\0'};

    Vertice* head;

    errno = 0;
    FILE* file = fopen(fileName, "rt");

    if (nullptr == file)
    {
        printf("Error of opening at line %d of file %s : %s\n", __LINE__ , fileName, strerror(errno));
        return nullptr;
    }

    /* We save the number of vertices */
    fscanf(file, "%d", &NumberOfVertices);
    head = initializer_vertices(NumberOfVertices);

    /* We save the number of edges */
    fscanf(file, "%d\n", &NumberOfEdges);

    printf("\nvertices : %d\nedges : %d\n", NumberOfVertices, NumberOfEdges);

    for(int i = 0; i < NumberOfEdges; i++)
    {
        /* We save the edge in a char* and we delete the '\n' */
        fgets(str, 999, file);
        strtok(str, "\n");

        /* We split the char* into a vector : ingoing outgoing weight */
        vector = Split(str);
        //printVector(vector);

        head = setEdges(vector, head);
    }

    fclose(file);

    return head;
}