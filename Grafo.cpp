#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <ctime>
#include <stack>
#include <climits>
#include <list>
#include <numeric>


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

    return listaNos;
}

bool Grafo::independente(vector<No> Nos)
{
    for (int i = 0; i < Nos.size() - 1; i++)
    {
        for (int j = i + 1; j < Nos.size(); j++)
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
    clock_t inicio_guloso, fim_guloso;
    float duracao;
    inicio_guloso = clock();
    vector<No> candidatos = listaNos();
    sort(candidatos.begin(), candidatos.end(), [](No &p, No &q)
         { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });
    vector<int> sol;
    int soma = 0;
    while (!independente(candidatos))
    {
        sol.push_back(candidatos[0].getId());
        soma+=candidatos[0].getPeso();
        candidatos.erase(candidatos.begin());
        if (candidatos.empty())
        {
            break;
        }
        
    }
    fim_guloso = clock();
    duracao = static_cast<float>(fim_guloso - inicio_guloso) / CLOCKS_PER_SEC;
    if (!sol.empty())
    {
        
        cout << "Solucao guloso:" << endl;
        // for (int c : sol)
        // {   
        //     cout << c << " ";
        // }
        // cout << endl;
        cout<<"Peso: "<<soma<<endl;
        cout<<"Duração: "<<duracao<<"s"<<endl;
        return sol;
    }

    fim_guloso = clock();

    duracao = static_cast<double>(fim_guloso - inicio_guloso) / CLOCKS_PER_SEC;
    cout<<duracao<<endl;
    cout << "Nao ha solucao" << endl;
    return sol;
}

vector<int> Grafo::adaptativo(float alpha, int numIter)

{   
    clock_t inicio_adaptativo, fim_adaptativo;
    float duracao;
    inicio_adaptativo = clock();
    srand(time(0));
    vector<int> solucao;
    vector<No> solBest, sol;
    int k, somaSol, somaSolbest;
    list<No> candidatos;
    for (int i = 0; i < numIter; i++)
    {

        for (auto c:listaNos())
        {
            candidatos.push_back(c);
        }
        candidatos.sort([](No &p, No &q)
             { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });
        somaSol=0;
        while (!candidatos.empty())
        {
            
            if (alpha*candidatos.size()<1)
            {
                k=0;
            }else
            {
                k = rand()%int(alpha*candidatos.size());
            }

            if (next(candidatos.begin(),k)->getGrauNo()==0)
            {
                candidatos.erase(next(candidatos.begin(),k));
                continue;
            }
            
            sol.push_back(*next(candidatos.begin(),k));
            auto sol_it = sol.end()-1;
            somaSol+=sol_it->getPeso();
            candidatos.erase(next(candidatos.begin(),k));

            for (No &no : candidatos)
            {

                if (no.buscaAresta(no.getId(), sol_it->getId()))
                {
                    no.removeAresta(no.getId(),sol_it->getId());
                }
            }

            candidatos.sort([&](No &p, No &q)
                {
                    if (p.getGrauNo()==0 && q.getGrauNo()==0)
                    {
                        return p.getPeso() / 0.001 < q.getPeso() / 0.001;
                    }               
                    if (p.getGrauNo()==0)
                    {
                        return p.getPeso() / 0.001 < q.getPeso() / q.getGrauNo();
                    }
                    if (q.getGrauNo()==0)
                    {
                        return p.getPeso() / p.getGrauNo() < q.getPeso() / 0.001;
                    }
                    return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); 
                });
        }
        
        if (i == 0)
        {
            solBest = sol;
            somaSolbest=somaSol;
        }
        else
        {
            if (somaSol < somaSolbest)
            {
                solBest = sol;
                somaSolbest = somaSol;
            }
            
        }
        sol.erase(sol.begin(), sol.end());
    }

    fim_adaptativo = clock();
    duracao = static_cast<double>(fim_adaptativo-inicio_adaptativo)/CLOCKS_PER_SEC;
    if (!solBest.empty())
    {
        cout << "Solucao guloso adaptativo:" << endl;
        for (No &no : solBest)
        {
            solucao.push_back(no.getId());
            // cout << no.getId() << " ";
        }
        cout << endl;
        
        cout<<"Peso: "<<somaSolbest<<endl;
        cout<<"Duração: "<<duracao<<"s"<<endl;

        return solucao;
    }

    cout<<"Duração: "<<duracao<<"s"<<endl;
    cout << "Nao ha solucao" << endl;
    return solucao;
}

