#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include <iostream>
#include "Aresta.h"

using namespace std;

class No{
    private:
        Aresta *primeira_aresta;
        No *proximo_no;
        int id;
        int grau;
        int grau_entrada;
        int grau_saida;
        int peso;

    public:
        No();
        No(int id);
        ~No();

        Aresta *getPrimeiraAresta();
        int getGrauNo();
        int getEntrada();
        int getSaida();
        int getId();
        No *getProxNo();
        int getPeso();
        void setPeso(int);

        void setId(int id);
        void setProxNo(No *proximo);
        void setGrau(int grau);
        void setEntrada(int grau);
        void setSaida(int grau);

        void insereAresta(int id_cauda, int id_cabeca, float peso);
        Aresta *buscaAresta(int id_cauda, int id_cabeca);
        bool removeAresta(int id_cauda, int id_cabeca);
        

};

#endif
