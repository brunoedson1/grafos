#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <stack>
#include <climits>
#include "Grafo.h"

using namespace std;

Grafo::Grafo(bool digrafo)
{
    this->digrafo = digrafo;
    this->primeiro_no = nullptr;
    this->ultimo_no = nullptr;
}

Grafo::~Grafo(){};

bool Grafo::getDigrafo() { return this->digrafo; }
No *Grafo::getPrimeiroNo() { return this->primeiro_no; }

vector<No> Grafo::listaNos()
{
    vector<No> listaNos;
    No *no = primeiro_no;
    while (no != nullptr)
    {
        listaNos.push_back(*no);
        no = no->getProxNo();
    }

    sort(listaNos.begin(), listaNos.end(), [](No &p, No &q)
         { return p.getId() < q.getId(); });

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
    for (std::vector<int>::size_type i = 0; i < Nos.size() - 1; i++)
    {
        for (std::vector<int>::size_type j = i + 1; j < Nos.size(); j++)
        {
            if (Nos[i].buscaAresta(Nos[i].getId(), Nos[j].getId()))
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
    sort(candidatos.begin(), candidatos.end(), [](No &p, No &q)
         { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });
    vector<int> sol;
    while (!independente(candidatos) || candidatos.empty())
    {
        sol.push_back(candidatos[0].getId());
        candidatos.erase(candidatos.begin());
    }

    if (!sol.empty())
    {

        cout << "Solucao guloso:" << endl;
        for (int c : sol)
        {
            cout << c << " ";
        }
        cout << endl;
        return sol;
    }

    cout << "Nao ha solucao" << endl;
    return sol;
}

vector<int> Grafo::randomizado(float alpha, int numIter)

{
    vector<int> solucao;
    vector<No> solBest, sol;
    int k, somaSol, somaSolbest;
    vector<No> candidatos;
    sort(candidatos.begin(), candidatos.end(), [](No &p, No &q)
         { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });

    for (int i = 0; i < numIter; i++)
    {
        sol.erase(sol.begin(), sol.end());
        cout << "i: " << i << endl;
        candidatos = listaNos();
        sort(candidatos.begin(), candidatos.end(), [](No &p, No &q)
             { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });

        while (!independente(candidatos) || candidatos.empty())
        {
            k = rand() % int(alpha * candidatos.size());
            cout << "  " << k << ": ";
            sol.push_back(candidatos[k]);
            cout << candidatos[k].getId();
            candidatos.erase(candidatos.begin() + k);
        }
        cout << endl;
        cout << "pass" << endl;
        if (i == 0)
        {
            solBest = sol;
            cout << "somaSol: " << somaSol << endl;
            cout << "somaSolbest: " << somaSolbest << endl;
        }
        else
        {
            somaSol = 0;
            somaSolbest = 0;

            for (No &No : sol)
            {
                somaSol += No.getPeso();
            }

            for (No &No1 : solBest)
            {
                somaSolbest += No1.getPeso();
            }

            cout << "somaSol: " << somaSol << endl;
            cout << "somaSolbest: " << somaSolbest << endl;

            if (somaSol < somaSolbest)
            {
                solBest = sol;
            }
        }
    }

    if (!solBest.empty())
    {
        cout << "Solucao guloso randomizado:" << endl;
        for (No &no : solBest)
        {
            solucao.push_back(no.getId());
            cout << no.getId() << " ";
        }
        cout << endl;
        return solucao;
    }
    cout << "Nao ha solucao" << endl;
    return solucao;
}

vector<int> Grafo::reativo(float alpha, int numIter)

{
    vector<int> solucao;

    vector<No> solBest, sol;
    int k, somaSol, somaSolbest;
    vector<No> candidatos;
    sort(candidatos.begin(), candidatos.end(), [](No &p, No &q)
         { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });
    int n = 0;
    int m = 0;
    for (int i = 0; i < numIter; i++)
    {
        sol.erase(sol.begin(), sol.end());
        cout << "i: " << i << endl;
        candidatos = listaNos();
        sort(candidatos.begin(), candidatos.end(), [](No &p, No &q)
             { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });

        while (!independente(candidatos) || candidatos.empty())
        {
            k = rand() % int(alpha * candidatos.size() + 1);
            cout << "  " << k << ": ";
            sol.push_back(candidatos[k]);
            cout << candidatos[k].getId() << endl;
            candidatos.erase(candidatos.begin() + k);
            sort(candidatos.begin(), candidatos.end(), [&](No &p, No &q){
                for (No &no : sol){
                    if (no.buscaAresta(no.getId(), p.getId())){
                        n += 1;
                    }
                    if (no.buscaAresta(no.getId(), q.getId())){
                        m += 1;
                    }
                }

                if (p.getGrauNo() - n == 0 && q.getGrauNo() - m == 0){
                    return p.getPeso() / 0.0001 < q.getPeso() / 0.0001;
                }
                else if (q.getGrauNo() - m == 0){
                    return p.getPeso() / (p.getGrauNo() - n) < q.getPeso() / 0.0001;
                }
                else if (p.getGrauNo() - n == 0){
                    return p.getPeso() / 0.0001 < q.getPeso() / (q.getGrauNo() - m);
                }

                return p.getPeso() / (p.getGrauNo() - n) < q.getPeso() / (q.getGrauNo() - m); });
        }
        if (i == 0){
            solBest = sol;
        }
        else{
            somaSol = 0;
            somaSolbest = 0;
            for (auto &No : sol){
                somaSol += No.getPeso();
            }
            for (auto &No : solBest){
                somaSolbest += No.getPeso();
            }
            if (somaSol < somaSolbest){
                solBest = sol;
            }
            cout << "somaSol: " << somaSol << endl;
            cout << "somaSolbest: " << somaSolbest << endl;
        }
    }

    if (!solBest.empty()){
        cout << "Solucao guloso reativo:" << endl;
        for (No &no : solBest){
            solucao.push_back(no.getId());
            cout << no.getId() << " ";
        }
        cout << endl;
        return solucao;
    }
    cout << "Nao ha solucao" << endl;
    return solucao;
}

void Grafo::insereNoInicio(int id){
    No *no = new No(id);
    no->setProxNo(this->primeiro_no);
    this->primeiro_no = no;
}

void Grafo::insereNoFim(int id)
{
    No *no = new No(id);
    no->setProxNo(nullptr);

    if (this->primeiro_no == nullptr)
    {
        this->primeiro_no = no;
        this->ultimo_no = no;
    }
    else
    {
        this->ultimo_no->setProxNo(no);
        this->ultimo_no = no;
    }
}

void Grafo::insereAresta(int id_cauda, int id_cabeca, float peso)
{
    No *cauda = encontrarNo(id_cauda);
    No *cabeca = encontrarNo(id_cabeca);

    if (cauda == nullptr)
    {
        this->insereNoFim(id_cauda);
        cauda = this->ultimo_no;
    }
    if (cabeca == nullptr)
    {
        this->insereNoFim(id_cabeca);
        cabeca = this->ultimo_no;
    }

    cauda->insereAresta(id_cauda, id_cabeca, peso);

    if (!this->digrafo)
        cabeca->insereAresta(id_cabeca, id_cauda, peso);

    if (!this->getDigrafo())
    {
        cabeca->setGrau(cabeca->getGrauNo() + 1);
        cauda->setGrau(cauda->getGrauNo() + 1);
    }
    else
    {
        cabeca->setEntrada(cabeca->getEntrada() + 1);
        cauda->setSaida(cauda->getSaida() + 1);
    }
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

void Grafo::removeNo(int id)
{
    No *no = encontrarNo(id);
    if (no == nullptr)
    {
        cout << "Nó não encontrado no grafo" << endl;
        return;
    }

    // Remover as arestas relacionadas ao nó a ser removido
    No *no_atual = primeiro_no;
    while (no_atual != nullptr)
    {
        no_atual->removeAresta(id, no->getId());
        no_atual = no_atual->getProxNo();
    }

    if (no == primeiro_no)
        primeiro_no = no->getProxNo();
    else
    {
        No *no_anterior = primeiro_no;
        while (no_anterior->getProxNo() != no)
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
        cout << no->getId() << "(" << no->getPeso() << "):" << endl;
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

bool Grafo::ehMultiGrafo()
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
}

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

void Grafo::caminhoMinimoDijkstra(int origem, int destino) {
    No *p = encontrarNo(origem - 1);
    No *q = encontrarNo(destino - 1);
    No *aux;
    int indice;

    if (p == nullptr || q == nullptr) {
        cout << "Os vértices de origem ou destino não existem no grafo." << endl;
        return;
    }

    int n = lista_nos.size();
    int distancias[n];
    int antecessores[n];
    bool visitados[n];

    for (int i = 0; i < n; i++) {
        distancias[i] = INT_MAX / 2;
        antecessores[i] = -1;
        visitados[i] = false;
    }

    distancias[p->getId()] = 0;
    antecessores[p->getId()] = 0;

    while (!verificaVisit(visitados, n)) {
        int menor = -1;
        for (int i = 0; i < n; i++) {
            if (!visitados[i] && (menor == -1 || distancias[i] < distancias[menor])) {
                menor = i;
            }
        }

        if (menor == -1) {
            break;
        }

        visitados[menor] = true;
        No *no_atual = encontrarNo(menor);

        Aresta *a = no_atual->getPrimeiraAresta();
        while (a != nullptr) {
            if (a->getPeso() >= 0) {
                aux = encontrarNo(a->getIdCabeca());
                indice = aux->getId();

                if (distancias[indice] > distancias[menor] + a->getPeso()) {
                    distancias[indice] = distancias[menor] + a->getPeso();
                    antecessores[indice] = menor;
                }
            }

            a = a->getProxAresta();
        }
    }

    if (distancias[q->getId()] == INT_MAX / 2) {
        cout << "Não existe caminho entre os vértices." << endl;
    } else {
        cout << "Menor Caminho(Dijkstra) entre " << origem << " e " << destino << " : " << distancias[q->getId()] << endl;
    }
}


bool Grafo::verificaVisit(bool visitados[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!visitados[i])
        {
            return false;
        }
    }
    return true;
}

void Grafo::caminhoMinimoFloyd(int origem, int destino)
{
    // Matriz de distâncias mínimas entre pares de nós
    int tamanho = lista_nos.size();
    int distancias[tamanho][tamanho];

    // Inicializa a matriz de distâncias com valores iniciais
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (i == j)
            {
                distancias[i][j] = 0; // A distância de um nó para ele mesmo é 0
            }
            else
            {
                distancias[i][j] = INT_MAX; // Inicializa as outras distâncias como infinito
            }
        }
    }

    // Preenche a matriz de distâncias com os pesos das arestas existentes
    No *no = primeiro_no;
    while (no != nullptr)
    {
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int cauda = aresta->getIdCauda();
            int cabeca = aresta->getIdCabeca();
            float peso = aresta->getPeso();
            distancias[cauda][cabeca] = peso;
            aresta = aresta->getProxAresta();
        }
        no = no->getProxNo();
    }

    // Algoritmo de Floyd para encontrar o caminho mínimo entre pares de nós
    for (int k = 0; k < tamanho; k++)
    {
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                if (distancias[i][k] != INT_MAX && distancias[k][j] != INT_MAX && distancias[i][k] + distancias[k][j] < distancias[i][j])
                {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }

    // Verifica se o caminho mínimo entre os vértices existe
    if (distancias[origem][destino] == INT_MAX)
    {
        cout << "Não há caminho mínimo entre os vértices " << origem << " e " << destino << endl;
    }
    else
    {
        cout << "Caminho mínimo entre os vértices " << origem << " e " << destino << ": " << distancias[origem][destino] << endl;
    }
}

void Grafo::vizinhancaAberta(int id)
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

void Grafo::vizinhancaFechada(int id)
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
}