vector<int> Grafo::reativo(vector<float> vet_alpha, int numIter,int bloco)

{   
    clock_t inicio_reativo, fim_reativo;
    float duracao;
    inicio_reativo = clock();
    vector<int> solucao;
    vector<No> solBest, sol;
    auto sol_it = sol.begin();
    vector<float> probabilidade(vet_alpha.size(),float(1)/vet_alpha.size());
    

    random_device rd;
    mt19937 gen(rd());
    vector<vector<float>> qualidade(vet_alpha.size());
    vector<No> candidatos;
    vector<float> q(vet_alpha.size(),float(1)/vet_alpha.size()), media(vet_alpha.size());

    float alpha;

    int k, somaSol, somaSolbest, indice,soma;
    int soma_q;

    for (int i = 0; i < numIter; i++)
    {
        candidatos = listaNos();
        sort(candidatos.begin(), candidatos.end(), [](No &p, No &q)
             { return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); });

        discrete_distribution<int> distribuicao(probabilidade.begin(),probabilidade.end());
        indice = distribuicao(gen);
        alpha = vet_alpha[indice];
        somaSol = 0;
        while (!candidatos.empty())
        {
            
            if (alpha*candidatos.size()<1)
            {
                k=0;
            }else
            {
                k = rand()%int(alpha*candidatos.size());
            }

            if (candidatos[k].getGrauNo()==0)
            {
                candidatos.erase(candidatos.begin()+k);
                continue;
            }
            
            sol.push_back(candidatos[k]);
            sol_it = sol.end()-1;
            somaSol+=sol_it->getPeso();
            candidatos.erase(candidatos.begin() + k);

            for (No &no : candidatos)
            {

                if (no.buscaAresta(no.getId(), sol_it->getId()))
                {
                    no.removeAresta(no.getId(),sol_it->getId());
                }
            }

        
            sort(candidatos.begin(), candidatos.end(), [&](No &p, No &q)
                {
                    if (p.getGrauNo()==0 && q.getGrauNo()==0)
                    {
                        return p.getPeso() / 0.001 < q.getPeso() / 0.001;
                    }               
                    if (p.getGrauNo()==0)
                    {
                        return p.getPeso() / 0.001 < q.getPeso() / q.getGrauNo();
                    }
                    if (q.getGrauNo()==0)
                    {
                        return p.getPeso() / p.getGrauNo() < q.getPeso() / 0.001;
                    }
                    return p.getPeso() / p.getGrauNo() < q.getPeso() / q.getGrauNo(); 
                });
        }
        
        
        if (i == 0)
        {
            solBest = sol;
            somaSolbest = somaSol;
        }
        else
        {
            
            
            if (somaSol < somaSolbest)
            {
                solBest = sol;
                somaSolbest = somaSol;
            }
        }
        
        qualidade[indice].push_back(somaSol);
        media[indice]=accumulate(qualidade[indice].begin(),qualidade[indice].end(),0)/qualidade[indice].size();
        q[indice]=somaSolbest/media[indice];
        if ((i+1)%bloco==0)
        {
            for (int j = 0; j < probabilidade.size(); j++)
            {
                
                probabilidade[j]=q[j]/accumulate(q.begin(),q.end(),0);
            }
            
        }
        
        sol.erase(sol.begin(), sol.end());
    }
    fim_reativo = clock();
    duracao = static_cast<double>(fim_reativo-inicio_reativo)/CLOCKS_PER_SEC;

    if (!solBest.empty())
    {
        cout << "Solucao guloso reativo:" << endl;
        for (No &no : solBest)
        {
            solucao.push_back(no.getId());
            // cout << no.getId() << " ";
        }
        cout << endl;
        
        
        cout<<"Peso: "<<somaSolbest<<endl;
        cout<<"Duração: "<<duracao<<"s"<<endl;
        return solucao;
    }
    
    
    cout<<"Duração: "<<duracao<<"s"<<endl;
    cout << "Nao ha solucao" << endl;
    return solucao;
}

