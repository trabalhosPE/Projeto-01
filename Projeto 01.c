//Projeto 01
//Aluno: Ricardo Alves de Lima Júnior | Matrícula: UC20102577
//Aluno: Luiz Gustavo da Costa Gonçalves | Matrícula: UC20201242

//Bibliotecas:
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//Constantes:
#define MAX 1000     //MAX é número máximo de usuários que serão cadastrados.
#define MAX_C 50 + 2 //MAX_C é número máximo de caracteres que cada variável char pode ler.

//Índice das funções:

//Funções do menu principal:
void configInicial(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int *id_backup, char nome_backup[][MAX_C], char email_backup[][MAX_C], char genero_backup[][MAX_C], char endereco_backup[][MAX_C], double *altura_backup, bool *vacina_backup);                             //Função que atribui valores iniciais para as variáveis.
void cadastraUsuario(int quantidade_usuario, int *id, char nome_completo[][MAX_C], char email[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, bool *vacina, int usuario);                                                                                                                                                                     //Função que cadastra um usuário.
void editarUsuario(int *id, char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, char email[][MAX_C], bool *vacina);                                                                                                                                                                                                            //Função que edita um usuário.
void excluiUsuario(int *id, char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, char email[][MAX_C], bool *vacina);                                                                                                                                                                                                            //Função que exclui um usuário.
void pesquisarCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int usuario);                                                                                                                                                                                           //Função que pesquisa um cadastro pelo ID.
void pesquisarEmail(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int usuario);                                                                                                                                                                                              //Função que pesquisa um cadastro pelo email.
void listaCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int quantidade_usuario);                                                                                                                                                                                    //Função que mostra uma lista com todos os usuários cadastrados.
void backupCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int quantidade_usuario, int *id_backup, char nome_backup[][MAX_C], char email_backup[][MAX_C], char genero_backup[][MAX_C], char endereco_backup[][MAX_C], double *altura_backup, bool *vacina_backup);    //Função que faz o backup de todos os cadastros.
void restaurarCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int quantidade_usuario, int *id_backup, char nome_backup[][MAX_C], char email_backup[][MAX_C], char genero_backup[][MAX_C], char endereco_backup[][MAX_C], double *altura_backup, bool *vacina_backup); //Função que restaura os cadastros a partir do backup.

//Funções de verificação:
void verificaNome(char nome_completo[MAX][MAX_C], int posicao); //Função que verifica se o nome não é nulo.
void verificaEmail(char email[MAX][MAX_C], int posicao);        //Função que verifica se o email é valido.
void verificaGenero(char genero[MAX][MAX_C], int posicao);      //Função que verifica se o gênero é válido.
void verificaAltura(double *altura, int posicao);               //Função que verifica se a altura é válida.
void verificaVacina(bool *vacina, int posicao);                 //Função que verifica se o usuário é vacinado.
bool verificaID(int *id, int id_aux);                           //Função que verifica se o ID existe.

//Outras funções:
void criacaoConta(char *login, char *senha); //Função que cria uma conta (necessária para fazer o backup).
void preencheId(int *id, int posicao);       //Função que radomiza os IDs.
int pegaPosicaoID(int *id, int id_aux);      //Função que pega a posição do ID no vetor de IDs.

