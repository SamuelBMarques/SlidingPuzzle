#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "quebracabecas_tp.h"


/* Função para a criação de matrizes por meio da alocação dinâmica
   Entrada: Tamanho da matriz(MxM)
   Saída: Endereço do bloco consecutivo de memória alocado para a matriz
*/

int** criaMatriz(int n){
	int**mat;
	mat = malloc(n*sizeof(int*));			//Aloca o tamanho necessário para as linhas da matriz na memória
	for(int i =0;i<n;i++){
		mat[i] = malloc(n*sizeof(int));		//Aloca o tamanho necessário para as colunas da matriz na memória
	}
	return mat;
}

/*Função para liberação da memória alocada para a matriz
  Entrada: Matriz e tamanho da linha;
  Saída:-
*/

void liberaMatriz(int** A, int n){
	for(int i=0; i<n;i++){
		free(A[i]);	//Libera o espaço das colunas da matriz na memória
	}
	free(A);		//Libera o espaço das linhas da matriz na memória
}

/*Função que converte letras maiusculas de uma string para minúsculas
  Entrada: String a ser convertida e tamanho dela
  Saída:-
*/
void stringMinuscula(char *str, int size){
	int i=0;
	while (str[i] != '\0' && i<size){ 
        	str[i] = tolower(str[i]);			//Converte caracter por caracter para minúsculo na string	
       		i++;
    }
}

/*Função para imprimir o menu do jogo
  Entrada:-
  Saída:-
*/
void Menu(char *op){
	int len;					
	
	//Imprime os espacos até o início do menu
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_TL);
	
	//Imprime as linhas de cima do menu
	for(int i=0;i<tam_menu;i++)
		printf(TAB_HOR);
	printf(TAB_TR);
	printf("\n");
	
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
		
	printf(TAB_VER);
	printf(YELLOW("      Bem vindo ao Quebra-Cabeças!      "));
	printf(TAB_VER);
	printf("\n");
	
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_VER);
	printf("                                        ");
	printf(TAB_VER);
	printf("\n");
	
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_VER);
	printf("X. Sair do Jogo                         ");
	printf(TAB_VER);
	printf("\n");
	
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_VER);
	printf("N. Iniciar um novo jogo                 ");
	printf(TAB_VER); 
	printf("\n");
	
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_VER);
	printf("C. Continuar o jogo atual               ");
	printf(TAB_VER);
	printf("\n");
	
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_VER);
	printf("S. Continuar um jogo salvo              ");
	printf(TAB_VER);   
	printf("\n");
	
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_VER);
	printf("A. Ajuda com as instruções do jogo      ");
	printf(TAB_VER);
	printf("\n");
	
	//Imprime o canto esquerdo inferior do menu após um determinado número de espaços
	for(int i=0;i<(largura-tam_menu)/2;i++)
		printf(" ");
	printf(TAB_BL);
	
	//Imprime a linha inferior e o canto direito do menu
	for(int i=0;i<tam_menu;i++)
		printf(TAB_HOR);
	printf(TAB_BR);
	printf("\n");
	
	
	printf(CYAN("Escolha a opção (digite “voltar” em qualquer lugar para voltar ao menu principal):"));
	fgets(op,tam,stdin);
	len = strlen(op);
	if (op[len-1]=='\n')
		 op[len-1]='\0';	
	stringMinuscula(op,len);				
}

	