vector<No *> Grafo::getFechoTransitivoDireto(int idNo)
{
    vector<No *> fecho;

    No *no = encontrarNo(idNo);
    if (no != nullptr)
    {
        // Adicionar o nó inicial ao fecho
        fecho.push_back(no);

        // Percorrer as arestas do nó
        Aresta *aresta = no->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            // Obter o próximo nó da aresta
            No *proximoNo = encontrarNo(aresta->getIdCabeca());

            // Verificar se o nó já está no fecho
            bool encontrado = false;
            for (No *fechoNo : fecho)
            {
                if (fechoNo->getId() == proximoNo->getId())
                {
                    encontrado = true;
                    break;
                }
            }

            // Se o nó ainda não estiver no fecho, adicioná-lo
            if (!encontrado)
            {
                fecho.push_back(proximoNo);
            }

            // Avançar para a próxima aresta
            aresta = aresta->getProxAresta();
        }
    }

    return fecho;
}

vector<No *> Grafo::getFechoTransitivoIndireto(int idNo)
{
    // Verifica se o nó informado existe no grafo
    No *no = encontrarNo(idNo);
    if (no == nullptr)
    {
        cout << "Nó não encontrado no grafo." << endl;
        return vector<No *>();
    }

    // Vetor para armazenar os nós visitados durante a busca em profundidade
    vector<No *> visitados;
    // Pilha para armazenar os nós a serem visitados
    stack<No *> pilha;

    // Marca o nó inicial como visitado e o coloca na pilha
    visitados.push_back(no);
    pilha.push(no);

    while (!pilha.empty())
    {
        // Obtém o nó do topo da pilha
        No *atual = pilha.top();
        pilha.pop();

        // Percorre todas as arestas do nó atual
        Aresta *aresta = atual->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            // Obtém o nó adjacente
            No *adjacente = encontrarNo(aresta->getIdCabeca());
            // Verifica se o nó adjacente já foi visitado
            if (adjacente != nullptr && find(visitados.begin(), visitados.end(), adjacente) == visitados.end())
            {
                // Marca o nó adjacente como visitado e o coloca na pilha
                visitados.push_back(adjacente);
                pilha.push(adjacente);
            }
            // Avança para a próxima aresta
            aresta = aresta->getProxAresta();
        }
    }

    return visitados;
}

