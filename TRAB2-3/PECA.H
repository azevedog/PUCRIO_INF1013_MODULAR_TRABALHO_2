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
*     peca  - Ponteiro para passagem da peca criada por referência.
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
*
*     Se ocorreu algum erro, retorna PEC_CondRetERRO.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca peca, char identificador, char corTime,
int ( * MoverPeca ) ( int inicialX, int inicialY, int finalX, int finalY)) ;

/***********************************************************************
*
*  $FC Função: PEC  &Mover
*
*  $ED Descrição da função
*     Move a .
*
*  $EP Parâmetros
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
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

PEC_tppPeca PEC_Mover(int inicialX, int inicialY, int finalX, int finalY) ;
/********** Fim do módulo de definição: PEC Peca de um jogo de tabuleiro**********/
