#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <cmath>
#include "Aresta.h"
#include "No.h"

using namespace std;

Grafo *ler(ifstream &entrada)
{
    int ordem_grafo;
    int id_cauda;
    int id_cabeca;
    char aux;
    int aux2;
    float peso;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo, true, true);

    entrada >> ordem_grafo >> aux2;

    cout << "A ordem do grafo é: " << ordem_grafo << endl;

    while (entrada >> aux >> id_cabeca >> id_cauda)
        grafo->insereAresta(id_cauda, id_cabeca, 1);

    // grafo->imprime();

    return grafo;
}

int main(int argc, char const *argv[])
{
    ifstream entrada;
    ofstream saida;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo, true, true);

    if (argc != 6)
    {
        cout << "ERRO: Esperado: <nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 5;
    }


    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    if (entrada.is_open())
        grafo = ler(entrada);
    else
        cout << "Não foi possível abrir o arquivo " << argv[1] << endl;

    No *no = grafo->getPrimeiroNo();
    if (no == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return 0;
    }

    while (no != nullptr)
    {
        saida << "(" << no->getId() << ")" << endl;
        Aresta *aresta = no->getPrimeiraAresta();
        saida << " ";
        while (aresta != nullptr)
        {
            saida << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
            aresta = aresta->getProxAresta();
        }
        saida << endl;
        no = no->getProxNo();
    }

    ;

    /*for (auto &no : grafo->ordenaLista())
    {   
        cout<< "no: " << no.getId()<<" valor: "  << no.getValor() << endl;
        cout  << " " <<endl;
    }*/

    //grafo->randomizado(0.5,20);
    //cout<<"multigrafo: "<<grafo->ehMultiGrafo();
    grafo->fechoTransitivoIndireto(2);
    grafo->imprime();
    

    entrada.close();
    saida.close();
    delete grafo;

    return 0;
}