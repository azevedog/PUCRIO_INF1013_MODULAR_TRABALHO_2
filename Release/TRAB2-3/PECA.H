/***************************************************************************
*
*  $MCD M�dulo de defini��o: PEC Peca de um jogo de tabuleiro
*
*  Arquivo gerado:              PECA.h
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    OpenJogos
*
*  Projeto: MODULAR_T2
*  Gestor:  EAMCEMP LTDA
*  Autores: MCS e GBHA
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  2       gbha   3/out/2016	conclus�o desenvolvimento
*     1       gbha   1/out/2016 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa uma estrutura gen�rica de peca para jogos de tabuleiro.
*	  Esta peca � definida por um identificacao (char) e uma cor(char).
*
*     A fun��o de movimento das pecas deve ser fornecida pelo usuario do
*	  modulo respeitando a assinatura detalhada na mesma.
*
***************************************************************************/

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma peca */
typedef struct PEC_tagPeca* PEC_tppPeca ;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da peca
*
***********************************************************************/
   typedef enum {
         PEC_CondRetOK,
               /* Concluiu corretamente */
			   
		 PEC_CondRetERRO,
               /* Concluiu com erro */
			   
		 PEC_CondRetTimeDiferente,
               /* Duas pecas NAO tem a mesma cor*/
			   
		 PEC_CondRetMesmoTime
               /* Duas pecas tem a mesma cor*/

   } PEC_tpCondRet;
 
/***********************************************************************
*
*  $FC Fun��o: PEC  &Criar Peca
*
*  $ED Descri��o da fun��o
*     Cria uma peca generica para um jogo de tabuleiro.
*
*  $EP Par�metros
*     ppPeca  - Ponteiro de ponteiro para passagem da peca criada
*     por refer�ncia.
*
*     identificador  - Caracter que identifica o tipo de peca. Como
*     este atributo � armazenado em um byte, permite 128 tipos
*	  diferentes.
*
*     corTime  - Caracter que identifica o time que esta peca
*     pertence. Como este atributo � armazenado em um byte,
*	   permite 128 tipos diferentes.
*
*     MoverPeca  - Ponteiro para a fun��o que processa a validade
*     do movimento da peca. Se respeita as regras da peca. N�O
*	  VALIDA SE O MOVIMENTO � OUT OF BOUNDS NO TABU
*	  LEIRO.
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
*
*     Se ocorreu algum erro, retorna PEC_CondRetERRO.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca* ppPeca, char* identificador, char* corTime,
int ( * MoverPeca ) ( int inicialX, int inicialY, int finalX, int finalY)) ;

/***********************************************************************
*
*  $FC Fun��o: PEC  &Mover
*
*  $ED Descri��o da fun��o
*     Valida o movimento da peca. Verifica se respeita as regras
*	  da peca. N�O VALIDA SE O MOVIMENTO � OUT OF
*	  BOUNDS NO TABULEIRO.
*
*  $EP Par�metros
*     pPeca  - Ponteiro para peca que sera movida.
*
*     inicialX  - Coordenada horizontal da posicao inicial da peca
*
*     inicialY  - Coordenada vertical da posicao inicial da peca
*
*     finalX  - Coordenada horizontal da posicao final da peca
*
*     finalY  - Coordenada vertical da posicao final da peca
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
*
*     Se ocorreu algum erro, retorna PEC_CondRetERRO.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tpCondRet PEC_Mover(PEC_tppPeca pPeca, int inicialX, int inicialY, int finalX, int finalY) ;

/***********************************************************************
*
*  $FC Fun��o: PEC  &LiberarPeca
*
*  $ED Descri��o da fun��o
*     Libera o espa�o de mem�ria utilizado para armazaner a peca.
*
*  $EP Par�metros
*     pPeca  - Ponteiro para peca que sera liberada.
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
*
*     Se ocorreu algum erro, retorna PEC_CondRetERRO.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tpCondRet PEC_LiberarPeca(PEC_tppPeca pPeca) ;

/***********************************************************************
*
*  $FC Fun��o: PEC  &ComparaPeca
*
*  $ED Descri��o da fun��o
*     Determina se duas pecas sao do mesmo time pela sua cor.
*
*  $EP Par�metros
*     elem1  - Ponteiro para peca 1.
*
*     elem2  - Ponteiro para peca 2.
*
*  $FV Valor retornado
*     PEC_CondRetTimeDiferente, se as duas pecas NAO tem a mesma cor
			   
	   PEC_CondRetMesmoTime, se as duas pecas TEM a mesma cor.
*
*     Se ocorreu algum erro, retorna PEC_CondRetERRO.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/
PEC_tpCondRet PEC_ComparaPeca(void* elem1, void* elem2);

/********** Fim do m�dulo de defini��o: PEC Peca de um jogo de tabuleiro**********/
