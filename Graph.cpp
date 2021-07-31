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
void topologicalSorting()
{
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
    for (Edge *&arestaAux : listEdge)
    {
        if (!graph->cicle(arestaAux))
        {
        }
    }
    return 0;
}

Graph *agmPrim(Graph *graph, ofstream &output_file)
{
    Graph *minSpanningTree = new Graph(graph->getOrder(), graph->getDirected(), graph->getWeightedEdge(), graph->getWeightedNode());
    // Seja (u,v) a aresta de menor peso.
    // F <- {(u,v)}
    vector<Node> no;
    int contadorNode = 0;
    Edge *minEdge = graph->getFirstNode()->getFirstEdge();
    Node *aux;
    for (Node *node = graph->getFirstNode(); node != nullptr; node = node->getNextNode(), contadorNode++)
    {
        node->setPosition(contadorNode);
    }
    for (Node *node = graph->getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            if (edge < minEdge)
            {
                edge = minEdge;
                aux = node;
            }
        }
    }
    minSpanningTree->insertEdge(aux->getId(), minEdge->getTargetId(), minEdge->getWeight());
    no[aux->getId()] = 0;
    no[minEdge->getTargetId()] = 0;
    // Para i = 1,...,n faça
    //     Se c(i,u) < c(i,v) então prox(i) <- u
    //     Senão prox(i) <- v
    // fim-para

    for (Node *node = graph->getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        do
        {
            min = node->getFirstEdge();

        } while ();
        for (Edge *aresta = node->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
        {
            if (minEdge->getWeight() > aresta->getWeight())
            {
                min = node->getFirstEdge();
            }
        }
        node[node->getId()] = minEdge->getWeight();
    }

    /*
    for (int i = 1; i < graph->getOrder(); i++)
    {
        if (Custo_entre_Nos(i, u) < Custo_entre_Nos(i, v))
        {
            prox[i] = u;
        }
        else
        {
            prox[i] = v;
        }
    }
    // prox(u), prox(v) <- 0, contador <- 0
    prox[u] = 0, prox[v] = 0;
    int j = 0;
    // Enquanto contador < n-2 faça
    //     Seja j tal que prox(j)!=0 e c(j,prox(j)) é mínimo.
    //     F <- F [UNIãO] {(j,prox(j))}
    //     prox(j) <- 0
    //     Para i = 1,...,n faça
    //         Se prox(i) 1 0 e c(i,prox(i)) > c(i,j) então
    //         prox(i) <- j
    //     fim-para
    //     contador <- contador + 1
    // fim-enquanto
    while (j < graph->GetOrder())
    {
        if (prox[j] != 0 && Custo_entre_Nos(j, prox[j]) é mínimo.)
        {
            minSpanningTree->insertNode(j->getPosition());
            minSpanningTree->insertNode(prox[j]->getPosition());
            prox[j] = 0;
        }
        for (int i = 1; i < graph->getOrder(); i++)
        {
            if (prox[i] != 0 && Custo_entre_Nos(i, prox[i]) > Custo_entre_Nos(i, j))
            {
                prox(i) = j;
            }
        }
        j++;
    }
    */
}

void Graph::walk(Node *node)
{
    node->unchecks();
    for (Node *no = this->first_node; no != nullptr; no = no->getNextNode())
    {
        if (no->hasEdgeBetween(no->getId()))
        {
            if (!no->getChecks())
            {
                walk(no);
            }
        }
    }
}

bool Graph::getConected()
{
    Node *first = this->first_node;
    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        node->unchecks();
    }

    walk(first);

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        if (!node->getChecks())
        {
            return false;
        }
    }
    return true;
}

// Funções da primeira etapa

void Graph::transitivoDireto(ofstream *arquivo_saida, int id)
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
        *arquivo_saida << no[i] << " ";
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

void Graph::transitivoIndireto(ofstream *arquivo_saida, int id)
{
    vector<int> no;

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        transitivoIndireto_Aux(&no, node, id);
    }

    for (int i = 0; i < no.size(); i++)
    {
        *arquivo_saida << no[i] << " ";
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
