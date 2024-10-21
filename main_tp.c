/*                                                                                                                                                                      
|	Trabalho Prático - Introdução à programação(BCC201)                                                                                                             
|	                                                                                                                                                               
|	Descrição: O objetivo do trabalho é de criar um jogo do tipo quebra-cabeça, chamado Slide Puzzle, que consiste em ordenar um determinado número de pastilhas	 
|	em um tabuleiro de forma a organizá-lo, considerando que apenas as peças adjacentes ao "buraco" podem ser movidas.                                              
|	                                                                                                                                                                
|	Nome do aluno: Samuel Braga Marques                                                                                                                             
|	Turma: 32                                                                                                                                               
|	Versão do programa: 1.4
|	Data: 01/10/2024
|	
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "quebracabecas_tp.h"

int main() {
	char op[tam], lado[tam]; 
	int ja_comecou=0;
	int continua = 1;
	int count;
	int n, **A=NULL,**inicial=NULL,dif;
	int voltar =0;
	char nome[tam];
	Coordenada zero,valor;
	srand(time(NULL));			//Cria uma semente para os números aleatórios que está sempre mudando, baseada no relógio do computador
	
	do{
		Menu(op);
		if(strcmp(op,"n") == 0){
			if(A != NULL){							//Se a matriz estava preenchida, libera ela para poder alocar novamente
				liberaMatriz(inicial,n);
				liberaMatriz(A,n);	
			}							
			do{								//Caso queira começar um novo jogo
				count = 0;
				n =0;
				printf("\n"CYAN("Qual será a dimensão do tabuleiro (3 a 10): "));
				fgets(lado,tam,stdin);
				int size = strlen(lado);
				if (lado[size - 1] == '\n'){
            				lado[size - 1] = '\0';
        			}
        			n = atoi(lado);
				if(n == 0){
					stringMinuscula(lado,size);
					if((strcmp(lado, "voltar") == 0)){
						voltar = 1;
						break;
					}
					else if(lado[0] == '0' && lado [1] == '\n')
						n = 0;
					else
						printf(RED("Esse comando não existe!")"\n");
					}
				if(n<3 || n>10)
					printf(RED("Digite um número entre 3 e 10!")"\n");
			}while((n<3 || n>10) && voltar == 0);
				
			if(voltar){
				voltar = 0;					//Impede que o voltar continue setado e atrapalhe o próximo loop
				continue;
			}
				
			A=criaMatriz(n);					//Aloca dinamicamente a matriz
			inicial = criaMatriz(n);
			preencheMatriz(A,n);
			preencheMatriz(inicial,n);
			imprimeMatriz(A,n);
			encontraValor(A,n,0, &valor);
			zero.l = valor.l;					//Atualiza o numero da linha em que esta o valor zero
			zero.c = valor.c;					//Atualiza o numero da linha em que esta o valor zero
			printf("Tabuleiro Ordenado!\n\n");
			dif = dificuldade();
				
			if (dif == 0)	
				continue;					//Se a pessoa digitou voltar na escolha de dificuldade
			
			embaralhaMatriz(A,dif,n,&zero);
			imprimeMatriz(A,n);
			printf("Tabuleiro Embaralhado!\n\n");
			ja_comecou =1;						//Variável auxiliar para permitir a continuação desse jogo criado
			while(movePecas(A,n,&zero, &count)){
				if(A[n-1][n-1] == 0){
					if(comparaMatriz(A,inicial,n)){
						printf(GREEN("Parabéns! Você completou o quebra-cabeças em %d movimentos.")"\n", count);
						ja_comecou = 0;				//Terminou o quebra cabeça
						continua = 0;		//Se não quer mais jogar, sai do jogo
						break;
					}
				}
			}
		}
		
		else if(strcmp(op,"c") == 0){								//Caso queira continuar um jogo em andamento
			if(ja_comecou){
				imprimeMatriz(A,n);
				while(movePecas(A,n,&zero, &count)){
					if(A[n-1][n-1] == 0){
						if(comparaMatriz(A,inicial,n)){
							printf(GREEN("Parabéns! Você completou o quebra-cabeças em %d movimentos.")"\n", count);
							ja_comecou = 0;
							continua = 0;
							break;					//Sai do loop While
						}
					}
				}
			}
			else{
				printf(RED("Você precisa ter iniciado um jogo e não ter finalizado o mesmo para poder continuar!""\n"));
			}
		}							
				
		else if(strcmp(op,"s") == 0){						//Caso queira continuar um jogo salvo	
			if(A != NULL){							//Se a matriz estava preenchida (tinha um jogo em andamento), a mesma é liberada
				liberaMatriz(inicial,n);
				liberaMatriz(A,n);	
			}						
			printf("\n"CYAN("Digite o nome do arquivo: "));
			scanf("%s",nome);						//Pega o nome do arquivo
			getchar();
			A = leJogo(nome,&n,&count);
			inicial = criaMatriz(n);
			preencheMatriz(inicial,n);
			if(A == NULL)
				printf(RED("Não foi possível abrir o arquivo!")"\n");
			else{
				printf(GREEN("Arquivo \"%s\" carregado. Vamos começar o jogo!")"\n",nome);
				ja_comecou = 1;
				imprimeMatriz(A,n);
				encontraValor(A,n,0, &valor);
				zero.l = valor.l;
				zero.c = valor.c;
				while(movePecas(A,n,&zero, &count)){
					if(A[n-1][n-1] == 0){
						if(comparaMatriz(A,inicial,n)){
							printf(GREEN("Parabéns! Você completou o quebra-cabeças em %d movimentos.")"\n", count);
							ja_comecou = 0;
							continua = 0;
							break;
						}
					}
				}
			}
		}
				
		else if(strcmp(op,"a") == 0){								//Caso queira saber as instruções do jogo
			instrucoes();	
		}
		else if(strcmp(op,"x") == 0){
			continua = 0;
		}
		else{
			printf(RED("Essa opção não existe!")"\n");
		}
	}while(continua);
	liberaMatriz(inicial,n);
	liberaMatriz(A,n);
	return 0;
}
