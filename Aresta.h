#ifndef TRACKS_H_INCLUDED
#define TRACKS_H_INCLUDED
#include "No.h"

using namespace std;

class Aresta
{
private:
    No *inicio;
    No *fim;
    void transitivoDireto_Aux(vector<int> *no, Aresta *aresta);

public:
    Aresta();
    ~Aresta();
    void adicionar(int id);
    void remover();
    bool vazia();
    void imprime();
    void transitivoDireto(string arq_saida, Aresta *aresta);
};

#endif // TRACKS_H_INCLUDED