    //
// Created by Arnaud on 07/04/2020.
//

#include "Edge.h"


Edge :: Edge() : weight('\0'), next_vert(nullptr), prev_vert(nullptr), next_edge(nullptr), prev_edge(nullptr) {}
Edge :: Edge(const Edge& e) : weight(e.weight), next_vert(e.next_vert), prev_vert(e.prev_vert), next_edge(e.next_edge), prev_edge(e.prev_edge) {}
Edge& Edge :: operator=(const Edge& e)
{
    weight = e.weight;

    next_vert = e.next_vert;
    prev_vert = e.prev_vert;

    next_edge = e.next_edge;
    prev_edge = e.prev_edge;

    return *this;
}

Edge :: ~Edge()
{
    delete next_vert;
    delete prev_vert;
    delete next_edge;
    delete prev_edge;
}


/*-----------------------------------------SET------------------------------------------------------------------------*/

void Edge :: setWeight(int w) {weight = w;}
void Edge :: setNextVert(Vertice* vertice) {next_vert = vertice;}
void Edge :: setPrevVert(Vertice* vertice) {prev_vert = vertice;}
void Edge :: setNextEdge(Edge* edge) {next_edge = edge;}
void Edge :: setPrevEdge(Edge* edge)
{
    if(edge == nullptr)
        delete this;
    else
        prev_edge = edge;
}


/*-----------------------------------------GET------------------------------------------------------------------------*/

int Edge :: getWeight() {return weight;}
Vertice* Edge :: getNextVert() {return next_vert;}
Vertice* Edge :: getPrevVert() {return prev_vert;}
Edge* Edge :: getNextEdge() {return next_edge;}
Edge* Edge :: getPrevEdge() {return prev_edge;}

