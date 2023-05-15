#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

class Aresta{
    private:
        Aresta *proxima_aresta;
        float peso;
        int id_cauda;
        int id_cabeca;
        
    public:
        Aresta(int id_cauda, int id_cabeca, float peso);
        //Aresta(Aresta *proxima_aresta, int id_cabeca, int id_cauda, float peso);
        ~Aresta();

        float getPeso();
        int getIdCauda();
        int getIdCabeca();
        Aresta *getProxAresta();
        
        void setPeso(float peso);
        void setIdCauda(int id);
        void setIdCabeca(int id);
        void setProxAresta(Aresta *aresta);
};

#endif // ARESTA_H_INCLUDED