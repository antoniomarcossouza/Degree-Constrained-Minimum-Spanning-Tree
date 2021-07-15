#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class No
{
private:
    int id;
    int peso = 0;
    No *proximo;

public:
    void setProximo(No *p) { proximo = p; };
    No *getProx() { return proximo; };

    int setId(int id) { this->id = id; };
    int getId() { return id; };

    int setPeso(int peso) { this->peso = peso; };
    int getPeso() { return peso; };
};

#endif // NO_H_INCLUDED