Grafo Grafo::subgrafoInduzido(const vector<int>& conjuntoVertices) {
    Grafo subgrafo(digrafo);

    // Adicionar os vértices do conjunto no subgrafo
    for (int id : conjuntoVertices) {
        subgrafo.insereNoFim(id);
    }

    // Adicionar as arestas entre os vértices do conjunto no subgrafo
    for (int id : conjuntoVertices) {
        No* no = encontrarNo(id);
        Aresta* aresta = no->getPrimeiraAresta();

        while (aresta != nullptr) {
            if (std::find(conjuntoVertices.begin(), conjuntoVertices.end(), aresta->getIdCabeca()) != conjuntoVertices.end()) {
                subgrafo.insereAresta(id, aresta->getIdCabeca(), aresta->getPeso());
            }

            aresta = aresta->getProxAresta();
        }
    }

    return subgrafo;
}

void Grafo::componentesFortementeConexas() {
    // Vetor de vértices visitados
    vector<bool> visitados(lista_nos.size(), false);

    // Pilha para ordenação topológica
    stack<int> pilha;

    // Realiza uma DFS modificada para obter a ordenação topológica
    for (No* no : lista_nos) {
        if (!visitados[no->getId()]) {
            dfsOrdenacaoTopologica(no, visitados, pilha);
        }
    }

    // Transpõe o grafo (inverte as arestas)
    Grafo grafoTransposto(digrafo);
    for (No* no : lista_nos) {
        Aresta* aresta = no->getPrimeiraAresta();
        while (aresta != nullptr) {
            grafoTransposto.insereAresta(aresta->getIdCabeca(), aresta->getIdCauda(), aresta->getPeso());
            aresta = aresta->getProxAresta();
        }
    }

    // Vetor de vértices visitados para o grafo transposto
    visitados = vector<bool>(lista_nos.size(), false);

    // Realiza uma DFS no grafo transposto para encontrar as componentes fortemente conexas
    while (!pilha.empty()) {
        int vertice = pilha.top();
        pilha.pop();

        if (!visitados[vertice]) {
            vector<int> componente;
            dfsComponenteFortementeConexa(grafoTransposto, vertice, visitados, componente);
            // Imprime a componente fortemente conexa
            cout << "Componente Fortemente Conexa: ";
            for (int v : componente) {
                cout << v + 1 << " ";
            }
            cout << endl;
        }
    }
}

