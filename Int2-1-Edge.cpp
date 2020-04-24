    //
// Created by Arnaud on 07/04/2020.
//

#include "Int2-1-Edge.h"


Int2 :: Int2() : weight('\0'), next_vert(nullptr), prev_vert(nullptr), next_edge(nullptr), prev_edge(nullptr) {}
Int2 :: Int2(const Int2& e) : weight(e.weight), next_vert(e.next_vert), prev_vert(e.prev_vert), next_edge(e.next_edge), prev_edge(e.prev_edge) {}
Int2& Int2 :: operator=(const Int2& e)
{
    weight = e.weight;

    next_vert = e.next_vert;
    prev_vert = e.prev_vert;

    next_edge = e.next_edge;
    prev_edge = e.prev_edge;

    return *this;
}

Int2 :: ~Int2()
{
    delete next_edge;
    delete prev_edge;
}


/*-----------------------------------------SET------------------------------------------------------------------------*/

void Int2 :: setWeight(int w) { weight = w;}
void Int2 :: setNextVert(Vertice* vertice) { next_vert = vertice;}
void Int2 :: setPrevVert(Vertice* vertice) { prev_vert = vertice;}
void Int2 :: setNextEdge(Int2* edge) { next_edge = edge;}
void Int2 :: setPrevEdge(Int2* edge) { prev_edge = edge;}


/*-----------------------------------------GET------------------------------------------------------------------------*/

int Int2 :: getWeight() {return weight;}
Vertice* Int2 :: getNextVert() {return next_vert;}
Vertice* Int2 :: getPrevVert() {return prev_vert;}
Int2* Int2 :: getNextEdge() {return next_edge;}
Int2* Int2 :: getPrevEdge() {return prev_edge;}