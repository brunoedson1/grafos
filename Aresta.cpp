#include <iostream>
#include "Aresta.h"

using namespace std;

Aresta::Aresta(int id_cabeca, float peso){
    this->proxima_aresta = nullptr;
    this->id_cabeca = id_cabeca;
    //this->id_cauda = ;
    this->peso = peso;
}

// Aresta::Aresta(Aresta *proxima_aresta, int id_cabeca, int id_cauda, float peso){
//     this->proxima_aresta = nullptr;
//     this->id_cabeca = id_cabeca;
//     this->id_cauda = id_cauda;
//     this->peso = peso;
// }

Aresta::~Aresta(){
    if(this->proxima_aresta != nullptr){
        delete this->proxima_aresta;
        this->proxima_aresta = nullptr;
    }
}

float Aresta::getPeso(){
    return this->peso;
}

// int Aresta::getIdCauda(){
//     return id_cauda;
// }

int Aresta::getIdCabeca(){
    return this->id_cabeca;
}

Aresta *Aresta::getProxAresta(){
    return this->proxima_aresta;
}

void Aresta::setPeso(float peso) {
    this->peso = peso;
}

// void Aresta::setIdCauda(int id) {
//     this->id_cauda = id;
// }

void Aresta::setIdCabeca(int id) {
    this->id_cabeca = id;
}

void Aresta::setProxAresta(Aresta *aresta){
    this->proxima_aresta = aresta;
}