#include <iostream>
#include <vector>
#include <cmath>
#include <locale.h>
using namespace std;


// Função para preencher uma matriz utlizando a entrada padrão (teclado)
void preencherMatriz(int linhas, int colunas,vector<vector<int> > &matriz)
{
    int valor;
    vector<int> vLinha;
    for ( int i = 0 ; i < linhas ; i++)
    {
        for (int j = 0 ; j < colunas ; j++)
        {
            std::cout << "Informe o valor para linha " << i + 1 << " coluna " << j + 1  << ": ";
            std::cin >> valor;
            vLinha.push_back(valor);
        }
        matriz.push_back(vLinha);
        vLinha.clear();
    }
}

//Função apenas para exibição de uma matriz na saída padrão (monitor)
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


 // função principal onde é calculado a determinando utilizando a recursividade
 int determinante(vector<vector<int> > &matriz)
{
    // quando a entrada for uma matriz de ordem 1 , retorna como determinante o seu próprio valor
    if(matriz.size()==1)
    {
        return matriz[0][0];
    }

    //Caso a matriz seja de ordem maior que 1 , é criado uma matriz auxiliar excluindo a linha 0 e uma coluna por vez e
    // chamando a função novamente com esta nova matriz
    int soma = 0;
    vector<vector<int> > matrizResultado;  // Matriz auxiliar (utilizado a classe vector para criar matriz dinamicamente conforme o informado pelo usuário)
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
        // abaixo é calculado a determinante utilizando a fórmula: (-1)^(i+j) * aij * det(A-,A-j)
        soma+= pow(-1,1+(1 + coluna)) * matriz[0][coluna] * determinante(matrizResultado);
    }
    return soma;
}


std::vector<float> equacaoLinearCramer(std::vector<vector<int> > mEntrada)
{
    vector<float> mResultado; // declaração do vetor que conterá o resultado de cada incógnita
    if (mEntrada.size()<1) return mResultado; //se matriz de entrada estiver varia retorna vazio para a função
    int linhas = mEntrada.size();
    int colunas = mEntrada[0].size();
    if (colunas != linhas+1) return mResultado; // verifica se a matriz de entrada possui uma coluna a mais do que a quantidade de linhas , senão será inválido e retornará vazio

    vector<vector<int> > mAuxiliar1;// cria duas matrizes auxiliares para o calculo de determinante
    vector<vector<int> > mAuxiliar2;
    vector<int> lAuxiliar;
    float numerador, denominador; // recebe a determinante de cada matriz de acordo com o método de Cramer

    for ( int i = 0 ; i < linhas ; i++) // Preenche a Matriz auxiliar 1
    {
        lAuxiliar.clear();
        for( int j = 0 ; j < colunas - 1; j++)
        {
            lAuxiliar.push_back(mEntrada[i][j]);
        }
        mAuxiliar1.push_back(lAuxiliar);
    }
    int det = determinante(mEntrada);
    if (det == 0)
    {
        std::cout << "Não é possível resolver pelo método de Cramer. (Determinante da matriz = 0)" << std::endl;
        return mResultado;
    }

    lAuxiliar.clear();
    for ( int inc = 0 ; inc < linhas ; inc ++) // Preenche a matriz do denominador do método de cramer.
    {
        mAuxiliar2.clear();
        for (int i = 0 ; i < linhas; i++) // troca-se a coluna i pela coluna do resultado da equação
        {
            lAuxiliar.clear();
            for ( int j = 0 ; j < colunas - 1 ; j++)
            {
                if(inc == j)
                {
                    lAuxiliar.push_back(mEntrada[i][colunas-1]);
                }
                else
                {
                    lAuxiliar.push_back(mEntrada[i][j]);
                }
            }
            mAuxiliar2.push_back(lAuxiliar);
        }
    numerador = determinante(mAuxiliar2);
    denominador = determinante(mAuxiliar1);
    mResultado.push_back(numerador/denominador); // preenche o resultado de cada incógnita no vetor resultado
    }

    return mResultado;
}


int main()
{
setlocale(LC_ALL,"Portuguese_Brazil");

// declaração das variáveis de entrada
int det;
int ordem;
char sair;

do // loop para opção de inserir dados para uma nova matriz
{
    system("cls"); // limpa a tela
    std::cout << "Informe o número de incógnitas da Equação Linear: ";
    std::cin >> ordem ; // recebe entrada do teclado e atribiu à variável
    if(ordem==0) break;

    vector<vector<int> > matriz; // declara a matriz com uso da classe vector dinamicamente , de acordo com a ordem desejada
    vector<float> resultado; // vetor com resultado das incógnitas
    preencherMatriz(ordem, ordem +1,matriz); // chama a função para preencher a matriz

    std::cout << "\nMatriz de entrada" << std::endl;
    imprimeMatriz(matriz); // mostra a variável de entrada na tela
    resultado = equacaoLinearCramer(matriz);

    std::cout << "Resultado\n";
    for (size_t i = 0 ; i < resultado.size();i++)
    {
        std::cout << resultado[i];
        if(i < resultado.size()-1) std::cout << " ,  ";
    }
    std::cout << std::endl;


    std::cout << "\n\nGerar outra matriz? (s/n)";
    std::cin >> sair;
} while(sair=='s' || sair =='S'); // se resposta por S , retorna para o ponto do

return 0; // finaliza o programa
}
