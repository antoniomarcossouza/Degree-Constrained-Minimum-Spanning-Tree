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
    number_edges++;
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

bool Graph::searchPosition(float x, float y)
{
    if (this->first_node != nullptr)
    {
        for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
            if (aux->getX() == x && aux->getY() == y)
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

float Graph::dijkstra(ofstream &output_file, int idSource, int idTarget)
{
    // vetores

    //  Graph *graph = new Graph(this->getOrder(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());new Graph()

    int *nodes = new int[getOrder()];
    int *dist = new int[getOrder()];
    int *ant = new int[getOrder()];
    int *aux = new int[getOrder()];

    // setando indice de busca de cada no
    int counter = 0;
    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        node->setIndexSearch(counter);
        counter++;
    }

    // O grafo agora passa a ter seu primeiro no correspondente ao idSource
    this->first_node->setIdNode(idSource);

    // agora apontando para o novo primeiro no(idSource)
    Node *p = this->first_node;

    // percorrendo todos os nos
    while (p != nullptr)
    {
        // definindo que cada vertice terá seu proprio indice de busca e posicao no vetor de nodes
        nodes[p->getIndexSearch()] = p->getId();

        // verificando a igualdade de nos
        if (p->getId() == this->first_node->getId())
        {
            // atribuindo distancia 0 a nodes que se correspondem
            dist[p->getIndexSearch()] = 0;
            ant[p->getIndexSearch()] = p->getId();
        }
        else
        {
            // atribuindo infinito para os nodes que não pertence ao seu conjunto de vizinhos
            dist[p->getIndexSearch()] = INF;
            ant[p->getIndexSearch()] = -1;
        }

        aux[p->getIndexSearch()] = -1;
        p = p->getNextNode();
    }

    p = this->first_node;
    Edge *visinhos;

    int numeroNosaux = getOrder();
    int menor;

    while (numeroNosaux > 0)
    {
        menor = findIndice(dist, aux, getOrder());

        if (aux[menor] == -1)
        {
            aux[menor] = 1;

            visinhos = getNode(nodes[menor])->getFirstEdge();

            while (visinhos != nullptr)
            {
                Node *aux = getNode(visinhos->getTargetId());
                if (dist[menor] + visinhos->getWeight() < dist[aux->getIndexSearch()])
                {
                    dist[aux->getIndexSearch()] = dist[menor] + visinhos->getWeight();
                    ant[aux->getIndexSearch()] = nodes[menor];
                }
                visinhos = visinhos->getNextEdge();
            }
        }
        numeroNosaux--;
    }
    output_file << "Distância mínima entre " << idSource << " e " << idTarget << endl;

    for (int i = 0; i < getOrder(); i++)
    {
        if (i == getNode(idTarget)->getIndexSearch())
        {
            output_file << nodes[getNode(i)->getId()] << " = " << dist[i] << endl;
        }
    }
    return 0;
}

int Graph::findIndice(int *dist, int *aux, int tam)
{
    int menor;
    int indice = 0;

    for (int i = 0; i < tam; i++)
    {
        if (aux[i] == -1)
            menor = dist[i];
    }

    for (int i = 0; i < tam; i++)
    {
        if (aux[i] == -1)
        {
            if (dist[i] < menor)
            {
                menor = dist[i];
                indice = i;
            }
        }
    }

    return indice;
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

void Graph::depthFirstSearch(int v, ofstream &output_file)
{

    Node *node = this->first_node;        // no aponta para primeiro no
    bool *visited = new bool[getOrder()]; // vetor para verificar os nós visited

    for (int i = 0; i < getOrder(); i++)
    {
        node->setIndexSearch(i);    // setando indice de busca dos nós
        visited[i] = 0;             // setando indice visited como false
        node = node->getNextNode(); // percorrendo todos os nós
    }

    node = getNode(v); // buscando o nó no grafo

    if (node == nullptr)
    { // checando a presença do nó no grafo

        output_file << "Erro de busca: No não encontrado!" << endl;
    }
    else
    {

        depthFirstSearchAux(node, visited, output_file);
    }

    delete[] visited; // desalocando vetor de visited
}

void Graph::breadthFirstSearch(int v, fstream &output_file)
{
}

void Graph::depthFirstSearchAux(Node *node, bool *visited, ofstream &output_file)
{

    output_file << "\n*** Visitando o no '" << node->getId() << "':" << endl;
    visited[node->getIndexSearch()] = 1; // marcando como vistado

    Edge *edge = node->getFirstEdge();

    while (edge != nullptr)
    {
        Node *aux = getNode(edge->getTargetId());

        if (visited[aux->getIndexSearch()] == 0)
        {

            output_file << "(v) Avanco: (" << node->getId() << " , " << aux->getId() << ")" << endl;

            depthFirstSearchAux(aux, visited, output_file);
        }
        else
        {
            output_file << "(x) Retorno: (" << node->getId() << " , " << aux->getId() << ")" << endl;
        }
        edge = edge->getNextEdge();
    }
}

Graph *getVertexInduced(int *listIdNodes)
{
    return 0;
}

struct ListaArestaComparator
{
    // Compara 2 Arestas usando Peso
    bool operator()(Edge *&edge1, Edge *&edge2)
    {
        if (edge1->getScore() == edge2->getScore())
            return edge1 < edge2;
        return edge1->getScore() < edge2->getScore();
    }
};

Graph *
Graph::agmKruskal(Graph *graph, ofstream &output_file)
{
    Graph *graphKruskal = new Graph(graph->getOrder(), graph->getDirected(), graph->getWeightedEdge(), graph->getWeightedNode());

    // preenchendo lista de arestas
    list<Edge *> listEdgesAux;
    list<Edge *> listEdgesFinal;

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            edge->setScore(edge->getWeight());
            listEdgesAux.push_back(edge);
        }
    }

    // inserindo em lista final elementos que nÃ£o se repetem
    int contador;
    for (Edge *&EdgeAux : listEdgesAux)
    {
        contador = 0;
        for (Edge *&EdgeAux2 : listEdgesFinal)
        {
            /*if(EdgeAux2->getIdAlvo() == EdgeAux->getIdOrigem()
                    &&   EdgeAux2->getIdOrigem() == EdgeAux->getIdAlvo())*/
            if (EdgeAux2->getTargetId() == EdgeAux->getIdOrigem() && EdgeAux2->getIdOrigem() == EdgeAux->getTargetId())
                break;
            else
                contador++;
        }
        if (contador == listEdgesFinal.size())
            listEdgesFinal.push_front(EdgeAux);
    }

    // ordenando a lista de arestas de acordo com o peso
    listEdgesFinal.sort(ListaArestaComparator());

    // inserindo os nos no grafo final

    for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
    {

        graphKruskal->insertNode(node->getId());
    }

    // setando os pais
    //father();

    for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
    {
        node->setFather(node->getId());
    }

    // Union find algorithm

    int custoTotalArvore = 0;
    for (Edge *&EdgeAux : listEdgesFinal)
    {
        if (!cicle(EdgeAux))
        {
            graphKruskal->insertEdge(EdgeAux->getIdOrigem(), EdgeAux->getTargetId(), EdgeAux->getWeight());
            custoTotalArvore += EdgeAux->getWeight();
        }
    }

    // imprimir o resultado final (Grafo) em tela
    output_file << graphKruskal->imprimir();
}