/*Função para embaralhar o quebra-cabeça sem torná-lo impossível de resolver
  Entrada: Matriz não embaralhada, nível de dificuldade, tamanho do lado e a posição do número zero
  Saída:- 
*/
void embaralhaMatriz( int **A, int dif, int n, Coordenada *zero){
	int num_mov;
	int i = 0; 
	
	//Define o número de movimentos de acordo com a dificuldade selecionada 
	switch(dif){
		case(1):
			num_mov = 5*n;	
			break;
		case(2):
			num_mov = 10*n;
			break;
		case(3):
			num_mov = 20*n;
			break;
	}
	int aux;
	//Loop até ocorrer o número de movimentos necessários
	while(i<num_mov){
		int mov = -1;
		aux = mov;
		mov = rand() % 4; 							// seleciona uma das direções aleatorias para movimentar
		switch(mov){
			case(0): //Zero para baixo
				if(aux != 1){							//Garante que não serão feitos movimentos que se anulam em sequência
					if (zero->l+1 < n){					//Se a nova posição existe dentro da matriz
					 	A[zero->l][zero->c] = A[zero->l+1][zero->c];	//Troca o valor da posição aleatória para o lugar do zero 
					 	A[zero->l+1][zero->c] = 0;			//Muda o zero para a nova posição
						zero->l = zero->l+1;				//Muda o valor da linha em que está o zero para futuras alterações
						i++;						//Incrementa apenas quando for permitido pelo "if"
					 }
				}
				break;							//Sai do case
			case(1): //Zero para cima
				if(aux != 0){
					if (zero->l-1 >= 0){			//Semelhante ao case anterior, porém alterando o valor da posição da linha de zero para a linha de zero menos 1
					 	A[zero->l][zero->c] = A[zero->l-1][zero->c];	 
					 	A[zero->l-1][zero->c] = 0;			
					 	zero->l = zero->l-1;				
					 	i++;
					 }
				}
				break;
			case(2): //Zero para direita
				if(aux != 3){
					if (zero->c+1 < n){			//Semelhante ao case anterior, porém alterando o valor da posição da coluna de zero para a coluna de zero mais 1
					 	A[zero->l][zero->c] = A[zero->l][zero->c+1];
					 	A[zero->l][zero->c+1] = 0;
					 	zero->c = zero->c+1;
					 	i++;
					 }
				}
				break;
			case(3): //Zero para esquerda
				if(aux != 2){					//Garante que não serão feitos movimentos que se anulam em sequência
					if (zero->c-1 >= 0){			//Semelhante ao case anterior, porém alterando o valor da posição da coluna de zero para a coluna de zero menos 1
					 	A[zero->l][zero->c] = A[zero->l][zero->c-1];
					 	A[zero->l][zero->c-1] = 0;
					 	zero->c = zero->c-1;
					 	i++;
					 }			
				}
				break;	
			}
	}
		
}

/*Função que preenche a matriz com valores do maior ao menor, da esquerda para a direita e de cima para baixo
  Entrada: Endereço da matriz vazia e o tamanho do seu lado
  Saída:-
*/

void preencheMatriz(int **A, int n){
	int num = 0;			
	int max = pow(n,2)-1;				//Define o maior número da matriz
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(num == max)
				A[i][j]=0;		//Insere o número "0" na matriz caso esteja na ultima posição
			else
				A[i][j]=num+1;		//Insere os números na matriz
			num++;				//Aumenta o número em uma unidade
			
		}
	}
}

/*Função que imprime a matriz (tabuleiro), incluindo as linhas de separação
  Entrada: Matriz e o tamanho do lado
  Saída:-
*/

void imprimeMatriz(int **A, int n){
	printf("\n");
	int aux = (largura - 3*n)/2;
	
	//Imprime os espaços para que a matriz esteja centralizada
	for (int i = 0; i<aux;i++)
		printf(" ");
		
	//Imprime a linha superior
	printf(TAB_TL TAB_HOR TAB_HOR);
	for(int i=0; i<n-1; i++){
		printf(TAB_TJ TAB_HOR TAB_HOR);
	}
	printf(TAB_TR "\n");
	
	for(int i=0; i<n;i++){
		//Imprime os espaços para que a matriz esteja centralizada
		for (int i = 0; i<aux;i++)
			printf(" ");
		//Imprime as linhas verticais e os valores
		for(int j=0; j<n;j++){
			if(A[i][j] == 0){
				printf(TAB_VER "  ");
			}
			else{
				printf(TAB_VER "%2d", A[i][j]);
			}
		}
		printf(TAB_VER "\n");
		
		//Imprime as linhas horizontais 
		if(i<n-1){
			for (int i = 0; i<aux;i++)
				printf(" ");
			printf(TAB_ML TAB_HOR TAB_HOR);
			for(int j=0; j<n-1; j++){
				printf(TAB_MJ TAB_HOR TAB_HOR);
			}
			printf(TAB_MR "\n");
		}
	}
	
	for (int i = 0; i<aux;i++)
		printf(" ");
	//Imprime a linha superior
	printf(TAB_BL TAB_HOR TAB_HOR);
	for(int i=0; i<n-1; i++){
		printf(TAB_BJ TAB_HOR TAB_HOR);
	}
	printf(TAB_BR "\n");
	printf("\n");
}

/*Função que testa se o jogo foi terminado, comparando as peças com suas posições iniciais
  Entrada: Matriz e o tamanho
  Saída: Verdadeiro ou falso (se está completo ou não)
*/

