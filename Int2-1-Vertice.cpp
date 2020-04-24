//
// Created by Arnaud on 07/04/2020.
//
#include <iostream>
#include <sstream>
#include <iterator>

#include <cstring>
#include <cstdio>
#include <vector>

#include "Int2-1-Vertice.h"

int NB_VERTICES = 0;
int BUFF = 1000;


Vertice :: Vertice() : name(), source(true), sink(false), next(nullptr), prev(nullptr), rank(-1), edges(nullptr) {}
Vertice :: Vertice(const Vertice & v) : name(v.name), source(v.source), sink(v.sink), next(v.next), prev(v.prev), rank(v.rank), edges(v.edges) {}
Vertice& Vertice :: operator=(const Vertice & v)
{
    name = v.name;
    source = v.source;
    sink = v.sink;
    next = v.next;
    prev = v.prev;
    rank = v.rank;
    edges = v.edges;
    return *this;
}

Vertice::~Vertice()
{
    delete next;
    delete prev;
    while(edges -> getNextEdge() != nullptr)
    {
        edges = edges -> getNextEdge();
        delete (edges -> getPrevEdge());
    }
    delete edges;
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




void Vertice :: printVertices(Vertice* list)
{
    Vertice* tmp = list;

    while(tmp)
    {
        cout << green << "Vertex " << tmp -> name << white << endl;

        Int2* t = tmp -> edges;

        if(t == nullptr)
            cout << "No transition" << endl;
        else
        {
            while(t != nullptr)
            {

                cout <<  t -> getPrevVert() -> getName() << " -> " << t -> getNextVert() -> getName() << " = " << t -> getWeight() << endl;

                t = t -> getNextEdge();
            }
        }

        cout << endl;
        tmp = tmp -> next;
    }
}


/*-----------------------------------------SET------------------------------------------------------------------------*/

void Vertice :: setSource(bool b) {source = b;}

Vertice* Vertice :: setEdges(const vector<string> &vectors, Vertice* list)
{
    Vertice* tmp = list;
    Int2* newEdge = new Int2;
    Int2* t = nullptr;

    newEdge -> setWeight((stoi(vectors[2]) ) );        // convert string to int

    /* find the ingoing vertex in the list */
    while( (tmp -> name) != vectors[1] )
        tmp = tmp -> next;
    newEdge -> setNextVert(tmp);
    newEdge -> getNextVert() -> setSource(false);       // the vertex has at least 1 ingoing edge, so it is not a source

    tmp = list;         // make sure we start at the beginning again

    /* find the outgoing vertex in the list */
    while( (tmp -> name) != vectors[0])
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
Vertice* Vertice :: getNext() {return next;}
int Vertice :: getRank() {return rank;}


/*-------------------------------------MATRIX-------------------------------------------------------------------------*/

// A for Adjacency, V for Values
string** Vertice :: initializer_matrix(char c) {
    auto** adj = new string*[NB_VERTICES + 1];

    for(int i = 0; i < NB_VERTICES + 1; i++)
    {

        adj[i] = new string[NB_VERTICES + 1];

        for(int j = 0; j < NB_VERTICES + 1; j++)
        {
            if(i == 0 && j != 0)
                adj[i][j] = to_string(j - 1);

            else if(j == 0 && i != 0)
                adj[i][j] = to_string(i - 1);

            else if(j != 0)
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
    Int2* t = nullptr;

    for(int i = 0; i < NB_VERTICES + 1; i++)
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
    Int2* t = nullptr;

    for(int i = 0; i < NB_VERTICES + 1; i++)
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
        cout << "Adjacency Matrix" << endl;
    else if(c == 'V')
        cout << "Values Matrix" << endl;


    for(int i = 0; i < NB_VERTICES + 1; i++)
    {

        if(i < 11 )
            cout << " ";

        for(int j = 0; j < NB_VERTICES + 1; j++)
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

            if(j > 9)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}


/*-------------------------------------RANK---------------------------------------------------------------------------*/


Vertice* Vertice :: findRanks(string** matrix, Vertice* list, int rank)
{
    Vertice* tmp = list;
    int ddl[NB_VERTICES];

    for(int i = 0; i < NB_VERTICES; i ++)
        ddl[i] = -1;

    int cpt = 0;
    bool change = false;        // determine if we have found new sources or not (after deleting the previous ones)
    bool finish = true;        // determine if there is a cycle or not

    for(int i = 1; i < NB_VERTICES + 1; i++)
    {
        for(int j = 1; j < NB_VERTICES + 1; j++)
        {
            cpt += stoi(matrix[j][i]);
        }

        if(cpt == 0)
        {

            while( (tmp -> name) != matrix[0][i] )
            {
                tmp = tmp -> next;
            }

            if(tmp -> rank == -1)
            {
                change = true;
                tmp -> rank = rank;            // the aim is to attribute the value of the operation to the attribute "rank" of the vertice, we will reset it if there is a cycle

                // we put the vertices to "delete" in an array to delete them at the end of the for loop
                int e = 0;
                while(ddl[e] != -1)
                {
                    if(e == NB_VERTICES)
                        break;
                    else
                        e += 1;
                }

                ddl[e] = stoi(matrix[0][i]);
            }

            tmp = list;
        }
        else
            finish = false;     // there are still some possible sources


        cpt = 0;
    }



    int i = 0;
    while(ddl[i] != -1)
    {
        for(int j = 1; j < NB_VERTICES + 1; j++)
        {
            if(ddl[i] == stoi(matrix[j][0]) )
            {
                // we "destroy" the sources found by saying there is no edge going from them
                for(int k = 1; k < NB_VERTICES + 1; k++)
                    matrix[j][k] = "0";
            }
        }

        i++;
    }

    if(change && !finish)      // if we made some modification and there are still some possible sources
        list = findRanks(matrix, list, rank + 1);

    else if (!change && !finish)        // if we didn't make any modification but there are still some possible edges -> there is a cycle
    {
        cout << red << "There is a least 1 cycle, we can't determine rank" << white << endl;

        while(tmp)
        {
            tmp -> rank = -1;
            tmp = tmp -> next;
        }

        return list;
    }

    else            // there is no possible sources anymore AND we didn't make a change this time
        return list;

    return list;
}

// the aim of this function is to return the list of vertice ordered by their ranks
Vertice* Vertice :: listByRank(Vertice * list)
{
    Vertice* rankList = nullptr;
    Vertice* tmpL = list;
    Vertice* tmpR = nullptr;

    int ranksFound[NB_VERTICES];            // all the vertice of rank i



    for(int i = 0; i < NB_VERTICES; i++)
    {
        // we initialize the array at each passage
        for(int j = 0; j < NB_VERTICES; j++)
            ranksFound[j] = -1;

        // we find all the vertice of rank i
        for(int j = 0; j < NB_VERTICES; j++)
        {
            if(tmpL -> rank == i)
            {
                int e = 0;
                while(ranksFound[e] != -1)
                {
                    if(e == NB_VERTICES)
                        break;
                    else
                        e += 1;
                }
                ranksFound[e] = stoi(tmpL -> name);
            }
            tmpL = tmpL -> next;
        }


        int j = 0;
        while(ranksFound[j] != -1)
        {
            tmpL = list;
            while( (tmpL -> name)  != to_string(ranksFound[j]) )
                tmpL = tmpL -> next;

            auto* newV = new Vertice(*tmpL);
            newV -> prev = nullptr;
            newV -> next = nullptr;

            if(rankList == nullptr)
                rankList = newV;
            else
            {
                tmpR = rankList;
                while(tmpR -> next != nullptr)
                    tmpR = tmpR -> next;

                newV -> prev = tmpR;
                tmpR -> next = newV;
            }

            j++;
        }

        tmpL = list;
    }

    return rankList;
}

void Vertice :: printRank(Vertice* list)
{
    Vertice* tmp = list;

    if(tmp -> getRank() != -1)      // if there is no cycle
    {
        cout << green << "Vertex    " << white;
        while(tmp)
        {
            if(stoi(tmp -> getName()) < 9)
                cout << tmp -> getName() << "  ";
            else
                cout << tmp -> getName() << " ";

            tmp = tmp -> getNext();
        }

        tmp = list;

        cout << endl << green << "Rank      " << white;
        while(tmp)
        {
            if(stoi(tmp -> getName()) > 9)
                cout << tmp -> getRank() << "  ";
            else
                cout << tmp -> getRank() << "  ";
            tmp = tmp -> getNext();
        }
        cout << endl;
    }
}


/*-------------------------------------SCHEDULING---------------------------------------------------------------------*/


bool Vertice :: checkScheduling(Vertice* list, char* save)
{
    int nbSource = 0;
    int nbSink = 0;
    bool cycle = false;
    bool valueEdge = true;
    bool outgoingAt0 = true;
    bool negativeEdge = false;

    Vertice* tmp = list;

    if(tmp -> rank == -1)
        cycle = true;

    while(tmp)
    {
        if(tmp -> source)
            nbSource += 1;

        if(tmp -> sink)
            nbSink += 1;

        Int2* t = tmp -> edges;
        if(t != nullptr)
        {
            int currentValue = t -> getWeight();

            while(t)
            {
                if(t -> getWeight() < 0)
                    negativeEdge = true;

                if(currentValue != t -> getWeight())
                    valueEdge = false;

                if(tmp -> source && t -> getWeight() != 0)
                    outgoingAt0 = false;

                currentValue = t -> getWeight();
                t = t -> getNextEdge();
            }
        }


        tmp = tmp -> next;
    }

    if(!(!cycle && valueEdge && outgoingAt0 && !negativeEdge && nbSource == 1 && nbSink == 1) )
        errorSaves(save);

    return (!cycle && valueEdge && outgoingAt0 && !negativeEdge && nbSource == 1 && nbSink == 1);
}


void Vertice :: scheduling(Vertice* list, Vertice* ranks, char* save)
{
    if(checkScheduling(list, save))
    {

        Vertice* tmp = list;
        int cpt = 0;        // Vertice with or whitout alpha and omega

        while(tmp)
        {
            cpt++;
            tmp = tmp -> next;
        }

        int earliestTime[cpt];
        int latestTime[cpt];
        int margin[cpt];
        string shortestPath[cpt];

        for(int i = 0; i < cpt; i++)
        {
            earliestTime[i] = 0;
            latestTime[i] = -1;
            margin[i] = 0;
            shortestPath[i] = '\0';
        }

        tmp = list;

        // calculation of the earliest time
        while(tmp)
        {
            Int2* t = tmp -> edges;

            while(t)
            {
                // if the value of the vertexwe are going to is inferior to the new one, we keep the new one
                if(earliestTime[stoi(t -> getNextVert() -> getName() )] < (earliestTime[stoi(t -> getPrevVert() -> getName() )] + t -> getWeight()))
                    earliestTime[stoi(t -> getNextVert() -> getName() )] = earliestTime[stoi(t -> getPrevVert() -> getName() )] + t -> getWeight();

                t = t -> getNextEdge();
            }

            if(tmp -> next == nullptr)
                latestTime[cpt - 1] = earliestTime[cpt - 1];

            tmp = tmp -> next;
        }


        // calculation of the latest path

        tmp = ranks;

        while(tmp -> next != nullptr)
            tmp = tmp -> next;

        while(tmp)
        {
            Int2* t = tmp -> edges;


            while(t)
            {
                // if the value we have minus the weight of the edge is positive (important because we keep the smallest one but we need it to be positive)
                if(latestTime[stoi(t -> getNextVert() -> getName()) ] - t -> getWeight() >= 0)
                {
                    //if the value we already is superior to the new value or the value of the box is -1 (it was not visited yet)
                    if(latestTime[stoi(t -> getPrevVert() -> getName()) ] > (latestTime[stoi(t -> getNextVert() -> getName()) ] - t -> getWeight())
                            ||  latestTime[stoi(t -> getPrevVert() -> getName()) ] == -1)
                    {
                        latestTime[stoi(t -> getPrevVert() -> getName()) ] = latestTime[stoi(t -> getNextVert() -> getName()) ] - t -> getWeight();
                        shortestPath[stoi(t -> getPrevVert() -> getName()) ] = t -> getNextVert() -> getName();                                     // we determine it was the shortest path if we are going thru this vertex later
                    }
                }

                t = t -> getNextEdge();
            }

            tmp = tmp -> prev;
        }


        for(int i = 0; i < cpt; i++)
            margin[i] = abs(earliestTime[i] - latestTime[i]);



        printRank(list);



        cout << green << "Earliest " << white;
        tmp = list;
        while(tmp)
        {
            int i = 0;
            while(i != stoi(tmp -> getName()) )
                i++;

            // just a beautiful print
            if(earliestTime[i] > 9)
                cout << earliestTime[i] << " " ;
            else
                cout << " " << earliestTime[i] << " " ;

            tmp = tmp -> next;
        }
        cout << endl;

        cout << green << "Latest   " << white;
        tmp = list;
        while(tmp)
        {
            int i = 0;
            while(i != stoi(tmp -> getName()) )
                i++;

            if(latestTime[i] > 9)
                cout << latestTime[i] << " " ;
            else
                cout << " " << latestTime[i] << " " ;

            tmp = tmp -> next;
        }
        cout << endl;

        cout << green << "Margin   " << white;
        tmp = list;
        while(tmp)
        {
            int i = 0;
            while(i != stoi(tmp -> name) )
                i++;

            if(margin[i] > 9)
                cout << margin[i] << " " ;
            else
                cout << " " << margin[i] << " " ;

            tmp = tmp -> next;
        }
        cout << endl;

        cout << green << "Shortest Path : " << white;
        // we start at the source
        tmp = ranks;
        while(!tmp -> source)
            tmp = tmp -> next;

        // we take its emplacement in the array
        int i = stoi(tmp -> name);

        cout << tmp -> name;

        // while we did not found the sink, we continue to check which vertex we pass thru
        do
        {
            cout << " -> " << shortestPath[i];
            i = stoi(shortestPath[i]);
        }while(stoi(shortestPath[i]) != cpt - 1);
        cout << " -> " << cpt - 1 << endl;

        timeSaves(save, earliestTime, list, 'E');
        timeSaves(save, latestTime, list, 'L');
        timeSaves(save, margin, list, 'M');
        shortSaves(save, shortestPath, ranks);
    }
    else
        cout << red << "The graph can not be scheduled in consideration to the properties asked" << white << endl;
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


void Vertice :: makeGraph(char* str, char* save)
{
    auto* head = new Vertice();
    auto* rank = new Vertice();

    head = head -> readText(str);
    printVertices(head);

    string** Adjacent = adjacentMatrix(head);
    string** Values = valuesMatrix(head);

    printMatrix(Adjacent, 'A');
    printMatrix(Values, 'V');

    matSaves(save, Adjacent, 'A');
    matSaves(save, Values, 'V');

    findRanks(Adjacent, head, 0);
    rankSaves(save, head);

    rank = listByRank(head);
    rank -> scheduling(head, rank, save);
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
    NB_VERTICES = NumberOfVertices;
    head = initializer_vertices(NumberOfVertices);

    /* We save the number of edges */
    fscanf(file, "%d\n", &NumberOfEdges);

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


/*-------------------------------------SAVE TEXT----------------------------------------------------------------------*/

void Vertice :: matSaves(char* fileName, string** mat, char c)
{

    char str[BUFF];
    FILE* file = fopen(fileName, "at");

    if(c == 'A')
        fputs("\nAdjaceny Matrix\n", file);
    else
        fputs("Values Matrix\n", file);

    for(int i = 0; i < NB_VERTICES + 1; i++)
    {
        for(int j = 0; j < BUFF; j++)
            str[j] = '\0';

        if(i < 11 )
            fputs(" ", file);

        for(int j = 0; j < NB_VERTICES + 1; j++)
        {
            if(i == 0 && j <= 10)
            {
                fputs("  ", file);
                strcpy(str, mat[i][j].c_str() );
                fputs(str, file);
            }

            else if (i == 0 && j > 10)
            {
                fputs(" ", file);
                strcpy(str, mat[i][j].c_str() );
                fputs(str, file);
            }

            else if (j == 0 && i != 0)
            {
                fputs("  ", file);
                strcpy(str, mat[i][j].c_str() );
                fputs(str, file);
            }

            else
            {
                if(c == 'A')
                {
                    fputs(" ", file);
                    strcpy(str, mat[i][j].c_str() );
                    fputs(str, file);
                    fputs(" ", file);
                }
                else
                {
                    if(mat[i][j] == "*")
                    {
                        fputs(" ", file);
                        strcpy(str, mat[i][j].c_str() );
                        fputs(str, file);
                        fputs(" ", file);
                    }
                    else
                    {
                        if(stoi(mat[i][j]) > 9 || stoi(mat[i][j]) < 0)
                        {
                            fputs(" ", file);
                            strcpy(str, mat[i][j].c_str() );
                            fputs(str, file);
                        }
                        else
                        {
                            fputs(" ", file);
                            strcpy(str, mat[i][j].c_str() );
                            fputs(str, file);
                            fputs(" ", file);
                        }
                    }
                }

            }

            if(j > 9)
               fputs(" ", file);
        }
        fputs("\n", file);
    }
    fputs("\n", file);

    fclose(file);
}

void Vertice :: rankSaves(char* fileName, Vertice* list)
{
    char str[BUFF];
    FILE* file = fopen(fileName, "at");
    Vertice* tmp = list;

    if(tmp -> getRank() != -1)      // if there is no cycle
    {
        for(int j = 0; j < BUFF; j++)
            str[j] = '\0';

        fputs("Vertex    " , file);

        while(tmp)
        {
            strcpy(str, tmp -> getName().c_str());
            fputs(str, file);

            if(stoi(tmp -> getName()) < 9)
                fputs("  ", file);
            else
                fputs(" ", file);

            tmp = tmp -> getNext();
        }

        tmp = list;

        fputs("\nRank      " , file);
        while(tmp)
        {
            sprintf(str, "%d", tmp -> getRank());
            fputs(str, file);

            if(stoi(tmp -> getName()) > 9)
                fputs("  ", file);
            else
                fputs("  ", file);

            tmp = tmp -> getNext();
        }
        fputs("\n", file);
    }
    else
        fputs("there is a cycle", file);


    fclose(file);
}

void Vertice :: errorSaves(char* fileName)
{
    FILE* file = fopen(fileName, "at");
    fputs("\nWe can not go any further", file);
    fclose(file);
}

void Vertice :: timeSaves(char* fileName, int* tab, Vertice* list, char c)
{
    Vertice* tmp = list;
    FILE* file = fopen(fileName, "at");
    char str[BUFF];

    if(c == 'E')
        fputs("Earliest ", file);
    else if(c == 'L')
        fputs("Latest   ", file);
    else
        fputs("Margin   ", file);


    while(tmp)
    {
        for(int j = 0; j < BUFF; j++)
            str[j] = '\0';

        int i = 0;
        while(i != stoi(tmp -> getName()) )
            i++;

        sprintf(str, "%d", tab[i]);

        if(tab[i] > 9)
        {
            fputs(str, file);
            fputs(" ", file);
        }
        else
        {
            fputs(" ", file);
            fputs(str, file);
            fputs(" ", file);
        }

        tmp = tmp -> next;
    }
    fputs("\n", file);

    fclose(file);
}

void Vertice :: shortSaves(char* fileName, string* path, Vertice * list)
{
    Vertice* tmp = list;
    char str[BUFF];
    FILE* file = fopen(fileName, "at");

    for(int j = 0; j < BUFF; j++)
        str[j] = '\0';

    fputs("\nShortest Path : ", file);

    while(!tmp -> source)
        tmp = tmp -> next;

    // we take its emplacement in the array
    int i = stoi(tmp -> name);

    sprintf(str, "%d", stoi(tmp -> name));
    fputs(str, file);

    // while we did not found the sink, we continue to check which vertex we pass thru
    do
    {
        fputs(" -> ", file);
        strcpy(str, path[i].c_str() );
        fputs(str, file);
        i = stoi(path[i]);

    }while(stoi(path[i]) != NB_VERTICES - 1);
    fputs(" -> ", file);
    sprintf(str, "%d", NB_VERTICES - 1);
    fputs(str, file);

    fclose(file);
}

void Vertice :: initSaves(char* fileName, int graph)
{
    FILE* file = fopen(fileName, "w+");
    char str[BUFF];
    sprintf(str, "Graph %d", graph);
    fputs(str, file);
    fclose(file);
}