#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Grafo.h"
#include "Aresta.h"
#include "No.h"

using namespace std;

Grafo *ler(ifstream &entrada)
{
    int ordem_grafo;
    int id_cauda;
    int id_cabeca;
    bool digrafo = false;
    char *e = new char;
    Grafo *grafo = new Grafo(digrafo);

    entrada >> ordem_grafo >> e;
    cout << "A ordem do grafo e: " << ordem_grafo << endl
         << endl;

    while (entrada >> e >> id_cauda >> id_cabeca)
        grafo->insereAresta(id_cauda, id_cabeca, 0);

    grafo->imprime();

    int indice_no = 5;
    cout << "Grau do no " << indice_no << ": " << grafo->retornaGrauNo(indice_no) << endl
         << endl;

    int k = 4;

    if (grafo->verificaKRegularidade(k))
    {
        cout << "Grafo é " << k << "-regular" << endl << endl;
    }
    else
    {
        cout << "Grafo não é k-regular" << endl << endl;
    }

    if(grafo->grafoCompleto())
        cout << "Grafo completo" << endl << endl;
    else
        cout << "Grafo não é completo" << endl << endl;
        
    grafo->caminhoMinimoDijkstra(3,5);
    delete e;
    return grafo;
}

int main(int argc, char const *argv[])
{
    ifstream entrada;
    ofstream saida;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo);

    if (argc != 6)
    {
        cout << "ERRO: Esperado: <nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }

    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    if (entrada.is_open())
        grafo = ler(entrada);
    else
        cout << "Não foi possível abrir o arquivo " << argv[1] << endl;

    entrada.close();
    saida.close();

    grafo->guloso();
    grafo->randomizado(0.5, 5);
    grafo->reativo(0.5, 5);
    delete grafo;

    return 0;
}
