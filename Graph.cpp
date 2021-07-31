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

void breadthFirstSearch(int v, ofstream &output_file)
{
    Node* node = this->first_node;                // no aponta para primeiro no  

    for(int i = 0; i < getOrder(); i++)     
    {
        node->setIndexSearch(i);                  // setando indice de busca dos nós

        visitados[i] = 0;                         // setando indice visitados como false

        node = node->getNextNode();               // percorrendo todos os nós
    }

    node = getNode(v);                            // buscando o nó no grafo

    if(node == nullptr) {                         // checando a presença do nó no grafo

        outputFile << "Erro de busca: No não encontrado!" << endl;

        return false;

    } else {

        bool* visitados = new bool[getOrder()];   // vetor para verificar os nós visitados
        
        depthFirstSearchAux(node,visitados,outputFile);

    }

    delete [] visitados;                         // desalocando vetor de visitados

    return true;                                 // retornando sucesso na busca
}


void Grafo::depthFirstSearchAux(Node* node, bool* visitados, fstream &outputFile)
{

    outputFile << "Visitando o nó : " <<  node->getId() <<  endl;

    visitados[node->getIndexSearch()] = 1;        // marcando como vistado 

    Edge* edge;

    for(edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge()) // percorrendo as arestas desse nó
    {
        Node* aux = getNode(edge->getTargetId());   // verificando o nó w

        if(visitados[aux->getIndexSearch()] == 0) {  // w não foi visitado

            if(cicle(aux->getFirstEdge())) {

                output_file << "( " << node->getId() << " -- Ret -- "  << aux->getId() << " )"; // destacando arestas de retorno
            }

            depthFirstSearchAux(aux, visitados, outputFile); // chamo recursivo

        }        

    }

}

Graph *getVertexInduced(int *listIdNodes)
{
}

Graph *agmKruskal(Graph *graph)
{
    
    Graph *graphKruskal = new Graph(graph->getOrder(), graph->getDirected(), graph->getWeightedEdge(), graph->getWeightedNode());
    
    // preenchendo lista de arestas 
    list<Edge*> listEdgesAux;
    list<Edge*> listEdgesFinal;
 
    for(Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        for(Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            listEdgesAux.push_back(edge);
        }
    }

    // inserindo em lista final elementos que não se repetem
    int contador;
    for(Edge* & EdgeAux : listEdgesAux)
    {
        contador=0;
        for(Edge* & EdgeAux2 : listEdgesFinal)
        {   
            /*if(EdgeAux2->getIdAlvo() == EdgeAux->getIdOrigem()
                    &&   EdgeAux2->getIdOrigem() == EdgeAux->getIdAlvo())*/
            if(EdgeAux2->getTargetId() == EdgeAux->getIdOrigem() 
                    && EdgeAux2->getIdOrigem() == EdgeAux->getTargetId()) 
                break;
            else
                contador++;
        }
        if(contador == listEdgesFinal.size())
            listEdgesFinal.push_front(EdgeAux);
    }

    // ordenando a lista de arestas de acordo com o peso
    sort(listEdgesFinal.begin(), listEdgesFinal.end());

    // inserindo os nos no grafo final

    for(Node *node = getFirstNode(); node != nullptr; node = node->getNextNode()) {

        graphKruskal.insertNode(node->getId());    
    }

    // setando os pais

    //father();

    for (Node * node = getFirstNode() ; node !=nullptr; node = node->getNextNode())
    {
        node->setFather(node->getId());
    }

    // Union find algorithm

    pesoSolucao=0;
    for(Edge* & EdgeAux : listEdgesFinal)
    {
        if(!cicle(EdgeAux))
        {
            grafoKruskal.insertEdge(EdgeAux->getIdOrigem(), EdgeAux->getTargetId(), EdgeAux->getWeight());
            pesoSolucao+=EdgeAux->getWeight();

        }
    }
  
    // imprimir o resultado final (Grafo) em tela
    cout << "\nArvore Minima Geradora(Kruskal):\n";
    cout << "\nSomatorio dos pesos: " << pesoSolucao << endl;

    // imprimindo no arquivo
    output_file << 
}

Graph *agmPrim()
{
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

void Kruskal::preencheListaNos()
{

    for (Node *node=getFirstNode; node !=nullptr; node = node ->getNextEdge())
    {
        grafoKruskal.insertNode(node->getId());
        // grafoKruskal.inserirNo(i->getId());
    }
}

void Kruskal::imprimeFile(fstream &outputFile)
{
    outputFile<< grafoKruskal.imprimir();
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

    Node *aux1 = getNode(edge->getId());
    Node *aux2 = getNode(edge->getTargetId());

    if (find(aux1) == find(aux2))
        return true;
    else
        unites(aux1, aux2);
    return false;
}
