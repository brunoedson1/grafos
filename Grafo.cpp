#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <string>
#include "Grafo.h"

using namespace std;

Grafo::Grafo(bool digrafo, bool pVertice, bool pAresta)
{
    this->digrafo = digrafo;
    this->primeiro_no = nullptr;
    this->ultimo_no = nullptr;
    ponderado_vertice = pVertice;
    ponderado_aresta = pAresta;
    num_vertice = this->getOrdem();
}

Grafo::~Grafo()
{
}

void Grafo::insereNoInicio(int id, int peso){
    No *no = new No(id, peso); 
    no->setProxNo(this->primeiro_no);
    this->primeiro_no = no;
}

void Grafo::insereNoFim(int id, int peso){
    No *no = new No(id, peso);
    no->setProxNo(nullptr);

    if(this->primeiro_no == nullptr){
        this->primeiro_no = no;
        this->ultimo_no = no;
    }
    else{
        this->ultimo_no->setProxNo(no);
        this->ultimo_no = no;
    }
}

void Grafo::insereAresta(int id_cauda, int id_cabeca, int peso){
    No *cauda = encontrarNo(id_cauda);
    No *cabeca = encontrarNo(id_cabeca);

    if(cauda == nullptr){
        this->insereNoFim(id_cauda, peso);
        cauda = encontrarNo(id_cauda); //atualiza cauda após a inserção
    }
    if(cabeca == nullptr){
        this->insereNoFim(id_cabeca, peso);
        cabeca = encontrarNo(id_cabeca); //atualiza cabeça após a inserção
    }

    cauda->insereAresta(id_cabeca, peso);

    if(!this->getDigrafo()){
        cabeca->insereAresta(id_cauda, peso);
        cauda->setGrau(cauda->getGrauNo() + 1);
        cabeca->setGrau(cabeca->getGrauNo() + 1);
    }
    else{
        cabeca->setEntrada(cabeca->getEntrada() + 1);
        cauda->setSaida(cauda->getSaida() + 1);
    }
}

bool Grafo::getDigrafo()
{
    return this->digrafo;
}

int Grafo::getGrauNo(int id)
{
    No *no = encontrarNo(id);

    if (!getDigrafo())
        return no->getGrauNo();
    else
    {
        cout << "Não é possível obter grau de um dígrafo com essa função!" << endl;
        return 0;
    }
}

No *Grafo::getPrimeiroNo()
{
    return this->primeiro_no;
}

bool Grafo::getKRegular(int k)
{
    No *no = this->primeiro_no;

    if (no->getGrauNo() != k)
        return false;
    else
    {
        while (no != nullptr)
        {
            if (no->getGrauNo() != k)
                return false;

            no = no->getProxNo();
        }
        return true;
    }
}

int Grafo::getGrauGrafo()
{
    No *no = this->primeiro_no;
    int grau = no->getGrauNo();

    while (no != nullptr)
        if (no->getGrauNo() > grau)
        {
            grau = no->getGrauNo();

            no = no->getProxNo();
        }
    return grau;
}

int Grafo::getOrdem()
{
    No *no = this->primeiro_no;
    int ordem = 0;

    while (no != nullptr)
    {
        ordem++;
        no = no->getProxNo();
    }
    return ordem;
}

void Grafo::removeNo(int id){
    No *no = encontrarNo(id);
    if(no == nullptr) {
        cout << "Nó não encontrado no grafo" << endl;
        return;
    }

    // Remover as arestas relacionadas ao nó a ser removido
    No *no_atual = primeiro_no;
    
    while (no_atual != nullptr){
        Aresta *aresta = no_atual->getPrimeiraAresta();
        while (aresta != nullptr ){
            if(aresta->getIdCabeca() == id)
                removeAresta(no_atual->getId(),id);
            aresta = aresta->getProxAresta();
        }
        no_atual = no_atual->getProxNo();
    }

    //Remover nó
    if(no == primeiro_no)
        primeiro_no = no->getProxNo();
    else{
        No *no_anterior = primeiro_no;
        while(no_anterior->getProxNo() != no)
            no_anterior = no_anterior->getProxNo();
        
        no_anterior->setProxNo(no->getProxNo());
    }

    delete no;
    cout << "Nó removido com sucesso." << endl;
}

