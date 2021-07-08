#ifndef TRACKS_H_INCLUDED
#define TRACKS_H_INCLUDED
#include "No.h"

using namespace std;

class Aresta
{
private:
    No *inicio;
    No *fim;

public:
    Aresta();
    ~Aresta();
    void adicionar(int id);
    void remover();
    bool vazia();
    void imprime();
};

#endif // TRACKS_H_INCLUDED