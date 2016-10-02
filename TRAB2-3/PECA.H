/***************************************************************************
*
*  $MCD Módulo de definição: PEC Peca de um jogo de tabuleiro
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
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gbha   1/set/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa uma estrutura genérica de peca para jogos de tabuleiro.
*	  Esta peca é definida por um identificacao (String) e uma cor.
*
*     A função de movimento das pecas deve ser fornecida pelo usuario do
*	  modulo respeitando a assinatura detalhada na mesma.
*
***************************************************************************/

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peca */

typedef struct PEC_tagPeca* PEC_tppPeca ;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peca
*
***********************************************************************/
   typedef enum {
         PEC_CondRetOK,
               /* Concluiu corretamente */
			   
		 PEC_CondRetERRO
               /* Concluiu com erro */

   } PEC_tpCondRet;
 
/***********************************************************************
*
*  $FC Função: PEC  &Criar Peca
*
*  $ED Descrição da função
*     Cria uma peca generica para um jogo de tabuleiro.
*
*  $EP Parâmetros
*     peca  - Ponteiro de ponteiro para passagem da peca criada
*     por referência.
*
*     identificador  - Caracter que identifica o tipo de peca. Como
*     este atributo é armazenado em um byte, permite 128 tipos
*	  diferentes.
*
*     corTime  - Caracter que identifica o time que esta peca
*     pertence. Como este atributo é armazenado em um byte,
*	   permite 128 tipos diferentes.
*
*     MoverPeca  - Ponteiro para a função que processa a validade
*     do movimento da peca. Se respeita as regras da peca. NÃO
*	  VALIDA SE O MOVIMENTO É OUT OF BOUNDS NO TABU
*	  LEIRO.
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
*
*     Se ocorreu algum erro, retorna PEC_CondRetERRO.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca* peca, char identificador, char corTime,
int ( * MoverPeca ) ( int inicialX, int inicialY, int finalX, int finalY)) ;

/***********************************************************************
*
*  $FC Função: PEC  &Mover
*
*  $ED Descrição da função
*     Valida o movimento da peca. Verifica se respeita as regras
*	  da peca. NÃO VALIDA SE O MOVIMENTO É OUT OF
*	  BOUNDS NO TABULEIRO.
*
*  $EP Parâmetros
*     peca  - Ponteiro para peca que sera movida.
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
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tppPeca PEC_Mover(PEC_tppPeca peca, int inicialX, int inicialY, int finalX, int finalY) ;

/***********************************************************************
*
*  $FC Função: PEC  &LiberarPeca
*
*  $ED Descrição da função
*     Libera o espaço de memória utilizado para armazaner a peca.
*
*  $EP Parâmetros
*     peca  - Ponteiro para peca que sera liberada.
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
*
*     Se ocorreu algum erro, retorna PEC_CondRetERRO.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tppPeca PEC_LiberarPeca(PEC_tppPeca peca) ;
/********** Fim do módulo de definição: PEC Peca de um jogo de tabuleiro**********/
