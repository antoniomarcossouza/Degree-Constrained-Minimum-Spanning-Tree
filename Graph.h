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
    Node *getNode(int id);

    //methods phase1
    void topologicalSorting();
    void breadthFirstSearch(ofstream &output_file);
    Graph *getVertexInduced(int *listIdNodes);
    Graph *agmKruskal(Graph *graph);
    Graph *agmPrim();
    void floydWarshall(ofstream &output_file);
    float dijkstra(int idSource, int idTarget);

    //methods phase1
    float greed();
    float greedRandom();
    float greedRactiveRandom();

    //primeira etapa
    void transitivoDireto(ofstream *arquivo_saida, int id);
    void transitivoIndireto(ofstream *arquivo_saida, int id);
    void depthFirstSearchAux(Node* node, bool* visitados,fstream &outputFile)
    void father();
    bool cicle(Edge *edge);
    void imprimeFile(ofstream *arquivo_saida); // kruskal
    void preencheListaNos();
private:
    //Auxiliar methods
    void transitivoDireto_Aux(vector<int> *no, Node *node);
    void transitivoIndireto_Aux(vector<int> *no, Node *node, int id);

    void unites(Node *x, Node *y);
    Node *find(Node *node);
};

#endif // GRAPH_H_INCLUDED
