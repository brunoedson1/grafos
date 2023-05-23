#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "Aresta.h"
#include "No.h"

using namespace std;

Grafo *ler(ifstream &entrada){
    int ordem_grafo;
    int id_cauda;
    int id_cabeca;
    float peso;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo);

    entrada >> ordem_grafo;
    cout << "A ordem do grafo é: " << ordem_grafo << endl;

    while(entrada >> id_cauda >> id_cabeca >> peso)
        grafo->insereAresta(id_cauda, id_cabeca, peso);

    grafo->imprime();

    return grafo;
}

int main(int argc, char const *argv[]){
    ifstream entrada;
    ofstream saida;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo);

    if (argc != 3){
        cout << "ERRO: Esperado: <nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }

    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    if(entrada.is_open())
        grafo = ler(entrada);   
    else
        cout << "Não foi possível abrir o arquivo " << argv[1] << endl;
    
    
    cout << "Removendo no 2" << endl;
    grafo->removeNo(2);
    grafo->imprime();

    cout << "Removendo a aresta 1 - 2" << endl;
    grafo->removeAresta(1,2);
    cout << "Removendo a aresta 2 - 1" << endl;
    grafo->removeAresta(2,1);
    grafo->imprime();


    cout << "É nulo: " << boolalpha << grafo->nulo() << endl;

    cout << "É trivial: " << boolalpha << grafo->trivial() << endl;

    // cout << "É multigrafo: " << boolalpha << grafo->ehMultiGrafo() << endl;

    cout << "É bipartido: " << boolalpha << grafo->ehBipartido() << endl;

    cout << "É grafo completo: " << boolalpha << grafo->grafoCompleto() << endl;

    entrada.close();
    saida.close();
    delete grafo;

    return 0;
}