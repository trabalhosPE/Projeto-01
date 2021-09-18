#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX 1000     //MAX � n�mero m�ximo de usu�rios que ser�o cadastrados.
#define MAX_C 50 + 2 //MAX_C � n�mero m�ximo de caracteres que cada vari�vel char pode ler.

//�ndice das fun��es:
void preencheId(int *id, int posicao);//Fun��o que radomiza os IDs.
 //Fun��o para verificar se o ID existe e passar para a edi��o.
void verificaNome(char nome_completo[MAX][MAX_C], int posicao); //Fun��o que verifica se o nome n�o � nulo.
void verificaEmail(char email[MAX][MAX_C], int posicao);        //Fun��o que verifica se o email � valido.
void verificaGenero(char genero[MAX][MAX_C], int posicao);      //Fun��o que verifica se o g�nero � v�lido.
void verificaAltura(double *altura, int posicao);               //Fun��o que verifica se a altura � v�lida.
void verificaVacina(bool *vacina, int posicao);                 //Fun��o que verifica se o usu�rio � vacinado.
void verificaLogin(char *login);  
int ValidaID(int idValido[]);      //teste ricardo - fun�ao validar o id
void editar (int id[] ,char nome_completo[][MAX_C] ,char genero[][MAX_C] ,char endereco[][MAX_C] ,double altura[] ,char email[][MAX_C] ,bool vacina[]);    //teste ricardo - fun�ao edit              
int main()
{
    setlocale(LC_ALL, "Portuguese"); //Fun��o que habilita a formata��o em Portugu�s para todos os printfs.
    srand((int)time(0));             //Fun��o que da a semente para o calculo da fun��o rand().

    int usuario = 0; //Variavel que indica a o n�mero de cadastros realizados
    int id[MAX],id_aux[MAX];
    int menu;
    char login[MAX_C];
    char nome_completo[MAX][MAX_C];
    char email[MAX][MAX_C];
    char genero[MAX][MAX_C];
    char endereco[MAX][MAX_C];
    double altura[MAX];
    bool vacina[MAX];

    printf("Ol�, seja bem-vindo ao cadastro online da Universidade Cat�lica de Bras�lia.\n"); // START DO PROGRAMA
    printf("Digite seu primeiro e ultimo nome para iniciar: ");
    fgets(login, MAX_C, stdin); //L� o login
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
        printf("8 - RESTAURA��O (Backup necess�rio)\n");
        printf("9 - SAIR\n");
        printf("Escolha: ");
        scanf("%d", &menu);
        system("cls");
        getchar();

        switch (menu)
        { // caso 1 : cadastros
        case 1:
            if (usuario < MAX) //Se ainda houver vagas para novos usu�rios...
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
                //G�nero
                printf("Informe o seu g�nero. Escreva \"Feminino\", \"Masculino\" ou \"N�o Declarar\": ");
                fgets(genero[usuario], MAX_C, stdin);
                verificaGenero(genero, usuario);
                //Endere�o
                printf("Informe o seu endere�o: ");
                fgets(endereco[usuario], MAX_C, stdin);
                //Altura
                printf("Informe a sua altura: ");
                scanf("%lf", &altura[usuario]);
                verificaAltura(altura, usuario);
                getchar();
                //Vacina
                printf("Voc� se vacinou? Escreva \"Sim\" ou \"N�o\": ");
                verificaVacina(vacina, usuario);
                //Pr�ximo usu�rio
                usuario++;
            }
            else
            {
                system("cls");
                printf("A capacidade m�xima de usu�rios cadastrados j� foi atingida.\n");
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

//Fun��es:

void verificaVacina(bool *vacina, int posicao)
{
    char aux[4 + 2];
    fgets(aux, 4 + 2, stdin); //L� uma string com sim ou n�o
    fflush(stdin);
    for (int i = 0; i < strlen(aux); i++)
        aux[i] = tolower(aux[i]); //Deixa todas as letras em min�sculo
    if (strcmp(aux, "sim\n") == 0)
    {
        vacina[posicao] = true; //Se sim a vacina � true
        printf("Vacina cadastrada com sucesso!\n");
    }
    else if (strcmp(aux, "n�o\n") == 0 || strcmp(aux, "n�o\n") == 0)
    {
        vacina[posicao] = false; //Se n�o a vacina � false
        printf("Vacina cadastrada com sucesso!\n");
    }
    else
    {
        if (strchr(aux, '\n') == NULL) //Por causa da forma como o fgets l� e da necessidade da fun��o eu coloquei um "eliminador" de \n
            while (getchar() != '\n')
                ;
        system("cls");
        printf("Voc� deve escrever apenas \"Sim\" ou \"N�o\".\n");
        printf("Voc� se vacinou? ");
        verificaVacina(vacina, posicao); //A fun��o chama a si mesma (recursividade)
    }
}
void verificaAltura(double *altura, int posicao)
{
    if (altura[posicao] < 1 || altura[posicao] > 2) //Se for menor que 1 ou maior que 2, l� de novo
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
        genero[posicao][i] = tolower(genero[posicao][i]); //Deixa a string em min�sculo
    if (strcmp(genero[posicao], "masculino\n") == 0)      //Se for masculino...
    {
        strcpy(genero[posicao], "Masculino.\n"); //Substitui a string pro "Masculino.\n"
        printf("G�nero cadastrado com sucesso!\n");
    }
    else if (strcmp(genero[posicao], "feminino\n") == 0) //Se for feminino...
    {
        strcpy(genero[posicao], "Feminino.\n"); //Substitui a string pro "Feminino.\n"
        printf("G�nero cadastrado com sucesso!\n");
    }
    else if (strcmp(genero[posicao], "n�o declarar\n") == 0 || strcmp(genero[posicao], "n�o declarar\n") == 0) //Se for n�o declarar...
    {
        strcpy(genero[posicao], "N�o declarado.\n"); //Substitui a string pro "N�o declarado.\n"
        printf("G�nero cadastrado com sucesso!\n");
    }
    else //Se for inv�lido...
    {
        system("cls");
        printf("O g�nero deve ser Feminino, Masculino ou N�o Declarar.\n");
        printf("Informe o seu g�nero: ");
        fgets(genero[posicao], MAX_C, stdin);
        verificaGenero(genero, posicao); //A fun��o chama a si mesma (recursividade)
    }
}
void verificaEmail(char email[MAX][MAX_C], int posicao)
{
    if (strchr(email[posicao], '@') == NULL) //Checa se o '@' n�o existe na string
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
            printf("O nome n�o pode ser nulo.\n");
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
    if (posicao > 0) //Caso n�o seja a primeira vez que a fun��o � chamada.
    {
        do //Loop do-while da um valor para numero_randomico e verifica se ele existe no vetor id.
        {
            aux = false;
            numero_randomico = (1 + rand() % MAX);
            for (int i = 0; i < posicao; i++) //O loop for percorre o vetor id e verifica se o numero_randomico j� existe no vetor.
                if (numero_randomico == id[i])
                    aux = true;
        } while (aux == true); //Caso o numero_randomico n�o exista no vetor ele � escrito na primeira posi��o dispon�vel.
        id[posicao] = numero_randomico;
    }
    else //Caso seja a primeira vez que a fun��o � chamada, ela simplesmente recebe um n�mero aleat�rio.
    {
        numero_randomico = (1 + rand() % MAX);
        id[posicao] = numero_randomico;
    }
    	printf("O seu ID �: %d\n",id[posicao]);
    	printf("**ATEN��O: Para editar ou excluir o seu cadastro ser� necess�rio o ID, guarde-o\n**");
}
void verificaLogin(char *login)
{
    do
    {
        if (strlen(login) <= 5)
        {
            printf("Insira um nome v�lido!\n");
            fgets(login, MAX_C, stdin);
        }
    } while (strlen(login) <= 5);
}
void editar(int id[], char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double altura[], char email[][MAX_C]){
	int id_aux, i,menu; // fun��o para a aba de edit
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
						printf("3. Endere�o: %s\n",endereco[i]);
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
int ValidaID(int idValido[]){ // fun��o que valida o ID se existe ou n�o. Falta trocar a valida�ao para ID existente no vetor
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
