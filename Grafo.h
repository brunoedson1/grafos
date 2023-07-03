#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <unordered_map>
#include <unordered_set>
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
        bool ponderado_aresta;
        bool ponderado_vertice;
        int num_vertice; // getOrdem
        int num_aresta;// terminar contAresta
        vector<No*> lista_nos; 

    public:
        Grafo(bool digrafo, bool pVertice, bool pAresta);
        ~Grafo();

        void insereNoInicio(int id);
        void insereNoFim(int id);
        void insereAresta(int id_cauda, int id_cabeca, int peso);
        
        bool getDigrafo();
        int getGrauNo(int id);
        
        No* getPrimeiroNo(); 
        bool getKRegular(int k);
        int getGrauGrafo();
        int getOrdem();
        int contAresta();
        vector<No> listaNos();
        bool independente(vector<No> Nos);
        vector<int> guloso();
        vector<int> randomizado(float alpha, int numIter);
        vector<int> reativo(float alpha, int numIter);


        
        void removeNo(int id);
        void removeAresta(int id_cauda, int id_cabeca);
        void imprime(); 
        bool trivial(); 
        bool nulo();
        bool ehMultiGrafo();
        bool grafoCompleto();
        bool ehBipartido();
        bool comparaPeso(No &p,No &q);

        No *encontrarNo(int id);
        int *seqDeGraus();

        // vector<int> dijkstra(int id_calda, int id_cabeca);
        // vector<int> floydWarshall(int id_calda, int id_cabeca);

        // void vizinhancaAberta(int id);
        // void vizinhancaFechada(int id);
        void fechoTransitivoDireto(int id_no);
        void dfsFechoTransitivoDireto(No* no, unordered_map<No*, bool>& visitado);
        void fechoTransitivoIndireto(int id);
        void dfsFechoTransitivoIndireto(No* no, unordered_set<No*>& visitado);
        vector<No> ordenaLista();
};

#endif // GRAFO_H_INCLUDED