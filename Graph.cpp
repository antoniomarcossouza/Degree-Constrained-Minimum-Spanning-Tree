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
        no->insertEdge(id, target_id, weight);
        no->incrementInDegree();
        no_alvo->incrementOutDegree();
    }
    else
    {
        Node *no = getNode(id);
        no->insertEdge(id, target_id, weight);
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


void Graph::depthFirstSearch(int v, ofstream &output_file)
{

    Node* node = this->first_node;                // no aponta para primeiro no  
    bool* visitados = new bool[getOrder()];       // vetor para verificar os nós visitados

    for(int i = 0; i < getOrder(); i++)     
    {
        node->setIndexSearch(i);                  // setando indice de busca dos nós
        visitados[i] = 0;                         // setando indice visitados como false
        node = node->getNextNode();               // percorrendo todos os nós
    }

    node = getNode(v);                            // buscando o nó no grafo

    if(node == nullptr) {                         // checando a presença do nó no grafo

        output_file << "Erro de busca: No não encontrado!" << endl;

    } else {
        
        depthFirstSearchAux(node, visitados,output_file);

    }

    delete [] visitados;                         // desalocando vetor de visitados
}

void Graph::breadthFirstSearch(int v, fstream &output_file)
{
}


void Graph::depthFirstSearchAux(Node* node, bool* visitados, ofstream &output_file)
{

    output_file << "\n*** Visitando o no '" <<  node->getId() << "':" <<  endl;
    visitados[node->getIndexSearch()] = 1;        // marcando como vistado 

    Edge *edge = node->getFirstEdge();

    while(edge != nullptr)
    {
        Node *aux = getNode(edge->getTargetId());

        if(visitados[aux->getIndexSearch()] == 0) {

            output_file << "(v) Avanco: (" << node->getId() << " , "  << aux->getId() << ")" << endl;

            depthFirstSearchAux(aux, visitados, output_file);
        } else {
            output_file << "(x) Retorno: (" << node->getId() << " , "  << aux->getId() << ")"<< endl;
        }
        edge = edge->getNextEdge();
    }
}

Graph *getVertexInduced(int *listIdNodes)
{
}

struct ListaArestaComparator
{
    // Compara 2 Arestas usando Peso
    bool operator ()( Edge* &edge1,  Edge* &edge2)
    {
        if(edge1->getWeight() == edge2->getWeight())
            return edge1 < edge2;
        return edge1->getWeight() < edge2->getWeight();
    }
};

Graph *Graph::agmKruskal(Graph *graph, ofstream &output_file)
{
    cout << "Chegou aqui 1!" << endl;
    Graph *graphKruskal = new Graph(graph->getOrder(), graph->getDirected(), graph->getWeightedEdge(), graph->getWeightedNode());
    
    // preenchendo lista de arestas 
    list<Edge*> listEdgesAux;
    list<Edge*> listEdgesFinal;
 
    for(Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        for(Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            listEdgesAux.push_back(edge);
        }
    }

    cout << "Chegou aqui 2!" << endl;
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

    cout << "Chegou aqui 3!" << endl;
    // ordenando a lista de arestas de acordo com o peso
    listEdgesFinal.sort(ListaArestaComparator());

    cout << "Chegou aqui 4!" << endl;
    // inserindo os nos no grafo final

    for(Node *node = getFirstNode(); node != nullptr; node = node->getNextNode()) {

        graphKruskal->insertNode(node->getId());    
    }

    // setando os pais
    cout << "Chegou aqui 5!" << endl;
    //father();

    for (Node * node = getFirstNode() ; node !=nullptr; node = node->getNextNode())
    {
        node->setFather(node->getId());
    }
    
    cout << "Chegou aqui 6!" << endl;
    // Union find algorithm

    int pesoSolucao=0;
    for(Edge* & EdgeAux : listEdgesFinal)
    {
        if(!cicle(EdgeAux))
        {
            graphKruskal->insertEdge(EdgeAux->getIdOrigem(), EdgeAux->getTargetId(), EdgeAux->getWeight());
            pesoSolucao+=EdgeAux->getWeight();

        }
    }
   
    // imprimir o resultado final (Grafo) em tela
    //output_file << "\nArvore Minima Geradora(Kruskal): " << endl;

    //graphKruskal->imprimeListaAdjacencia();


    // imprimindo no arquivo
    
    output_file << "Custo total: ";
    output_file << pesoSolucao << endl;
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

    Node *aux1 = getNode(edge->getIdOrigem());
    Node *aux2 = getNode(edge->getTargetId());

    if (find(aux1) == find(aux2))
        return true;
    else
        unites(aux1, aux2);
    return false;
}

void Graph::imprimeListaAdjacencia(ofstream &output_file)
{
    for(Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        output_file << "[" << node->getId() << "] --> ";
        for(Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            output_file << edge->getTargetId() << " --> " ;
        }
        
        output_file << endl;
    }
}
