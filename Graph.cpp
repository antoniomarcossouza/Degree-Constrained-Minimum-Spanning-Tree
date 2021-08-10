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
#include <tuple>

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
        node->setPosition(contadorNode); // Seta a posição dos nós
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
            // Itera por todos as arestas, colocando o peso como a distância entre os 2 nós
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
                // Coloca a menor distância entre os nós restantes
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
            // Output
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
    return 0;
}

//function that prints a topological sorting
void Graph::topologicalSorting(ofstream &output_file)
{
    vector<int> no;
    int in[order + 1];

    for (int i = 0; i < order + 1; i++)
        in[i] = -1;

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
        in[node->getId()] = node->getOutDegree();

    topologicalSorting_aux(&no, in);

    if (no.size() == order)
    {
        if (no.size() > 0)
            output_file << no[0];
        for (int i = 1; i < no.size(); i++)
            output_file << " -> " << no[i];
    }
}

void Graph::topologicalSorting_aux(vector<int> *no, int in[])
{
    if (no->size() != order)
    {
        for (int i = 0; i < order + 1; i++)
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
                topologicalSorting_aux(no, in);
                return;
            }
        }
        cout << "O grafo não é acíclico direcionado." << endl;
    }
}

void breadthFirstSearch(ofstream &output_file)
{
}
Graph *getVertexInduced(int *listIdNodes)
{
    return 0;
}

Graph *agmKuskal(Graph *graph)
{
    Graph *graphKuskal = new Graph(graph->getOrder(), graph->getDirected(), graph->getWeightedEdge(), graph->getWeightedNode());

    list<Edge *> listEdge;
    graph->father();
    /* for (Edge *&arestaAux : listEdge)
    {
        if (!graph->cicle(arestaAux))
        {
        }
    }*/
    return 0;
}

void Graph::agmPrim(ofstream &output_file)
{
    Graph *minSpanningTree = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());
    typedef vector<tuple<int, int, int>> no;
    no tl;

    Edge *minEdge = this->getFirstNode()->getFirstEdge();
    Node *aux = this->getFirstNode();

    for (Node *node = this->getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            if (edge->getWeight() < minEdge->getWeight())
            {
                edge = minEdge;
                aux = node;
            }
        }
    }

    minSpanningTree->insertEdge(aux->getId(), minEdge->getTargetId(), minEdge->getWeight());
    tl.push_back(tuple<int, int, int>(aux->getId(), minEdge->getTargetId(), 0));

    for (int i = 0; i < this->getOrder(); i++)
    {
        for (Node *node = minSpanningTree->getFirstNode(); node != nullptr; node = node->getNextNode())
        {
            minEdge = node->getFirstEdge();
            for (Edge *aresta = this->getNode(node->getId())->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
            {
                if (get<2>(tl[minEdge->getTargetId()]) == 0 || (aresta->getWeight() < minEdge->getWeight() && get<2>(tl[aresta->getTargetId()]) != 0))
                {
                    minEdge = aresta;
                    aux = node;
                }
            }
            if (minEdge != NULL)
                tl.push_back(tuple<int, int, int>(aux->getId(), minEdge->getTargetId(), minEdge->getWeight()));
        }

        int min = 999999999;
        int idMin = 0;

        for (int i = 0; i < tl.size(); i++)
        {
            if (get<2>(tl[i]) < min && get<2>(tl[i]) != 0)
            {
                min = get<2>(tl[i]);
                idMin = i;
            }
        }

        cout << idMin << endl;

        minSpanningTree->insertEdge(get<0>(tl[idMin]), get<1>(tl[idMin]), get<2>(tl[idMin]));
        tl[idMin] = tuple<int, int, int>(get<0>(tl[idMin]), get<1>(tl[idMin]), 0);
    }

    cout << minSpanningTree->imprimir();
}

void Graph::walk(Node *node)
{
    node->setCheck(false);
    for (Node *no = this->first_node; no != nullptr; no = no->getNextNode())
    {
        if (no->hasEdgeBetween(no->getId()))
        {
            if (!no->getCheck())
            {
                walk(no);
            }
        }
    }
}

bool Graph::isConnected()
{
    Node *first = this->first_node;
    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        node->setCheck(false);
    }

    walk(first);

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        if (!node->getCheck())
        {
            return false;
        }
    }
    return true;
}

// Funções da primeira etapa

void Graph::transitivoDireto(ofstream &output_file, int id)
{

    Graph *graphTransitivo = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());

    Node *node = getNode(id);
    for (Edge *aresta = node->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
    {
        if (!graphTransitivo->searchNode(aresta->getTargetId()))
        {
            graphTransitivo->insertEdge(node->getId(), aresta->getTargetId(), aresta->getWeight());
            transitivoDireto_Aux(graphTransitivo, getNode(aresta->getTargetId()));
        }
    }

    output_file << graphTransitivo->imprimir();
}

void Graph::transitivoDireto_Aux(Graph *graphTransitivo, Node *node)
{
    for (Edge *aresta = node->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
    {
        if (!graphTransitivo->searchNode(aresta->getTargetId()))
        {
            graphTransitivo->insertEdge(node->getId(), aresta->getTargetId(), aresta->getWeight());
            transitivoDireto_Aux(graphTransitivo, getNode(aresta->getTargetId()));
        }
    }
}

void Graph::transitivoIndireto(ofstream &output_file, int id)
{
    Graph *graphTransitivo = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());
    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
        transitivoIndireto_Aux(graphTransitivo, node, id);

    output_file << graphTransitivo->imprimir();
}

void Graph::transitivoIndireto_Aux(Graph *graphTransitivo, Node *node, int id)
{
    for (Edge *aresta = node->getFirstEdge(); aresta != NULL; aresta = aresta->getNextEdge())
    {
        if (aresta->getTargetId() == id)
        {
            graphTransitivo->insertEdge(node->getId(), aresta->getTargetId(), aresta->getWeight());

            for (Node *nodeAux = this->first_node; nodeAux != nullptr; nodeAux = nodeAux->getNextNode())
                transitivoIndireto_Aux(graphTransitivo, nodeAux, node->getId());
        }
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

void Graph::percorre(Node *u)
{
    u->setCheck(true);
    for (Node *v = this->first_node; v != nullptr; v = v->getNextNode())
    {
        if (v->hasEdgeBetween(u->getId()))
        {
            if (!v->getCheck())
                percorre(v);
        }
    }
}

bool Graph::cicle()
{
    Node *node = this->first_node;
    for (Node *no = this->first_node; no != nullptr; no = no->getNextNode())
        no->setCheck(false);
    percorre(node);
    for (Node *no = this->first_node; no != nullptr; no = no->getNextNode())
        if (!no->getCheck())
            return false;
    return true;
}

string Graph::imprimir()
{
    stringstream stream;

    int i = 0;

    stream << "graph imprimir {" << endl;
    for (Node *no = this->first_node; no != nullptr; no = no->getNextNode())
    {
        if (no->getFirstEdge() == NULL)
            stream << "    " << no->getId() << endl;
        for (Edge *aresta = no->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
        {
            if (this->directed)
                stream << "    " << no->getId() << " -> " << aresta->getTargetId() << endl;
            else
                stream << "    " << no->getId() << " -- " << aresta->getTargetId() << endl;
        }
    }

    stream << "}" << endl;

    return stream.str();
}