int comparaMatriz(int **A, int **inicial, int n ){	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(A[i][j] != inicial[i][j]){	//Compara se o valor que está na matriz é igual ao que estava no momento inicial
				return 0;
			}
		}
	}
	return 1;
	
}

/*Função que salva o jogo no computador, com o nome indicado pelo usuário
  Entrada: Matriz, nome do arquivo, tamanho do lado da matriz, numero de jogadas
  Saída:-
*/

void salvaJogo(int **A, char *nome,int n ,int *jgd){
	FILE *arquivo = fopen(nome,"w");			//Abre o arquivo
	fprintf(arquivo," %d\n",n);				//Imprime o tamanho da matriz no arquivo
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			fprintf(arquivo, " %d", A[i][j]);	//Imprime a matriz no aquivo
		}
		fprintf(arquivo, "\n");
	}
	fprintf(arquivo," %d\n",*jgd);				//Imprime o número de jogadas no arquivo
	if(!fclose(arquivo)){					//Se foi salvo com sucesso
		printf(GREEN("Arquivo \"%s\" salvo com sucesso!") "\n",nome);
	}
	else
		printf(RED("Não foi possível salvar o arquivo!") "\n");
}

/*Função que le o jogo salvo no computador, com o nome indicado pelo usuário
  Entrada: Nome do arquivo,endereço do numero de jogadas
  Saída: Matriz que estava salva
*/
int** leJogo(char *nome, int *n, int *jgd){ 
	int size, **A;
	FILE *arquivo = fopen(nome,"r");			//Abre o arquivo
	if(arquivo == NULL)					//Se o arquivo não existir ou não for possível de abrir, retorna o valor nulo
		return NULL;	
	fscanf(arquivo, "%d\n", &size);
	*n = size;
	A = criaMatriz(size);
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			fscanf(arquivo, "%d", &A[i][j]); 	//Lê os valores da matriz salva no arquivo
		}
		fscanf(arquivo, "\n");
	}
	
	fscanf(arquivo, "%d", jgd);				//Lê o número de jogadas já feitas
	fclose(arquivo);
	return A;
}

/*Função que procura um determinado valor dentro da matriz e passa sua "coordenada" para uma variável
  Entrada: Matriz, tamanho da matriz, o valor a ser procurado e a variável para armazenar a posição do valor
  Saída: 1 se encontrou o valor e 0 se não encontrou
*/
int encontraValor(int **A, int n, int num, Coordenada *valor){
	for(int i=0; i<n;i++){
		for(int j=0; j<n;j++){
			if(A[i][j] == num){
				valor->l = i;				//Armazena a linha do valor procurado
				valor->c = j;				//Armazena a linha do valor procurado
				return 1;
			}
		}
	}
	return 0;
}

/*Função que troca dois valores de posição dentro da matriz
  Entrada: Matriz, endereço do valor (sua linha e coluna), endereço do zero
  Saída:-
*/

void troca(int **A, Coordenada *valor, Coordenada *zero){
	A[zero->l][zero->c] = A[valor->l][valor->c];			//Troca os valores dentro da matriz
	A[valor->l][valor->c] = 0;					//Coloca o zero na posição em que estava o número movido
	zero->l = valor->l;						//Armazena a nova posição do zero
	zero->c = valor->c;
}


/*Função que decide se é possível trocar dois valores dentro da matriz e chama a função para trocá-los
  Entrada: Matriz, tamanho da matriz, endereço do zero (sua linha e coluna), endereço do contador
  Saída:-
*/
int movePecas(int **A, int n, Coordenada *zero, int*count){
	int num,size;
	char comando[tam];
	Coordenada valor;
	printf(CYAN("Digite um comando ou número da peça que quer mover: "));
	fgets(comando,tam,stdin);
	num = atoi(comando);							//Converte a string para um inteiro (ASCII to Integer), retorna zero se o primeiro caracter digitado não for um número
	size = strlen(comando);
	stringMinuscula(comando,size);
	char nome[size];
	if (comando[size-1]=='\n')
		 comando[size-1]='\0';	
	
		 					
	if(num == 0){
		if(comando [0] == '0' && comando[1] == '\0'){
				printf("\n"RED("\nA peça %d não existe no tabuleiro.")"\n",num);
				return 1;
		}
		else if(!strcmp(comando,"voltar")){							//Se quiser voltar ao menu
			return 0;
		}
		else if(!strncmp(comando,"salvar ", 7)){						//Se for digitado salvar
			sscanf(comando + 7, "%s", nome);
			salvaJogo(A,nome,n,count);
			imprimeMatriz(A,n);
			return 1;
		}
		else {
			printf(RED("Esse comando não existe!")"\n");
			return 1;
		}
			
	}
	else{
		if(encontraValor(A,n,num,&valor)){							//Se o valor for encontrado
			if((valor.l == zero->l+1 || valor.l == zero->l-1) && valor.c==zero->c){
				troca(A,&valor,zero);
				*count = *count+1;							//Atualiza o número de jogadas
				imprimeMatriz(A,n);
				printf("Quantidade de jogadas até agora: %d.\n",*count);		
			}
			else if((valor.c == zero->c+1 || valor.c == zero->c-1) && valor.l==zero->l){
				troca(A,&valor,zero);
				*count = *count+1;
				imprimeMatriz(A,n);
				printf("Quantidade de jogadas até agora: %d.\n",*count);
			}
			else 
				printf("\n"RED("Não é possível mover a peça %d.")"\n",num);
		}
		else 
			printf("\n"RED("A peça %d não existe no tabuleiro.")"\n",num);
	}
	return num;
}

