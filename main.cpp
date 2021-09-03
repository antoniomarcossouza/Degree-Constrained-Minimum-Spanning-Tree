#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"

using namespace std;

Graph *leitura(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    if (!graph->getWeightedEdge() && !graph->getWeightedNode())
    {

        while (input_file >> idNodeSource >> idNodeTarget)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 0);
        }
    }
    else if (graph->getWeightedEdge() && !graph->getWeightedNode())
    {

        float edgeWeight;

        while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }
    }
    else if (graph->getWeightedNode() && !graph->getWeightedEdge())
    {

        float nodeSourceWeight, nodeTargetWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    else if (graph->getWeightedNode() && graph->getWeightedEdge())
    {

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }

    return graph;
}

Graph *leituraInstancia(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int weight;
    int order;
    int numEdges;

    //Pegando a ordem do grafo
    input_file >> order >> numEdges;

    //Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo
    while (input_file >> idNodeSource >> idNodeTarget)
    {

        graph->insertEdge(idNodeSource, idNodeTarget, 0);
    }

    return graph;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Fecho transitivo direto deste vértice." << endl;
    cout << "[2] Fecho transitivo indireto deste vértice." << endl;
    cout << "[3] Caminho Mínimo entre dois vértices - Dijkstra" << endl;
    cout << "[4] Caminho Mínimo entre dois vértices - Floyd" << endl;
    cout << "[5] Árvore Geradora Mínima de Prim" << endl;
    cout << "[6] Árvore Geradora Mínima de Kruskal" << endl;
    cout << "[7] Árvore dada pela ordem de caminhamento em profundidade" << endl;
    cout << "[8] Grafo acíclico direcionado" << endl;
    cout << "[9] AGMRG" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, Graph *graph, ofstream &output_file)
{

    switch (selecao)
    {
    case 0:
    {
        cout << "Você está saindo." << endl;
        break;
    }
    case 1:
    {
        if (graph->getDirected())
        {
            int id;
            cout << "Digite o valor de um Id do vertice: ";
            cin >> id;
            graph->transitivoDireto(output_file, id);
        }
        else
            cout << "Esté grafo não é direcionado" << endl;
        break;
    }

    case 2:
    {
        if (graph->getDirected())
        {
            int id;
            cout << "Digite o valor de um Id do vertice: ";
            cin >> id;
            graph->transitivoIndireto(output_file, id);
        }
        else
            cout << "Esté grafo não é direcionado" << endl;
        break;
    }

    case 3:
    {
        if (!graph->getWeightedEdge())
        {
            cout << "O Algoritmo de Djikstra precisa de peso nas arestas!\n";
            break;
        }
        else
        {
            int id1;
            int id2;
            cout << "Digite o vertice inicial: " << endl;
            cin >> id1;
            cout << "Digite o vertice final: " << endl;
            cin >> id2;

            if (graph->getWeightedEdge())
            {
                graph->dijkstra(output_file, id1, id2);
            }
            break;
        }
    }

    case 4:
    {
        //Floyd-Warshall
        if (graph->getWeightedEdge() && graph->getDirected())
        {
            graph->floydWarshall(output_file);
        }
        else
        {
            cout << "Esté grafo não tem aresta ponderada ou direcionado!" << endl;
        }
        break;
    }

    case 5:
    {
        //Prim
        if (graph->getWeightedEdge() && !graph->getDirected())
        {
            graph->agmPrim(output_file);
        }
        else
        {
            cout << "Esté grafo não tem aresta ponderada ou direcionado!" << endl;
        }
        break;
    }

    case 6:
    {
        if (!graph->getDirected())
        {
            cout << "Erro: O Algoritmo de Kruskal exige que as arestas sejam ponderadas!" << endl;
            break;
        }
        cout << "Algoritmo de Kruskal selecionado!" << endl;

        graph->agmKruskal(graph, output_file);
        break;
    }
    case 7:
    {
        if (graph->getOrder() == 0)
        {
            cout << "Erro: O algoritmo de DFS precisa de vertices para executar!";
            break;
        }
        cout << "Busca em Profundidade selecionada!" << endl;
        int id;
        cout << "Infome um ID inicial: " << endl;
        cin >> id;

        graph->depthFirstSearch(id, output_file);
        break;
    }
    case 8:
    {
        if (graph->getDirected())
        {
            graph->topologicalSorting(output_file);
        }
        else
            cout << "O grafo não é acíclico direcionado." << endl;
        break;
    }
    case 9:
    {
        if (!graph->getDirected() && graph->getWeightedEdge())
        {
            int grau;
            cout << "Qual o menor grau da arvore geradora? " << endl;
            cin >> grau;
            graph->AGMRG_Guloso(grau);
        }
        else
        {
            cout << "O grafo precisa ser não direciona e ter peso nas arestas." << endl;
        }
        break;
    }
    default:
    {
        cout << " Error!!! invalid option!!" << endl;
    }
    }
}

int mainMenu(ofstream &output_file, Graph *graph)
{

    int selecao = 1;

    while (selecao != 0)
    {
        //system("clear");
        selecao = menu();

        if (output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6)
    {
        cout << "ERROR: Expecting: ./execGrupo15 <arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if (input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Graph *graph;

    if (input_file.is_open())
        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    else
        cout << "Unable to open " << argv[1];

    mainMenu(output_file, graph);

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}
