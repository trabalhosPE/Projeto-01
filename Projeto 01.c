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
void preencheId(int *id, int posicao);                          //Função que radomiza os IDs.
void verificaNome(char nome_completo[MAX][MAX_C], int posicao); //Função que verifica se o nome não é nulo.
void verificaEmail(char email[MAX][MAX_C], int posicao);        //Função que verifica se o email é valido.
void verificaGenero(char genero[MAX][MAX_C], int posicao);      //Função que verifica se o gênero é válido.
void verificaAltura(double *altura, int posicao);               //Função que verifica se a altura é válida.
void verificaVacina(bool *vacina, int posicao);                 //Função que verifica se o usuário é vacinado.
void verificaLogin(char *login);
bool ValidaID(int *id, int id_aux);
int pegaPosicaoID(int *id, int id_aux);
void cadastraUsuario(int quantidade_usuario, int *id, char nome_completo[][MAX_C], char email[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, bool *vacina, int usuario); //Função que cadastra um usuário.                                                                                                                          //teste ricardo - funçao validar o id
void editarUsuario(int *id, char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, char email[][MAX_C], bool *vacina);                                        //Função que edita um usuário.
void pesquisarCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], int usuario);
void pesquisarEmail(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], int usuario);
void listaCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], int usuario);
void backupCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], int usuario, int *idbkp, char nomebkp[][MAX_C], char emailbkp[][MAX_C], char generobkp[][MAX_C], char enderecobkp[][MAX_C], int back, double *alturabkp);
void restaurarCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], int usuario, int *idbkp, char nomebkp[][MAX_C], char emailbkp[][MAX_C], char generobkp[][MAX_C], char enderecobkp[][MAX_C], int back, double *alturabkp);

int main()
{
  setlocale(LC_ALL, "Portuguese"); //Função que habilita a formatação em Português para todos os printfs.
  srand((int)time(0));             //Função que da a semente para o calculo da função rand().

  int quantidade_usuario = 0, usuario = 0; //Variavel que indica a o número de cadastros realizados
  int id[MAX], id_aux[MAX];
  int menu;
  int qtd = 0, back;
  int idbkp[MAX];
  char nomebkp[MAX][MAX_C], emailbkp[MAX][MAX_C], generobkp[MAX][MAX_C], enderecobkp[MAX][MAX_C];
  char login[MAX_C];
  char nome_completo[MAX][MAX_C];
  char email[MAX][MAX_C];
  char genero[MAX][MAX_C];
  char endereco[MAX][MAX_C];
  double altura[MAX];
  double alturabkp[MAX];
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
    {
    case 1: //CADASTRO DE USUARIO
      cadastraUsuario(quantidade_usuario, id, nome_completo, email, genero, endereco, altura, vacina, usuario);
      break;
    case 2:
      editarUsuario(id, nome_completo, genero, endereco, altura, email, vacina);
      break;
    case 3:
      //fazer
      break;
    case 4:
      pesquisarCadastro(id, nome_completo, email, endereco, altura, genero, usuario); // pesquisar cadastro por id. obs:Arrumar a altura e vacina.
      break;
    case 5:
      pesquisarEmail(id, nome_completo, email, endereco, altura, genero, usuario);
      break;
    case 6:
      listaCadastro(id, nome_completo, email, endereco, altura, genero, usuario);
      break;
    case 7:
      backupCadastro(id, nome_completo, email, endereco, altura, genero, usuario, idbkp, nomebkp, emailbkp, generobkp, enderecobkp, back, alturabkp);
      break;
    case 8:
      restaurarCadastro(id, nome_completo, email, endereco, altura, genero, usuario, idbkp, nomebkp, emailbkp, generobkp, enderecobkp, back, alturabkp);
      break;
    default:
      printf("Opção inválida.\n");
      system("pause");
      break;
    }
  } while (menu != 9);
}

