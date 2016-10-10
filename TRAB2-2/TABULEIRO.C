/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro para jogo generico 
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    OpenJogos
*
*  Projeto: MODULAR_T2
*  Gestor:  EAMCEMP LTDA
*  Autores: MCS e GBHA
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	   3       gbha  4/out/2016 Conclusao desenvolvimento
*	   2       gbha  3/out/2016 Continuacao desenvolvimento
*     1       mcs   1/out/2016 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include	"TABULEIRO.h"
#include	"LISTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: TAB Elemento do tabuleiro
*
*
***********************************************************************/

   typedef struct tagElemTabuleiro {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         LIS_tppLista ameacantes;
               /* Ponteiro para elementos que podem ocupar essa posicao */

         LIS_tppLista ameacados;
               /* Ponteiro para elementos de posicoes que posso ocupar */

   } tpElemTabuleiro;
   

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor do tabuleiro
*
*
***********************************************************************/

   typedef struct TAB_tagTabuleiro {

        tpElemTabuleiro** posicoes;
               /* Matriz de posicoes do tabuleiro*/
			   
		int linhas;
				/* Numero de linhas no tabuleiro. */
				
		int colunas;
				/* Numero de colunas no tabuleiro. */
			   
   } TAB_tpTabuleiro ;

/***** Protótipos das funções encapuladas no módulo *****/
	
	static TAB_tpCondRet posicaoInvalida(int x, int y, TAB_tppTabuleiro tabuleiro);
	
	static int converteColuna(char coluna);

   /*static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/
TAB_tpCondRet TAB_CriarTabuleiro(int numColunas, int numLinhas,
		TAB_tppTabuleiro* novoTabuleiro){
		
	int lin, col;
	
	(*novoTabuleiro) =  (TAB_tppTabuleiro) malloc(sizeof(TAB_tpTabuleiro));
	if ((*novoTabuleiro) == NULL ){
      return TAB_CondRetErro ;
    } /* if */
	
	(*novoTabuleiro)->posicoes = (tpElemTabuleiro**)
	malloc(sizeof(tpElemTabuleiro*)*numLinhas);
	
	for(lin =0; lin < numLinhas; lin++){
		(*novoTabuleiro)->posicoes[lin] = 
			 (tpElemTabuleiro*) malloc(sizeof(tpElemTabuleiro)*numColunas);
		for(col = 0; col < numColunas; col++){
			(*novoTabuleiro)->posicoes[lin][col].pValor = NULL;
			(*novoTabuleiro)->posicoes[lin][col].ameacantes = NULL;
			(*novoTabuleiro)->posicoes[lin][col].ameacados = NULL;
		} 	
	}	
	
	(*novoTabuleiro)->linhas = numLinhas;
	(*novoTabuleiro)->colunas = numColunas;
	
	return TAB_CondRetOK;
	}/* Fim função: TAB  &Criar Tabuleiro */


