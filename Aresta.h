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
    void transitivoIndireto_Aux(vector<int> *no, Aresta *aresta, int id, int i, int qntNo);

public:
    Aresta();
    ~Aresta();
    void adicionar(int id);
    void adicionar(int id, int peso);
    void remover();
    bool vazia();
    void imprime(int id);
    void transitivoDireto(ofstream *arquivo_saida, Aresta *aresta);
    void transitivoIndireto(ofstream *arquivo_saida, Aresta *aresta, int qntNo, int id);
};

#endif // TRACKS_H_INCLUDED