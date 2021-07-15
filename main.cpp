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

    ifstream arquivo_entrada(arq_entrada);

    if (!arquivo_entrada.is_open())
    {
        cout << "Ocorreu um erro ao abrir o arquivo de entrada!";
        exit(1);
    }

    string line;
    getline(arquivo_entrada, line);

    int qntNo = stoi(line);
    Aresta *aresta = new Aresta[qntNo + 1];

    int dado1, dado2;
    while (arquivo_entrada >> dado1 >> dado2)
    {
        aresta[dado1].adicionar(dado2);
        if (Opc_Direc == 0)
            aresta[dado2].adicionar(dado1);
    }

    for (int i = 1; i <= qntNo; i++)
    {
        cout << i;
        aresta[i].imprime();
    }

    int option;
    cout << "**********************" << endl;
    cout << "Trabalho de Grafos" << endl;
    cout << "----------------------" << endl;
    cout << "1- Transitivo Direto" << endl;
    cout << "2- " << endl;
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
            aresta[id].transitivoDireto(arq_saida, aresta);
        }
        else
        {
            cout << "Esté grafo não é direcionado" << endl;
        }
        break;
    }

    delete[] aresta;
    return 0;
}