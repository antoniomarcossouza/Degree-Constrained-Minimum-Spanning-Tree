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
    ifstream arquivo_entrada(argv[1]);

    if (!arquivo_entrada.is_open())
    {
        cout << "Ocorreu um erro ao abrir o arquivo de entrada!";
        exit(1);
    }

    string line;
    getline(arquivo_entrada, line);

    int qntNo = stoi(line);
    Aresta *aresta = new Aresta[qntNo+1];

    int dado1, dado2;
    while (arquivo_entrada >> dado1 >> dado2)
    {
        aresta[dado1].adicionar(dado2);
    }

    for (int i = 1; i <= qntNo; i++)
    {
        cout << i;
        aresta[i].imprime();
    }

    return 0;
}