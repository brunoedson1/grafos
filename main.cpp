#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits>
#include "Grafo.h"
#include <cmath>
#include "Aresta.h"
#include "No.h"

using namespace std;

Grafo *ler(ifstream &entrada)
{
    int ordem_grafo;
    int id_cauda;
    int id_cabeca;
    char aux;
    int aux2;
    float peso;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo);

    entrada >> ordem_grafo >> aux2;

    cout << "A ordem do grafo é: " << ordem_grafo << endl;

    while (entrada >> aux >> id_cabeca >> id_cauda)
        grafo->insereAresta(id_cauda, id_cabeca, 1);

    // grafo->imprime();

    return grafo;
}

int main(int argc, char const *argv[])
{
    ifstream entrada;
    ofstream saida;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo);

    if (argc != 6)
    {
        cout << "ERRO: Esperado: <nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 5;
    }

    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    if (entrada.is_open())
        grafo = ler(entrada);
    else
        cout << "Não foi possível abrir o arquivo " << argv[1] << endl;

    No *no = grafo->getPrimeiroNo();
    if (no == nullptr)
    {
        cout << "Grafo Vazio!" << endl;
        return 0;
    }

    while (no != nullptr)
    {
        saida << "(" << no->getId() << ")" << endl;
        Aresta *aresta = no->getPrimeiraAresta();
        saida << " ";
        while (aresta != nullptr)
        {
            saida << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
            aresta = aresta->getProxAresta();
        }
        saida << endl;
        no = no->getProxNo();
    }

    int escolha = 0;
    int noh;
    bool sair = false;

    while (!sair)
    {

        cout << "Menu:" << endl;
        cout << "[1] - Vizinhanca aberta de um no" << endl;
        cout << "[2] - Vizinhanca fechada de um no" << endl;
        cout << "[3] - Verificar se e bipartido" << endl;
        cout << "[4] - Fecho transitivo direto de um no" << endl;
        cout << "[5] - Fecho transitivo indireto de um no" << endl;
        cout << "[6] - Subgrafo induzido por um conjunto de vertices" << endl;
        /*cout << "2. Função 2" << endl;
        cout << "2. Função 2" << endl;
        cout << "2. Função 2" << endl;
        cout << "2. Função 2" << endl;
        cout << "2. Função 2" << endl;

        cout << "0. Sair" << endl;*/
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        // Executa a função correspondente à escolha do usuário
        switch (escolha)
        {
        case 0:
            sair = true;
            break;
        case 1:
            cout << "Informe o no: ";
            cin >> noh;
            grafo->vizinhoAberta(noh);
            break;
        case 2:
            cout << "Informe o no: ";
            cin >> noh;
            grafo->vizinhoFechada(noh);
            break;
        case 3:
            if (grafo->ehBipartido())
            {
                cout << "O grafo eh bipartido" << endl;
            }
            else
            {
                cout << "O grafo nao eh bipartido" << endl;
            };
        case 4:
            cout << "Informe o no: ";
            cin >> noh;
            grafo->fechoTransitivoDireto(noh);
            break;
        case 5:
            cout << "Informe o no: ";
            cin >> noh;
            grafo->fechoTransitivoIndireto(noh);
            break;

        case 6:
            vector<int> vertices;
            int ent;
            cout << "Informe os vertices (envie '0' para sair):" << endl;
            while (true)
            {
               cin >> ent;

                    if (ent == 0)
                    {
                        break; // Sai do loop se o número for zero
                    }

                    vertices.push_back(ent);
            }
            grafo->apresentarSubgrafoInduzido(vertices);
            break;
            // Adicione mais cases para cada função disponível
            /*default:
               cout << "Opção inválida. Tente novamente." <<endl;
                break;*/
        }
    }

    entrada.close();
    saida.close();
    delete grafo;

    return 0;
}