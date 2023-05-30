#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <vector>

using namespace std;

class Grafo{
    private:
        No *primeiro_no;
        No *ultimo_no;
        bool digrafo;
        bool ponderado_aresta;// implementar
        bool ponderado_vertice;// implementar
        int num_vertice; // implementar
        int num_aresta;// implementar
        vector<No*> lista_nos; 

    public:
        Grafo(bool digrafo, bool pVertice, bool pAresta);
        ~Grafo();

        void insereNoInicio(int id);
        void insereNoFim(int id);
        void insereAresta(int id_cauda, int id_cabeca, float peso);
        
        bool getDigrafo();
        int getGrauNo(int id); 
        No* getPrimeiroNo(); 
        bool getKRegular(int k);
        int getGrauGrafo();
        int getOrdem();
        
        void removeNo(int id);
        void removeAresta(int id_cauda, int id_cabeca);
        void imprime(); 
        bool trivial(); 
        bool nulo();
        //bool ehMultiGrafo();
        bool grafoCompleto();
        bool ehBipartido();

        No *encontrarNo(int id);
        int *seqDeGraus();

        // vector<int> dijkstra(int id_calda, int id_cabeca);
        // vector<int> floydWarshall(int id_calda, int id_cabeca);

        // void vizinhancaAberta(int id);
        // void vizinhancaFechada(int id);
};

#endif // GRAFO_H_INCLUDED