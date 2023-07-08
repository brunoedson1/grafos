#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Visitados
            {
                int id;
                bool visitado = false;
                int disctime;
                int low;
                int pai=NULL;
                bool articulacao = false;
            };

class Grafo{
    private:
        No *primeiro_no;
        No *ultimo_no;
        bool digrafo;
        vector<No*> lista_nos;
        void auxArticulacao(No*,vector<Visitados>& ,int&);
        

    public:
        Grafo(bool digrafo);
        ~Grafo();

        void insereNoInicio(int id);
        void insereNoFim(int id);
        void insereAresta(int id_cauda, int id_cabeca, float peso);

        vector<No> listaNos();
        bool independente(vector<No>);
        bool verificaVisit(bool visitados[], int n);
        vector<int> guloso();
        vector<int> adaptativo(float,int);
        vector<int> reativo(vector<float>,int,int);
        
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
        bool ehMultiGrafo();
        bool grafoCompleto();
        bool ehBipartido();

        No *encontrarNo(int id);
        int *seqDeGraus();

        void caminhoMinimoDijkstra(int origem, int destino);
         void caminhoMinimoFloyd(int origem, int destino);

        void vizinhancaAberta(int id);
        void vizinhancaFechada(int id);
        void fechoTransitivoDireto(int id_no);
        void dfsFechoTransitivoDireto(No* no, unordered_map<No*, bool>& visitado);
        void fechoTransitivoIndireto(int id);
        void dfsFechoTransitivoIndireto(No* no, unordered_set<No*>& visitado);
        void apresentarSubgrafoInduzido(const vector<int>& vertices);
        vector<int> encontrarCentroDoGrafo();
        vector<int> calcularPeriferiaDoGrafo();
        int calcularDistanciaMaxima(No& noInicial);

        void articulacao();
        void ponte();


        
};

#endif // GRAFO_H_INCLUDED
