#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <queue>
#include "TGrafo.h"

// Construtor do TGrafo, respons�vel por 
// Criar a matriz de adjac�ncia v x v do Grafo
TGrafo::TGrafo( int n ){
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
    this->m = 0; 
    // aloca da matriz do TGrafo
    int **adjac = new int*[n];
    for(int i = 0; i < n; i++)
    	adjac[i]= new int[n];
    adj = adjac;
    // Inicia a matriz com zeros
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j]=0;	
}

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafo::~TGrafo(){
	n = 0;
	m = 0;
	delete [] *adj;
	std::cout << "espa�o liberado";
}

// Insere uma aresta no Grafo tal que
// v é adjacente a w com o número da aresta especificado
void TGrafo::insereA(int v, int w, int numeroAresta) {
    // Verifica se o número da aresta já foi usado
    if (adj[v][w] == 0) {
        adj[v][w] = numeroAresta;
        m++; // Atualiza a quantidade de arestas
    } else {
        std::cout << "A aresta entre os vértices " << v << " e " << w << " já existe com o número " << adj[v][w] << "." << std::endl;
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] == 1 ){
        adj[v][w] = 0;
        m--; // atualiza qtd arestas
    }
}

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência com números de aresta
void TGrafo::show() {
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "\n";
        for (int w = 0; w < n; w++) {
            if (adj[i][w] > 0) {
                std::cout << "Adj[" << i << "," << w << "]=" << adj[i][w] << " ";
            } else {
                std::cout << "Adj[" << i << "," << w << "]=- ";
            }
        }
    }
    std::cout << "\nfim da impressao do grafo." << std::endl;
}


// Insere um vértice no Grafo
void TGrafo::insereV(int novoVertice) {
    // Verifica se o vértice já existe
    if (novoVertice >= 0 && novoVertice < n) {
        std::cout << "O vértice " << novoVertice << " já existe." << std::endl;
    } else if (novoVertice < 0) {
        std::cout << "O número do vértice deve ser não negativo." << std::endl;
    } else {
        // Cria uma nova matriz de adjacência com um vértice a mais
        int **novaMatriz = new int*[n + 1];
        for (int i = 0; i < n + 1; i++)
            novaMatriz[i] = new int[n + 1];

        // Copia os valores da matriz anterior para a nova matriz
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                novaMatriz[i][j] = adj[i][j];
            }
        }

        // Inicializa as novas entradas da matriz com zeros
        for (int i = 0; i <= n; i++) {
            novaMatriz[i][n] = 0;
            novaMatriz[n][i] = 0;
        }

        // Libera a matriz anterior e atualiza o ponteiro
        for (int i = 0; i < n; i++) {
            delete[] adj[i];
        }
        delete[] adj;

        adj = novaMatriz;
        n++; // Atualiza o número de vértices
        std::cout << "Vértice " << novoVertice << " inserido com sucesso." << std::endl;
    }
}

// Remove um vértice do Grafo
void TGrafo::removeV(int verticeRemover) {
    if (verticeRemover < 0 || verticeRemover >= n) {
        std::cout << "O vértice " << verticeRemover << " não existe." << std::endl;
    } else {
        // Cria uma nova matriz de adjacência com um vértice a menos
        int **novaMatriz = new int*[n - 1];
        for (int i = 0; i < n - 1; i++)
            novaMatriz[i] = new int[n - 1];

        int novaI = 0;
        int novaJ = 0;

        // Copia os valores da matriz anterior para a nova matriz,
        // ignorando a linha e coluna correspondentes ao vértice a ser removido
        for (int i = 0; i < n; i++) {
            if (i != verticeRemover) {
                novaJ = 0;
                for (int j = 0; j < n; j++) {
                    if (j != verticeRemover) {
                        novaMatriz[novaI][novaJ] = adj[i][j];
                        novaJ++;
                    }
                }
                novaI++;
            }
        }

        // Libera a matriz anterior e atualiza o ponteiro
        for (int i = 0; i < n; i++) {
            delete[] adj[i];
        }
        delete[] adj;

        adj = novaMatriz;
        n--; // Atualiza o número de vértices
        std::cout << "Vértice " << verticeRemover << " removido com sucesso." << std::endl;
    }
}

