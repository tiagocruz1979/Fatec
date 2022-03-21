#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


// Fun��o para preencher uma matriz utlizando a entrada padr�o (teclado)
void preencherMatriz(int ordem ,vector<vector<int> > &matriz)
{
    int valor;
    vector<int> vLinha;
    for ( int i = 0 ; i < ordem ; i++)
    {
        for (int j = 0 ; j < ordem ; j++)
        {
            std::cout << "Informe o valor para linha " << i + 1 << " coluna " << j +1  << ": ";
            std::cin >> valor;
            vLinha.push_back(valor);
        }
        matriz.push_back(vLinha);
        vLinha.clear();
    }
}

//Fun��o apenas para exibi��o de uma matriz na sa�da padr�o (monitor)
void imprimeMatriz(vector<vector<int> > &m)
{
    int linhas = m.size();
    int colunas = m[0].size();

    for(size_t i = 0; i < linhas;i++)
    {
        std::cout << "| ";
        for (size_t j = 0; j < colunas;j++)
        {
            std::cout << m[i][j];
            if(j < colunas - 1) std::cout << "  ";
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
}


 // fun��o principal onde � calculado a determinando utilizando a recursividade
 int determinante(vector<vector<int> > &matriz)
{
    // quando a entrada for uma matriz de ordem 1 , retorna como determinante o seu pr�prio valor
    if(matriz.size()==1)
    {
        return matriz[0][0];
    }

    //Caso a matriz seja de ordem maior que 1 , � criado uma matriz auxiliar excluindo a linha 0 e uma coluna por vez e
    // chamando a fun��o novamente com esta nova matriz
    int soma = 0;
    vector<vector<int> > matrizResultado;  // Matriz auxiliar (utilizado a classe vector para criar matriz dinamicamente conforme o informado pelo usu�rio)
    vector<int>vLinha; // vector auxiliar para montar a matriz auxiliar

    // linha fixada em 0
    for(size_t coluna = 0 ; coluna < matriz.size(); coluna++)
    {
        matrizResultado.clear();
        for(size_t i = 1;i<matriz.size(); i ++)
        {
            vLinha.clear();
            for(size_t j = 0; j < matriz.size(); j++)
            {
                if(coluna != j)
                {
                    vLinha.push_back(matriz[i][j]);
                }
            }
            matrizResultado.push_back(vLinha);
        }
        // abaixo � calculado a determinante utilizando a f�rmula: (-1)^(i+j) * aij * det(A-,A-j)
        soma+= pow(-1,1+(1 + coluna)) * matriz[0][coluna] * determinante(matrizResultado);
    }
    return soma;
}

int main()
{

// declara��o das vari�veis de entrada
int det;
int ordem;
char sair;

do // loop para op��o de inserir dados para uma nova matriz
{
    system("cls"); // limpa a tela
    std::cout << "Informe a ordem da matriz: ";
    std::cin >> ordem ; // recebe entrada do teclado e atribiu � vari�vel
    if(ordem==0) break;

    vector<vector<int> > matriz; // declara a matriz com uso da classe vector dinamicamente , de acordo com a ordem desejada
    preencherMatriz(ordem,matriz); // chama a fun��o para preencher a matriz

    det = determinante(matriz); // atribui o resultado do determinando a vari�vel

    std::cout << "\nResultado\n\nMatriz" << std::endl;
    imprimeMatriz(matriz); // mostra a vari�vel de entrada na tela
    std::cout << "Determinante: " << det;
    std::cout << std::endl;

    std::cout << "\n\nGerar outra matriz? (s/n)";
    std::cin >> sair;
} while(sair=='s' || sair =='S'); // se resposta por S , retorna para o ponto do

return 0; // finaliza o programa
}
