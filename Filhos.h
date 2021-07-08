#ifndef FILHOS_H_INCLUDED
#define FILHOS_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include <Arestas.h>
using namespace std;

class Filho
{
private:
    Aresta *aresta;
    Filho *proximo;

public:
    void setProximo(Filho *p) { proximo = p; };
};

#endif // FILHOS_H_INCLUDED