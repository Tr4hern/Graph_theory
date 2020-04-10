//
// Created by Arnaud on 07/04/2020.
//
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "Vertice.h"


Vertice* Vertice :: initializer_vertices(int lenght)
{
    Vertice *node, *tmp = nullptr, *head;
    for(int i = 0; i < lenght; i++)
    {
        node = new Vertice;
        node -> name = to_string(i);
        node -> next = nullptr;
        node -> prev = nullptr;
        node -> source = false;
        node -> sink = false;
        node -> edges = nullptr;

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

/*-----------------------------------------GET------------------------------------------------------------------------*/


string Vertice :: getName() {return name;}
bool Vertice::getSink() {return sink;}
bool Vertice::getSource() {return source;}
Vertice* Vertice :: getNext() {return next;}
Vertice *Vertice::getPrev() {return prev;}
Edge *Vertice::getEdges() {return edges;}




/*-------------------------------------READ TEXT----------------------------------------------------------------------*/




Vertice* Vertice :: readText(char *fileName)
{
    int NumberOfVertices[1] = {'\0'};
    int NumberOfEdges[1] = {'\0'};
    char str[999];

    Vertice* head;

    errno = 0;
    FILE* file = fopen(fileName, "rt");

    if (NULL == file)
    {
        printf("Error of opening at line %d of file %s : %s\n", __LINE__ , fileName, strerror(errno));
        return nullptr;
    }

    fscanf(file, "%d", NumberOfVertices);
    head = initializer_vertices(*NumberOfVertices);

    fscanf(file, "%d", NumberOfEdges);

    for(int i = 0; i < *NumberOfEdges; i++)
    {
        fgets(str, 999, file);
        printf("%s", str);
    }

    printf("\nvertices : %d\nedges : %d", *NumberOfVertices, *NumberOfEdges);
    printf("\nend\n");

    fclose(file);

    return head;
}