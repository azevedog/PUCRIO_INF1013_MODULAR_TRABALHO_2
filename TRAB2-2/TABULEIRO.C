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
#include <ctype.h>
#include "TABULEIRO.h"
#include "LISTA.h"


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


	static tpElemLista* CriarElemento(void* pValor);
	
	static TAB_tpCondRet posicaoValida(int x, int y, TAB_tpTabuleiro tabuleiro);
	
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
		
	int lin;
	
	(*novoTabuleiro) =  (TAB_tpTabuleiro*) malloc(sizeof(TAB_tpTabuleiro));
	if ((*novoTabuleiro) == NULL ){
      return TAB_CondRetErro ;
    } /* if */
	
	(*novoTabuleiro)->posicoes = (tagElemTabuleiro**)
	malloc(sizeof(tagElemTabuleiro*)*numLinhas);
	  
	for(lin =0; lin <= numLinhas; lin++){
		(*novoTabuleiro)->posicoes[lin] = 
			 (tagElemTabuleiro*) malloc(sizeof(tagElemTabuleiro)*numColunas);
		for(col = 0; col <= numColunas; col++){
			(*novoTabuleiro)->posicoes[lin][col]->pValor = NULL;
		}
	}		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Criar Tabuleiro */


/***************************************************************************
*
*  Função: TAB  &Inserir peca no tabuleiro
*  ****/
 TAB_tpCondRet TAB_InserirPeca(int linha, char coluna,
		void* peca, TAB_tppTabuleiro tabuleiro){
		
		int col = converteColuna(coluna);
		
		if(!posicaoValida(linha, col, tabuleiro)){
			return TAB_CondRetErro;
		}
		
		tabuleiro->posicoes[linha][col] = CriarElemento(peca);
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Inserir peca no tabuleiro */

  

/***************************************************************************
*
*  Função: TAB  &Mover peca no tabuleiro
*  ****/
 TAB_tpCondRet TAB_MoverPeca(int inicialX, char inicialY, int finalX, char finalY){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Mover peca no tabuleiro */

   
/***************************************************************************
*
*  Função: TAB  &Retirar peca do tabuleiro
*  ****/
 TAB_tpCondRet TAB_RetirarPeca(int inicialX, char inicialY){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Retirar peca do tabuleiro */
   

/***************************************************************************
*
*  Função: TAB  &Obter peca do tabuleiro
*  ****/
 TAB_tpCondRet TAB_ObterPeca(int inicialX, char inicialY, char* nome, char* cor){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter peca do tabuleiro */
	

/***************************************************************************
*
*  Função: TAB  &Obter ameacantes
*  ****/
 TAB_tpCondRet TAB_ObterListaAmeacantes(int inicialX, char inicialY, LIS_tppLista lista){
		
		if(lista != NULL){
			LIS_DestruirLista(lista);
		}
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter ameacantes */

	
/***************************************************************************
*
*  Função: TAB  &Obter ameacados
*  ****/
 TAB_tpCondRet TAB_ObterListaAmeacados(int inicialX, char inicialY, LIS_tppLista* lista){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter ameacados */


	/***************************************************************************
*
*  Função: TAB  &Destriuir tabuleiro
*  ****/
 TAB_tpCondRet TAB_DestruirTabuleiro(){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB &Destriuir tabuleiro */
	



/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TAB  -Criar o elemento
*
***********************************************************************/

   tpElemTabuleiro* CriarElemento(void* pValor){

      tpElemTabuleiro* pElem ;

      pElem = (tpElemTabuleiro*) malloc( sizeof( tpElemTabuleiro )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->ameacantes   = NULL  ;
      pElem->ameacados  = NULL  ;
	  
      return pElem ;
   } /* Fim função: TAB  -Criar o elemento */
   
/***********************************************************************
*
*  $FC Função: TAB  -Validar posicao
*
***********************************************************************/

   int posicaoValida(int x, int y, TAB_tppTabuleiro tabuleiro){

		if((x < 0) || (x > tabuleiro->linhas) ||
			(y < 0) ||(y > tabuleiro->colunas)){
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
		
		int lower = toLower(coluna);
		return lower - 'a';
	}/* Fim função: TAB  -Converte coordenada da coluna*/	
	
   

/********** Fim do módulo de implementação: TAB  Tabuleiro de jogo generico **********/

