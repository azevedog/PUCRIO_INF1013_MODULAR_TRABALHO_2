/***************************************************************************
*  $MCI Módulo de implementação: TTAB Teste tabuleiro
*
*  Arquivo gerado:              TestTAB.c
*  Letras identificadoras:      TTAB
*
*  Nome da base de software:    OpenJogos
*
*  Projeto: MODULAR_T2
*  Gestor:  EAMCEMP LTDA
*  Autores: MCS e GBHA
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	   3       gbha  5/out/2016 Conclusao desenvolvimento
*	   2       gbha  4/out/2016 Continuacao desenvolvimento
*     1       mcs   1/out/2016 início desenvolvimento
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "TABULEIRO.h"
#include	"PECA.h"



static const char CRIAR_TAB_CMD         [ ] = "=criartabuleiro"     ;
static const char INSERIR_PECA_CMD         [ ] = "=inserirpeca"     ;
static const char MOVER_PECA_CMD         [ ] = "=moverpeca"     ;
static const char RETIRAR_PECA_CMD         [ ] = "=retirarpeca"     ;
static const char OBTER_PECA_CMD         [ ] = "=obterpeca"     ;
static const char OBTER_CADOS_CMD         [ ] = "=obterameacados"     ;
static const char OBTER_CANTES_CMD         [ ] = "=obterameacantes"     ;
static const char DESTRUIR_TABULEIRO_CMD      [ ] = "=destruirtabuleiro"  ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VALOR     100
  
TAB_tppTabuleiro tab = NULL;
PEC_tppPeca pPeca = NULL;
LIS_tppLista pLista = NULL;


/***** Protótipos das funções encapuladas no módulo *****/

   static int Mover( int inicialX, int inicialY, int finalX, int finalY);
		/* Essa funcao é de peca, mas enquanto nao existe um modulo jogo
		que use essa condicao de criar a peca e inserir de fora, o teste do 
		tabuleiro deve exercer essa funcao (simular minimamente um jogo)*/
		
	static void ExcluirValor ( void * pDado );
		/* Essa funcao é de lista, mas enquanto nao existe um modulo jogo
		que use essa condicao inserir de fora, o teste do tabuleiro deve exercer
		essa funcao (simular minimamente um jogo)*/
		
	static int Compara ( void* elem1, void* elem2);
		/* Essa funcao é de peca, mas enquanto nao existe um modulo jogo
		que use essa condicao de criar a peca e inserir de fora, o teste do 
		tabuleiro deve exercer essa funcao (simular minimamente um jogo)*/
		

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     É criado um tabuleiro LinhaxColuna com duas torres do xadrez que se
*	   ameacam mutuamente
*
*     Comandos disponíveis:
*
*     =criartabuleiro             string int CondRetEsp
*     =inserirpeca                int string string CondRetEsp
*     =moverpeca                  int string int string CondRetEsp
*     =retirarpeca                int string  CondRetEsp
*	  =obterpeca				  int string CondRetEsp
*     =obterameacados             int string  CondRetEsp
*     =obterameacantes            int string  CondretPonteiro
*     =destruirtabuleiro         CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
   
	  int x;
	  char y;
	  int fX = -1;
	  
      int numLidos   = -1 ,
          CondRetEsp = -1,
		  CondRet = -1;

      //char   StringDado[  DIM_VALOR ] ;
      //char * pDado ;

       /* Testar Criar tabuleiro */
         if  ( strcmp( ComandoTeste , CRIAR_TAB_CMD) == 0 )
         {
			int numCol;

            numLidos = LER_LerParametros( "iii" , &numCol, &x,
                       &CondRetEsp ) ;

            if (numLidos != 3){
               return TST_CondRetParm ;
            } /* if */
			
			tab = *((TAB_tppTabuleiro*) malloc(sizeof(TAB_tppTabuleiro)));
			
			CondRet = TAB_CriarTabuleiro(numCol, x, &tab);
			
            return TST_CompararInt(CondRetEsp, CondRet,
               "Erro ao criar tabuleiro.") ;
         } /* fim ativa: Testar Criar tabuleiro */
		 
		  /* Testar Inserir peca */
        else if  ( strcmp( ComandoTeste , INSERIR_PECA_CMD) == 0 ){

			char identificador = 'T';
			char corTime;
			
            numLidos = LER_LerParametros( "issi" , &x, &y, &corTime,
                       &CondRetEsp ) ;

					   
            if (numLidos != 4){
               return TST_CondRetParm ;
            } /* if */
			
			
			pPeca  = *((PEC_tppPeca*) malloc(sizeof(PEC_tppPeca)));
			
			if(PEC_CriarPeca(&pPeca, &identificador, &corTime, Mover)){
				CondRet = TAB_CondRetErro;
			}
			
            CondRet = TAB_InserirPeca(x, y, pPeca, tab, ExcluirValor);

            return TST_CompararInt(CondRetEsp, CondRet,
               "Erro ao inserir peca.") ;
        } /* fim ativa: Testar Inserir peca */

