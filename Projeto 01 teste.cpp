#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <stdbool.h>

#include <string.h>

#include <time.h>

#define MAX 1000 //MAX � n�mero m�ximo de usu�rios que ser�o cadastrados.
#define MAX_C 100 + 2 //MAX_C � n�mero m�ximo de caracteres que cada vari�vel char pode ler.

//�ndice das fun��es:
bool verificaContinuidade(); //Fun��o que verifica se o usu�rio quer continuar o programa.
void preencheId(int * id, int posicao_cont); //Fun��o que radomiza os IDs.

/*Ideias;
Usar vetor de vetores para faciliar a leitura e organiza��o dos dados.
Reservar 0,'\0' e false como sinal de espa�o vazio no vetor.
Verificar se h� menos de 1000 cadastros realizados quando solicitar um novo cadastro.
Padronizar a leitura das strings(talvez fgets?).
*/

int main() {
  setlocale(LC_ALL, "Portuguese"); //Fun��o que habilita a formata��o em Portugu�s para todos os printfs.
  srand((int) time(0)); //Fun��o que da a semente para o calculo da fun��o rand().
  int z,y;
  int id[MAX], menu; // vetor de id
  int i, contador = 0; // variaveis da valida��o de @
  char nomeLogin[35];
  char nome_completo[MAX][MAX_C]; // vetor de nome com 100 caracteres + 2
  char email[MAX][50]; // 50 o numero de caracteres de email
  char genero[MAX][12 + 2];
  char endereco[MAX][MAX_C];
  double altura[MAX];
  bool vacina[MAX];

  printf("Ol�, seja bem vindo ao cadastro online da cat�lica."); // START DO PROGRAMA
  do {
    printf("\nDigite seu primeiro e ultimo nome para iniciar: "); // Valida��o do tamanho de nome
    fgets(nomeLogin, 35, stdin);
    if (strlen(nomeLogin) <= 5) {
      printf("Insira um nome v�lido! ");
    }
  } while (strlen(nomeLogin) <= 5);

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

  printf("8.RESTAURA��O(backup necess�rio)\n\n");

  printf("9.SAIR\n\n");
  scanf("%d", & menu);
  system("cls");

  switch (menu) { // caso 1 : cadastros
  case 1:
    printf("Nome completo: ");
    scanf("%s", &nome_completo[MAX][MAX_C]);
    do {
      printf("Digite seu email: ");
      fgets(email[MAX], MAX_C, stdin);

      for (i = 0; i < strlen(email[MAX]); i++) {
        if ((email[MAX][i] == '@')) {
          contador++;
        }
      }
      if (contador == 1) {
        printf("Email valido.\n");
        break;
      } else
        printf("Email Invalido.\n");
    } while (contador != 1);

    do {
      printf("\nInforme o sexo(Feminino,Masculino ou N�o Declarar): ");
      scanf("%s", & genero[MAX]);
      fflush(stdin);
      if (stricmp(genero[MAX], "Feminino") && (stricmp(genero[MAX], "Masculino")) && (stricmp(genero[MAX], "N�odeclarar"))) // N�o declarar gera erro ao colocar o espa�o na palavra
        printf("\nGenero invalido.");
    } while (strlen(genero[MAX]) < 8); // Se o sexo for menor de 7 letras ele repete. Possivel altera��o: limitar apenas a 3 generos 
    printf("\nEndere�o: ");
    fgets(endereco[MAX], MAX_C, stdin);
    do {
      printf("Altura: ");
      scanf("%lf", & altura[MAX]);
      if (altura[MAX] < 1 || altura[MAX] > 2)
        printf("Altura invalida.\n");
      fflush(stdin);
    } while (altura[MAX] < 1 || altura[MAX > 2]);
	
  }

}

void preencheId(int * id, int posicao_cont) {
  int numero_randomico;
  bool aux;
  if (posicao_cont > 0) //Caso n�o seja a primeira vez que a fun��o � chamada.
  {
    do //Loop do-while da um valor para numero_randomico e verifica se ele existe no vetor id.
    {
      aux = false;
      numero_randomico = (1 + rand() % MAX);
      for (int i = 0; i < posicao_cont; i++) //O loop for percorre o vetor id e verifica se o numero_randomico j� existe no vetor.
        if (numero_randomico == id[i])
          aux = true;
    } while (aux == true); //Caso o numero_randomico n�o exista no vetor ele � escrito na primeira posi��o dispon�vel.
    id[posicao_cont] = numero_randomico;
  } else //Caso seja a primeira vez que a fun��o � chamada, ela simplesmente recebe um n�mero aleat�rio.
  {
    numero_randomico = (1 + rand() % MAX);
    id[posicao_cont] = numero_randomico;
  }
}
bool verificaContinuidade() {
  printf("Para continuar aperte a tecla Enter...\n");
  char caractere;
  caractere = getchar(); //Leitura do caractere.
  if (caractere == '\n') //Retorna true se o caractere for igual a '\n' (o usu�rio apertou enter).
    return true;
  else
    return false; //Retorna false se o usu�rio inseriu algo diferente de enter.
}
