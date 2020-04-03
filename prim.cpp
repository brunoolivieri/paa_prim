#include <vector>
#include <set>
#include <fstream>
#include "prim.hpp"
#include "heap.hpp"
#include "fibonacci.hpp"
#include "tipono.hpp"
#include "heaplazy.hpp"

using namespace std;

unsigned primAVL(Grafo grafo){
    ///Lista de Adjacência
    vector<std::vector<aresta> > adj = grafo.listaAdj;

    unsigned tamMST = 0; ///qtd de Nós na MST
    unsigned custoMST = 0; ///Custo atual da MST

    /// Distância de todos os nós para a MST
    vector<unsigned> prioridadeAtual(adj.size(),INFINITO);
    prioridadeAtual[0] = 0; ///Nó inicial (0), custo 0

    /// AVL - Árvore Rubro-Negra
    set< pair<unsigned,unsigned> > AVL;

    ///Ponteiros para os nós da ávore
    vector< set< pair<unsigned,unsigned> >::iterator > ponteiro(adj.size());

    ///Insere na árvore o nó 0 com distância 0
    ponteiro[0] = AVL.insert( make_pair(0,0) ).first;

    ///Demais nós com distância infinita
    for (unsigned i=1;i<adj.size();i++) {
        ponteiro[i] = (AVL.insert( make_pair(INFINITO,i) )).first;
    }

    ///Verifica se o nó já faz parte da MST
    vector<bool> inTree(adj.size(),false);


    while(tamMST!=adj.size()){

        tamMST++;

        /// Pega o nó com maior prioridade
        pair<unsigned,unsigned> node;
        node = *AVL.begin();
        AVL.erase(AVL.begin());

        /// Marca como visitado
        inTree[node.second] = true;

        custoMST += node.first;///Incrementa o custo

        /// Verifica a adjacência do nó atual
        for (vector<aresta>::iterator i = adj[node.second].begin();i != adj[node.second].end(); i++) {
            if (inTree[(*i).destino] == false && (*i).peso < prioridadeAtual[(*i).destino]) {
                /// Atualiza na árvore a prioridade do nó
                AVL.erase( ponteiro[(*i).destino] );
                prioridadeAtual[(*i).destino] = (*i).peso;
                ponteiro[(*i).destino] = AVL.insert( make_pair((*i).peso,(*i).destino) ).first;
            }
        }
    }
    return custoMST;
}

unsigned primHeapLazy(Grafo grafo){
    ///Lista de Adjacência
    vector<std::vector<aresta> > adj = grafo.listaAdj;

    unsigned tamMST = 0; ///qtd de Nós na MST
    unsigned custoMST = 0; ///Custo atual da MST

    /// Distância de todos os nós para a MST
    vector<unsigned> minDist(adj.size(),INFINITO);
    minDist[0] = 0; ///Nó inicial (0), custo 0

    vector<noHeap> nosHeap;
    ///Insere todos nos na Heap com custo infinito
    for(unsigned i=0;i<adj.size();i++)
        nosHeap.push_back(noHeap(i,INFINITO,i));

    ///Nó inicial (0) com custo 0
    nosHeap[0].prioridade = 0;
    Heaplazy heap;
    heap.build(nosHeap);

    ///Verifica se o nó já faz parte da MST
    vector<bool> inTree(adj.size(),false);

    ///Enquanto a MST não tem todos os nós do grafo
    while(tamMST!=adj.size()){
        tamMST++;
        /// Pega o nó com maior prioridade
        noHeap node = heap.extractHead();
        inTree[node.idNo] = true;

        custoMST += node.prioridade;

        /// Verifica a adjacência do nó atual
        for (vector<aresta>::iterator i = adj[node.idNo].begin();i != adj[node.idNo].end(); i++) {
            /// Atualiza na árvore a prioridade do nó
            if (inTree[(*i).destino] == false && (*i).peso < minDist[(*i).destino]) {
                minDist[(*i).destino] = (*i).peso;
                heap.update((*i).destino,(*i).peso);
            }
        }
    }
    return custoMST;
}

