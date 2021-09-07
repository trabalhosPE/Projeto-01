#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX 1000     //MAX é número máximo de usuários que serão cadastrados.
#define MAX_C 50 + 2 //MAX_C é número máximo de caracteres que cada variável char pode ler.

//Índice das funções:
void preencheId(int *id, int posicao);                          //Função que radomiza os IDs.
void verificaNome(char nome_completo[MAX][MAX_C], int posicao); //Função que verifica se o nome não é nulo.
void verificaEmail(char email[MAX][MAX_C], int posicao);        //Função que verifica se o email é valido.
void verificaGenero(char genero[MAX][MAX_C], int posicao);      //Função que verifica se o gênero é válido.
void verificaAltura(double *altura, int posicao);               //Função que verifica se a altura é válida.

int main()
{
    setlocale(LC_ALL, "Portuguese"); //Função que habilita a formatação em Português para todos os printfs.
    srand((int)time(0));             //Função que da a semente para o calculo da função rand().

    int usuario = 0; //Variavel que indica a o número de cadastros realizados
    int id[MAX];
    int menu;
    char login[MAX_C];
    char nome_completo[MAX][MAX_C];
    char email[MAX][MAX_C];
    char genero[MAX][MAX_C];
    char endereco[MAX][MAX_C * 2];
    double altura[MAX];
    bool vacina[MAX];
    do
    {
        /*printf("Olá, seja bem vindo ao cadastro online da católica."); // START DO PROGRAMA
        do
        {
            printf("\nDigite seu primeiro e ultimo nome para iniciar: "); // Validação do tamanho de nome
            fgets(login, 35, stdin);
            if (strlen(login) <= 5)
            {
                printf("Insira um nome válido! ");
            }
        } while (strlen(login) <= 5);
*/
        system("cls"); // MENU INICIAL
        printf("-----------------\n");
        printf("CADASTROS ONLINE \n\n");
        printf("1.CADASTRO\n\n");
        printf("2.EDITAR CADASTRO\n\n");
        printf("3.EXCLUIR CADASTRO\n\n");
        printf("4.PROCURAR CADASTRO VIA ID\n\n");
        printf("5.PROCURAR CADASTRO VIA E-MAIL\n\n");
        printf("6.LISTA DE CADASTROS\n\n");
        printf("7.BACKUP DE CADASTROS\n\n");
        printf("8.RESTAURAÇÃO(backup necessário)\n\n");
        printf("9.SAIR\n\n");
        scanf("%d", &menu);
        system("cls");
        getchar();

        switch (menu)
        { // caso 1 : cadastros
        case 1:

            preencheId(id, usuario);

            printf("Informe o seu nome completo: ");
            fgets(nome_completo[usuario], MAX_C, stdin);
            verificaNome(nome_completo, usuario);

            printf("Informe o seu email: ");
            fgets(email[usuario], MAX_C, stdin);
            verificaEmail(email, usuario);
            //
            printf("Informe o seu gênero (Feminino, Masculino ou Não Declarar): ");
            fgets(genero[usuario], MAX_C, stdin);
            verificaGenero(genero, usuario);

            printf("Informe o seu endereço: ");
            fgets(endereco[usuario], MAX_C, stdin);

            printf("Informe a sua altura: ");
            scanf("%lf", &altura[usuario]);
            verificaAltura(altura, usuario);

            usuario++;
            //fazer a verificação do usuario menor que 1000.
        }
    } while (menu != 9);
}
void verificaAltura(double *altura, int posicao)
{
    if (altura[posicao] < 1 || altura[posicao] > 2)
    {
        do
        {
            system("cls");
            printf("A altura deve ser entre 1 e 2 metros.\n");
            printf("Informe a sua altura: ");
            scanf("%lf", &altura[posicao]);
        } while (altura[posicao] < 1 || altura[posicao] > 2);
        printf("Altura cadastrada com sucesso.\n");
    }
    else
        printf("Altura cadastrada com sucesso.\n");
}
void verificaGenero(char genero[MAX][MAX_C], int posicao)
{
    //resolver
    printf("\nGenero invalido.");
}
void verificaEmail(char email[MAX][MAX_C], int posicao)
{
    if (strchr(email[posicao], '@') == NULL)
    {
        do
        {
            system("cls");
            printf("O email deve conter um \"@\".\n");
            printf("Informe o seu email: ");
            fgets(email[posicao], MAX_C, stdin);
        } while (strchr(email[posicao], '@') == NULL);
        printf("Email cadastrado com sucesso.\n");
    }
    else
        printf("Email cadastrado com sucesso.\n");
}
void verificaNome(char nome_completo[MAX][MAX_C], int posicao)
{
    if (strcmp(nome_completo[posicao], "") == 10)
    {
        do
        {
            system("cls");
            printf("O nome não pode ser nulo.\n");
            printf("Informe o seu nome completo: ");
            fgets(nome_completo[posicao], MAX_C, stdin);
        } while (strcmp(nome_completo[posicao], "") == 10);
        printf("Nome cadastrado com sucesso!\n");
    }
    else
        printf("Nome cadastrado com sucesso!\n");
}
void preencheId(int *id, int posicao)
{
    int numero_randomico;
    bool aux;
    if (posicao > 0) //Caso não seja a primeira vez que a função é chamada.
    {
        do //Loop do-while da um valor para numero_randomico e verifica se ele existe no vetor id.
        {
            aux = false;
            numero_randomico = (1 + rand() % MAX);
            for (int i = 0; i < posicao; i++) //O loop for percorre o vetor id e verifica se o numero_randomico já existe no vetor.
                if (numero_randomico == id[i])
                    aux = true;
        } while (aux == true); //Caso o numero_randomico não exista no vetor ele é escrito na primeira posição disponível.
        id[posicao] = numero_randomico;
    }
    else //Caso seja a primeira vez que a função é chamada, ela simplesmente recebe um número aleatório.
    {
        numero_randomico = (1 + rand() % MAX);
        id[posicao] = numero_randomico;
    }
}
