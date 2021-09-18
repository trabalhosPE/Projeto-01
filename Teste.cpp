#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX 1000     //MAX é número máximo de usuários que serão cadastrados.
#define MAX_C 50 + 2 //MAX_C é número máximo de caracteres que cada variável char pode ler.

//Índice das funções:
void preencheId(int *id, int posicao);//Função que radomiza os IDs.
 //Função para verificar se o ID existe e passar para a edição.
void verificaNome(char nome_completo[MAX][MAX_C], int posicao); //Função que verifica se o nome não é nulo.
void verificaEmail(char email[MAX][MAX_C], int posicao);        //Função que verifica se o email é valido.
void verificaGenero(char genero[MAX][MAX_C], int posicao);      //Função que verifica se o gênero é válido.
void verificaAltura(double *altura, int posicao);               //Função que verifica se a altura é válida.
void verificaVacina(bool *vacina, int posicao);                 //Função que verifica se o usuário é vacinado.
void verificaLogin(char *login);  
int ValidaID(int idValido[]);      //teste ricardo - funçao validar o id
void editar (int id[] ,char nome_completo[][MAX_C] ,char genero[][MAX_C] ,char endereco[][MAX_C] ,double altura[] ,char email[][MAX_C] ,bool vacina[]);    //teste ricardo - funçao edit              
int main()
{
    setlocale(LC_ALL, "Portuguese"); //Função que habilita a formatação em Português para todos os printfs.
    srand((int)time(0));             //Função que da a semente para o calculo da função rand().

    int usuario = 0; //Variavel que indica a o número de cadastros realizados
    int id[MAX],id_aux[MAX];
    int menu;
    char login[MAX_C];
    char nome_completo[MAX][MAX_C];
    char email[MAX][MAX_C];
    char genero[MAX][MAX_C];
    char endereco[MAX][MAX_C];
    double altura[MAX];
    bool vacina[MAX];

    printf("Olá, seja bem-vindo ao cadastro online da Universidade Católica de Brasília.\n"); // START DO PROGRAMA
    printf("Digite seu primeiro e ultimo nome para iniciar: ");
    fgets(login, MAX_C, stdin); //Lê o login
    verificaLogin(login);

    do
    {
        system("cls"); // MENU INICIAL
        printf("-----------------\n");
        printf("MENU:\n");
        printf("1 - CADASTRO\n");
        printf("2 - EDITAR CADASTRO\n");
        printf("3 - EXCLUIR CADASTRO\n");
        printf("4 - PROCURAR CADASTRO VIA ID\n");
        printf("5 - PROCURAR CADASTRO VIA E-MAIL\n");
        printf("6 - LISTA DE CADASTROS\n");
        printf("7 - BACKUP DE CADASTROS\n");
        printf("8 - RESTAURAÇÃO (Backup necessário)\n");
        printf("9 - SAIR\n");
        printf("Escolha: ");
        scanf("%d", &menu);
        system("cls");
        getchar();

        switch (menu)
        { // caso 1 : cadastros
        case 1:
            if (usuario < MAX) //Se ainda houver vagas para novos usuários...
            {
                //ID
                preencheId(id, usuario);
                //Nome completo
                printf("Informe o seu nome completo: ");
                fgets(nome_completo[usuario], MAX_C, stdin);
                verificaNome(nome_completo, usuario);
                //Email
                printf("Informe o seu email: ");
                fgets(email[usuario], MAX_C, stdin);
                verificaEmail(email, usuario);
                //Gênero
                printf("Informe o seu gênero. Escreva \"Feminino\", \"Masculino\" ou \"Não Declarar\": ");
                fgets(genero[usuario], MAX_C, stdin);
                verificaGenero(genero, usuario);
                //Endereço
                printf("Informe o seu endereço: ");
                fgets(endereco[usuario], MAX_C, stdin);
                //Altura
                printf("Informe a sua altura: ");
                scanf("%lf", &altura[usuario]);
                verificaAltura(altura, usuario);
                getchar();
                //Vacina
                printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
                verificaVacina(vacina, usuario);
                //Próximo usuário
                usuario++;
            }
            else
            {
                system("cls");
                printf("A capacidade máxima de usuários cadastrados já foi atingida.\n");
                system("pause");
            }
            break;
        case 2:
        	editar(id,nome_completo,genero,endereco,altura,email,vacina);
            break;
        case 3:
            //fazer
            break;
        case 4:
            //fazer
            break;
        case 5:
            //fazer
            break;
        case 6:
            //fazer
            break;
        case 7:
            //fazer
            break;
        case 8:
            //fazer
            break;
        }
    } while (menu != 9);
}

//Funções:

