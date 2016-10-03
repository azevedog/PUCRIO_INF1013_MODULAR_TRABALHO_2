/***************************************************************************
*  $MCI Módulo de implementação: TPEC Peca de um jogo de 
*	tabuleiro
*
*  Arquivo gerado:              TESTPEC.c
*  Letras identificadoras:      TPEC
*
*  Nome da base de software:    OpenJogos
*
*  Projeto: MODULAR_T2
*  Gestor:  EAMCEMP LTDA
*  Autores: MCS e GBHA
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     2       gbha   3/out/2016 Fim desenvolvimento
*	  1       gbha   1/out/2016 Início desenvolvimento
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"
#include    "PECA.h"


static const char CRIAR_PECA_CMD         [ ] = "=criarpeca"     ;
static const char LIBERAR_PECA_CMD      [ ] = "=liberarpeca"  ;
static const char MOVER_PECA_CMD      [ ] = "=moverpeca"    ;


#define TRUE  1
#define FALSE 0

#define DIM_VT_PECA   10

LIS_tppLista   vtPecas[ DIM_VT_PECA] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criarpeca                 inxPec string string CondRetEsp
*     =liberarpeca               inxLista CondRetEsp
*     =moverpeca               inxLista int int int int CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ){

      int inxPeca  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 
		;
		
      TST_tpCondRet CondRet ;
	  
      char   tipoPeca;
      char * pTipoPeca;
	  
	  char   corPeca;
      char * pCorPeca;	
		
      /* Efetuar reset de teste de lista */
		if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issi" ,
                       &inxPeca, &tipoPeca, &corPeca, &CondRetEsp) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxPeca( inxPeca)))
            {
               return TST_CondRetParm ;
            } /* if */
			
			pTipoPeca = (char*) malloc(sizeof(char));
			pCorPeca = (char*) malloc(sizeof(char));
			

            CondRet =
                 PEC_CriarPeca(&(vtPecas[ inxPeca]), pTipoPeca, pCorPeca, Mover) ;
				 
            return TST_CompararInt( CondRetEsp ,CondRet ,
               "Erro ao criar peca.") ;

        } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */
        else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 ){

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

        } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */
        else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 ){

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

        } /* fim ativa: Testar Destruir lista */

      return TST_CondRetNaoConhec ;
	}/* Fim função: TLIS &Testar lista */
/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Mover (teste hardcoded para torre xadrez)
*
***********************************************************************/

   int Mover( int inicialX, int inicialY, int finalX, int finalY)
   {
		if((inicialX != finalX) && (inicialY != finalY){
			return 0;
		}
		return 1;
   } /* Fim função: TLIS -Mover */


/***********************************************************************
*
*  $FC Função: TPEC -Validar indice de peca
*
***********************************************************************/

   int ValidarInxPeca( int inxPeca)
   {

      if ( ( inxPeca <  0 )
        || ( inxPeca >= DIM_VT_PECA))
      {
         return FALSE ;
      } /* if */
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de peca */

/********** Fim do módulo de implementação: TPEC Teste peca para um jogo e tabuleiro **********/