void Grafo::removeAresta(int id_cauda, int id_cabeca)
{
    No *cauda = encontrarNo(id_cauda);
    No *cabeca = encontrarNo(id_cabeca);

    if (cauda == nullptr || cabeca == nullptr)
    {
        cout << "Aresta inexiste" << endl;
        return;
    }

    bool remove = cauda->removeAresta(id_cauda, id_cabeca);
    if (remove)
    {
        if (this->digrafo)
            cauda->setSaida(cauda->getSaida() - 1);
        else
            cauda->setGrau(cauda->getGrauNo() - 1);
    }
    if (!this->digrafo)
    {
        remove = cabeca->removeAresta(id_cabeca, id_cauda);
        if (remove)
            cabeca->setGrau(cabeca->getGrauNo() - 1);
    }
}

void Grafo::imprime()
{
    No *no = this->primeiro_no;

    if (no == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return;
    }

    while (no != nullptr)
    {
        cout << "(" << no->getId() << ")" << endl;
        Aresta *aresta = no->getPrimeiraAresta();
        cout << " ";
        while (aresta != nullptr)
        {
            cout << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
            aresta = aresta->getProxAresta();
        }
        cout << endl;

        no = no->getProxNo();
    }
}



bool Grafo::trivial()
{
    No *no = this->primeiro_no;

    if (no->getProxNo() == nullptr)
        return true;
    else
        return false;
}

bool Grafo::nulo()
{
    No *no = this->primeiro_no;

    if (no == nullptr)
        return true;
    else
        return false;
}

/*bool Grafo::ehMultiGrafo()
{
    unordered_map<string, int> contador;

    // percorre os nos do grafo
    No *no_atual = this->primeiro_no;
    while (no_atual != nullptr)
    {
        Aresta *aresta_atual = no_atual->getPrimeiraAresta();

        // percorre as arestas do no atual
        while (aresta_atual != nullptr)
        {
            string chave = to_string(aresta_atual->getIdCauda()) + "-" + to_string(aresta_atual->getIdCauda());
            contador[chave]++;

            aresta_atual = aresta_atual->getProxAresta();
        }

        no_atual = no_atual->getProxNo();
    }

    // verifica se tem aresta duplicada
    for (const auto &par : contador)
    {
        if (par.second > 1)
            return true;
    }

    return false;
}*/

bool Grafo::grafoCompleto()
{
    No *no_atual = this->primeiro_no;

    // percorre os nos do grafo
    while (no_atual != nullptr)
    {
        Aresta *aresta_atual = no_atual->getPrimeiraAresta();

        // verifica se o no atual esta conectado a todos os outros nos
        No *outro_no = this->primeiro_no;
        while (outro_no != nullptr)
        {
            if (outro_no != no_atual)
            {
                bool aresta_encontrada = false;

                // verifica se tem uma artesta entre os nos
                while (aresta_atual != nullptr)
                {
                    if (aresta_atual->getIdCabeca() == outro_no->getId())
                    {
                        aresta_encontrada = true;
                        break;
                    }
                    aresta_atual = aresta_atual->getProxAresta();
                }

                if (!aresta_encontrada) // se nao, nao é completo
                    return false;
            }
            outro_no = outro_no->getProxNo();
        }
        no_atual = no_atual->getProxNo();
    }
    return true;
}

