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

int LENGHT_VERTICES = 0;
int LENGHT_EDGES = 0;


Vertice :: Vertice() : name(), source(true), sink(false), next(nullptr), prev(nullptr), edges(nullptr) {}
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

Vertice::~Vertice()
{
    next = nullptr;
    prev = nullptr;
    while(edges -> getNextEdge() != nullptr)
    {
        edges = edges -> getNextEdge();
        edges -> setPrevEdge(nullptr);
    }
    edges = nullptr;
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

void Vertice :: setName(string str) {name = str;}
void Vertice :: setSource(bool b) {source = b;}
void Vertice :: setSink(bool b) {sink = b;}
void Vertice :: setNext(Vertice* v) {next = v;}
void Vertice :: setPrev(Vertice* v) {prev = v;}

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
    newEdge -> getNextVert() -> setSource(false);       // the vertex has at least 1 ingoing edge, so it is not a source

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

    return list;
}

Vertice* Vertice :: findSinks(Vertice* list)
{
    Vertice* tmp = list;

    while(tmp != nullptr)
    {
        if(tmp -> edges == nullptr)         // there is no outgoing edge on this vertex, so it is a sink
            tmp -> sink = true;

        tmp = tmp -> next;
    }

    return list;
}


/*-----------------------------------------GET------------------------------------------------------------------------*/


string Vertice :: getName() {return name;}
bool Vertice :: getSink() {return sink;}
bool Vertice :: getSource() {return source;}
Vertice* Vertice :: getNext() {return next;}
Vertice* Vertice :: getPrev() {return prev;}
Edge* Vertice :: getEdges() {return edges;}



/*-------------------------------------MATRIX-------------------------------------------------------------------------*/

string** Vertice :: initializer_matrix(char c)      // A for Adjency, V for Values
{
    string** adj = new string*[LENGHT_VERTICES + 1];

    for(int i = 0; i < LENGHT_VERTICES + 1; i++)
    {
        adj[i] = new string[LENGHT_VERTICES + 1];

        for(int j = 0; j < LENGHT_VERTICES + 1; j++)
        {
            if(i == 0 && j != 0)
                adj[i][j] = to_string(j - 1);

            else if(j == 0 && i != 0)
                adj[i][j] = to_string(i - 1);

            else if(j != 0 && i != 0)
            {
                if(c == 'V')
                    adj[i][j] = "*";

                else if(c == 'A')
                    adj[i][j] = "0";
            }
        }
    }

    return adj;
}


string** Vertice :: adjacentMatrix(Vertice * list)
{
    string** adj = initializer_matrix('A');

    Vertice* tmp = list;
    Edge* t = nullptr;

    for(int i = 0; i < LENGHT_VERTICES + 1; i++)
    {
        if(i > 0)
        {
            t = tmp -> edges;

            while(t != nullptr)
            {
                adj[stoi(t -> getPrevVert() -> getName() ) + 1] [stoi(t -> getNextVert() -> getName() ) + 1] = "1";
                t = t -> getNextEdge();
            }

            tmp = tmp -> next;
        }
    }

    return adj;
}

string** Vertice :: valuesMatrix(Vertice* list)
{
    string** adj = initializer_matrix('V');

    Vertice* tmp = list;
    Edge* t = nullptr;

    for(int i = 0; i < LENGHT_VERTICES + 1; i++)
    {
        if(i > 0)
        {
            t = tmp -> edges;

            while(t != nullptr)
            {
                adj[stoi(t -> getPrevVert() -> getName() ) + 1] [stoi(t -> getNextVert() -> getName() ) + 1] = to_string(t -> getWeight() );
                t = t -> getNextEdge();
            }

            tmp = tmp -> next;
        }
    }

    return adj;
}

void Vertice ::printMatrix(string ** matrix, char c)
{
    if(c == 'A')
        cout << "Adjency Matrix" << endl;
    else if(c == 'V')
        cout << "Values Matrix" << endl;


    for(int i = 0; i < LENGHT_VERTICES + 1; i++)
    {

        if(i < 11 )
            cout << " ";

        for(int j = 0; j < LENGHT_VERTICES + 1; j++)
        {
            if(i == 0 && j <= 10)
                cout << "  " << red << matrix[i][j] << white;

            else if (i == 0 && j > 10)
                cout << " " << red << matrix[i][j] << white;

            else if (j == 0 && i != 0)
                cout << "  " << red << matrix[i][j] << white;

            else
            {
                if(c == 'A')
                {
                    if(matrix[i][j] == "1")
                        cout << " " << green << matrix[i][j] << white << " ";
                    else
                        cout << " " << matrix[i][j] << " ";
                }

                if(c == 'V')
                {
                    if(matrix[i][j] == "*")
                        cout << " " << matrix[i][j] << " ";
                    else
                    {
                        if(stoi(matrix[i][j]) > 9 || stoi(matrix[i][j]) < 0)
                            cout << " " << green << matrix[i][j] << white;
                        else
                            cout << " " << green << matrix[i][j] << white << " ";
                    }
                }
            }

            if(j >= 9)
                cout << " ";
        }
        cout << endl;
    }
}



/*-------------------------------------NOT IN VERTICE-----------------------------------------------------------------*/


vector<string> Split(const string& txt)
{
    istringstream iss(txt);
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
    return tokens;
}




/*-------------------------------------READ TEXT----------------------------------------------------------------------*/

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
    LENGHT_VERTICES = NumberOfVertices;
    head = initializer_vertices(NumberOfVertices);

    /* We save the number of edges */
    fscanf(file, "%d\n", &NumberOfEdges);
    LENGHT_EDGES = NumberOfEdges;

    for(int i = 0; i < NumberOfEdges; i++)
    {
        /* We save the edge in a char* and we delete the '\n' */
        fgets(str, 999, file);
        strtok(str, "\n");

        /* We split the char* into a vector : ingoing outgoing weight */
        vector = Split(str);

        head = setEdges(vector, head);
    }

    head = findSinks(head);

    fclose(file);

    return head;
}








