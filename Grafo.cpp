#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include "Grafo.h"

using namespace std;

Grafo::Grafo(bool digrafo){
    this->digrafo = digrafo;
    this->primeiro_no = nullptr;
    this->ultimo_no = nullptr;
}

Grafo::~Grafo(){};

bool Grafo::getDigrafo(){return this->digrafo;}
No *Grafo::getPrimeiroNo(){return this->primeiro_no;}

vector<No> Grafo::listaNos()
{
    vector<No> listaNos;
    No *no = primeiro_no;
    while (no != nullptr)
    {
        listaNos.push_back(*no);
        no = no->getProxNo();
    }
    
    sort(listaNos.begin(), listaNos.end(), []( No &p,  No &q){
        return p.getId() < q.getId();});

    // cout<<"Lista ordenada:"<<endl;    
    // for(auto& elemento : listaNos)
    // {
    //     cout<<elemento.getId()<<" ";
    // }
    // cout << endl;
    return listaNos;
    
}

bool Grafo::independente(vector<No> Nos)
{
    for (int i = 0; i < Nos.size()-1; i++)
    {
        for (int j = i+1; j < Nos.size(); j++)
        {
            if (Nos[i].buscaAresta(Nos[i].getId(),Nos[j].getId()))
            {
                return false;
            }    
        }       
    }

    return true;
    
}

vector<int> Grafo::guloso()
{   
    vector<No> candidatos = listaNos();
    sort(candidatos.begin(), candidatos.end(), []( No &p,  No &q){
        return p.getPeso()/p.getGrauNo() < q.getPeso()/q.getGrauNo();});
    vector<int> sol;
    while (!independente(candidatos) || candidatos.empty())
    {
        sol.push_back(candidatos[0].getId());
        candidatos.erase(candidatos.begin());
    }

    if(!sol.empty())
    {
    
        cout<<"Solucao guloso:"<<endl;
        for(int c : sol)
        {
            cout << c << " ";
        }
        cout << endl;
        return sol;
        
    }

    cout<<"Nao ha solucao"<<endl;
    return sol;  

}

vector<int> Grafo::randomizado(float alpha, int numIter)

{
    vector<int> solucao;
    vector<No> solBest,sol;
    int k, somaSol, somaSolbest;
    vector<No> candidatos;
    sort(candidatos.begin(), candidatos.end(), []( No &p,  No &q){
        return p.getPeso()/p.getGrauNo() < q.getPeso()/q.getGrauNo();});

    for (int i = 0; i < numIter; i++)
    {   
        cout<<"i: "<<i<<endl;
        candidatos = listaNos();
        sort(candidatos.begin(), candidatos.end(), []( No &p,  No &q){
        return p.getPeso()/p.getGrauNo() < q.getPeso()/q.getGrauNo();});
        
        while (!independente(candidatos) || candidatos.empty())
            {   
                k=rand()%int(alpha*candidatos.size());
                cout<<"  "<<k<<": ";
                sol.push_back(candidatos[k]);
                cout<<candidatos[k].getId();
                candidatos.erase(candidatos.begin()+k);
                
            }
        cout<<endl;
        cout<<"pass"<<endl;
        if (i==0)
        {
            solBest=sol;
        }else
        {
            somaSol, somaSolbest = 0;
            for (auto& No : sol)
            {
                somaSol+=No.getPeso();
            }

            for (auto& No : solBest)
            {
                somaSolbest+=No.getPeso();
            
            }
            if (somaSol<somaSolbest)
            {
                solBest=sol;
            }
        }
  
    }
    
    if (!solBest.empty())
    {   
        cout<<"Solucao guloso randomizado:"<<endl;
        for(No& no : solBest)
        {
            solucao.push_back(no.getId());
            cout<<no.getId()<<" ";
        }
        cout<<endl;
        return solucao;
    }
    cout<<"Nao ha solucao"<<endl;
    return solucao;
    
}

vector<int> Grafo::reativo(float alpha, int numIter)

