#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "Aresta.h"

using namespace std;

int main(int argc, char *argv[])
{
    string arq_entrada = argv[1];
    string arq_saida = argv[2];
    int Opc_Direc = stoi(argv[3]);
    int Opc_Peso_Aresta = stoi(argv[4]);

    ifstream arquivo_entrada(arq_entrada);
    ofstream arquivo_saida(arq_saida);

    if (!arquivo_entrada.is_open())
    {
        cout << "Ocorreu um erro ao abrir o arquivo de entrada!";
        exit(1);
    }

    if (!arquivo_saida.is_open())
    {
        cout << "Ocorreu um erro ao abrir o arquivo de saida!";
    }

    string line;
    getline(arquivo_entrada, line);

    int qntNo = stoi(line);
    Aresta *aresta = new Aresta[qntNo + 1];

    int dado1, dado2, dado3;
    if (Opc_Peso_Aresta == 0)
    {
        while (arquivo_entrada >> dado1 >> dado2)
        {
            aresta[dado1].adicionar(dado2);
            if (Opc_Direc == 0)
                aresta[dado2].adicionar(dado1);
        }
    }
    else
    {
        while (arquivo_entrada >> dado1 >> dado2 >> dado3)
        {
            aresta[dado1].adicionar(dado2, dado3);
            if (Opc_Direc == 0)
                aresta[dado2].adicionar(dado1, dado3);
        }
    }

    int option;
    cout << "**********************" << endl;
    cout << "Trabalho de Grafos" << endl;
    cout << "----------------------" << endl;
    cout << "1- Transitivo Direto" << endl;
    cout << "2- Transitivo Indireto" << endl;
    cout << "3- " << endl;
    cout << "4- " << endl;
    cout << "5- " << endl;
    cout << "6- " << endl;
    cout << "7- " << endl;
    cout << "8- " << endl;
    cout << "**********************" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
        if (Opc_Direc == 1)
        {
            int id;
            cout << "Digite o valor de um Id do vertice: ";
            cin >> id;
            aresta[id].transitivoDireto(&arquivo_saida, aresta);
        }
        else
        {
            cout << "Esté grafo não é direcionado" << endl;
        }
        break;
    case 2:
        if (Opc_Direc == 1)
        {
            int id;
            cout << "Digite o valor de um Id do vertice: ";
            cin >> id;
            aresta[id].transitivoIndireto(&arquivo_saida, aresta, qntNo, id);
        }
        else
        {
            cout << "Esté grafo não é direcionado" << endl;
        }
        break;
    }

    delete[] aresta;
    arquivo_saida.close();
    arquivo_entrada.close();
    return 0;
}