void Grafo::dfsOrdenacaoTopologica(No* no, vector<bool> &visitados, stack<int> &pilha) {
    visitados[no->getId()] = true;

    Aresta* aresta = no->getPrimeiraAresta();
    while (aresta != nullptr) {
        if (!visitados[aresta->getIdCabeca()]) {
            dfsOrdenacaoTopologica(encontrarNo(aresta->getIdCabeca()), visitados, pilha);
        }
        aresta = aresta->getProxAresta();
    }

    pilha.push(no->getId());
}

void Grafo::dfsComponenteFortementeConexa(Grafo &grafo, int vertice, vector<bool> &visitados, vector<int>& componente) {
    visitados[vertice] = true;
    componente.push_back(vertice);

    No *no = grafo.encontrarNo(vertice);
    Aresta* aresta = no->getPrimeiraAresta();
    while (aresta != nullptr) {
        if (!visitados[aresta->getIdCabeca()]) {
            dfsComponenteFortementeConexa(grafo, aresta->getIdCabeca(), visitados, componente);
        }
        aresta = aresta->getProxAresta();
    }
}

bool Grafo::conectado() {
    int n = lista_nos.size();

    // Verificar se há pelo menos um vértice
    if (n == 0) {
        return false;
    }

    // Vetor de vértices visitados
    vector<bool> visitados(n, false);

    // Fila para a BFS
    queue<int> fila;

    // Começar a BFS a partir do primeiro vértice
    visitados[0] = true;
    fila.push(0);

    // Executar a BFS
    while (!fila.empty()) {
        int vertice = fila.front();
        fila.pop();

        No* no = lista_nos[vertice];
        Aresta* aresta = no->getPrimeiraAresta();

        while (aresta != nullptr) {
            int id_cabeca = aresta->getIdCabeca();
            if (!visitados[id_cabeca]) {
                visitados[id_cabeca] = true;
                fila.push(id_cabeca);
            }
            aresta = aresta->getProxAresta();
        }
    }

    // Verificar se todos os vértices foram visitados
    for (bool visitado : visitados) {
        if (!visitado) {
            return false;
        }
    }

    return true;
}