{
    vector<int> solucao;
    vector<No> solBest,sol;
    int k, somaSol, somaSolbest;
    vector<No> candidatos;
    sort(candidatos.begin(), candidatos.end(), []( No &p,  No &q){
        return p.getPeso()/p.getGrauNo() < q.getPeso()/q.getGrauNo();});

    for (int i = 0; i < numIter; i++)
    {   
        cout<<"i: "<<i<<endl;
        candidatos = listaNos();
        sort(candidatos.begin(), candidatos.end(), []( No &p,  No &q){
        return p.getPeso()/p.getGrauNo() < q.getPeso()/q.getGrauNo();});
        
        while (!independente(candidatos) || candidatos.empty())
            {   
                k=rand()%int(ceil(alpha*candidatos.size()));
                cout<<"  "<<k<<": ";
                sol.push_back(candidatos[k]);
                cout<<candidatos[k].getId();
                candidatos.erase(candidatos.begin()+k);
                sort(candidatos.begin(), candidatos.end(), [&]( No &p,  No &q)
                {   
                    int n, m  = 0;
                    for (No& no : sol)
                    {
                        if (no.buscaAresta(no.getId(),p.getId()))
                        {
                            n+=1;
                        }
                        if (no.buscaAresta(no.getId(),q.getId()))
                        {
                            m+=1;
                        }
                        
                    }                          
                    
                    return p.getPeso()/(p.getGrauNo()-n) < q.getPeso()/(q.getGrauNo()-m);
                });    
                
            }
        if (i==0)
        {
            solBest=sol;
        }else
        {
            somaSol, somaSolbest = 0;
            for (auto& No : sol)
            {
                somaSol+=No.getPeso();
            }

            for (auto& No : solBest)
            {
                somaSolbest+=No.getPeso();
            
            }
            if (somaSol<somaSolbest)
            {
                solBest=sol;
            }
        }
  
    }
    
    if (!solBest.empty())
    {   
        cout<<"Solucao guloso reativo:"<<endl;
        for(No& no : solBest)
        {
            solucao.push_back(no.getId());
            cout<<no.getId()<<" ";
        }
        cout<<endl;
        return solucao;
    }
    cout<<"Nao ha solucao"<<endl;
    return solucao;
    
}

void Grafo::insereNoInicio(int id){
    No *no = new No(id); 
    no->setProxNo(this->primeiro_no);
    this->primeiro_no = no;
}

