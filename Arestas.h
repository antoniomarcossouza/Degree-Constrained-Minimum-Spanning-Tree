#ifndef ARESTAS_H_INCLUDED
#define ARESTAS_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include <Filhos.h>
using namespace std;

struct Aresta_struct
{
    int value;
};

class Aresta
{
private:
    Filho *primeiro;
    Aresta_struct no;
    Aresta *proximo;

public:
    void setProximo(Aresta *p) { proximo = p; };
};

#endif // ARESTAS_H_INCLUDED