bool Grafo::ehBipartido()
{
    unordered_map<No *, int> verifica; // verifica cada no para seu numero(1 ou 2)
    queue<No *> fila;                  // percorrer os nos durante a busca na largura
    No *no_atual = this->primeiro_no;

    verifica[no_atual] = 1;
    fila.push(no_atual);

    while (!fila.empty())
    {
        No *no = fila.front();
        fila.pop();
        int atual = verifica[no];
        Aresta *aresta_atual = no->getPrimeiraAresta();

        while (aresta_atual != nullptr)
        {
            No *no_adjacente = encontrarNo(aresta_atual->getIdCabeca());

            if (verifica.find(no_adjacente) == verifica.end())
            { // se o no adjacente nao foi verificado, atribui o numero oposto a do no atual
                verifica[no_adjacente] = atual == 1 ? 2 : 1;
                fila.push(no_adjacente);
            }
            else if (verifica[no_adjacente] == atual) // se o no adjacente tiver o mesmo numero do atual, nao eh bipartido
                return false;

            aresta_atual = aresta_atual->getProxAresta();
        }

        // verifica se tem mais nos a ser visitado
        if (fila.empty())
        {
            for (No *no : lista_nos)
            {
                if (verifica.find(no) == verifica.end())
                { // encontra o proximo no nao visitado
                    verifica[no] = 1;
                    fila.push(no);
                    break;
                }
            }
        }
    }
    return true;
}

No *Grafo::encontrarNo(int id)
{
    No *no_atual = this->primeiro_no;
    while (no_atual != nullptr)
    {
        if (no_atual->getId() == id)
            return no_atual;

        no_atual = no_atual->getProxNo();
    }
    return nullptr;
}

int Grafo::contAresta(){
    No *no = this->primeiro_no;
    int cont = 0;
    if (no == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return 0;
    }

    while (no != nullptr)
    {
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            cont++;
            aresta = aresta->getProxAresta();
            
        }

        no = no->getProxNo();
    }

    return cont/2;
}

int *Grafo::seqDeGraus()
{
    if (this->primeiro_no == nullptr || getOrdem() <= 0)
    {
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }

    No *no = this->primeiro_no;
    int *sequencia = new int[getOrdem()];

    if (no == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }
    else
    {
        for (int i = 0; i < getOrdem(); i++)
        {
            if (no != nullptr)
            {
                sequencia[i] = no->getGrauNo();
                no = no->getProxNo();
            }
            else
                sequencia[i] = 0;
        }
    }
    return sequencia;
}