unsigned primHeap(Grafo grafo){
    ///Lista de Adjacência
    vector<std::vector<aresta> > adj = grafo.listaAdj;

    unsigned tamMST = 0; ///qtd de Nós na MST
    unsigned custoMST = 0; ///Custo atual da MST

    /// Distância de todos os nós para a MST
    vector<unsigned> prioridadeAtual(adj.size(),INFINITO);
    prioridadeAtual[0] = 0; ///Nó inicial (0), custo 0

    vector<noHeap> nosHeap;

    ///Insere todos nos na Heap com custo infinito
    for(unsigned i=0;i<adj.size();i++)
        nosHeap.push_back(noHeap(i,INFINITO,i));

    ///Nó inicial (0) com custo 0
    nosHeap[0].prioridade = 0;
    Heap heap;
    heap.build(nosHeap);

    ///Verifica se o nó já faz parte da MST
    vector<bool> inTree(adj.size(),false);

    while(tamMST<adj.size()){
        tamMST++;

        /// Pega o nó com maior prioridade
        noHeap node = heap.extractHead();
        inTree[node.idNo] = true;

        custoMST += node.prioridade;

        /// Verifica a adjacência do nó atual
        for (vector<aresta>::iterator i = adj[node.idNo].begin();i != adj[node.idNo].end(); i++) {
            if (inTree[(*i).destino] == false && (*i).peso < prioridadeAtual[(*i).destino]) {
                /// Atualiza na árvore a prioridade do nó
                prioridadeAtual[(*i).destino] = (*i).peso;
                heap.update((*i).destino,(*i).peso);
            }
        }
    }
    return custoMST;
}

unsigned primFibonacci(Grafo grafo){
    ///Lista de Adjacência
    vector<std::vector<aresta> > adj = grafo.listaAdj;

    unsigned tamMST = 0; ///qtd de Nós na MST
    unsigned custoMST = 0; ///Custo atual da MST

    /// Distância de todos os nós para a MST
    vector<unsigned> prioridadeAtual(adj.size(),INFINITO);
    prioridadeAtual[0] = 0; ///Nó inicial (0), custo 0

    FibonacciHeap<noHeap> heap;

    ///Verifica se o nó já faz parte da MST
    vector<bool> inTree(adj.size(),false);

    ///Ponteiro para os nós da heap
    vector<node<noHeap>*> posicao(adj.size(),NULL);

    ///Insere todos nos na Heap com custo infinito
    for(unsigned i=1;i<adj.size();i++){
       posicao[i] = heap.insert(noHeap(i,INFINITO,i));
    }
    ///Nó inicial (0) com custo 0
    posicao[0] = heap.insert(noHeap(0,0,0));

    while(tamMST!=adj.size()){
        tamMST++;

        /// Pega o nó com maior prioridade
        noHeap noAtual = heap.removeMinimum();
        inTree[noAtual.idNo] = true;

        custoMST += noAtual.prioridade;

        /// Verifica a adjacência do nó atual
        for (vector<aresta>::iterator i = adj[noAtual.idNo].begin();i != adj[noAtual.idNo].end(); i++) {
            if (inTree[(*i).destino] == false && (*i).peso < prioridadeAtual[(*i).destino]) {
                /// Atualiza na árvore a prioridade do nó
                noHeap novoNo = noHeap((*i).destino,(*i).peso,(*i).destino);
                node<noHeap> * posicaoNo = posicao[(*i).destino];
                heap.decreaseKey(posicaoNo,novoNo);
                prioridadeAtual[(*i).destino] = (*i).peso;
            }
        }
    }

    return custoMST;
}

unsigned primVetor(Grafo grafo){
    ///Lista de Adjacência
    vector<std::vector<aresta> > adj = grafo.listaAdj;

    unsigned tamMST = 0; ///qtd de Nós na MST
    unsigned custoMST = 0; ///Custo atual da MST

    /// Distância de todos os nós para a MST
    vector<unsigned> prioridadeAtual(adj.size(),INFINITO);
    prioridadeAtual[0] = 0; ///Nó inicial (0), custo 0

    ///Verifica se o nó já faz parte da MST
    vector<bool> inTree(adj.size(),false);

    while(tamMST!=adj.size()){
        tamMST++;

        ///Remove o de maior prioridade
        unsigned menor = INFINITO;
        int posMenor = -1;

        for(unsigned i=0;i<prioridadeAtual.size();i++){
            if(inTree[i]==false && prioridadeAtual[i]<menor){
                menor = prioridadeAtual[i];
                posMenor = i;
            }
        }

        inTree[posMenor] = true;
        custoMST += prioridadeAtual[posMenor];

        /// Verifica a adjacência do nó atual
        for (vector<aresta>::iterator i = adj[posMenor].begin();i != adj[posMenor].end(); i++) {
            /// Atualiza na árvore a prioridade do nó
            if (inTree[(*i).destino] == false && (*i).peso < prioridadeAtual[(*i).destino]) {
                prioridadeAtual[(*i).destino] = (*i).peso;
            }
        }

    }
    return custoMST;
}
