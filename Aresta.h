#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

class Aresta{
    private:
        Aresta *proxima_aresta;
        int peso;
        //int id_cauda;
        int id_cabeca;
        
    public:
        Aresta(int id_cabeca, int peso);
        //Aresta(Aresta *proxima_aresta, int id_cabeca, int id_cauda, float peso);
        ~Aresta();

        int getPeso();
        //int getIdCauda();
        int getIdCabeca();
        Aresta *getProxAresta();
        
        void setPeso(float peso);
        //void setIdCauda(int id);
        void setIdCabeca(int id);
        void setProxAresta(Aresta *aresta);
};

#endif // ARESTA_H_INCLUDED