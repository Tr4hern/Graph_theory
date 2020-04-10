    //
// Created by Arnaud on 07/04/2020.
//

#include "Edge.h"


/*-----------------------------------------GET------------------------------------------------------------------------*/

int Edge :: getWeight() {return weight;}
Vertice* Edge :: getNextVert() {return next_vert;}
Vertice* Edge :: getPrevVert() {return prev_vert;}
Edge* Edge :: getNextEdge() {return next_edge;}
Edge* Edge :: getPrevEdge() {return prev_edge;}