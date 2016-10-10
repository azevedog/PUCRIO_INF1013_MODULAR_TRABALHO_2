/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro para jogo generico 
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
*     1       mcs   1/out/2016 Início desenvolvimento
*
*  $ED Descrição do módulo
*   Implementa um tabuleiro generico para jogos organizado
*	por linhas e colunas, ocupados por elementos genericos.
*	
*	Um jogo pode ser desenvolvido com este tabuleiro que
*	permite:
*		- Inserir peca
*		- Mover peca
*		- Remover peca
*		- Obter peca
*		- Obter lista de ameacantes (outras pecas que podem
*		alcancar aquela posicao. ELIMINACOES NAO SAO IMPLEMEN
*		TADAS NESSE MODULO. DEPENDE DAS REGRAS DE JOGOS QUE
*		SAO IMPLEMENTADAS FORA DESTE MODULO.
*
***************************************************************************/

#include "LISTA.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */
typedef struct TAB_tagTabuleiro* TAB_tppTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum {

         TAB_CondRetOK ,
               /* Concluiu corretamente */

         TAB_CondRetErro,
               /* Nao concluiu a solicitacao */
			   
		 TAB_CondRetForaTabuleiro,
               /* Movimento para fora do tabuleiro */
		  
		 TAB_CondRetElementoNaoFaz,
               /* Movimento invalido para o elemento selecionado */

         TAB_CondRetSubstituiuOutroElemento
               /* Movimento tirou um elemento original da posicao */
			   
} TAB_tpCondRet ;


/***********************************************************************
*
*  $FC Função: TAB  &Criar Tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro genérico para jogos.
*
*  $EP Parâmetros
*     numColunas  - Número de colunas do tabuleiro.
*
*     numLinhas  - Número de linhas do tabuleiro.
*
*     novoTabuleiro  - Ponteiro para o endereço de tabuleiro, para passagem do retorno
*		por referencia.
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro(int numColunas, int numLinhas,
		TAB_tppTabuleiro* novoTabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Inserir peca
*
*  $ED Descrição da função
*     Insere uma peca no tabuleiro genérico para jogos.
*
*  $EP Parâmetros
*     linha  - Posicao X no tabuleiro.
*
*     coluna  - Posicao Y no tabuleiro.
*
*     peca  - Ponteiro para elemento da posicao.
*
*     tabuleiro  - Ponteiro o tabuleiro que terá a peca inserida
*
*     ExcluirValor  - Ponteiro para funcao que exclui valores das listas do elemento do
*	   tabuleiro.
*
*		OBS: ESSA FUNCAO NAO VALIDA SE ESTA INSERINDO POR CIMA DE OUTRA PECA
*		CABE AO JOGO VALIDAR ISSO OBTENDO A PECA NA POSICAO ANTES!
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetForaTabuleiro - Caso x e y estajam fora dos limites.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

    TAB_tpCondRet TAB_InserirPeca(int linha, char coluna,
		void* peca, TAB_tppTabuleiro tabuleiro, void ( * ExcluirValor ) ( void * pDado ));

/***********************************************************************
*
*  $FC Função: TAB  &Mover peca
*
*  $ED Descrição da função
*     Move uma peca no tabuleiro genérico para jogos.
*
*  $EP Parâmetros
*     inicialX  - Coordenada horizontal da posicao inicial da peca
*
*     inicialY  - Coordenada vertical da posicao inicial da peca
*
*     finalX  - Coordenada horizontal da posicao final da peca
*
*     finalY  - Coordenada vertical da posicao final da peca
*
*     tabuleiro  - Ponteiro o tabuleiro que terá a peca inserida
*
*     MoverPeca  - Ponteiro para funcao movimento do elemento do  tabuleiro.
*
*     ComparaElementos  - Ponteiro para funcao que compara dois elementos do
*	   tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetForaTabuleiro - Caso x e y estajam fora dos limites.
*     TAB_CondRetElementoNaoFaz - Caso o elemento nao possa realizar o movimento.
*     TAB_CondRetSubstituiuOutroElemento - Caso existisse uma peca na posicao alvo.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

   TAB_tpCondRet TAB_MoverPeca(int inicialX, char inicialY, int finalX, char finalY,
	int ( * MoverPec ) ( int inicialX, int inicialY, int finalX, int finalY), TAB_tppTabuleiro tabuleiro,
	int(* ComparaElementos)(void* elem1, void* elem2));
   
/***********************************************************************
*
*  $FC Função: TAB  &Retirar peca
*
*  $ED Descrição da função
*     Retira uma peca no tabuleiro genérico para jogos.
*
*  $EP Parâmetros
*     inicialX  - Coordenada horizontal da posicao da peca
*
*     inicialY  - Coordenada vertical da posicao  da peca
*
*     tabuleiro  - Ponteiro o tabuleiro que terá a peca inserida
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetForaTabuleiro - Caso x e y estajam fora dos limites.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

   TAB_tpCondRet TAB_RetirarPeca(int inicialX, char inicialY, TAB_tppTabuleiro tabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Obter peca
*
*  $ED Descrição da função
*     Obtem uma peca no tabuleiro genérico para jogos.
*
*  $EP Parâmetros
*     inicialX  - Coordenada horizontal da posicao da peca
*
*     inicialY  - Coordenada vertical da posicao da peca
*
*     pValor  - Ponteiro para elemento na posicao, passado por referencia.
*
*     tabuleiro  - Ponteiro o tabuleiro que terá a peca inserida
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetForaTabuleiro - Caso x e y estajam fora dos limites.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

 TAB_tpCondRet TAB_ObterPeca(int inicialX, char inicialY, void** pValor,
	TAB_tppTabuleiro tabuleiro);
	
/***********************************************************************
*
*  $FC Função: TAB  &Obter ameacantes
*
*  $ED Descrição da função
*     Obtem a cabeca da lista de ameacantes.
*
*  $EP Parâmetros
*     inicialX  - Coordenada horizontal da posicao da peca
*
*     inicialY  - Coordenada vertical da posicao  da peca
*
*     lista  - Ponteirto para o cabecalho da lista (retornado por referencia).
*
*     tabuleiro  - Ponteiro o tabuleiro que terá a peca inserida
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetForaTabuleiro - Caso x e y estajam fora dos limites.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterListaAmeacantes(int inicialX, char inicialY, LIS_tppLista* lista,
	TAB_tppTabuleiro tabuleiro);
	
/***********************************************************************
*
*  $FC Função: TAB  &Obter ameacados
*
*  $ED Descrição da função
*     Obtem a cabeca da lista de ameacados.
*
*  $EP Parâmetros
*     inicialX  - Coordenada horizontal da posicao da peca
*
*     inicialY  - Coordenada vertical da posicao  da peca
*
*     lista  - Ponteirto para o cabecalho da lista (retornado por referencia).
*
*     tabuleiro  - Ponteiro o tabuleiro que terá a peca inserida
*
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetForaTabuleiro - Caso x e y estajam fora dos limites.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

	TAB_tpCondRet TAB_ObterListaAmeacados(int inicialX, char inicialY, LIS_tppLista* lista,
	TAB_tppTabuleiro tabuleiro);

/***********************************************************************
*
*  $FC Função: TAB  &Destriuir tabuleiro
*
*  $ED Descrição da função
*     Libera a memoria do tabuleiro e todas as suas pecas.
*
*  $EP Parâmetros
*     tabuleiro  - Ponteiro o tabuleiro que terá a peca inserida
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente.
*     TAB_CondRetErro - Caso contrário.
* 
*
***********************************************************************/

	TAB_tpCondRet TAB_DestruirTabuleiro();
	
/********** Fim do módulo de definição: TAB Tabuleiro de jogo genérico. **********/

