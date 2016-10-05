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
			   
   } TAB_tpTabuleiro ;

/***** Protótipos das funções encapuladas no módulo *****/

  /* static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/
TAB_tpCondRet TAB_CriarTabuleiro(int numColunas, int numLinhas,
		TAB_tppTabuleiro* novoTabuleiro){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Criar Tabuleirol */


/***************************************************************************
*
*  Função: TAB  &Inserir peca no tabuleiro
*  ****/
 TAB_tpCondRet TAB_InserirPeca(int linha, char coluna,
		void* peca){
		
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
 TAB_tpCondRet TAB_ObterListaAmeacantes(int inicialX, char inicialY, LIS_tppLista* lista){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter ameacantes */

	
/***************************************************************************
*
*  Função: TAB  &Obter ameacados
*  ****/
 TAB_tpCondRet TAB_ObterListaAmeacados(int inicialX, char inicialY, LIS_tppLista* lista){
		
		
		return TAB_CondRetOK;
	}/* Fim função: TAB  &Obter ameacados */

/***********************************************************************
*
*  $FC Função: TAB  &Destriuir tabuleiro
*
*  $ED Descrição da função
*     Libera a memoria do tabuleiro e todas as suas pecas.
*
*  $EP Parâmetros
*     inicialX  - Coordenada horizontal da posicao da peca
*
*     inicialY  - Coordenada vertical da posicao  da peca
*
*     lista  - Ponteirto para o cabecalho da lista (retornado por referencia).
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

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
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

