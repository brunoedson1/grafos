#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <vector>
#include <stack>

using namespace std;

class Grafo{
    private:
        No *primeiro_no;
        No *ultimo_no;
        bool digrafo;
        vector<No*> lista_nos;

    public:
        Grafo(bool digrafo);
        ~Grafo();

        void insereNoInicio(int id);
        void insereNoFim(int id);
        void insereAresta(int id_cauda, int id_cabeca, float peso);
        vector<No> listaNos();
        vector<int> guloso();
        vector<int> randomizado(float,int);
        vector<int> reativo(float,int);
        
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

        //vector<int> dijkstra(int id_calda, int id_cabeca);
        void caminhoMinimoFloyd(int origem, int destino);
        void caminhoMinimoDijkstra(int origem, int destino);

        void vizinhancaAberta(int id);
        void vizinhancaFechada(int id);
        bool independente(vector<No>);
        bool verificaVisit(bool visitados[], int n);
        Grafo subgrafoInduzido(const vector<int> &conjuntoVertices);
        void componentesFortementeConexas();
        void dfsOrdenacaoTopologica(No* no, vector<bool> &visitados, stack<int> &pilha);
        void dfsComponenteFortementeConexa(Grafo &grafo, int vertice, vector<bool> &visitados, vector<int> &componente);

        bool conectado();
        bool fortementeConectado();
        void dfsAlcancavel(Grafo &grafo, int vertice, vector<bool> &visitados);
        bool mesmoComponenteConexaoFraca();
        bool euleriano();

        vector<No*> getFechoTransitivoDireto(int idNo);
        vector<No*> getFechoTransitivoIndireto(int idNo);
};

#endif // GRAFO_H_INCLUDED
