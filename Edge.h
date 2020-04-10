//
// Created by Arnaud on 07/04/2020.
//

#ifndef PROJET_EDGE_H
#define PROJET_EDGE_H

using namespace std;


class Vertice;

class Edge
{
    private:
        int weight;
        Vertice* next_vert;
        Vertice* prev_vert;
        Edge* next_edge;
        Edge* prev_edge;

    public:
        int getWeight();
        Vertice* getNextVert();
        Vertice* getPrevVert();
        Edge* getNextEdge();
        Edge* getPrevEdge();
};


#endif //PROJET_EDGE_H