void Grafo::insereNoFim(int id){
    No *no = new No(id);
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

void Grafo::insereAresta(int id_cauda, int id_cabeca, float peso){
    No *cauda = encontrarNo(id_cauda);
    No *cabeca = encontrarNo(id_cabeca);

    if(cauda == nullptr){
        this->insereNoFim(id_cauda);
        cauda = this->ultimo_no;
    }
    if(cabeca == nullptr){
        this->insereNoFim(id_cabeca);
        cabeca = this->ultimo_no;
    }

    cauda->insereAresta(id_cauda, id_cabeca, peso);

    if(!this->digrafo)
        cabeca->insereAresta(id_cabeca, id_cauda, peso);

    if(!this->getDigrafo()){
        cabeca->setGrau(cabeca->getGrauNo() + 1);
        cauda->setGrau(cauda->getGrauNo() + 1);
    }
    else{
        cabeca->setEntrada(cabeca->getEntrada() + 1);
        cauda->setSaida(cauda->getSaida() + 1);
    }
}


int Grafo::getGrauNo(int id){
    No *no = encontrarNo(id);

    if(!getDigrafo()) 
        return no->getGrauNo();
    else{
        cout << "Não é possível obter grau de um dígrafo com essa função!" << endl;
        return 0;
    }
}


bool Grafo::getKRegular(int k){
    No *no = this->primeiro_no;

    if(no->getGrauNo() != k)
        return false;
    else{
        while(no != nullptr){
            if(no->getGrauNo() != k)
                return false;

            no = no->getProxNo();
        }
        return true;
    }
}

int Grafo::getGrauGrafo(){
    No *no = this->primeiro_no;
    int grau = no->getGrauNo();

    while(no != nullptr)
        if(no->getGrauNo() > grau){ 
            grau = no->getGrauNo();

        no = no->getProxNo(); 
    }
    return grau;
}

int Grafo::getOrdem(){
    No *no = this->primeiro_no;
    int ordem = 0;

    while (no != nullptr){
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
    while(no_atual != nullptr) {
        no_atual->removeAresta(id, no->getId());
        no_atual = no_atual->getProxNo();
    }

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


void Grafo::removeAresta(int id_cauda, int id_cabeca){
    No *cauda = encontrarNo(id_cauda);
    No *cabeca = encontrarNo(id_cabeca);

    if(cauda == nullptr || cabeca == nullptr){
        cout << "Aresta inexiste" << endl;
        return;
    }
    
    bool remove = cauda->removeAresta(id_cauda, id_cabeca);
    if(remove){
        if(this->digrafo)
            cauda->setSaida(cauda->getSaida() - 1);
        else
            cauda->setGrau(cauda->getGrauNo() - 1);
    }
    if(!this->digrafo){
        remove = cabeca->removeAresta(id_cabeca, id_cauda);
        if(remove)
            cabeca->setGrau(cabeca->getGrauNo() - 1);
    }
}

void Grafo::imprime(){
    No *no = this->primeiro_no;

    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return;
    }

    while (no != nullptr){
        cout <<no->getId() <<"("<<no->getPeso()<< "):" << endl;
        Aresta *aresta = no->getPrimeiraAresta();
        cout << " ";
        while(aresta != nullptr ){
            cout << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
            aresta = aresta->getProxAresta();
        }
        cout << endl;

        no = no->getProxNo();
    }
}

bool Grafo::trivial(){
    No *no = this->primeiro_no;
    
    if(no->getProxNo() == nullptr)
        return true;
    else
        return false;
}

bool Grafo::nulo(){
    No *no = this->primeiro_no;

    if(no == nullptr)
        return true;
    else
        return false;
    
}

bool Grafo::ehMultiGrafo() {
    unordered_map<string, int> contador;

    // percorre os nos do grafo
    No *no_atual = this->primeiro_no;
    while(no_atual != nullptr) {
        Aresta *aresta_atual = no_atual->getPrimeiraAresta();
        
        // percorre as arestas do no atual
        while(aresta_atual != nullptr) {
            string chave = to_string(aresta_atual->getIdCauda()) + "-" + to_string(aresta_atual->getIdCauda());
            contador[chave]++;
            
            aresta_atual = aresta_atual->getProxAresta();
        }
        
        no_atual = no_atual->getProxNo();
    }

    //verifica se tem aresta duplicada
    for(const auto& par : contador) {
        if(par.second > 1)
            return true;
    }

    return false;
}

bool Grafo::grafoCompleto() {
    No* no_atual = this->primeiro_no;

    // percorre os nos do grafo
    while(no_atual != nullptr) {
        Aresta *aresta_atual = no_atual->getPrimeiraAresta();

        //verifica se o no atual esta conectado a todos os outros nos
        No *outro_no = this->primeiro_no;
        while(outro_no != nullptr) {
            if(outro_no != no_atual) {
                bool aresta_encontrada = false;

                //verifica se tem uma artesta entre os nos
                while(aresta_atual != nullptr){
                    if (aresta_atual->getIdCabeca() == outro_no->getId()) {
                        aresta_encontrada = true;
                        break;
                    }
                    aresta_atual = aresta_atual->getProxAresta();
                }

                if(!aresta_encontrada) //se nao, nao é completo
                    return false;
            }
            outro_no = outro_no->getProxNo();
        }
        no_atual = no_atual->getProxNo();
    }
    return true;
}

bool Grafo::ehBipartido() {
    unordered_map<No*, int> verifica; //verifica cada no para seu numero(1 ou 2)
    queue<No*> fila; //percorrer os nos durante a busca na largura
    No* no_atual = this->primeiro_no;

    verifica[no_atual] = 1;
    fila.push(no_atual);

    while(!fila.empty()) {
        No *no = fila.front();
        fila.pop();
        int atual = verifica[no];
        Aresta *aresta_atual = no->getPrimeiraAresta();

        while(aresta_atual != nullptr) {
            No *no_adjacente = encontrarNo(aresta_atual->getIdCabeca());

            if(verifica.find(no_adjacente) == verifica.end()){ //se o no adjacente nao foi verificado, atribui o numero oposto a do no atual
                verifica[no_adjacente] = atual == 1 ? 2 : 1;
                fila.push(no_adjacente);
            } 
            else if(verifica[no_adjacente] == atual) //se o no adjacente tiver o mesmo numero do atual, nao eh bipartido
                return false;

            aresta_atual = aresta_atual->getProxAresta();
        }

        //verifica se tem mais nos a ser visitado
        if(fila.empty()){
            for(No *no : lista_nos){
                if (verifica.find(no) == verifica.end()){ //encontra o proximo no nao visitado
                    verifica[no] = 1;
                    fila.push(no);
                    break;
                }
            }
        }
    }
    return true;
}

No *Grafo::encontrarNo(int id) {
    No *no_atual = this->primeiro_no;
    while(no_atual != nullptr) {
        if(no_atual->getId() == id)
            return no_atual;

        no_atual = no_atual->getProxNo();
    }
    return nullptr;
}

int* Grafo::seqDeGraus(){
    if(this->primeiro_no == nullptr || getOrdem() <= 0) {
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }

    No *no = this->primeiro_no;
    int *sequencia=new int[getOrdem()];

    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }
    else{
        for(int i = 0; i < getOrdem(); i++){
            if(no != nullptr) {
                sequencia[i] = no->getGrauNo();
                no = no->getProxNo();
            }
            else
                sequencia[i] = 0;
        }
    }
    return sequencia;
}

vector<int> Grafo::dijkstra(int id_cauda, int id_cabeca){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_map<int, int> distancias; //armazena distancia minima
    unordered_map<int, int> predecessores; //armazena predecessores dos nos
    unordered_set<int> visitados; //armazena nos visitados

    //inicialização das distâncias com infinito e predecessores como -1
    for(No *no = primeiro_no; no != nullptr; no = no->getProxNo()){
        int id = no->getId();
        distancias[id] = numeric_limits<int>::max();
        predecessores[id] = -1;
    }

    //define a distância da origem como 0 e adiciona na fila de prioridade
    distancias[id_cauda] = 0;
    pq.push(make_pair(0, id_cauda));

    while(!pq.empty()){
        int no_atual = pq.top().second;
        pq.pop();

        if(visitados.find(no_atual) == visitados.end()){
            visitados.insert(no_atual);

            Aresta *aresta_atual = encontrarNo(no_atual)->getPrimeiraAresta();
            while (aresta_atual != nullptr) {
                int no_adjacente = aresta_atual->getIdCabeca();
                int peso_aresta = aresta_atual->getPeso();

                if(distancias[no_atual] + peso_aresta < distancias[no_adjacente]){
                    distancias[no_adjacente] = distancias[no_atual] + peso_aresta;
                    predecessores[no_adjacente] = no_atual;
                    pq.push(make_pair(distancias[no_adjacente], no_adjacente));
                }

                aresta_atual = aresta_atual->getProxAresta();
            }
        }
    }

    //construi o caminho mínimo e seu custo
    vector<int> caminho;
    int no_atual = id_cabeca;
    while(no_atual != -1){
        caminho.push_back(no_atual);
        no_atual = predecessores[no_atual];
    }
    reverse(caminho.begin(), caminho.end());

    return caminho;
}

vector<int> Grafo::floydWarshall(int id_calda, int id_cabeca){
    const int infinito = numeric_limits<int>::max();
    vector<vector<int>> distancias; //matriz de distancia minima

    //inicializacao da matriz de distancias com infinito e 0 na diagonal principal   
    for(No *no = primeiro_no; no != nullptr; no = no->getProxNo()){
        distancias[no->getId()][no->getId()] = 0;
        Aresta *aresta_atual = no->getPrimeiraAresta();

        while(aresta_atual != nullptr){
            distancias[no->getId()][aresta_atual->getIdCabeca()] = aresta_atual->getPeso();
            aresta_atual = aresta_atual->getProxAresta();
        }
    }

    //algoritmo de floyd
    for(No *k = primeiro_no; k != nullptr; k = k->getProxNo()){
        for(No *i = primeiro_no; i != nullptr; i = i->getProxNo()){
            for(No *j = primeiro_no; j != nullptr; j = j->getProxNo()){
                if((distancias[i->getId()][k->getId()] != infinito) && (distancias[k->getId()][j->getId()] != infinito) &&
                    (distancias[i->getId()][k->getId()] + distancias[k->getId()][j->getId()]) < distancias[i->getId()][j->getId()]){
                        distancias[i->getId()][j->getId()] = distancias[i->getId()][k->getId()] + distancias[k->getId()][j->getId()];
                }
            }
        }
    }

    //construcao do caminho minimo e seu custo
    vector<int> caminho;
    int custo = distancias[id_calda][id_cabeca];
    if (custo != infinito){
        int no_atual = id_calda;
        caminho.push_back(no_atual);
        while (no_atual != id_cabeca){
            for (No *no = primeiro_no; no != nullptr; no = no->getProxNo()) {
                if (distancias[no_atual][no->getId()] + distancias[no->getId()][id_cabeca] == custo){
                    no_atual = no->getId();
                    caminho.push_back(no_atual);
                    break;
                }
            }
        }
    }
    return caminho;
}


void Grafo::vizinhancaAberta(int id){
    No *no = encontrarNo(id);
    Aresta *aresta = no->getPrimeiraAresta();
    vector< int > vizinhancaAberta;

    for(; aresta != nullptr; aresta = aresta->getProxAresta()){
        if(aresta->getIdCauda() == id)
            vizinhancaAberta.push_back(aresta->getIdCabeca());
        else
            vizinhancaAberta.push_back(aresta->getIdCauda());
    }
    cout << "A vizinhança aberta é: " << endl; 
    for (int i = 0; i < static_cast<int>(vizinhancaAberta.size()); i++){
        cout << vizinhancaAberta[i] << " ";
    }
    cout << endl;

    return;
}

void Grafo::vizinhancaFechada(int id){
    No *no = encontrarNo(id);
    Aresta *aresta = no->getPrimeiraAresta();
    vector<int> vizinhancaFechada;

    vizinhancaFechada.push_back(id);

    for(; aresta != nullptr; aresta = aresta->getProxAresta()){
        if(aresta->getIdCauda() == id)
            vizinhancaFechada.push_back(aresta->getIdCabeca());
        else
            vizinhancaFechada.push_back(aresta->getIdCauda());
        
    }
    
    cout << "A vizinhança fechada é: " << endl; 
    for (int i = 0; i < static_cast<int>(vizinhancaFechada.size()); i++)
        cout << vizinhancaFechada[i] << " ";

    cout << endl;

    return;
}