/*vector<int> Grafo::dijkstra(int id_cauda, int id_cabeca)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_map<int, int> distancias;    // armazena distancia minima
    unordered_map<int, int> predecessores; // armazena predecessores dos nos
    unordered_set<int> visitados;          // armazena nos visitados

    // inicialização das distâncias com infinito e predecessores como -1
    for (No *no = primeiro_no; no != nullptr; no = no->getProxNo())
    {
        int id = no->getId();
        distancias[id] = numeric_limits<int>::max();
        predecessores[id] = -1;
    }

    // define a distância da origem como 0 e adiciona na fila de prioridade
    distancias[id_cauda] = 0;
    pq.push(make_pair(0, id_cauda));

    while (!pq.empty())
    {
        int no_atual = pq.top().second;
        pq.pop();

        if (visitados.find(no_atual) == visitados.end())
        {
            visitados.insert(no_atual);

            Aresta *aresta_atual = encontrarNo(no_atual)->getPrimeiraAresta();
            while (aresta_atual != nullptr)
            {
                int no_adjacente = aresta_atual->getIdCabeca();
                int peso_aresta = aresta_atual->getPeso();

                if (distancias[no_atual] + peso_aresta < distancias[no_adjacente])
                {
                    distancias[no_adjacente] = distancias[no_atual] + peso_aresta;
                    predecessores[no_adjacente] = no_atual;
                    pq.push(make_pair(distancias[no_adjacente], no_adjacente));
                }

                aresta_atual = aresta_atual->getProxAresta();
            }
        }
    }

    // construi o caminho mínimo e seu custo
    vector<int> caminho;
    int no_atual = id_cabeca;
    while (no_atual != -1)
    {
        caminho.push_back(no_atual);
        no_atual = predecessores[no_atual];
    }
    reverse(caminho.begin(), caminho.end());

    return caminho;
}

vector<int> Grafo::floydWarshall(int id_calda, int id_cabeca)
{
    const int infinito = numeric_limits<int>::max();
    vector<vector<int>> distancias; // matriz de distancia minima

    // inicializacao da matriz de distancias com infinito e 0 na diagonal principal
    for (No *no = primeiro_no; no != nullptr; no = no->getProxNo())
    {
        distancias[no->getId()][no->getId()] = 0;
        Aresta *aresta_atual = no->getPrimeiraAresta();

        while (aresta_atual != nullptr)
        {
            distancias[no->getId()][aresta_atual->getIdCabeca()] = aresta_atual->getPeso();
            aresta_atual = aresta_atual->getProxAresta();
        }
    }

    // algoritmo de floyd
    for (No *k = primeiro_no; k != nullptr; k = k->getProxNo())
    {
        for (No *i = primeiro_no; i != nullptr; i = i->getProxNo())
        {
            for (No *j = primeiro_no; j != nullptr; j = j->getProxNo())
            {
                if ((distancias[i->getId()][k->getId()] != infinito) && (distancias[k->getId()][j->getId()] != infinito) &&
                    (distancias[i->getId()][k->getId()] + distancias[k->getId()][j->getId()]) < distancias[i->getId()][j->getId()])
                {
                    distancias[i->getId()][j->getId()] = distancias[i->getId()][k->getId()] + distancias[k->getId()][j->getId()];
                }
            }
        }
    }

    // construcao do caminho minimo e seu custo
    vector<int> caminho;
    int custo = distancias[id_calda][id_cabeca];
    if (custo != infinito)
    {
        int no_atual = id_calda;
        caminho.push_back(no_atual);
        while (no_atual != id_cabeca)
        {
            for (No *no = primeiro_no; no != nullptr; no = no->getProxNo())
            {
                if (distancias[no_atual][no->getId()] + distancias[no->getId()][id_cabeca] == custo)
                {
                    no_atual = no->getId();
                    caminho.push_back(no_atual);
                    break;
                }
            }
        }
    }
    return caminho;
}

void Grafo::vizinhoAberta(int id)
{
    No *no = encontrarNo(id);
    Aresta *aresta = no->getPrimeiraAresta();
    vector<int> vizinhancaAberta;

    for (; aresta != nullptr; aresta = aresta->getProxAresta())
    {
        if (aresta->getIdCauda() == id)
            vizinhancaAberta.push_back(aresta->getIdCabeca());
        else
            vizinhancaAberta.push_back(aresta->getIdCauda());
    }
    cout << "A vizinhança aberta é: " << endl;
    for (int i = 0; i < static_cast<int>(vizinhancaAberta.size()); i++)
    {
        cout << vizinhancaAberta[i] << " ";
    }
    cout << endl;

    return;
}

void Grafo::vizinhoFechada(int id)
{
    No *no = encontrarNo(id);
    Aresta *aresta = no->getPrimeiraAresta();
    vector<int> vizinhancaFechada;

    vizinhancaFechada.push_back(id);

    for (; aresta != nullptr; aresta = aresta->getProxAresta())
    {
        if (aresta->getIdCauda() == id)
            vizinhancaFechada.push_back(aresta->getIdCabeca());
        else
            vizinhancaFechada.push_back(aresta->getIdCauda());
    }

    cout << "A vizinhança fechada é: " << endl;
    for (int i = 0; i < static_cast<int>(vizinhancaFechada.size()); i++)
        cout << vizinhancaFechada[i] << " ";

    cout << endl;

    return;
}*/