#include <vector>
#include "heap.hpp"
#include <iostream>
#include <stdlib.h>

int Heap::parent(int i){
    int temp = (i+1)/2;
    return temp-1;
}

int Heap::left(int i){
    int temp = 2*i+1;
    return temp;
}

int Heap::right(int i){
    int temp = 2*(i+1);
    return temp;
}

void Heap::build(std::vector<noHeap> temp){

    vetor.assign(temp.begin(),temp.end());

    ptr.resize(vetor.size());

    for(unsigned i=0;i<vetor.size();i++){
        ptr.at(vetor[i].idNo) = (vetor.begin()+i);
    }

    lenght = vetor.size();
    for (int i = lenght/2; i >= 0; i--){
        heapify(i);
    }
}

void Heap::heapify(int i){
    int menor = NULL;
    int l =left(i);
    int r = right(i);

    if((l <= (lenght-1)) && (vetor[l].prioridade < vetor[i].prioridade )){
        menor = l;
    } else {
        menor = i;
    }

    if ((r <= (lenght-1)) && (vetor[r].prioridade  < vetor[menor].prioridade ))
        menor = r;

    if(menor >= lenght)
        menor = lenght -1;

    if(menor != i){
        swapValues(i, menor);
        heapify(menor);
    }

}

void Heap::swapValues(int i, int iDest){
    noHeap temp;

    temp = vetor[i];

    vetor[i] = vetor[iDest];
    vetor[i].pos = i;
    vetor[iDest] = temp;
    vetor[iDest].pos = iDest;

    ptr[vetor[iDest].idNo] = vetor.begin() + iDest;
    ptr[vetor[i].idNo] = vetor.begin() + i;
}


void Heap::printVector(){
    cout << "Pos - Prioridade - Identificador (Vector)" << endl;
    for (int i = 0; i < lenght; ++i)
        cout << i << " - " << vetor[i].prioridade << " - " << vetor[i].idNo << endl;
    cout << endl;
}

void Heap::printPtr(){
    cout << "Pos - Prioridade - Identificador (Iterator)" << endl;
    for (unsigned i = 0; i < ptr.size(); ++i)
        cout << i << " - " << (*ptr[i]).prioridade << " - " << (*ptr[i]).idNo << endl;
    cout << endl;
}

noHeap Heap::extractHead(){
    if((lenght-1) < 0){
        cout << "Heap vazio!" << lenght << endl;
        exit(1);
    }
    noHeap max = vetor[0];
    lenght = lenght - 1;

    ///Sem esse if, o código bugava na hora de remover o último elemento e dar return
    if(lenght>0){
        vetor[0] = vetor[lenght];
        heapify(0);
    }
    return max;
}

void Heap::update(int i, int newValue){
    if(newValue>(int)(*ptr[i]).prioridade){
        printf("Erro! Tentativa de atualizar para um valor maior");
        return;
    }
    (*ptr[i]).prioridade = newValue;
    i = (*ptr[i]).pos;

    while((i > 0)&&(vetor[parent(i)].prioridade > vetor[i].prioridade)){
        swapValues(i, parent(i));
        i = parent(i);
    }
}

void Heap::insert(int newValue,unsigned key){
    lenght = lenght+1;
    vetor[lenght-1] = noHeap(newValue,key,lenght-1);
    update(lenght-1, newValue);
}

Heap::~Heap(){

}