bool Grafo::fortementeConectado() {
    // Cria o grafo transposto
    Grafo grafoTransposto(digrafo);
    for (No* no : lista_nos) {
        Aresta* aresta = no->getPrimeiraAresta();
        while (aresta != nullptr) {
            grafoTransposto.insereAresta(aresta->getIdCabeca(), aresta->getIdCauda(), aresta->getPeso());
            aresta = aresta->getProxAresta();
        }
    }

    // Realiza uma DFS no grafo original para obter a ordenação topológica
    stack<int> pilha;
    vector<bool> visitados(lista_nos.size(), false);
    for (No* no : lista_nos) {
        if (!visitados[no->getId()]) {
            dfsOrdenacaoTopologica(no, visitados, pilha);
        }
    }

    // Verifica se todos os vértices alcançáveis a partir do primeiro vértice da ordenação topológica no grafo transposto
    visitados = vector<bool>(lista_nos.size(), false);
    int primeiroVertice = pilha.top();
    dfsAlcancavel(grafoTransposto, primeiroVertice, visitados);

    // Verifica se todos os vértices foram visitados no grafo transposto
    for (bool visitado : visitados) {
        if (!visitado) {
            return false;
        }
    }

    return true;
}

void Grafo::dfsAlcancavel(Grafo &grafo, int vertice, vector<bool> &visitados) {
    visitados[vertice] = true;
    No* no = grafo.encontrarNo(vertice);
    Aresta* aresta = no->getPrimeiraAresta();
    while (aresta != nullptr) {
        if (!visitados[aresta->getIdCabeca()]) {
            dfsAlcancavel(grafo, aresta->getIdCabeca(), visitados);
        }
        aresta = aresta->getProxAresta();
    }
}

bool Grafo::mesmoComponenteConexaoFraca() {
    int n = lista_nos.size();

    // Verifica a conexão entre todos os pares de vértices usando uma BFS a partir do primeiro vértice
    vector<bool> visitados(n, false);
    queue<int> fila;
    int primeiroVertice = 0;
    visitados[primeiroVertice] = true;
    fila.push(primeiroVertice);

    while (!fila.empty()) {
        int vertice = fila.front();
        fila.pop();

        No* no = lista_nos[vertice];
        Aresta* aresta = no->getPrimeiraAresta();
        while (aresta != nullptr) {
            int id_cabeca = aresta->getIdCabeca();
            if (!visitados[id_cabeca]) {
                visitados[id_cabeca] = true;
                fila.push(id_cabeca);
            }
            aresta = aresta->getProxAresta();
        }
    }

    // Verifica se todos os vértices foram visitados
    for (bool visitado : visitados) {
        if (!visitado) {
            return false;
        }
    }

    return true;
}

bool Grafo::euleriano() {
    // Verificar se o grafo é conectado
    if (!conectado()) {
        return false;
    }

    // Verificar o grau dos vértices
    for (No* no : lista_nos) {
        if (no->getGrauNo() % 2 != 0) {
            return false;
        }
    }

    // Verificar se o grafo é fortemente conectado ou se todos os vértices têm o mesmo componente de conexão fraca
    if (fortementeConectado() || mesmoComponenteConexaoFraca()) {
        return true;
    }

    return false;
}