void Graph::agmPrim(ofstream &output_file)
{
    int *custo = new int[this->order];
    int *proximo = new int[this->order];
    bool *visited = new bool[this->order];

    int **matriz = new int *[this->order];

    for (int i = 0; i < this->order; i++)
    {
        matriz[i] = new int[this->order];
        for (int j = 0; j < this->order; j++)
            matriz[i][j] = INF;
    }

    for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
    {
        if (aux->getFirstEdge() != nullptr)
        {
            for (Edge *aux2 = aux->getFirstEdge(); aux2 != nullptr; aux2 = aux2->getNextEdge())
            {
                matriz[aux->getId() - this->first_node->getId() != 0 ? 1 : 0][aux2->getTargetId() - this->first_node->getId() != 0 ? 1 : 0] = aux2->getWeight();
                matriz[aux2->getTargetId() - this->first_node->getId() != 0 ? 1 : 0][aux->getId() - this->first_node->getId() != 0 ? 1 : 0] = aux2->getWeight();
            }
        }
    }

    visited[0] = true;
    for (int i = 1; i < this->order; i++)
    {
        custo[i] = matriz[0][i];
        proximo[i] = 0;
        visited[i] = false;
    }

    int peso = 0;
    int arestas = 0;
    int vert = 0;

    output_file << "graph imprimir {" << endl;

    for (int i = 0; i < this->order; i++)
    {
        int min = INF;
        int k = 1;

        for (int j = 0; j < this->order; j++)
        {
            if (custo[j] < min && !visited[j])
            {
                min = custo[j];
                k = j;
            }
        }

        if (k == 1 && min == INF)
            break;
        else
            peso += min;

        if (vert == 0)
            output_file << "    " << this->order - (this->first_node->getId() == 0 ? 1 : 0) << " -- " << k - (this->first_node->getId() == 0 ? 1 : 0) << ";" << endl;
        else if (k == 0)
            output_file << "    " << vert - (this->first_node->getId() == 0 ? 1 : 0) << " -- " << this->order << ";" << endl;
        else
            output_file << "    " << vert - (this->first_node->getId() == 0 ? 1 : 0) << " -- " << k - (this->first_node->getId() == 0 ? 1 : 0) << ";" << endl;

        vert = k;
        visited[k] = true;
        arestas++;
        for (int j = 1; j < this->order; j++)
        {
            if ((matriz[k][j] < custo[j]) && (!visited[j]))
            {
                custo[j] = matriz[k][j];
                proximo[j] = k;
            }
        }
    }

    output_file << "}" << endl;

    for (int i = 0; i < this->order; i++)
        delete[] matriz[i];
    delete[] matriz;
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

string Graph::imprimir()
{
    stringstream stream;

    if (directed)
        stream << "digraph imprimir {" << endl;
    else
        stream << "graph imprimir {" << endl;

    for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
    {
        stream << "    " << aux->getId() << ";" << endl;
    }

    for (Node *no = this->first_node; no != nullptr; no = no->getNextNode())
    {
        for (Edge *aresta = no->getFirstEdge(); aresta != nullptr; aresta = aresta->getNextEdge())
        {
            if (this->directed)
                stream << "    " << no->getId() << " -> " << aresta->getTargetId() << ";" << endl;
            else
                stream << "    " << no->getId() << " -- " << aresta->getTargetId() << ";" << endl;
        }
    }

    stream << "}" << endl;

    return stream.str();
}

void Graph::setId(int id)
{
    Node *n = this->first_node;

    while (n != nullptr)
    {
        if (n->getId() == id)
            break;
        n = n->getNextNode();
    }

    if (n != nullptr)
        n->setIdNode(id);
    else
        cout << "No nao encontrado!";
}

void Graph::AGMRG_Guloso(int grau)
{
    Graph *AGMRG = new Graph(getOrder(), getDirected(), getWeightedEdge(), getWeightedNode());

    list<Edge *> listEdgesAux;
    list<Edge *> listEdgesFinal;

    clock_t inicio = clock();
    float fator_penalizador1 = (2) + (((float) rand()) / (float) RAND_MAX) * (4);
    float fator_penalizador2 = (2) + (((float) rand()) / (float) RAND_MAX) * (4);

    for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
    {
        for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
        {
            edge->setScore(edge->getWeight());
            listEdgesAux.push_back(edge);
        }
    }

    int contador;
    for (Edge *&EdgeAux : listEdgesAux)
    {
        contador = 0;
        for (Edge *&EdgeAux2 : listEdgesFinal)
        {
            if (EdgeAux2->getTargetId() == EdgeAux->getIdOrigem() && EdgeAux2->getIdOrigem() == EdgeAux->getTargetId())
                break;
            else
                contador++;
        }
        if (contador == listEdgesFinal.size())
            listEdgesFinal.push_front(EdgeAux);
    }

    listEdgesFinal.sort(ListaArestaComparator());

    for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
        AGMRG->insertNode(node->getId());

    for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
        node->setFather(node->getId());

    long long custoTotalArvore = 0;
    for (Edge *&EdgeAux : listEdgesFinal)
    {
        if (AGMRG->getNode(EdgeAux->getTargetId())->getInDegree() < grau)
        {
            if (!cicle(EdgeAux))
            {
                AGMRG->insertEdge(EdgeAux->getIdOrigem(), EdgeAux->getTargetId(), EdgeAux->getWeight());
                custoTotalArvore += EdgeAux->getWeight();
            }
        }
    }

    clock_t fim = clock();
    cout << AGMRG->imprimir();
    cout << "Tempo: " << fim - inicio << " ms" << endl;
    cout << "Custo: " <<  custoTotalArvore << endl;
}

void Graph::AGMRG_GulosoRandomizado(int grau)
{
    Graph *AGMRG_Best = new Graph(getOrder(), getDirected(), getWeightedEdge(), getWeightedNode());
    long long menorCusto = 0;

    clock_t inicio = clock();

    for (int i = 0; i < 100; i++)
    {
        Graph *AGMRG = new Graph(getOrder(), getDirected(), getWeightedEdge(), getWeightedNode());
        list<Edge *> listEdgesAux;
        list<Edge *> listEdgesFinal;

        float fator_penalizador1 = (2) + (((float) rand()) / (float) RAND_MAX) * (4);
        float fator_penalizador2 = (2) + (((float) rand()) / (float) RAND_MAX) * (4);

        for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
        {
            for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
            {
                
                edge->setScore(fator_penalizador1 * edge->getWeight() + fator_penalizador2 * getNode(edge->getTargetId())->getInDegree());

                listEdgesAux.push_back(edge);
            }
        }
        int contador;
        for (Edge *&EdgeAux : listEdgesAux)
        {
            contador = 0;
            for (Edge *&EdgeAux2 : listEdgesFinal)
            {
                if (EdgeAux2->getTargetId() == EdgeAux->getIdOrigem() && EdgeAux2->getIdOrigem() == EdgeAux->getTargetId())
                    break;
                else
                    contador++;
            }
            if (contador == listEdgesFinal.size())
                listEdgesFinal.push_front(EdgeAux);
        }

        listEdgesFinal.sort(ListaArestaComparator());

        for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
            AGMRG->insertNode(node->getId());

        for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
            node->setFather(node->getId());

        long long custoTotalArvore = 0;
        for (Edge *&EdgeAux : listEdgesFinal)
        {
            if (!cicle(EdgeAux) && (AGMRG->getNode(EdgeAux->getTargetId())->getInDegree() < grau))
            {
                AGMRG->insertEdge(EdgeAux->getIdOrigem(), EdgeAux->getTargetId(), EdgeAux->getWeight());
                custoTotalArvore += EdgeAux->getWeight();
            }
        }

        if (AGMRG_Best->first_node == nullptr)
        {
            AGMRG_Best = AGMRG;
            menorCusto = custoTotalArvore;
        }
        else
        {
            if (custoTotalArvore < menorCusto)
            {
                AGMRG_Best = AGMRG;
                menorCusto = custoTotalArvore;
            }
        }
    }

    clock_t fim = clock();
    cout << AGMRG_Best->imprimir();
    cout << "Tempo: " << fim - inicio << " ms" << endl;
    cout << "Custo minimo encontrado: " << menorCusto << endl;
}

void Graph::AGMRG_GulosoRandomizadoReativo(int grau)
{
   Graph *AGMRG_Best = new Graph(getOrder(), getDirected(), getWeightedEdge(), getWeightedNode());
    int menorCusto = 0;

    clock_t inicio = clock();

    bool acrescentando = true;

    for (int i = 0; i < 100; i++)
    {
        Graph *AGMRG = new Graph(getOrder(), getDirected(), getWeightedEdge(), getWeightedNode());
        list<Edge *> listEdgesAux;
        list<Edge *> listEdgesFinal;

        float fator_penalizador1 = (2) + (((float) rand()) / (float) RAND_MAX) * (4);
        float fator_penalizador2 = (2) + (((float) rand()) / (float) RAND_MAX) * (4);

        for (Node *node = this->first_node; node != nullptr; node = node->getNextNode())
        {
            for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
            {
                
                edge->setScore(fator_penalizador1 * edge->getWeight() + fator_penalizador2 * getNode(edge->getTargetId())->getInDegree());

                listEdgesAux.push_back(edge);
            }
        }
        int contador;
        for (Edge *&EdgeAux : listEdgesAux)
        {
            contador = 0;
            for (Edge *&EdgeAux2 : listEdgesFinal)
            {
                if (EdgeAux2->getTargetId() == EdgeAux->getIdOrigem() && EdgeAux2->getIdOrigem() == EdgeAux->getTargetId())
                    break;
                else
                    contador++;
            }
            if (contador == listEdgesFinal.size())
                listEdgesFinal.push_front(EdgeAux);
        }

        listEdgesFinal.sort(ListaArestaComparator());

        for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
            AGMRG->insertNode(node->getId());

        for (Node *node = getFirstNode(); node != nullptr; node = node->getNextNode())
            node->setFather(node->getId());

        double custoTotalArvore = 0;
        for (Edge *&EdgeAux : listEdgesFinal)
        {
            if (!cicle(EdgeAux) && (AGMRG->getNode(EdgeAux->getTargetId())->getInDegree() < grau))
            {
                AGMRG->insertEdge(EdgeAux->getIdOrigem(), EdgeAux->getTargetId(), EdgeAux->getWeight());
                custoTotalArvore += EdgeAux->getWeight();
            }
        }

        if (AGMRG_Best->first_node == nullptr)
        {
            fator_penalizador1 += (2) + (((float) rand()) / (float) RAND_MAX) * (4);
            fator_penalizador2 += (2) + (((float) rand()) / (float) RAND_MAX) * (4);

            AGMRG_Best = AGMRG;
            for (Node *node = AGMRG_Best->first_node; node != nullptr; node = node->getNextNode())
            {
                for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
                {
                    menorCusto += edge->getWeight();
                }
            }
        }
        else
        {
            
            int custo = 0;
            for (Node *node = AGMRG->first_node; node != nullptr; node = node->getNextNode())
            {
                for (Edge *edge = node->getFirstEdge(); edge != nullptr; edge = edge->getNextEdge())
                {
                    custo += edge->getWeight();
                }
            }
            if (custo < menorCusto)
            {
                if(acrescentando) {

                    fator_penalizador1 += (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                    fator_penalizador2 += (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                
                } else {
                
                    fator_penalizador1 -= (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                    fator_penalizador2 -= (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                }

                AGMRG_Best = AGMRG;
                menorCusto = custo;
            } else {

                if(acrescentando) {
                    acrescentando = false;
                    fator_penalizador1 -= (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                    fator_penalizador2 -= (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                
                } else {
                    acrescentando = true;
                    fator_penalizador1 += (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                    fator_penalizador2 += (2) + (((float) rand()) / (float) RAND_MAX) * (4);
                }
            }
        }
    }

    clock_t fim = clock();
    cout << AGMRG_Best->imprimir();
    cout << "Tempo: " << fim - inicio << " ms" << endl;
    cout << "Custo minimo encontrado: " << menorCusto << endl;
}