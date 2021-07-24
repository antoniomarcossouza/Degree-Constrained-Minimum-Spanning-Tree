#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <string>
#include <algorithm>

#define INF 99999

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}

Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id)
{
    if (!searchNode(id))
    {
        if (this->first_node != nullptr)
        {
            Node *no = new Node(id);
            this->last_node->setNextNode(no);
            this->last_node = no;
        }
        else
        {
            this->first_node = new Node(id);
            this->last_node = this->first_node;
        }
    }
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    if (!searchNode(id))
        this->insertNode(id);

    if (!searchNode(target_id))
        this->insertNode(target_id);

    if (this->directed)
    {
        Node *no = getNode(id);
        Node *no_alvo = getNode(target_id);
        no->insertEdge(target_id, weight);
        no->incrementInDegree();
        no_alvo->incrementOutDegree();
    }
    else
    {
        Node *no = getNode(id);
        no->insertEdge(target_id, weight);
        no->incrementInDegree();
    }
}

void Graph::removeNode(int id)
{
    if (searchNode(id))
    {
        if (this->first_node->getId() == id)
        {
            Node *aux = this->first_node;
            this->first_node = this->first_node->getNextNode();
            delete aux;
        }
        else
        {
            Node *anterior;
            Node *aux = this->first_node;

            while (aux != nullptr)
            {
                if (aux->getId() == id)
                {
                    break;
                }

                anterior = aux;
                aux = aux->getNextNode();
            }

            if (this->last_node == aux)
            {
                this->last_node = anterior;
            }

            anterior->setNextNode(aux->getNextNode());

            Node *p = this->first_node;
            while (p != nullptr)
            {
                p->removeEdge(id, directed, p);
            }

            delete aux;
        }
    }
}

bool Graph::searchNode(int id)
{
    if (this->first_node != nullptr)
    {
        for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
            if (aux->getId() == id)
                return true;
    }

    return false;
}

Node *Graph::getNode(int id)
{
    if (this->first_node != nullptr)
    {
        for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
            if (aux->getId() == id)
                return aux;
    }

    return nullptr;
}

//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file)
{
}

void Graph::floydWarshall(ofstream &output_file)
{
    int dist[order][order];

    int contadorNode = 0;
    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode(), contadorNode++)
    {
        node->setPosition(contadorNode);
    }

    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            dist[i][j] = INF; // Seta todos os valores da matriz pra infinito
            if (i == j)
            {
                dist[i][j] = 0; // Coloca a distância entre o vértice e ele mesmo
            }
        }
    }

    for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            Node *aux = getNode(edge->getTargetId());
            dist[node->getPosition()][aux->getPosition()] = edge->getWeight();
        }
    }

    for (int k = 0; k < order; k++)
    {
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 0; i < order; i++)
    {
        output_file << endl;
        for (int j = 0; j < order; j++)
        {
            if (dist[i][j] == INF)
            {
                output_file << " INF ";
            }
            else
            {
                output_file << "  " << dist[i][j] << "  ";
            }
        }
    }
}

float Graph::dijkstra(int idSource, int idTarget)
{
}

//function that prints a topological sorting
void topologicalSorting()
{
}

void breadthFirstSearch(ofstream &output_file)
{
}
Graph *getVertexInduced(int *listIdNodes)
{
}

Graph *agmKuskal(Graph *graph)
{
    Graph *graphKuskal = new Graph(graph->getOrder(), graph->getDirected(), graph->getWeightedEdge(), graph->getWeightedNode());

    list<Edge *> listEdge;
    graph->father();
    for (Edge *&arestaAux : listEdge)
    {
        if (!graph->cicle(arestaAux))
        {
        }
    }
}
Graph *agmPrim()
{
}

// Funções da primeira etapa

void Graph::transitivoDireto(ofstream &output_file, int id)
{
    vector<int> no;

    Node *node = getNode(id);

    for (Edge *aresta = node->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
    {
        if (!std::count(no.begin(), no.end(), node->getId()))
        {
            no.push_back(aresta->getTargetId());
            transitivoDireto_Aux(&no, getNode(aresta->getTargetId()));
        }
    }

    for (int i = 0; i < no.size(); i++)
    {
        output_file << no[i] << " ";
    }
}

void Graph::transitivoDireto_Aux(vector<int> *no, Node *node)
{
    for (Edge *aresta = node->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
    {
        if (!std::count(no->begin(), no->end(), aresta->getTargetId()))
        {
            no->push_back(aresta->getTargetId());
            transitivoDireto_Aux(no, getNode(aresta->getTargetId()));
        }
    }
}

void Graph::transitivoIndireto(ofstream &output_file, int id)
{
    vector<int> no;

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        transitivoIndireto_Aux(&no, node, id);
    }

    for (int i = 0; i < no.size(); i++)
    {
        output_file << no[i] << " ";
    }
}

void Graph::transitivoIndireto_Aux(vector<int> *no, Node *node, int id)
{
    for (Edge *aresta = node->getFirstEdge(); aresta != NULL; aresta = aresta->getNextEdge())
    {
        if (aresta->getTargetId() == id && (!std::count(no->begin(), no->end(), node->getId())))
        {
            no->push_back(node->getId());
            for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
            {
                transitivoIndireto_Aux(no, node, node->getId());
            }
        }
    }
}

void Graph::ordenacaoTopologica(ofstream &output_file)
{
    vector<int> no;
    int in[order];

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
        in[node->getId()] = node->getInDegree();

    ordenacaoTopologica_Aux(&no, in);

    for (int i = 0; i < no.size(); i++)
        output_file << no[i] << " ";
}

void Graph::ordenacaoTopologica_Aux(vector<int> *no, int in[])
{
    if (no->size() != order)
    {
        for (int i = 0; i < order; i++)
        {
            if (in[i] == 0)
            {
                no->push_back(i);
                in[i] = -1;
                Node *node = getNode(i);
                for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
                {
                    in[edge->getTargetId()]--;
                }
                ordenacaoTopologica_Aux(no, in);
                return;
            }
        }
        cout << "O grafo não é acíclico direcionado." << endl;
    }
}

void Graph::father()
{
    for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        node->setFather(node->getId());
    }
}

Node *Graph::find(Node *node)
{
    Node *aux = getNode(node->getFather());

    if (aux == node)
        return aux;
    else
        return find(aux);
}

void Graph::unites(Node *x, Node *y)
{
    Node *xraiz = find(x);
    Node *yraiz = find(y);

    xraiz->setFather(yraiz->getId());
}

bool Graph::cicle(Edge *edge)
{

    Node *aux1 = getNode(edge->getTargetId());
    Node *aux2 = getNode(edge->getTargetId());

    if (find(aux1) == find(aux2))
        return true;
    else
        unites(aux1, aux2);
    return false;
}
