/*
Enzo Ryo Maeda Kanbayashi 41928369
Gustavo Aragão Guedes 32089678
Gustavo Fernandes Costa 32161093
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "TGrafo.h"

/*
1 Parque Ibirapuera
2 Catedral da Sé
3 Pinacoteca de São Paulo
4 Beco Do Batman
5 Estádio Morumbi
6 Bairro da Liberdade
7 Avenida Paulista
8 Estádio Allianz Parque
9 Neo Química Arena
10 Mercado Municipal
11 Universidade Presbiteriana Mackenzie
12 MASP
13 Museu do Futebol
14 Teatro Municipal
15 25 de Março
16 Jardim Botânico
17 Edificio Italia
18 Copan
19 Estação da Sé
20 Estação Pinheiros
21 Estação da Luz
22 Ponte Estaiada
23 Viaduto do Chá
24 Viaduto Santa Ifigênia
25 Praça da República
26 Vale do Anhangabaú
27 Pateo do Colégio
28 Museu Paulista
29 Palácio dos Bandeirantes
30 Aquário de São Paulo
31 Zoológico de São Paulo
32 Monumento dos Bandeirantes
33 Shopping Iguatemi
34 Shopping JK
35 Shopping Morumbi
36 Shopping Ibirapuera
37 Shopping Aricanduva
38 Zoo Safari
39 Shopping Anália Franco
40 Shopping El Dorado
41 Shopping Tatuapé
42 Shopping Tamboré
43 Shopping Cidade de São Paulo
44 Farol Santander
45 Parque Ibirapuera
46 Parque Villa-Lobo
47 Praia Grande
48 Edifício Altino Arantes
49 Teatro Municipal de São Paulo
50 Museu Catavento  
*/


void mostrarConteudoArquivo(const std::string& nomeArquivo) {
    // Abra o arquivo
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    std::string linha;

    // Leia e mostre o conteúdo linha por linha
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
    }

    // Feche o arquivo
    arquivo.close();
}



int main() {
    int v;
    int w;
    
    TGrafo grafo(0); // Crie um objeto TGrafo vazio

    // Leia o arquivo grafo.txt e preencha o grafo com as informações
    grafo.lerArquivo("matriz/grafo.txt");


    int escolha;
    while (true) {
        std::cout << "\nMenu Grafo dos locais de SP:" << std::endl;
        std::cout << "1. Inserir vértice" << std::endl;
        std::cout << "2. Inserir aresta" << std::endl;
        std::cout << "3. Remover vértice" << std::endl;
        std::cout << "4. Remover aresta" << std::endl;
        std::cout << "5. Mostrar Grafo" << std::endl;
        std::cout << "6. Verificar conexividade" << std::endl;
        std::cout << "7. Mostrar conteudo do arquivo" << std::endl;
        std::cout << "8. Salvar no arquivo grafo2.txt" << std::endl;
        std::cout << "9. Caminhos minimos" << std::endl;
        std::cout << "10. Ver em que grupo cada local esta (Coloracao)" << std::endl;
        std::cout << "11. Ver quantos locais estao ligados diretamente ao local selecionado" << std::endl;
        std::cout << "12. Verificar se o grafo e euleriano" << std::endl;
        std::cout << "13. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1: // Inserir vértice
                int novoVertice;
                std::cout << "Digite o número do novo vértice: ";
                std::cin >> novoVertice;
                grafo.insereV(novoVertice);
                break;
            case 2: // Inserir aresta
                // Solicita ao usuário os vértices e o número da aresta
                int numeroAresta;
                std::cout << "Digite o vértice v: ";
                std::cin >> v;
                std::cout << "Digite o vértice w: ";
                std::cin >> w;
                std::cout << "Digite o número da aresta: ";
                std::cin >> numeroAresta;
                
                grafo.insereA(v, w, numeroAresta);
                break;
            case 3: // Remover vértice
                int verticeRemover;
                std::cout << "Digite o número do vértice a ser removido: ";
                std::cin >> verticeRemover;
                grafo.removeV(verticeRemover);
                break;
            case 4: // Remover aresta
                int arestaV, arestaW;
                std::cout << "Digite o vértice de origem da aresta a ser removida: ";
                std::cin >> arestaV;
                std::cout << "Digite o vértice de destino da aresta a ser removida: ";
                std::cin >> arestaW;
                grafo.removeA(arestaV, arestaW);
                break;
            case 5: // Mostrar Grafo
                grafo.show();
                break;
            case 6: // Mostrar Grafo
                grafo.verificarConexao();
                break;
            case 7:
                mostrarConteudoArquivo("matriz/grafo.txt");
                break;
            case 8:
                grafo.salvarArquivo("grafo2.txt");
                break;
            case 9:
                int n;
                std::cout << "Digite o local inicial para ver o caminho minimo entre todos os outros pontos ";
                std::cin >> n;
                grafo.caminhosMinimos(n);
                break;
            case 10:
                grafo.coloracao();
                break;
            case 11:
                int vertice;
                int grau;
                std::cout << "Digite o local para ver quantos locais estao ligados diretamente a ele ";
                std::cin >> vertice;
                grau = grafo.grauDoVertice(vertice);
                std::cout << "O grau do local " << vertice << " é: " << grau <<std::endl;
                break;

            case 12:
                if (grafo.ehEuleriano()) {
                    std::cout << "O grafo é euleriano." << std::endl;
                } else {
                    std::cout << "O grafo não é euleriano." << std::endl;
                }
                break;
          
            case 13: // Sair
                return 0;

          
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
                break;
        }
    }

    return 0;
}