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

void Aresta::adicionar(int id, int peso)
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

void Aresta::imprime(int id)
{
    cout << id;
    for (No *p = inicio; p != NULL; p = p->getProx())
    {
        cout << " -> " << p->getId();
    }
    cout << endl;
}

void Aresta::transitivoDireto(ofstream *arquivo_saida, Aresta *aresta)
{
    vector<int> no;

    for (No *p = inicio; p != NULL; p = p->getProx())
    {
        if (!std::count(no.begin(), no.end(), p->getId()))
        {
            no.push_back(p->getId());
            aresta[p->getId()].transitivoDireto_Aux(&no, aresta);
        }
    }

    for (int i = 0; i < no.size(); i++)
    {
        *arquivo_saida << no[i] << " ";
    }
}

void Aresta::transitivoDireto_Aux(vector<int> *no, Aresta *aresta)
{
    for (No *p = inicio; p != NULL; p = p->getProx())
    {
        if (!std::count(no->begin(), no->end(), p->getId()))
        {
            no->push_back(p->getId());
            aresta[p->getId()].transitivoDireto_Aux(no, aresta);
        }
    }
}

void Aresta::transitivoIndireto(ofstream *arquivo_saida, Aresta *aresta, int qntNo, int id)
{
    vector<int> no;

    for (int i = 1; i <= qntNo; i++)
    {
        aresta[i].transitivoIndireto_Aux(&no, aresta, id, i, qntNo);
    }

    for (int i = 0; i < no.size(); i++)
    {
        *arquivo_saida << no[i] << " ";
    }
}

void Aresta::transitivoIndireto_Aux(vector<int> *no, Aresta *aresta, int id, int i, int qntNo)
{
    for (No *p = inicio; p != NULL; p = p->getProx())
    {
        if (p->getId() == id && (!std::count(no->begin(), no->end(), i)))
        {
            no->push_back(i);
            for (int j = 1; j <= qntNo; j++)
            {
                aresta[j].transitivoIndireto_Aux(no, aresta, i, j, qntNo);
            }
        }
    }
}