/***************************************************************************
*
*  Função: TAB  &Inserir peca no tabuleiro
*  ****/
 TAB_tpCondRet TAB_InserirPeca(int linha, char coluna,
		void* peca, TAB_tppTabuleiro tabuleiro, void ( * ExcluirValor ) ( void * pDado )){

		LIS_tppLista ameacados;
		LIS_tppLista ameacantes;
		char prefixAmeacado =  'D';
		char prefixAmeacante = 'T';
		char * idAmeacados;
		char * idAmeacantes;
		int col = converteColuna(coluna);
		
		/* Ajuste das coordenadas 1 based para a matriz interna 0 based*/
		linha = linha -1;
		
		if(posicaoInvalida(linha, col, tabuleiro) ){
			return TAB_CondRetForaTabuleiro;
		}
		
		idAmeacados = ( char * ) malloc( sizeof(char)*LIS_TAM_ID); 
		strcpy(idAmeacados, &prefixAmeacado);
		
		ameacados = *((LIS_tppLista*) malloc(sizeof(LIS_tppLista)));
		if(LIS_CriarLista(idAmeacados, ExcluirValor, &ameacados) != LIS_CondRetOK){
			return TAB_CondRetErro;
		}
		
		idAmeacantes = ( char * ) malloc( sizeof(char)*LIS_TAM_ID); 
		strcpy(idAmeacantes, &prefixAmeacante);
		
		ameacantes = *((LIS_tppLista*) malloc(sizeof(LIS_tppLista)));
		if(LIS_CriarLista(idAmeacantes, ExcluirValor, &ameacantes) != LIS_CondRetOK){
			return TAB_CondRetErro;
		}
		
		tabuleiro->posicoes[linha][col].pValor = peca;
		tabuleiro->posicoes[linha][col].ameacantes = ameacantes;
		tabuleiro->posicoes[linha][col].ameacados = ameacados;
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Inserir peca no tabuleiro */

  

/***************************************************************************
*
*  Função: TAB  &Mover peca no tabuleiro
*  ****/
 TAB_tpCondRet TAB_MoverPeca(int inicialX, char inicialY, int finalX, char finalY,
	int ( * MoverPec ) ( int inicialX, int inicialY, int finalX, int finalY), TAB_tppTabuleiro tabuleiro,
	int(* ComparaElementos)(void* elem1, void* elem2)){
		
		int iInicialY = converteColuna(inicialY);
		int iFinalY = converteColuna(finalY);
		TAB_tpCondRet ret;
		
		/* Ajuste das coordenadas 1 based para a matriz interna 0 based*/
		inicialX = inicialX -1;
		finalX = finalX -1;
		
		if(posicaoInvalida(finalX, iFinalY, tabuleiro)){
			return TAB_CondRetForaTabuleiro;
		}
		
		if(!MoverPec(inicialX, iInicialY, finalX, iFinalY)){
			return TAB_CondRetElementoNaoFaz;
		}
		
		if((tabuleiro->posicoes[inicialX][iInicialY].pValor) == NULL){
			return TAB_CondRetErro;
		}
		
		if((tabuleiro->posicoes[finalX][iFinalY].pValor) != NULL){
			if(ComparaElementos(tabuleiro->posicoes[inicialX][iInicialY].pValor,
				tabuleiro->posicoes[finalX][iFinalY].pValor)){
				ret = TAB_CondRetOK;
			}
			else{
				ret = TAB_CondRetSubstituiuOutroElemento;
			}
		}
		else{
			ret = TAB_CondRetOK;
		}

		if(!TAB_RetirarPeca(finalX, finalY, tabuleiro)){
			return TAB_CondRetErro;
		}
		
		tabuleiro->posicoes[finalX][iFinalY] =  tabuleiro->posicoes[inicialX][iInicialY];

		return ret;
	}/* Fim função: TAB  &Mover peca no tabuleiro */

   
/***************************************************************************
*
*  Função: TAB  &Retirar peca do tabuleiro
*  ****/
 TAB_tpCondRet TAB_RetirarPeca(int inicialX, char inicialY, TAB_tppTabuleiro tabuleiro){
 
		int iInicialY = converteColuna(inicialY);
		
		/* Ajuste das coordenadas 1 based para a matriz interna 0 based*/
		inicialX = inicialX -1;
 
		if(posicaoInvalida(inicialX, iInicialY, tabuleiro)){
			return TAB_CondRetForaTabuleiro;
		}
		
		if(tabuleiro->posicoes[inicialX][iInicialY].pValor == NULL){
			return TAB_CondRetErro;
		}
		
		tabuleiro->posicoes[inicialX][iInicialY].pValor = NULL;
		LIS_DestruirLista(tabuleiro->posicoes[inicialX][iInicialY].ameacantes);
		LIS_DestruirLista(tabuleiro->posicoes[inicialX][iInicialY].ameacados);
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Retirar peca do tabuleiro */
   

/***************************************************************************
*
*  Função: TAB  &Obter peca do tabuleiro
*  ****/
 TAB_tpCondRet TAB_ObterPeca(int inicialX, char inicialY, void** pValor,
	TAB_tppTabuleiro tabuleiro){
		
		int iInicialY = converteColuna(inicialY);

		/* Ajuste das coordenadas 1 based para a matriz interna 0 based*/
		inicialX = inicialX -1;
		
		if(posicaoInvalida(inicialX, iInicialY, tabuleiro)){
			return TAB_CondRetForaTabuleiro;
		}
		
		if(tabuleiro->posicoes[inicialX][iInicialY].pValor == NULL){
			return TAB_CondRetErro;
		}
		
		(*pValor) = tabuleiro->posicoes[inicialX][iInicialY].pValor;
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter peca do tabuleiro */
	

/***************************************************************************
*
*  Função: TAB  &Obter ameacantes
*  ****/
 TAB_tpCondRet TAB_ObterListaAmeacantes(int inicialX, char inicialY, LIS_tppLista* lista,
	TAB_tppTabuleiro tabuleiro){
		
		int iInicialY = converteColuna(inicialY);

		/* Ajuste das coordenadas 1 based para a matriz interna 0 based*/
		inicialX = inicialX -1;
		
		if(posicaoInvalida(inicialX, iInicialY, tabuleiro)){
			return TAB_CondRetForaTabuleiro;
		}
		
		(*lista) = tabuleiro->posicoes[inicialX][iInicialY].ameacantes;
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter ameacantes */

	
/***************************************************************************
*
*  Função: TAB  &Obter ameacados
*  ****/
 TAB_tpCondRet TAB_ObterListaAmeacados(int inicialX, char inicialY, LIS_tppLista* lista,
	TAB_tppTabuleiro tabuleiro){
		
		int iInicialY = converteColuna(inicialY);

		/* Ajuste das coordenadas 1 based para a matriz interna 0 based*/
		inicialX = inicialX -1;
		
		if(posicaoInvalida(inicialX, iInicialY, tabuleiro)){
			return TAB_CondRetForaTabuleiro;
		}
		
		(*lista) = tabuleiro->posicoes[inicialX][iInicialY].ameacados;
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter ameacados */


	/***************************************************************************
*
*  Função: TAB  &Destriuir tabuleiro
*  ****/
 TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro tabuleiro){
	
		int lin, col;
		int numLinhas = tabuleiro->linhas;
		int numColunas = tabuleiro->colunas;
		
		
		for(lin =0; lin < numLinhas; lin++){
			for(col = 0; col < numColunas; col++){
				free(tabuleiro->posicoes[lin][col].pValor);
				LIS_DestruirLista(tabuleiro->posicoes[lin][col].ameacantes);
				LIS_DestruirLista(tabuleiro->posicoes[lin][col].ameacados);
				free(&(tabuleiro->posicoes[lin][col]));
			}
		}		
		return TAB_CondRetOK;
	}/* Fim função: TAB &Destriuir tabuleiro */
	



/*****  Código das funções encapsuladas no módulo  *****/
   
/***********************************************************************
*
*  $FC Função: TAB  -Validar posicao
*
***********************************************************************/

   int posicaoInvalida(int x, int y, TAB_tppTabuleiro tabuleiro){
		if((x < 0) || (x >= tabuleiro->linhas) ||
			(y < 0) ||(y >= tabuleiro->colunas)){
			return TAB_CondRetErro;
		}
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  -Validar posicao */
	
/***********************************************************************
*
*  $FC Função: TAB  -Converte coordenada da coluna
*
***********************************************************************/

   int converteColuna(char coluna){
	
		int dist;
		if ((coluna >= 'a') && (coluna <= 'z')){
			dist = (coluna - 'a');
		}
		else{
			dist = coluna - 'A';
		}
		return dist;
	}/* Fim função: TAB  -Converte coordenada da coluna*/		

/********** Fim do módulo de implementação: TAB  Tabuleiro de jogo generico **********/