/*Função que define a dificuldade por meio da letra selecionada pelo usuario
  Entrada:-
  Saída: Dificulade(1,2 ou 3)
*/

int dificuldade(){              
	char escolha[tam];
	int dif;
	int size;
	do{
		printf(CYAN("Qual será a dificuldade desejada? (Fácil(F), Média(M) ou Dificil(D)):"));
		fgets(escolha,tam,stdin);
		size = strlen(escolha);
		stringMinuscula(escolha,size);
		if (escolha[size - 1] == '\n'){
            		escolha[size - 1] = '\0';
        	}

        	if (strcmp(escolha, "f") == 0){
          		dif = 1;  // Fácil
        	}
        	else if (strcmp(escolha, "m") == 0){
          		dif = 2;  // Médio
      		}
        	else if (strcmp(escolha, "d") == 0){
          		dif = 3;  // Difícil
        	}
        	else if (strcmp(escolha, "voltar") == 0){
          		dif = 0;  //Para voltar ao menu
        	}
        	else {
          		printf(RED("Escolha inválida! Tente novamente.\n"));
          		dif = -1;  // Valor inválido
        	}
        	
	}while(dif == -1);
	
	return dif;
}

void instrucoes(){
	printf("\n");
	for(int i=0; i<largura;i++)
		printf(TAB_HOR);
	printf("\n");
	    
	printf("Instruções:\n");
	printf(YELLOW("1. Objetivo do Jogo:")"\n");
	printf("\t- Colocar as peças do tabuleiro em ordem crescente, da esquerda para a direita e de cima para baixo . \n\n");
	
	printf(YELLOW("2. Como Jogar:")"\n");
	printf("\t- Após iniciar um jogo ou continuar um jogo salvo, movimente as peças digitando seu número correspondente.\n");
	printf("\t- Você só pode mover peças que estão adjacentes ao espaço vazio.\n");
	printf("\t- Continue movendo as peças até alcançar a disposição correta.\n\n");
	
	printf(YELLOW("3. Controles:")"\n");
	printf("\t- Pressione 'N' enquanto estiver no menu para iniciar um novo jogo.\n");
	printf("\t- Pressione 'C' enquanto estiver no menu para continuar um jogo já iniciado, essa opcão só funciona caso algum jogo já tenha sido iniciado e não acabado.\n");
	printf("\t- Pressione 'S' enquanto estiver no menu para carregar um jogo salvo em seu computador.\n");
	printf("\t- Pressione 'A' enquanto estiver no menu para voltar aqui, às instruções.\n");
	printf("\t- Digite \"Salvar\" + o nome do arquivo para salvar um jogo em andamento e poder jogá-lo depois.\n");
	printf("\t- Digite \"Voltar\" em qualquer momento para voltar ao menu.\n\n");
	
	
	printf(YELLOW("4. Dica:")"\n");
	printf("\t- Tente resolver as linhas superiores primeiro.\n\n");
	    
	printf(YELLOW("5. Tutorial:")"\n");
	printf("\t- Caso ainda tenha dificuldades na finalização, acesse o link seguir para facilitar o compreendimento.\n");
	printf("\t- Link: https://pt.wikihow.com/Resolver-o-Jogo-do-15 .\n\n");
		
	    
	printf(MAGENTA("Boa sorte e divirta-se jogando!")"\n");
	
	for(int i=0; i<largura;i++)
		printf(TAB_HOR);
	printf("\n\n");
}
