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
    bool digrafo = false;
    char *e = new char;
    Grafo *grafo = new Grafo(digrafo);

    entrada >> ordem_grafo >> e;
    cout << "A ordem do grafo e: " << ordem_grafo << endl;

    while(entrada >> e >> id_cauda >> id_cabeca)
        grafo->insereAresta(id_cauda, id_cabeca, 0);

    grafo->imprime();

    delete e;
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
    

    // grafo->guloso();
    // grafo->randomizado(0.5,5);
    // grafo->reativo(0.5,5);
    // vector<No*> fecho_direto = grafo->getFechoTransitivoDireto(3);

    // // Exibir o fecho transitivo direto
    // cout << "Fecho transitivo direto do nó " << 5 << ":" << endl;
    // for (No* no : fecho_direto) {
    //     cout << no->getId() << " ";
    // }
    // cout << endl;

    // vector<No*> fecho_indireto = grafo->getFechoTransitivoIndireto(3);
    // // Exibir o fecho transitivo direto
    // cout << "Fecho transitivo direto do nó " << 5 << ":" << endl;
    // for (No* no : fecho_indireto) {
    //     cout << no->getId() << " ";
    // }
    // cout << endl;

    //grafo->caminhoMinimoFloyd(4, 6);

    // grafo->caminhoMinimoDijkstra(5, 3);

    // vector<int> conjuntoVertices = {1, 2, 3, 4};  // Conjunto de vértices informado pelo usuário
    // // Preencha o conjuntoVertices com os vértices desejados
    // cout << endl;
    // cout << "subgrafo induzido" << endl;
    // Grafo subgrafo = grafo->subgrafoInduzido(conjuntoVertices);
    // subgrafo.imprime();  // Imprime o subgrafo induzido

    // cout << "Componentes Fortemente Conexas:" << endl;
    // grafo->componentesFortementeConexas();

    cout << boolalpha << grafo->euleriano() << endl;


    entrada.close();
    saida.close();
    delete grafo;

    return 0;
}