void Grafo::insereNoInicio(int id)
{
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


void Grafo::articulacao()
{
    vector<Visitados> v{getOrdem()};
    auto it = v.begin();
    int t=0;
    for (No no : listaNos())
    {
        it->id=no.getId();
        ++it;
    }
    
    
 
    auxArticulacao(primeiro_no,v,t);

    for (auto no : v)
    {
        if (no.articulacao)
        {
            cout<<no.id<<" ";
        }
        
    }
    cout<<endl;

}

void Grafo::auxArticulacao(No* no, vector<Visitados> &v, int& t)
{
    int k= t;
    auto& it_v=v[k];
    v[k].visitado = true;
    v[k].disctime=t+1;
    v[k].low = v[k].disctime;
    int filho = 0;
    for(Aresta *aresta = no->getPrimeiraAresta(); aresta!=nullptr; aresta = aresta->getProxAresta())
    {
        auto it = find_if(v.begin(),v.end(),[&](Visitados p)
        {
            return p.id == aresta->getIdCabeca();            
        });
        
        if(!(it->visitado))
        {
            filho++;
            it->pai = no->getId();
            No *nofilho = encontrarNo(it->id);
            auxArticulacao(nofilho,v,t=t+1);
            if (it->low<v[k].low)
            {
                v[k].low=it->low;
            }
            if (v[k].pai==NULL && filho>1)
            {
                v[k].articulacao = true;   
            }
            if (v[k].pai!=NULL && it->low>=v[k].disctime)
            {
                v[k].articulacao = true;
            }
            
        } else if (v[k].pai != it->id)
        {
            if (it->disctime<v[k].low)
            {
                v[k].low=it->disctime;
            }
            
        }
        
    }

}

void Grafo::ponte()
{
    vector<Visitados> v{getOrdem()};
    auto it = v.begin();
    int t=0;
    for (No no : listaNos())
    {
        it->id=no.getId();
        ++it;
    }
    
    auxArticulacao(primeiro_no,v,t);

    for(auto filho : v)
    {
        if (filho.pai==NULL)
        {
            continue;
        }else
        {
            it = find_if(v.begin(),v.end(),[&](Visitados p)
            {
                return p.id== filho.pai;
            });
            if (filho.low>it->disctime)
            {
                cout<<"("<<filho.pai<<","<<filho.id<<") ";
            }
            
        }
        
    }
    cout<<endl;
}

void Grafo::fechoTransitivoDireto(int id_no) {
    No* no = encontrarNo(id_no);
    if (no == nullptr) {
        cout << "O nó informado não existe no grafo." << endl;
        return;
    }
    vector<No> lista = this->listaNos();
    // Marcar todos os nós como não visitados
    unordered_map<No*, bool> visitado;
    for (No& no : lista) {
        visitado[&no] = false;
    }

    // Chamada recursiva da função auxiliar de DFS para o nó informado
    cout << "Fecho Transitivo Direto a partir do nó " << id_no << ": "<<endl;
    dfsFechoTransitivoDireto(no, visitado);

    cout << endl;
}

void Grafo::dfsFechoTransitivoDireto(No* no, unordered_map<No*, bool>& visitado) {
    // Marcar o nó atual como visitado
    visitado[no] = true;
    cout << no->getId() << " ";

    // Percorrer todas as arestas do nó atual
    for (Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
        No* proximoNo = encontrarNo(aresta->getIdCabeca());

        // Se o nó adjacente não foi visitado, fazer a chamada recursiva
        if (!visitado[proximoNo]) {
            dfsFechoTransitivoDireto(proximoNo, visitado);
        }
    }
}

void Grafo::fechoTransitivoIndireto(int id) {
    No* no = encontrarNo(id);
    if (no == nullptr) {
        // Nó não encontrado
        return;
    }

    unordered_set<No*> visitado;
    cout << "Fecho Transitivo indireto a partir do nó " << id << ": "<<endl;
    dfsFechoTransitivoIndireto(no, visitado);

    // Imprimir ou manipular o resultado, se necessário
}

void Grafo::dfsFechoTransitivoIndireto(No* no, unordered_set<No*>& visitado) {
    visitado.insert(no);
    cout << no->getId() << " ";
    for (Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
        No* vizinho = encontrarNo(aresta->getIdCabeca());
        if (vizinho != nullptr && visitado.find(vizinho) == visitado.end()) {
            dfsFechoTransitivoIndireto(vizinho, visitado);
        }
    }
}

void Grafo::apresentarSubgrafoInduzido(const vector<int>& vertices) {
    // Cria um novo grafo para armazenar o subgrafo induzido
    Grafo subgrafo(false);

    // Adiciona os vértices do conjunto ao subgrafo
    for (int id : vertices) {
        subgrafo.insereNoInicio(id);
    }

    // Percorre os vértices do conjunto para adicionar as arestas correspondentes ao subgrafo
    for (int id : vertices) {
        No* no = encontrarNo(id);

        if (no != nullptr) {
            Aresta* aresta = no->getPrimeiraAresta();

            while (aresta != nullptr) {
                int idDestino = aresta->getIdCabeca();

                // Verifica se o vértice de destino também pertence ao conjunto
                if (std::find(vertices.begin(), vertices.end(), idDestino) != vertices.end()) {
                    subgrafo.insereAresta(id, idDestino, aresta->getPeso());
                }

                aresta = aresta->getProxAresta();
            }
        }
    }

    // Imprime o subgrafo induzido
    subgrafo.imprime();
}

vector<int> Grafo::encontrarCentroDoGrafo() {
   vector<int> verticesCentrais;
    int grauMaximo = 0;

    // Encontra o grau máximo dos vértices no grafo
    for (No& no : listaNos()) {
        if (no.getGrauNo() > grauMaximo) {
            grauMaximo = no.getGrauNo();
        }
    }

    // Percorre todos os vértices e verifica se seu grau é igual ao grau máximo
    for (No& no : listaNos()) {
        if (no.getGrauNo() == grauMaximo) {
            verticesCentrais.push_back(no.getId());
        }
    }
    return verticesCentrais;
}

vector<int> Grafo::calcularPeriferiaDoGrafo() {
    vector<int> periferia;
    int grauMinimo = INT_MAX;

    // Encontra o grau mínimo dos vértices no grafo
    for (No& no : listaNos()) {
        if (no.getGrauNo() < grauMinimo) {
            grauMinimo = no.getGrauNo();
        }
    }

    // Percorre todos os vértices e verifica se seu grau é igual ao grau mínimo
    for (No& no : listaNos()) {
        if (no.getGrauNo() == grauMinimo) {
            periferia.push_back(no.getId());
        }
    }

    return periferia;
}

int Grafo::calcularDistanciaMaxima(No& noInicial) {
    int distanciaMaxima = 0;
    unordered_map<No*, int> distancia;

    for (No& no : listaNos()) {
        distancia[&no] = -1;
    }

    distancia[&noInicial] = 0;
    queue<No*> fila;
    fila.push(&noInicial);

    while (!fila.empty()) {
        No* no = fila.front();
        fila.pop();

        Aresta* aresta = no->getPrimeiraAresta();
        while (aresta != nullptr) {
            No* vizinho = encontrarNo(aresta->getIdCabeca());

            if (distancia[vizinho] == -1) {
                distancia[vizinho] = distancia[no] + 1;
                if (distancia[vizinho] > distanciaMaxima) {
                    distanciaMaxima = distancia[vizinho];
                }
                fila.push(vizinho);
            }

            aresta = aresta->getProxAresta();
        }
    }

    // Verifica se ainda há vértices com distância -1
    for (No& no : listaNos()) {
        if (distancia[&no] == -1) {
            return INT_MAX; // Grafo desconexo, retorna infinito
        }
    }

    return distanciaMaxima;
}