//Início do algoritmo principal:
int main()
{
  setlocale(LC_ALL, "Portuguese"); //Função que habilita a formatação em Português para todos os printfs.
  srand((int)time(0));             //Função que dá a semente para o cálculo da função rand().

  //Variáveis principais:
  int id[MAX];
  char nome_completo[MAX][MAX_C];
  char email[MAX][MAX_C];
  char genero[MAX][MAX_C];
  char endereco[MAX][MAX_C];
  double altura[MAX];
  bool vacina[MAX];

  //Variáveis de backup:
  int id_backup[MAX];
  char nome_backup[MAX][MAX_C];
  char email_backup[MAX][MAX_C];
  char genero_backup[MAX][MAX_C];
  char endereco_backup[MAX][MAX_C];
  double altura_backup[MAX];
  bool vacina_backup[MAX];

  //Outras variáveis:
  int usuario = 0;
  int quantidade_usuario = 0;
  int menu;
  char login[MAX_C];
  char senha[MAX_C];

  //Atribuição de valores iniciais para as variáveis:
  configInicial(id, nome_completo, email, endereco, altura, genero, vacina, id_backup, nome_backup, email_backup, genero_backup, endereco_backup, altura_backup, vacina_backup);

  //Criação de conta:
  printf("Olá, seja bem-vindo ao cadastro online da Universidade Católica de Brasília.\n");
  printf("Crie sua conta...\n");
  criacaoConta(login, senha);

  //Menu principal:
  do
  {
    system("cls");
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
    usuario = pegaPosicaoID(id, 0);
    switch (menu)
    {
    case 1: //Cadastro de usuário.
      cadastraUsuario(quantidade_usuario, id, nome_completo, email, genero, endereco, altura, vacina, usuario);
      quantidade_usuario++;
      break;
    case 2: //Edição de usuário.
      editarUsuario(id, nome_completo, genero, endereco, altura, email, vacina);
      break;
    case 3: //Exclusão de usuário.
      excluiUsuario(id, nome_completo, genero, endereco, altura, email, vacina);
      quantidade_usuario--;
      break;
    case 4: //Pesquisa de usuário pelo ID.
      pesquisarCadastro(id, nome_completo, email, endereco, altura, genero, vacina, usuario);
      break;
    case 5: //Pesquisa de usuário pelo email.
      pesquisarEmail(id, nome_completo, email, endereco, altura, genero, vacina, usuario);
      break;
    case 6: //Lista de usuários cadastrados.
      listaCadastro(id, nome_completo, email, endereco, altura, genero, vacina, quantidade_usuario);
      break;
    case 7: //Backup dos cadastros.
      backupCadastro(id, nome_completo, email, endereco, altura, genero, vacina, quantidade_usuario, id_backup, nome_backup, email_backup, genero_backup, endereco_backup, altura_backup, vacina_backup);
      break;
    case 8: //Restauração dos cadastros.
      restaurarCadastro(id, nome_completo, email, endereco, altura, genero, vacina, quantidade_usuario, id_backup, nome_backup, email_backup, genero_backup, endereco_backup, altura_backup, vacina_backup);
      break;
    default:
      printf("Opção inválida.\n");
      system("pause");
      break;
    }
  } while (menu != 9);
}
//Fim do algoritmo principal.

