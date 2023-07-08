#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <locale>

#include "Grafo.h"
#include "Aresta.h"
#include "No.h"

using namespace std;

Grafo *ler(ifstream &entrada){
    int ordem_grafo;
    int id_cauda;
    int id_cabeca;
    bool digrafo = false;
    char *e = new char;
    Grafo *grafo = new Grafo(digrafo);

    entrada >> ordem_grafo >> e;
    cout << "A ordem do grafo e: " << ordem_grafo << endl;

    while(entrada >> e >> id_cauda >> id_cabeca)
        grafo->insereAresta(id_cauda, id_cabeca, 1);

    // grafo->imprime();
    delete e;
    return grafo;
}

int main(int argc, char const *argv[]){
    ifstream entrada;
    ofstream saida;
    bool digrafo = false;
    Grafo *grafo = new Grafo(digrafo);

    if (argc != 6){
        cout << "ERRO: Esperado: <nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }

    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    if(entrada.is_open())
        grafo = ler(entrada);   
    else
        cout << "Não foi possível abrir o arquivo " << argv[1] << endl;


//     int escolha = 0;
//     int noh;
//     bool sair = false;
//     vector<int> vertices;
//     int ent;
//     while (!sair)
//     {

//         cout << "Menu:" << endl;
//         cout << "[1] - Vizinhanca aberta de um no" << endl;
//         cout << "[2] - Vizinhanca fechada de um no" << endl;
//         cout << "[3] - Verificar se e bipartido" << endl;
//         cout << "[4] - Fecho transitivo direto de um no" << endl;
//         cout << "[5] - Fecho transitivo indireto de um no" << endl;
//         cout << "[6] - Subgrafo induzido por um conjunto de vertices" << endl;
//         cout << "[7] ????????" << endl; /*para digrafos, apresentar as componentes fortemente
//  conexas;*/
//         cout << "[8] ????????" << endl; /*verificar se o grafo é eulerianos;*/
//         cout << "[9] - Nos de articulacao" << endl;
//         cout << "[10] - Arestas ponte" << endl; /*apresentar as arestas ponte;*/
//         cout << "[11] - Centro e Periferia do grafo" << endl;
//         cout << "[12] ????????" << endl; /*Apresentar a AGM do grafo ou, para grafos
// desconexos, as florestas de custo mínimo;*/
//         cout << "[13] Dijkstra ou Floyd" << endl; /*Apresentar o caminho mínimo entre dois vértices
//  usando o algoritmo de Dijkstra ou de Floyd (escolha do
//  usuário).*/

//         cout << "[0] - Sair" << endl;
//         cout << "Escolha uma opcao: ";
//         cin >> escolha;

//         switch (escolha)
//         {
//         case 0:
//             sair = true;
//             break;
//         case 1:
//             cout << "Informe o no: ";
//             cin >> noh;
//             grafo->vizinhancaAberta(noh);
//             break;
//         case 2:
//             cout << "Informe o no: ";
//             cin >> noh;
//             grafo->vizinhancaFechada(noh);
//             break;
//         case 3:
//             if (grafo->ehBipartido())
//             {
//                 cout << "O grafo eh bipartido" << endl;
//             }
//             else
//             {
//                 cout << "O grafo nao eh bipartido" << endl;
//             };
//             break;
//         case 4:
//             cout << "Informe o no: ";
//             cin >> noh;
//             grafo->fechoTransitivoDireto(noh);
//             break;
//         case 5:
//             cout << "Informe o no: ";
//             cin >> noh;
//             grafo->fechoTransitivoIndireto(noh);
//             break;

//         case 6:
            
//             cout << "Informe os vertices (envie '0' para sair):" << endl;
//             while (true)
//             {
//                 cin >> ent;

//                 if (ent == 0)
//                 {
//                     break; // Sai do loop se o número for zero
//                 }

//                 vertices.push_back(ent);
//             }
//             grafo->apresentarSubgrafoInduzido(vertices);
//             break;
//         case  9:

//             grafo->articulacao();
//             break;

//         case 10:

//             grafo->ponte();
//             break;
//         case 11:
//             for (int a : grafo->encontrarCentroDoGrafo())
//             {
//                 cout << "Centro do Grafo: " << a << endl;
//             }
//             for (int a : grafo->calcularPeriferiaDoGrafo())
//             {
//                 cout << "Periferia do Grafo: " << a << endl;
//             }

//             break;

//         case 13:
//             cout<<"1) Dijkstra"<<endl;
//             cout<<"2) Floyd"<<endl;
//             int noh2;
//             cin>>escolha;
//             switch (escolha)
//             {
//             case 1:
//                 cout<<"Informe primeiro nó: "<<endl;
//             cin>>noh;
//             cout<<"Informe segundo nó: "<<endl;
//             cin>>noh2;

//             grafo->caminhoMinimoDijkstra(noh,noh2);
//                 break;
            
//             case 2:
//                 cout<<"Informe primeiro nó: "<<endl;
//             cin>>noh;
//             cout<<"Informe segundo nó: "<<endl;
//             cin>>noh2;

//             grafo->caminhoMinimoFloyd(noh,noh2);
//                 break;
            
//             default:
//                 break;
//             }
            
//             break;
//         case 14:
//             grafo->guloso();
//             break;
//         case 15:
//             grafo->adaptativo(0.5,10);
//             break;
//         case 16:
//             grafo->reativo({0.3,0.5,0.9},20,5);
//             break;

//         default:
//             cout << "Opção inválida. Tente novamente." <<endl;
//         break;
//         }
//     }

    
    clock_t inicio_reativo, fim_reativo;
    float duracao;

    grafo->guloso();
    cout<<endl;

    vector<float> alpha{0.05,0.1,0.15,0.3,0.5};

    for (float a:alpha)
    {   
        cout<<"Alpha: "<<a<<endl;
        grafo->adaptativo(a,500);
        cout<<endl;
    }
    

    entrada.close();
    saida.close();


   
    

    return 0;
}


