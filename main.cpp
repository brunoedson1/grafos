#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Grafo.h"
//#include "Grafo.cpp"
#include "Aresta.h"
//#include "Aresta.cpp"
#include "No.h"
//#include "No.cpp"

using namespace std;

Grafo *ler(ifstream &entrada){
    int ordem_grafo;
    int id_cauda;
    int id_cabeca;
    float peso;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo, true, true);

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
    Grafo *grafo = new Grafo(digrafo, true, true);

    if (argc != 3){
        cout << "ERRO: Esperado: <nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 5;
    }

    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    if(entrada.is_open())
        grafo = ler(entrada);   
    else
        cout << "Não foi possível abrir o arquivo " << argv[1] << endl;

    No *no = grafo->getPrimeiroNo();
    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return 0;
    }

    while (no != nullptr){
        saida << "(" << no->getId() << ")" << endl;
        Aresta *aresta = no->getPrimeiraAresta();
        saida << " ";
        while (aresta != nullptr ){
            saida << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
            aresta = aresta->getProxAresta();
        }
        saida << endl;
        no = no->getProxNo();
    }
    
    entrada.close();
    saida.close();
    delete grafo;

    return 0;
}