//
// Created by Arnaud on 07/04/2020.
//

#ifndef PROJET_INT2_1_EDGE_H
#define PROJET_INT2_1_EDGE_H

#include <vector>
#include <string>

using namespace std;

class Vertice;

class Int2
{
    private:
        int weight;
        Vertice* next_vert;
        Vertice* prev_vert;
        Int2* next_edge;
        Int2* prev_edge;

    public:
        Int2();
        Int2(const Int2 &);
        Int2& operator=(const Int2 &);
        ~Int2();

        void setWeight(int);
        void setNextVert(Vertice *);
        void setPrevVert(Vertice *);
        void setNextEdge(Int2 *);
        void setPrevEdge(Int2 *);

        int getWeight();
        Vertice* getNextVert();
        Vertice* getPrevVert();
        Int2* getNextEdge();
        Int2* getPrevEdge();
};


#endif //PROJET_INT2_1_EDGE_H