//Funções:
void configInicial(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int *id_backup, char nome_backup[][MAX_C], char email_backup[][MAX_C], char genero_backup[][MAX_C], char endereco_backup[][MAX_C], double *altura_backup, bool *vacina_backup)
{
  for (int i = 0; i < MAX; i++)
  {
    id[i] = 0;
    id_backup[i] = 0;
    altura[i] = 0;
    altura_backup[i] = 0;
    vacina[i] = false;
    vacina_backup[i] = false;
    for (int j = 0; j < MAX_C; j++)
    {
      nome_completo[i][j] = '\0';
      nome_backup[i][j] = '\0';
      email[i][j] = '\0';
      email_backup[i][j] = '\0';
      genero[i][j] = '\0';
      genero_backup[i][j] = '\0';
      endereco[i][j] = '\0';
      endereco_backup[i][j] = '\0';
    }
  }
}
void cadastraUsuario(int quantidade_usuario, int *id, char nome_completo[][MAX_C], char email[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, bool *vacina, int usuario)
{
  if (quantidade_usuario < MAX)
  {
    preencheId(id, usuario);
    printf("O seu ID é \"%d\".\n\n", id[usuario]);
    printf("Informe o seu nome completo: ");
    fgets(nome_completo[usuario], MAX_C, stdin);
    verificaNome(nome_completo, usuario);
    printf("Nome cadastrado com sucesso!\n\n");
    printf("Informe o seu email: ");
    fgets(email[usuario], MAX_C, stdin);
    verificaEmail(email, usuario);
    printf("Email cadastrado com sucesso!\n\n");
    printf("Informe o seu gênero. [\"Feminino\", \"Masculino\" ou \"Não Declarar\"]: ");
    fgets(genero[usuario], MAX_C, stdin);
    verificaGenero(genero, usuario);
    printf("Gênero cadastrado com sucesso!\n\n");
    printf("Informe o seu endereço: ");
    fgets(endereco[usuario], MAX_C, stdin);
    printf("Endereço cadastrado com sucesso!\n\n");
    printf("Informe a sua altura: ");
    scanf("%lf", &altura[usuario]);
    verificaAltura(altura, usuario);
    getchar();
    printf("Altura cadastrada com sucesso.\n\n");
    printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
    verificaVacina(vacina, usuario);
    printf("Vacina cadastrada com sucesso!\n\n");
  }
  else
  {
    system("cls");
    printf("A capacidade máxima de usuários cadastrados já foi atingida.\n");
  }
  system("pause");
}
void editarUsuario(int *id, char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, char email[][MAX_C], bool *vacina)
{
  int id_aux, menu_aux, aux_posicao;
  printf("Para editar, primeiro informe o seu ID: ");
  scanf("%d", &id_aux);
  getchar();
  if (verificaID(id, id_aux) == true)
  {
    aux_posicao = pegaPosicaoID(id, id_aux);
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
      printf("Escolha: ");
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
void excluiUsuario(int *id, char nome_completo[][MAX_C], char genero[][MAX_C], char endereco[][MAX_C], double *altura, char email[][MAX_C], bool *vacina)
{
  int id_aux, aux_posicao;
  printf("Para excluir um cadastro informe o ID: ");
  scanf("%d", &id_aux);
  getchar();
  if (verificaID(id, id_aux) == true)
  {
    aux_posicao = pegaPosicaoID(id, id_aux);
    id[aux_posicao] = 0;
    altura[aux_posicao] = 0;
    vacina[aux_posicao] = false;
    for (int i = 0; i < MAX_C; i++)
    {
      nome_completo[aux_posicao][i] = '\0';
      email[aux_posicao][i] = '\0';
      genero[aux_posicao][i] = '\0';
      endereco[aux_posicao][i] = '\0';
    }
    printf("Usuário excluido com sucesso!\n");
  }
  else
    printf("O ID informado não existe.\n");
  system("pause");
}
void pesquisarCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int usuario)
{
  int id_aux, aux_posicao;
  char continua;
  do
  {
    system("cls");
    printf("Informe o seu ID para continuar: ");
    scanf("%d", &id_aux);
    getchar();
    system("cls");
    if (verificaID(id, id_aux) == true)
    {
      aux_posicao = pegaPosicaoID(id, id_aux);
      printf("ID: %d \n", id[aux_posicao]);
      printf("1 - Nome completo: %s", nome_completo[aux_posicao]);
      printf("2 - Email: %s", email[aux_posicao]);
      printf("3 - Gênero: %s", genero[aux_posicao]);
      printf("4 - Endereço: %s", endereco[aux_posicao]);
      printf("5 - Altura: %.2lf metros\n", altura[aux_posicao]);
      ((vacina[aux_posicao] == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
    }
    else
      printf("O ID informado não existe.\n");
    system("pause");
    printf("\nDeseja fazer uma nova pesquisa? [S/N]: ");
    scanf(" %c", &continua);
  } while (continua == 'S' || continua == 's');
}
void pesquisarEmail(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int usuario)
{
  bool cadastroRetorno = false;
  char continua, cadastroPesquisa[MAX_C];
  do
  {
    printf("Informe o seu Email para continuar: ");
    fgets(cadastroPesquisa, MAX_C, stdin);
    for (int i = 0; i < MAX; i++)
      if (strcmp(email[i], cadastroPesquisa) == 0)
      {
        system("cls");
        printf("ID: %d\n", id[i]);
        printf("1 - Nome completo: %s", nome_completo[i]);
        printf("2 - Email: %s", email[i]);
        printf("3 - Gênero: %s", genero[i]);
        printf("4 - Endereço: %s", endereco[i]);
        printf("5 - Altura: %.2lf metros\n", altura[i]);
        ((vacina[i] == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
        cadastroRetorno = true;
      }
    if (cadastroRetorno == false)
      printf("Email não encontrado.\n");
    printf("\nDeseja fazer uma nova pesquisa? [S/N]: ");
    scanf(" %c", &continua);
  } while (continua == 'S' || continua == 's');
}
void listaCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int quantidade_usuario)
{
  printf("**Lista de cadastros**\n");
  if (quantidade_usuario == 0)
  {
    printf("Lista vazia!\n");
    system("pause");
  }
  else
  {
    system("cls");
    for (int i = 0; i < MAX; i++)
      if (id[i] > 0)
      {
        printf("ID: %d\n", id[i]);
        printf("1 - Nome completo: %s", nome_completo[i]);
        printf("2 - Email: %s", email[i]);
        printf("3 - Gênero: %s", genero[i]);
        printf("4 - Endereço: %s", endereco[i]);
        printf("5 - Altura: %.2lf metros\n", altura[i]);
        ((vacina[i] == true) ? (printf("6 - Vacinado(a): Sim\n\n")) : (printf("6 - Vacinado(a): Não\n\n")));
      }
    system("pause");
  }
}
void backupCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int quantidade_usuario, int *id_backup, char nome_backup[][MAX_C], char email_backup[][MAX_C], char genero_backup[][MAX_C], char endereco_backup[][MAX_C], double *altura_backup, bool *vacina_backup)
{
  if (quantidade_usuario == 0)
  {
    printf("O backup não foi concluido.");
    system("pause");
  }
  else
  {
    for (int i = 0; i < quantidade_usuario; i++)
    {
      id_backup[i] = id[i];
      strcpy(nome_backup[i], nome_completo[i]);
      strcpy(email_backup[i], email[i]);
      strcpy(endereco_backup[i], endereco[i]);
      strcpy(genero_backup[i], genero[i]);
      altura_backup[i] = altura[i];
    }
    printf("Backup concluido!!\n");
    system("pause");
  }
}
void restaurarCadastro(int *id, char nome_completo[][MAX_C], char email[][MAX_C], char endereco[][MAX_C], double *altura, char genero[][MAX_C], bool *vacina, int quantidade_usuario, int *id_backup, char nome_backup[][MAX_C], char email_backup[][MAX_C], char genero_backup[][MAX_C], char endereco_backup[][MAX_C], double *altura_backup, bool *vacina_backup)
{
  if (quantidade_usuario == 0)
  {
    printf("A restauração não foi concluida.\n");
    system("pause");
  }
  else
    for (int i = 0; i < quantidade_usuario; i++)
    {
      id[i] = id_backup[i];
      strcpy(nome_completo[i], nome_backup[i]);
      strcpy(email[i], email_backup[i]);
      strcpy(endereco[i], endereco_backup[i]);
      strcpy(genero[i], genero_backup[i]);
      altura[i] = altura_backup[i];
      printf("Restauração concluida!\n");
      system("pause");
    }
}
void verificaNome(char nome_completo[][MAX_C], int posicao)
{
  if (strcmp(nome_completo[posicao], "\n") == 0)
    do
    {
      system("cls");
      printf("O nome não pode ser nulo.\n");
      printf("Informe o seu nome completo: ");
      fgets(nome_completo[posicao], MAX_C, stdin);
    } while (strcmp(nome_completo[posicao], "\n") == 0);
}
void verificaEmail(char email[][MAX_C], int posicao)
{
  if (strchr(email[posicao], '@') == NULL)
    do
    {
      system("cls");
      printf("O email deve conter um \"@\".\n");
      printf("Informe o seu email: ");
      fgets(email[posicao], MAX_C, stdin);
    } while (strchr(email[posicao], '@') == NULL);
}
void verificaGenero(char genero[][MAX_C], int posicao)
{
  for (int i = 0; i < strlen(genero[posicao]); i++)
    genero[posicao][i] = tolower(genero[posicao][i]);
  if (strcmp(genero[posicao], "masculino\n") == 0)
    strcpy(genero[posicao], "Masculino\n");
  else if (strcmp(genero[posicao], "feminino\n") == 0)
    strcpy(genero[posicao], "Feminino\n");
  else if (strcmp(genero[posicao], "não declarar\n") == 0 || strcmp(genero[posicao], "nÃo declarar\n") == 0)
    strcpy(genero[posicao], "Não declarado\n");
  else
  {
    system("cls");
    printf("O gênero deve ser Feminino, Masculino ou Não Declarar.\n");
    printf("Informe o seu gênero: ");
    fgets(genero[posicao], MAX_C, stdin);
    verificaGenero(genero, posicao);
  }
}
void verificaAltura(double *altura, int posicao)
{
  if (altura[posicao] < 1 || altura[posicao] > 2)
    do
    {
      system("cls");
      printf("A altura deve ser entre 1 e 2 metros.\n");
      printf("Informe a sua altura: ");
      scanf("%lf", &altura[posicao]);
    } while (altura[posicao] < 1 || altura[posicao] > 2);
}
void verificaVacina(bool *vacina, int posicao)
{
  char aux[4 + 2];
  fgets(aux, 4 + 2, stdin);
  for (int i = 0; i < strlen(aux); i++)
    aux[i] = tolower(aux[i]);
  if (strcmp(aux, "sim\n") == 0)
    vacina[posicao] = true;
  else if (strcmp(aux, "não\n") == 0 || strcmp(aux, "nÃo\n") == 0)
    vacina[posicao] = false;
  else
  {
    if (strchr(aux, '\n') == NULL)
      while (getchar() != '\n')
        ;
    system("cls");
    printf("Você deve escrever apenas \"Sim\" ou \"Não\".\n");
    printf("Você se vacinou? ");
    verificaVacina(vacina, posicao);
  }
}
bool verificaID(int *id, int id_aux)
{
  for (int i = 0; i < MAX; i++)
    if (id_aux == id[i])
      return true;
  return false;
}
void criacaoConta(char *login, char *senha)
{
  system("pause");
  system("cls");
  printf("Crie o seu login: ");
  fgets(login, MAX_C, stdin);
  printf("Crie a sua senha: ");
  fgets(senha, MAX_C, stdin);
}
void preencheId(int *id, int posicao)
{
  int numero_randomico;
  do
  {
    numero_randomico = (1 + rand() % MAX);
  } while (verificaID(id, numero_randomico) == true);
  id[posicao] = numero_randomico;
}
int pegaPosicaoID(int *id, int id_aux)
{
  int i = 0;
  while (id[i] != id_aux)
    i++;
  return i;
}