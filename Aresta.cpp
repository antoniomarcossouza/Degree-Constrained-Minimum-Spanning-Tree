#include "Aresta.h"
#include "No.h"

using namespace std;

Aresta::Aresta()
{
    inicio = NULL;
    fim = NULL;
}

Aresta::~Aresta()
{
    No *p = inicio;
    while (inicio != NULL)
    {
        inicio = p->getProx();
        delete p;
        p = inicio;
    }
    fim = NULL;
}

bool Aresta::vazia()
{
    if (inicio == NULL)
        return true;
    else
        return false;
}

void Aresta::adicionar(int id)
{
    No *p = new No();
    p->setId(id);
    p->setProximo(NULL);
    if (fim == NULL)
        inicio = p;
    else
        fim->setProximo(p);
    fim = p;
}

void Aresta::remover()
{
    No *p;
    if (inicio != NULL)
    {
        p = inicio;
        inicio = p->getProx();
        if (inicio == NULL)
            fim = NULL;
        delete p;
    }
}

void Aresta::imprime()
{
    for (No *p = inicio; p != NULL; p = p->getProx())
    {
        cout << " -> " << p->getId();
    }
    cout << endl;
}