#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX 1000      //MAX é número máximo de usuários que serão cadastrados.
#define MAX_C 100 + 2 //MAX_C é número máximo de caracteres que cada variável char pode ler.

//Índice das funções:
bool verificaContinuidade();                //Função que verifica se o usuário quer continuar o programa.
void preencheId(int *id, int posicao_cont); //Função que radomiza os IDs.

/*Ideias;
Usar vetor de vetores para faciliar a leitura e organização dos dados.
Reservar 0,'\0' e false como sinal de espaço vazio no vetor.
Verificar se há menos de 1000 cadastros realizados quando solicitar um novo cadastro.
Padronizar a leitura das strings(talvez fgets?).
*/
int main()
{
    setlocale(LC_ALL, "Portuguese"); //Função que habilita a formatação em Português para todos os printfs.
    srand((int)time(0));             //Função que da a semente para o calculo da função rand().

    int id[MAX];
    char nome_completo[MAX][MAX_C];
    char email[MAX][MAX_C];
    char genero[MAX][12 + 2];
    char endereco[MAX][MAX_C];
    double altura[MAX];
    bool vacina[MAX];

    do
    {
        //menu
        //ler a escolha do usuario
        //switch
    } while (verificaContinuidade() == true);

    return 0;
}
void preencheId(int *id, int posicao_cont)
{
    int numero_randomico;
    bool aux;
    if (posicao_cont > 0) //Caso não seja a primeira vez que a função é chamada.
    {
        do //Loop do-while da um valor para numero_randomico e verifica se ele existe no vetor id.
        {
            aux = false;
            numero_randomico = (1 + rand() % MAX);
            for (int i = 0; i < posicao_cont; i++) //O loop for percorre o vetor id e verifica se o numero_randomico já existe no vetor.
                if (numero_randomico == id[i])
                    aux = true;
        } while (aux == true); //Caso o numero_randomico não exista no vetor ele é escrito na primeira posição disponível.
        id[posicao_cont] = numero_randomico;
    }
    else //Caso seja a primeira vez que a função é chamada, ela simplesmente recebe um número aleatório.
    {
        numero_randomico = (1 + rand() % MAX);
        id[posicao_cont] = numero_randomico;
    }
}
bool verificaContinuidade()
{
    printf("Para continuar aperte a tecla Enter...\n");
    char caractere;
    caractere = getchar(); //Leitura do caractere.
    if (caractere == '\n') //Retorna true se o caractere for igual a '\n' (o usuário apertou enter).
        return true;
    else
        return false; //Retorna false se o usuário inseriu algo diferente de enter.
}