void verificaVacina(bool *vacina, int posicao)
{
    char aux[4 + 2];
    fgets(aux, 4 + 2, stdin); //Lê uma string com sim ou não
    fflush(stdin);
    for (int i = 0; i < strlen(aux); i++)
        aux[i] = tolower(aux[i]); //Deixa todas as letras em minúsculo
    if (strcmp(aux, "sim\n") == 0)
    {
        vacina[posicao] = true; //Se sim a vacina é true
        printf("Vacina cadastrada com sucesso!\n");
    }
    else if (strcmp(aux, "não\n") == 0 || strcmp(aux, "nÃo\n") == 0)
    {
        vacina[posicao] = false; //Se não a vacina é false
        printf("Vacina cadastrada com sucesso!\n");
    }
    else
    {
        if (strchr(aux, '\n') == NULL) //Por causa da forma como o fgets lê e da necessidade da função eu coloquei um "eliminador" de \n
            while (getchar() != '\n')
                ;
        system("cls");
        printf("Você deve escrever apenas \"Sim\" ou \"Não\".\n");
        printf("Você se vacinou? ");
        verificaVacina(vacina, posicao); //A função chama a si mesma (recursividade)
    }
}
void verificaAltura(double *altura, int posicao)
{
    if (altura[posicao] < 1 || altura[posicao] > 2) //Se for menor que 1 ou maior que 2, lê de novo
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
    for (int i = 0; i < strlen(genero[posicao]); i++)
        genero[posicao][i] = tolower(genero[posicao][i]); //Deixa a string em minúsculo
    if (strcmp(genero[posicao], "masculino\n") == 0)      //Se for masculino...
    {
        strcpy(genero[posicao], "Masculino.\n"); //Substitui a string pro "Masculino.\n"
        printf("Gênero cadastrado com sucesso!\n");
    }
    else if (strcmp(genero[posicao], "feminino\n") == 0) //Se for feminino...
    {
        strcpy(genero[posicao], "Feminino.\n"); //Substitui a string pro "Feminino.\n"
        printf("Gênero cadastrado com sucesso!\n");
    }
    else if (strcmp(genero[posicao], "não declarar\n") == 0 || strcmp(genero[posicao], "nÃo declarar\n") == 0) //Se for não declarar...
    {
        strcpy(genero[posicao], "Não declarado.\n"); //Substitui a string pro "Não declarado.\n"
        printf("Gênero cadastrado com sucesso!\n");
    }
    else //Se for inválido...
    {
        system("cls");
        printf("O gênero deve ser Feminino, Masculino ou Não Declarar.\n");
        printf("Informe o seu gênero: ");
        fgets(genero[posicao], MAX_C, stdin);
        verificaGenero(genero, posicao); //A função chama a si mesma (recursividade)
    }
}
void verificaEmail(char email[MAX][MAX_C], int posicao)
{
    if (strchr(email[posicao], '@') == NULL) //Checa se o '@' não existe na string
    {
        do
        {
            system("cls");
            printf("O email deve conter um \"@\".\n");
            printf("Informe o seu email: ");
            fgets(email[posicao], MAX_C, stdin);
        } while (strchr(email[posicao], '@') == NULL);
        printf("Email cadastrado com sucesso!\n");
    }
    else
        printf("Email cadastrado com sucesso!\n");
}
void verificaNome(char nome_completo[MAX][MAX_C], int posicao)
{
    if (strcmp(nome_completo[posicao], "\n") == 0) //Se o nome for vazio...
    {
        do
        {
            system("cls");
            printf("O nome não pode ser nulo.\n");
            printf("Informe o seu nome completo: ");
            fgets(nome_completo[posicao], MAX_C, stdin);
        } while (strcmp(nome_completo[posicao], "\n") == 0);
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
    	printf("O seu ID é: %d\n",id[posicao]);
    	printf("**ATENÇÃO: Para editar ou excluir o seu cadastro será necessário o ID, guarde-o\n**");
}
void verificaLogin(char *login)
{
    do
    {
        if (strlen(login) <= 5)
        {
            printf("Insira um nome válido!\n");
            fgets(login, MAX_C, stdin);
        }
    } while (strlen(login) <= 5);
}
void editar(int id[], char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double altura[], char email[][MAX_C]){
	int id_aux, i,menu; // função para a aba de edit
	char aux;
	do{
		printf("Informe o ID para continuar: ");
		scanf("%i", &id_aux);
		fflush(stdin);
		for(i = 0; i < MAX; i++){
			if(id[i] == id_aux){
				id[i] = ValidaID(id);
				do{
					
						printf("Deseja editar o: \n");
						printf("1. Nome: %s\n",nome_completo[i]);
						printf("2. Sexo: %s\n",genero[i]);
						printf("3. Endereço: %s\n",endereco[i]);
						printf("4. Altura: %.2lf\n",altura[i]);
						printf("5. Email: %s\n",email[i]);
						scanf("%d",&menu);
						switch(menu){
							case 1:
								break;
							case 2:
								break;
							case 3:
								altura[i] = verificaAltura(altura,i);
								break;
							case 4:
								break;
							case 5:
								break;
}
				if(menu<1 || menu>5){
					printf("Escolha algo para editar.");
					}
				}while(menu<1 || menu>5);
			}
		}
			printf("Deseja editar outro dado[S|N] ? ");
			scanf("%c", &aux);
			fflush(stdin);
	}while (aux == 'S' || aux == 's');
}
int ValidaID(int idValido[]){ // função que valida o ID se existe ou não. Falta trocar a validaçao para ID existente no vetor
	int id;
	do{
		printf("Digite o seu ID: \n");
		scanf("%i", &id);
		if(id<1 || id>1000){
			printf("ID Invalido");
		}
	}while(id<1 || id>1000);
	return id;
}
