#ifndef HEAPLAZY_H
#define HEAPLAZY_H
#include "tipono.hpp"

using namespace std;

class Heaplazy
{
  public:
    ~Heaplazy();
    int  parent(int i);
    int  left(int i);
    int  right(int i);
    noHeap extractHead();
    void build(std::vector<noHeap> temp);
    void printVector();
    void printPtr();
    void heapify(int i);
    void swapValues(int i, int iDest);
    void update(int i, int newValue);
    void insert(int newValue,unsigned key);

  private:
    std::vector<noHeap> vetor;
    std::vector<int> alterados;
    std::vector<vector<noHeap>::iterator> ptr;

    int lenght;
};
#endif