// Função para ler um arquivo no formato especificado e criar um grafo
void TGrafo::lerArquivo(const std::string& nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo.c_str(), "r"); // Abra o arquivo em modo de leitura

    if (arquivo == nullptr) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    int numVertices, numArestas;
    fscanf(arquivo, "%d %d", &numVertices, &numArestas);

    this->n = numVertices;
    this->m = 0; // Inicializa o número de arestas como zero

    // Aloca a matriz do TGrafo
    int **adjac = new int*[numVertices];
    for (int i = 0; i < numVertices; i++)
        adjac[i] = new int[numVertices];

    // Inicializa a matriz com zeros
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            adjac[i][j] = 0;
        }
    }

    adj = adjac;

    // Lê as arestas e seus pesos do arquivo e insere nas duas direções
    int vertice1, vertice2, peso;
    for (int i = 0; i < numArestas; i++) {
        fscanf(arquivo, "%d %d %d", &vertice1, &vertice2, &peso);
        insereA(vertice1 - 1, vertice2 - 1, peso); // De A para B
        insereA(vertice2 - 1, vertice1 - 1, peso); // De B para A
    }

    fclose(arquivo); // Feche o arquivo após a leitura
    std::cout << "Arquivo lido com sucesso." << std::endl;
}

void TGrafo::verificarTipoGrafo() {
    // Verifica se o grafo é desconexo (C0)
    if (m == 0) {
        std::cout << "O grafo é desconexo (C0)." << std::endl;
        return;
    }

    // Verifica se o grafo é fortemente conexo (C3)
    bool fortementeConexo = true;
    for (int v = 0; v < n; v++) {
        std::vector<bool> visitado(n, false);
        std::queue<int> fila;

        // Inicia a busca em largura a partir do vértice v
        fila.push(v);
        visitado[v] = true;

        // Verifica se é possível alcançar todos os outros vértices a partir de v
        while (!fila.empty()) {
            int u = fila.front();
            fila.pop();

            for (int w = 0; w < n; w++) {
                if (adj[u][w] && !visitado[w]) {
                    visitado[w] = true;
                    fila.push(w);
                }
            }
        }

        // Se algum vértice não foi alcançado, o grafo não é fortemente conexo (C3)
        for (int i = 0; i < n; i++) {
            if (!visitado[i]) {
                fortementeConexo = false;
                break;
            }
        }
        if (!fortementeConexo) break;
    }

    if (fortementeConexo) {
        std::cout << "O grafo é fortemente conexo (C3)." << std::endl;
        return;
    }

    // Verifica se o grafo é semi-fortemente conexo (C2) e não é semi-conexo (C1)
    bool semiFortementeConexo = true;
    for (int v = 0; v < n; v++) {
        std::vector<bool> visitado(n, false);
        std::queue<int> fila;

        // Inicia a busca em largura a partir do vértice v
        fila.push(v);
        visitado[v] = true;

        // Verifica se é possível alcançar todos os outros vértices a partir de v
        while (!fila.empty()) {
            int u = fila.front();
            fila.pop();

            for (int w = 0; w < n; w++) {
                if (adj[u][w] && !visitado[w]) {
                    visitado[w] = true;
                    fila.push(w);
                }
            }
        }

        // Se algum vértice não foi alcançado, o grafo é semi-fortemente conexo (C2)
        for (int i = 0; i < n; i++) {
            if (!visitado[i]) {
                semiFortementeConexo = false;
                break;
            }
        }

        // Verifica se o grafo é semi-conexo (C1)
        if (!semiFortementeConexo) {
            bool semiConexo = true;
            for (int i = 0; i < n; i++) {
                std::vector<bool> visitado(n, false);
                std::queue<int> fila;

                // Inicia a busca em largura a partir do vértice v
                fila.push(i);
                visitado[i] = true;

                // Verifica se é possível alcançar todos os outros vértices a partir de v
                while (!fila.empty()) {
                    int u = fila.front();
                    fila.pop();

                    for (int w = 0; w < n; w++) {
                        if (adj[u][w] && !visitado[w]) {
                            visitado[w] = true;
                            fila.push(w);
                        }
                    }
                }

                // Se algum vértice não foi alcançado, o grafo é semi-conexo (C1)
                for (int j = 0; j < n; j++) {
                    if (!visitado[j]) {
                        semiConexo = false;
                        break;
                    }
                }
                if (!semiConexo) break;
            }

            if (semiConexo) {
                std::cout << "O grafo é simplesmente-conexo (C1) e não é semi-fortemente conexo (C2)." << std::endl;
                return;
            }
        }
    }

    // Se nenhuma das condições acima for atendida, o grafo é desconexo (C0)
    std::cout << "O grafo é desconexo (C0)." << std::endl;
}

void TGrafo::salvarArquivo(const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao criar o arquivo." << std::endl;
        return;
    }

    // Escreve o número de vértices e o número de arestas na primeira e segunda linhas
    arquivo << n << std::endl;
    arquivo << m << std::endl;

    // Escreve as arestas no formato vértice1 vértice2 peso
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i][j] > 0) {
                arquivo << i + 1 << " " << j + 1 << " " << adj[i][j] << std::endl;
            }
        }
    }

    arquivo.close();
    std::cout << "Informações do grafo salvas em " << nomeArquivo << " com sucesso." << std::endl;
}
