########################################################
################# Algoritmo de Prim ####################
########################################################

Pontifícia Universidade Católica do Rio de Janeiro (PUC-RIO)
Programa de Pós-Graduação em Informática
Departamento de Informática
Projeto e Análise de Algoritmos
Professor Marcus Poggi.

Junho de 2013
########################################################

#Componentes:

André Moreira – 1312365
Bruno Olivieri - 1312367
Eduardo Farias - 1312373
Rafael Pereira – 1312402

#Como compilar:

g++ *.cpp -o main -std=c++0x

Obs: O comando -std=c++0x indica ao compilador para utilizar o padrão C++0x ISO c++. Tal comando foi necessário devido a utilização da biblioteca padrão chrono para a medição de tempo.


#Como executar:

./main [Algoritmo] [Arquivo]

[Algoritmo]
	0 - Prim com AVL
	1 - Prim com Heap Binária sem Lazy
	2 - Prim com Heap de Fibonacci
	3 - Prim com Heap Binária com Lazy
	4 - Prim com Vetor

[Arquivo]
	Arquivo de entrada representando Grafo.
	Alguns exemplos na pasta ./data


Output:
	Arquivo resultados.txt

Formato de Saída:
	[Algoritmo Utilizado];[Arquivo de Entrada]; [Quantidade de Nós]; [Quantidade de Arestas]; [Tempo Total de Execução]; [Quantidade de Execuções do Algoritmo]; [Média do Tempo/Execução]
	
