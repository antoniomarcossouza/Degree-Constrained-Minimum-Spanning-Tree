/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <iostream>
#include <vector>

using namespace std;

class Graph
{

    //Atributes
private:
    int order;
    int number_edges;
    bool directed;
    bool weighted_edge;
    bool weighted_node;
    Node *first_node;
    Node *last_node;
    Graph *ArvoreGeradoraMinima;

public:
    //Constructor
    Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
    //Destructor
    ~Graph();
    //Getters
    int getOrder();
    int getNumberEdges();
    bool getDirected();
    bool getWeightedEdge();
    bool getWeightedNode();
    Node *getFirstNode();
    Node *getLastNode();
    //Other methods
    void insertNode(int id);
    void insertEdge(int id, int target_id, float weight);
    void removeNode(int id);
    bool searchNode(int id);
    bool searchPosition(float x, float y);
    Node *getNode(int id);

    //methods phase1
    void imprimeListaAdjacencia(ofstream &output_file);
    void topologicalSorting(ofstream &output_file);
    void breadthFirstSearch(int v, fstream &output_file);
    Graph *getVertexInduced(int *listIdNodes);
    Graph *agmKruskal(Graph *graph, ofstream &output_file);
    void agmPrim(ofstream &output_file);
    void floydWarshall(ofstream &output_file);
    float dijkstra(ofstream &output_file, int idSource, int idTarget);
    bool isConnected();
    int findIndice(int* distancias, int* abertos,int tam);

    //methods phase1
    float greed();
    float greedRandom();
    float greedRactiveRandom();

    //primeira etapa
    void transitivoDireto(ofstream &output_file, int id);
    void transitivoIndireto(ofstream &output_file, int id);
    void father();
    bool cicle(Edge *edge);
    string imprimir();
    void depthFirstSearch(int v, ofstream &output_file);
    void depthFirstSearchAux(Node *node, bool *visitados, ofstream &outputFile);
    void preencheListaNos();
    void setId(int id);

    void AGMRG_Guloso(int grau);
    void AGMRG_GulosoRandomizado(int grau);
    void AGMRG_GulosoRandomizadoReativo(int grau);

private:
    //Auxiliar methods
    void transitivoDireto_Aux(Graph *graphTransitivo, Node *node);
    void transitivoIndireto_Aux(Graph *graphTransitivo, Node *node, int id);
    void topologicalSorting_aux(vector<int> *no, int in[]);
    void unites(Node *x, Node *y);
    Node *find(Node *node);
    void walk(Node *node);
};

#endif // GRAPH_H_INCLUDED
