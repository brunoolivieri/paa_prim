#ifndef TIPONO
#define TIPONO

using namespace std;
///Tipo abstrato de nó da heap
typedef struct tipono{
    unsigned idNo;
    unsigned prioridade;
    unsigned pos;
    tipono(unsigned idNo,int prioridade,unsigned pos) : idNo(idNo), prioridade(prioridade),pos(pos) {};
    tipono(){};

    bool operator <(const tipono& x) const {
        return (prioridade < x.prioridade);
    }

    bool operator ==(const tipono& x) const {
        return (prioridade == x.prioridade);
    }

    bool operator >(const tipono& x) const {
        return (prioridade > x.prioridade);
    }

}noHeap;

#endif