/* Testar Mover peca */
        else if  ( strcmp( ComandoTeste , MOVER_PECA_CMD) == 0 ){

			
			char finalY;
			
            numLidos = LER_LerParametros( "isisi" , &x, &y, &fX, &finalY,
                       &CondRetEsp) ;

            if (numLidos != 5){
               return TST_CondRetParm ;
            } /* if */

			CondRet = TAB_MoverPeca(x, y, fX, finalY, Mover, tab,
			Compara);

            return TST_CompararInt(CondRetEsp, CondRet,
               "Erro ao mover peca.") ;
        } /* fim ativa: Testar Mover Peca */
		
		/* Testar Retirar peca */
        else if  ( strcmp( ComandoTeste , RETIRAR_PECA_CMD) == 0 ){

            numLidos = LER_LerParametros( "isi" , &x, &y,
                       &CondRetEsp ) ;

            if (numLidos != 3){
               return TST_CondRetParm ;
            } /* if */

			CondRet = TAB_RetirarPeca(x , y, tab);

            return TST_CompararInt(CondRetEsp, CondRet,
               "Erro ao retirar peca.") ;
        } /* fim ativa: Testar Retirar peca */
		
		/* Testar Obter peca */
        else if  ( strcmp(ComandoTeste , OBTER_PECA_CMD) == 0 ){

            numLidos = LER_LerParametros( "isi" , &x, &y,
                       &CondRetEsp ) ;

            if (numLidos != 3){
               return TST_CondRetParm ;
            } /* if */
			
			pPeca  = *((PEC_tppPeca*) malloc(sizeof(PEC_tppPeca)));
			CondRet = TAB_ObterPeca(x, y, &pPeca, tab); 
			
            if(CondRet == TAB_CondRetOK){
				if(pPeca == NULL){
					CondRet = TAB_CondRetErro;
				}
				else{
					CondRet = TAB_CondRetOK;
				}
			}

            return TST_CompararInt(CondRetEsp, CondRet,
               "Erro ao obter peca.") ;
        } /* fim ativa: Testar Obeter peca */
		
		/* Testar Obter ameacados */
        else if  ( strcmp( ComandoTeste , OBTER_CADOS_CMD) == 0 ){

            numLidos = LER_LerParametros( "isi" , &x, &y,
                       &CondRetEsp ) ;

            if (numLidos != 3){
               return TST_CondRetParm ;
            } /* if */

			pLista = *((LIS_tppLista*) malloc(sizeof(LIS_tppLista)));
			CondRet = TAB_ObterListaAmeacados(x, y, &pLista, tab);
			
			if( CondRet == TAB_CondRetOK){
				if(pLista == NULL){
					CondRet = TAB_CondRetErro;
				}
				else{
					CondRet = TAB_CondRetOK;
				}
			}

            return TST_CompararInt(CondRetEsp, CondRet,
               "Erro ao obter ameacados peca.") ;
        } /* fim ativa: Testar Obeter ameacados. */
		
		/* Testar Obter ameacantes */
        else if  ( strcmp( ComandoTeste , OBTER_CANTES_CMD) == 0 ){

            numLidos = LER_LerParametros( "isi" , &x, &y,
                       &CondRetEsp ) ;

            if (numLidos != 3){
               return TST_CondRetParm ;
            } /* if */

            pLista = *((LIS_tppLista*) malloc(sizeof(LIS_tppLista)));
			CondRet = TAB_ObterListaAmeacantes(x, y, &pLista, tab);
			
			if( CondRet == TAB_CondRetOK){
				if(pLista == NULL){
					CondRet = TAB_CondRetErro;
				}
				else{
					CondRet = TAB_CondRetOK;
				}
			}

            return TST_CompararInt(CondRetEsp, CondRet,
               "Erro ao obter ameacantes.") ;
        } /* fim ativa: Testar Obter ameacados */
		
		
		/* Testar Destruir tabuleiro */
        else if  (strcmp( ComandoTeste , DESTRUIR_TABULEIRO_CMD) == 0 ){

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if (numLidos != 1){
               return TST_CondRetParm ;
            } /* if */

			CondRet = TAB_DestruirTabuleiro(tab);
			
            return TST_CompararInt(CondRetEsp, CondRet,
			"Erro ao destruir tabuleiro.") ;
        } /* fim ativa: Testar Destruir tabuleiro. */
		
      return TST_CondRetNaoConhec ;

   } /* Fim função: TTAB &Testar Tabuleiro */
      

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB -Mover (teste hardcoded para torre xadrez)
*
***********************************************************************/

   int Mover( int inicialX, int inicialY, int finalX, int finalY)
   {
		if((inicialX != finalX) && (inicialY != finalY)){
			return 0;
		}
		return 1;
   } /* Fim função: TTAB -Mover */
   
   
/***********************************************************************
*
*  $FC Função: TTAB -Excluir simulando jogo
*
***********************************************************************/

   void ExcluirValor ( void * pDado ) {
		PEC_LiberarPeca(pDado);
   } /* Fim função: TTAB -Excluir */   
   
   
 /***********************************************************************
*
*  $FC Função: TTAB -Compara simulando jogo
*
***********************************************************************/

   int Compara ( void* elem1, void* elem2 ) {
		if(PEC_ComparaPeca(elem1, elem2) == PEC_CondRetMesmoTime){
			return 1;
		}
		return 0;
   } /* Fim função: TTAB -Excluir */   
   
/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

