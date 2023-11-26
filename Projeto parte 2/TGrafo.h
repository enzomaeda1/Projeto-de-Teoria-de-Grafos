#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <queue>

/*
Implementa�o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjac�ncia
e m�todos para utiliza�o de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

// defini�o de uma estrutura para armezanar um grafo
// Tamb�m seria poss�vel criar um arquivo grafo.h 
// e fazer a inclus�o "#include <grafo.h>"
class TGrafo{
	private:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		int **adj; //matriz de adjac�ncia
	public:
		TGrafo( int n);
		void insereA(int v, int w, int num);
		void removeA(int v, int w);
		void show();
    void insereV(int v);
    void removeV(int v);
    void lerArquivo(const std::string& nomeArquivo);
    void verificarTipoGrafo();
    void verificarConexao();
    void salvarArquivo(const std::string& nomeArquivo);
    void caminhosMinimos(int origem);
    int encontrarVerticeMenorDistancia(const std::vector<int>& distancia, const std::vector<bool>& visitado);
    void exibirCaminhosMinimos(int origem, const std::vector<int>& distancia, const std::vector<int>& anterior);
    void coloracao();
    int grauDoVertice(int vertice);
    bool ehEuleriano();
    void dfs(int vertice, std::vector<bool>& visitado);
		~TGrafo();		
};

#endif
