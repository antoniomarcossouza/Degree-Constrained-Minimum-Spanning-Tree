#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    fstream arquivo(argv[1]);

    string line;
    if (arquivo.is_open())
    {
        while (!arquivo.eof())
        {
            getline(arquivo, line);
        }
    }

    return 0;
}