//Funções:
void cadastraUsuario(int quantidade_usuario, int *id, char nome_completo[MAX][MAX_C], char email[MAX][MAX_C], char genero[MAX][MAX_C], char endereco[MAX][MAX_C], double *altura, bool *vacina, int usuario)
{
  if (quantidade_usuario < MAX)
  {
    //ID
    preencheId(id, usuario);
    printf("O seu ID é \"%d\".\n\n", id[usuario]);
    //Nome completo
    printf("Informe o seu nome completo: ");
    fgets(nome_completo[usuario], MAX_C, stdin);
    verificaNome(nome_completo, usuario);
    printf("Nome cadastrado com sucesso!\n\n");
    //Email
    printf("Informe o seu email: ");
    fgets(email[usuario], MAX_C, stdin);
    verificaEmail(email, usuario);
    printf("Email cadastrado com sucesso!\n\n");
    //Gênero
    printf("Informe o seu gênero. Escreva \"Feminino\", \"Masculino\" ou \"Não Declarar\": ");
    fgets(genero[usuario], MAX_C, stdin);
    verificaGenero(genero, usuario);
    printf("Gênero cadastrado com sucesso!\n\n");
    //Endereço
    printf("Informe o seu endereço: ");
    fgets(endereco[usuario], MAX_C, stdin);
    printf("Endereço cadastrado com sucesso!\n\n");
    //Altura
    printf("Informe a sua altura: ");
    scanf("%lf", &altura[usuario]);
    verificaAltura(altura, usuario);
    getchar();
    printf("Altura cadastrada com sucesso.\n\n");
    //Vacina
    printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
    verificaVacina(vacina, usuario);
    printf("Vacina cadastrada com sucesso!\n\n");
    usuario++;
    quantidade_usuario++;
  }
  else
  {
    system("cls");
    printf("A capacidade máxima de usuários cadastrados já foi atingida.\n");
  }
  system("pause");
}
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
  }
  else if (strcmp(aux, "não\n") == 0 || strcmp(aux, "nÃo\n") == 0)
  {
    vacina[posicao] = false; //Se não a vacina é false
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
  }
}
void verificaGenero(char genero[MAX][MAX_C], int posicao)
{
  for (int i = 0; i < strlen(genero[posicao]); i++)
    genero[posicao][i] = tolower(genero[posicao][i]); //Deixa a string em minúsculo
  if (strcmp(genero[posicao], "masculino\n") == 0)    //Se for masculino...
  {
    strcpy(genero[posicao], "Masculino\n"); //Substitui a string pro "Masculino.\n"
  }
  else if (strcmp(genero[posicao], "feminino\n") == 0) //Se for feminino...
  {
    strcpy(genero[posicao], "Feminino\n"); //Substitui a string pro "Feminino.\n"
  }
  else if (strcmp(genero[posicao], "não declarar\n") == 0 || strcmp(genero[posicao], "nÃo declarar\n") == 0) //Se for não declarar...
  {
    strcpy(genero[posicao], "Não declarado\n"); //Substitui a string pro "Não declarado.\n"
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
  }
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
  }
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
void editarUsuario(int *id, char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, char email[][MAX_C], bool *vacina)
{
  int id_aux, i, menu_aux;
  printf("Para editar, primeiro digite o seu ID: ");
  scanf("%d", &id_aux);
  getchar();
  if (ValidaID(id, id_aux) == true)
  {
    int aux_posicao = pegaPosicaoID(id, id_aux);
    do
    {
      system("cls");
      printf("Dados cadastrados:\n");
      printf("ID: %d \n", id[aux_posicao]);
      printf("1 - Nome completo: %s", nome_completo[aux_posicao]);
      printf("2 - Email: %s", email[aux_posicao]);
      printf("3 - Gênero: %s", genero[aux_posicao]);
      printf("4 - Endereço: %s", endereco[aux_posicao]);
      printf("5 - Altura: %.2lf metros\n", altura[aux_posicao]);
      ((vacina[aux_posicao] == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
      printf("7 - Sair\n");
      printf("deseja mudar oq?\n");
      scanf("%d", &menu_aux);
      getchar();
      switch (menu_aux)
      {
      case 1:
        printf("Informe o seu nome completo: ");
        fgets(nome_completo[aux_posicao], MAX_C, stdin);
        verificaNome(nome_completo, aux_posicao);
        printf("Nome editado com sucesso!\n\n");
        break;
      case 2:
        printf("Informe o seu email: ");
        fgets(email[aux_posicao], MAX_C, stdin);
        verificaEmail(email, aux_posicao);
        printf("Email editado com sucesso!\n\n");
        break;
      case 3:
        printf("Informe o seu gênero. Escreva \"Feminino\", \"Masculino\" ou \"Não Declarar\": ");
        fgets(genero[aux_posicao], MAX_C, stdin);
        verificaGenero(genero, aux_posicao);
        printf("Gênero editado com sucesso!\n\n");
        break;
      case 4:
        printf("Informe o seu endereço: ");
        fgets(endereco[aux_posicao], MAX_C, stdin);
        printf("Endereço editado com sucesso!\n\n");
        break;
      case 5:
        printf("Informe a sua altura: ");
        scanf("%lf", &altura[aux_posicao]);
        verificaAltura(altura, aux_posicao);
        getchar();
        printf("Altura editada com sucesso.\n\n");
        break;
      case 6:
        printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
        verificaVacina(vacina, aux_posicao);
        printf("Vacina editada com sucesso!\n\n");
        break;
      default:
        printf("Opção inválida.\n");
        system("pause");
        break;
      }
    } while (menu_aux != 7);
  }
  else
    printf("O ID informado não existe.\n");
  system("pause");
}
bool ValidaID(int *id, int id_aux)
{
  int i = 0;
  bool check;
  while (id[++i] != 0)
    ((id_aux == id[i - 1]) ? (check = true) : (check = false));
  return check;
}
int pegaPosicaoID(int *id, int id_aux)
{
  int i = 0, aux;
  for (int i = 0; id[i] == id_aux; i++)
    aux = i;
  return aux;
}
void pesquisarCadastro(int id[], char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double altura[], char genero[][MAX_C], int usuario)
{
  int cadastroPesquisa, cadastroRetorno, i;
  char continua;
  do
  {
    printf("Informe o seu ID para continuar: ");
    scanf("%i", &cadastroPesquisa);
    fflush(stdin);
    for (i = 0; i < MAX; i++)
    {
      if (id[i] == cadastroPesquisa)
      {
        printf("ID: %i\n Nome: %s\nEmail: %s\n Endereço: %s\n Altura: %lf\n Genero: %s\n Vacina: ", id[i], nome_completo[i], email[i], endereco[i], altura[i], genero[i]);
        cadastroRetorno++;
      }
      else if (cadastroRetorno == 0)
      {
        printf("ID não encontrado\n");
      }
    }
    printf("\nDeseja fazer uma nova pesquisa? [S/N]: ");
    scanf("%c", &continua);
  } while (continua == 'S' || continua == 's');
}

void pesquisarEmail(int id[], char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double altura[], char genero[][MAX_C], int usuario)
{
  int cadastroRetorno = 0, i;
  char continua, cadastroPesquisa[50];
  do
  {
    printf("Informe o seu Email para continuar: ");
    fgets(cadastroPesquisa, 50, stdin);
    for (i = 0; i < MAX; i++)
    {
      if (strcmp(email[i], cadastroPesquisa) == 0)
      {
        printf("ID: %i\n Nome: %s\nEmail: %s\n Endereço: %s\n Altura: %lf\n Genero: %s\n Vacina: ", id[i], nome_completo[i], email[i], endereco[i], altura[i], genero[i]);
        cadastroRetorno++;
      }
      else if (cadastroRetorno == 0)
      {
        printf("Email não encontrado.\n");
      }
    }
    printf("\nDeseja fazer uma nova pesquisa? [S/N]: ");
    scanf("%c", &continua);
  } while (continua == 'S' || continua == 's');
}
void listaCadastro(int id[], char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double altura[], char genero[][MAX_C], int usuario)
{
  int i, id_aux;
  printf("**Lista de cadastros**\n");
  if (usuario == 0)
  {
    printf("Lista vazia!\n");
    system("pause");
  }
  else
    for (i = 0; i < usuario; i++)
      printf("ID: %d\n Nome: %s\n Email: %s\n Endereço: %s\n Altura: %.2lf\n Genero: %s\n Vacina: \n************************\n", id[i], nome_completo[i], email[i], endereco[i], altura[i], genero[i]);
  system("pause");
}
void backupCadastro(int id[], char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double altura[], char genero[][MAX_C], int usuario, int idbkp[], char nomebkp[][MAX_C], char emailbkp[][MAX_C], char generobkp[][MAX_C], char enderecobkp[][MAX_C], int back, double alturabkp[])
{
  int i;
  for (i = 0; i < usuario; i++)
  {
    idbkp[i] = id[i];
    strcpy(nomebkp[i], nome_completo[i]);
    strcpy(emailbkp[i], email[i]);
    strcpy(enderecobkp[i], endereco[i]);
    strcpy(generobkp[i], genero[i]);
    alturabkp[i] = altura[i];
    if (usuario = 0)
    {
      printf("O backup não foi concluido.");
      system("pause");
    }
    else
    {
      printf("Backup concluido!!\n");
      system("pause");
    }
  }
}
void restaurarCadastro(int id[], char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double altura[], char genero[][MAX_C], int usuario, int idbkp[], char nomebkp[][MAX_C], char emailbkp[][MAX_C], char generobkp[][MAX_C], char enderecobkp[][MAX_C], int back, double alturabkp[])
{
  int i;
  for (i = 0; i < usuario; i++)
  {
    id[i] = idbkp[i];
    strcpy(nome_completo[i], nomebkp[i]);
    strcpy(email[i], emailbkp[i]);
    strcpy(endereco[i], enderecobkp[i]);
    strcpy(genero[i], generobkp[i]);
    altura[i] = alturabkp[i];
    if (usuario = 0)
    {
      printf("A restauração não foi concluida.");
      system("pause");
    }
    else
    {
      printf("Restauração concluida!!\n");
      system("pause");
    }
  }
}