/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:  OpenJogos
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: mcs, gbha
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       mcs   1/out/2016 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         char * idLista;
               /* String identificadora de lista */

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( char * idLista, void ( * ExcluirValor ) ( void * pDado ), LIS_tppLista pLista )
   {

      char * identificaLista;
      int contarChar = strlen(idLista);

      if ( contarChar <= 4 && contarChar > 0)
      {
         return LIS_CondRetErro;
      } /* if */

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return LIS_CondRetErro ;
      } /* if */

      LimparCabeca( pLista );
      pLista->ExcluirValor = ExcluirValor;

      identificaLista = ( char * ) malloc( strlen(idLista) ) ;

      if( identificaLista == NULL){
         return LIS_CondRetErro;
      }

      strcpy( identificaLista , idLista ) ;

      pLista->idLista = identificaLista ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      pElem = pLista->pOrigemLista ;

      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;
      free( pLista ) ;

      return LIS_CondRetOK;

   } /* Fim função: LIS  &Destruir lista */



/***************************************************************************
*
*  Função: LIS  &Inserir elemento 
*  ****/

   LIS_tpCondRet LIS_InserirElemento( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, void * valor)
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
        return LIS_CondRetListaVazia ;
      } /* if */

      valor = pLista->pElemCorr->pValor ;

      return LIS_CondRetOK;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o próximo elemento 
*  ****/

   LIS_tpCondRet IrProximoLista ( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if( pLista->pElemCorr == pLista->pFimLista ){
         return LIS_CondRetFimLista ;
      } /* if */

      if ( pLista->pElemCorr == NULL){
         return LIS_CondRetListaVazia ;
      }

      pLista->pElemCorr = pLista->pElemCorr->pProx ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Ir para o próximo elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento anterior
*  ****/

   LIS_tpCondRet IrAnteriorLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if( pLista->pElemCorr == pLista->pOrigemLista ){
         return LIS_CondRetInicioLista ;
      } /* if */

      if ( pLista->pElemCorr == NULL){
         return LIS_CondRetListaVazia ;
      }

      pLista->pElemCorr = pLista->pElemCorr->pAnt ;

      return LIS_CondRetOK ;
   } /* Fim função: LIS  &Ir para o elemento anterior */

/***************************************************************************
*
*  Função: LIS  &Alterar valor do elemento corrente
*  ****/

  LIS_tpCondRet LIS_AlterarElementoCorrente( LIS_tppLista pLista ,
                                              void * novoElemento )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
            return LIS_CondRetListaVazia ;
         } /* fim ativa: Tratar lista vazia */

         pLista->pElemCorr->pValor = novoElemento;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Alterar valor do elemento corrente */

/***************************************************************************
*
*  Função: LIS  &Obter identificação da lista
*  ****/

   LIS_tpCondRet LIS_ObterId ( LIS_tppLista pLista , void * pDado )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->idLista == NULL )
         {
            return LIS_CondRetErro ;
         } /* fim ativa: Tratar lista vazia */

         pDado = pLista->idLista;

         if (pDado == NULL)
         {
            return LIS_CondRetErro;
         }

         return LIS_CondRetOK ;

   } /* Fim função: LIS &Obter identificação da lista*/




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

