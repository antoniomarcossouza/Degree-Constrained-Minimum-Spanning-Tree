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

void Aresta::transitivoDireto(string arq_saida, Aresta *aresta)
{
    ofstream arquivo_saida(arq_saida);

    if (!arquivo_saida.is_open())
    {
        cout << "Ocorreu um erro ao abrir o arquivo de saida!";
    }

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
        arquivo_saida << no[i] << " ";
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