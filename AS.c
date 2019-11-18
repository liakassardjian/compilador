/*
 Caio Augusto     31782809
 Leandro Soares   31715125
 Lia Kassardjian  31750370
 Vitor Barbosa    31780881
 TURMA 6G

 IMPLEMENTACAO DO ANALISADOR SINTATICO DESCENDENTE RECURSIVO PARA A GRAMATICA:
 (A GRAMATICA FOI ADAPTADA DE MODO QUE O ANALISADOR POSSA FUNCIONAR CORRETAMENTE)

 1. Programa -> DecFuncoesRep program Identificador Bloco
    DecFuncoesRep -> DeclaracoesFuncoes DecFuncoesRep
    DecFuncoesRep -> &

 2. Bloco -> { DecVariaveisOpcional ComandoComposto }
    DecVariaveisOpcional -> ParteDeclaracoesDeVariaveis
    DecVariaveisOpcional -> &

 3. ParteDeclaracoesDeVariaveis -> DecVariaveis ParteDeclaracoesDeVariaveis
    ParteDeclaracoesDeVariaveis -> &

 4. DecVariaveis -> int ListaDeIdentificadores ;
    DecVariaveis -> bool ListaDeIdentificadores ;

 5. ListaDeIdentificadores -> Identificador ListaIdRep
    ListaIdRep -> , Identificador ListaIdRep
    ListaIdRep -> &

 6. DeclaracoesFuncoes -> DeclaraFuncao DeclaracoesFuncoes
    DeclaracoesFuncoes -> &

 7. DeclaraFuncao -> void Identificador ( PDeclaracoesFuncoesarametroFormalOpcional ) Bloco
    ParametroFormalOpcional -> ParametroFormal
    ParametroFormalOpcional -> &

 8. ParametroFormal -> int Identificador
    ParametroFormal -> bool Identificador

 9. ComandoComposto -> Comando ; ComandoCompostoRep
    ComandoCompostoRep -> Comando ; ComandoCompostoRep
    ComandoCompostoRep -> &

        DEVIDO A PRESENCA DE FIRST IGUAIS EM DIFERENTES DERIVACOES DE COMANDO,
        OS NAO-TERMINAIS COMANDO, ATRIBUICAO E CHAMADA DE PROCEDIMENTO FORAM
        ATUALIZADOS A FIM DE EVITAR PROBLEMAS COM O ANALISADOR SINTATICO. FOI
        INSERIDO UM NAO-TERMINAL AUXILIAR PARA DIRECIONAR PARA ATRIBUICAO OU
        CHAMADA DE PROCEDIMENTO.

 10. Comando -> Identificador ComandoAuxiliar
     Comando -> ComandoCondicional
     Comando -> ComandoRepetitivo
     Comando -> print ( Identificador )
     ComandoAuxiliar -> Atribuicao
     ComandoAuxiliar -> ChamadaDeProcedimento

 11. Atribuicao -> = Expressao

 12. ChamadaDeProcedimento -> ( ParametroOpcional )
     ParametroOpcional -> Parametro
     ParametroOpcional -> &

 13. Parametro -> Identificador
     Parametro -> Numero
     Parametro -> Bool
     Parametro -> &

 14. ComandoCondicional -> if ( Expressao ) { ComandoComposto } ElseOpcional ;
     ElseOpcional -> else { ComandoComposto }
     ElseOpcional -> &

 15. ComandoRepetitivo -> do { ComandoComposto } while ( Expressao )

 16. Expressao -> ExpressaoSimples ExpressaoOpcional
     ExpresaoOpcional -> Relacao ExpressaoSimples

 17. Relacao -> ==
     Relacao -> <>
     Relacao -> <
     Relacao -> <=
     Relacao -> >=
     Relacao -> >

 18. ExpressaoSimples -> SinalOpcional Termo ExpressaoSimplesRep
     SinalOpcional -> +
     SinalOpcional -> -
     SinalOpcional -> &
     ExpressaoSimplesRep -> ExpressaoSimples ExpressaoSimplesRep
     ExpressaoSimplesRep -> &

 19. Termo -> Fator FatorRep
     FatorRep -> Operacao Fator FatorRep
     FatorRep -> &
     Operacao -> *
     Operacao -> /

 20. Fator -> Variavel
     Fator -> Numero
     Fator -> Bool
     Fator -> ( ExpressaoSimples )

 21. Variavel -> Identificador

 22. Bool -> true
     Bool -> false

 23. Numero -> num

 24. Identificador -> id

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/// ============================== TOKENS

#define _ERRO_LEXICO_         0
#define _MENOR_IGUAL_         1
#define _DIFERENTE_           2
#define _MENOR_               3
#define _DIVISAO_             4
#define _COMENTARIO_          5
#define _IDENTIFICADOR_       6
#define _IF_                  7
#define _INT_                 8
#define _BOOL_                9
#define _PROGRAM_             10
#define _PRINT_               11
#define _VOID_                12
#define _TRUE_                13
#define _FALSE_               14
#define _DO_                  15
#define _ELSE_                16
#define _WHILE_               17
#define _ABRE_CHAVES_         18
#define _FECHA_CHAVES_        19
#define _PONTO_VIRGULA_       20
#define _VIRGULA_             21
#define _ABRE_PARENTESES_     22
#define _FECHA_PARENTESES_    23
#define _SINAL_MAIS_          24
#define _SINAL_IGUAL_         25
#define _IGUAL_IGUAL_         26
#define _MAIOR_               27
#define _MAIOR_IGUAL_         28
#define _SINAL_MENOS_         29
#define _SINAL_MULTIPLICACAO_ 30
#define _NUM_                 31

/// ============================== DECLARACAO DAS FUNCOES RECURSIVAS DOS SIMBOLOS NAO-TERMINAIS

int Programa(char palavra[], int *pos);
int DecFuncoesRep(char palavra[], int *pos);
int Bloco(char palavra[], int *pos);
int DecVariaveisOpcional(char palavra[], int *pos);
int ParteDeclaracoesDeVariaveis(char palavra[], int *pos);
int DecVariaveis(char palavra[], int *pos);
int DeclaracoesFuncoes(char palavra[], int *pos);
int DeclaraFuncao(char palavra[], int *pos);
int ParametroFormalOpcional(char palavra[], int *pos);
int ParametroFormal(char palavra[], int *pos);
int ComandoComposto(char palavra[], int *pos);
int ComandoCompostoRep(char palavra[], int *pos);
int Comando(char palavra[], int *pos);
int ComandoAuxiliar(char palavra[], int *pos);
int Atribuicao(char palavra[], int *pos);
int ChamadaDeProcedimento(char palavra[], int *pos);
int ParametroOpcional(char palavra[], int *pos);
int Parametro(char palavra[], int *pos);
int ComandoCondicional(char palavra[], int *pos);
int ElseOpcional(char palavra[], int *pos);
int ComandoRepetitivo(char palavra[], int *pos);
int Expressao(char palavra[], int *pos);
int ExpresaoOpcional(char palavra[], int *pos);
int Relacao(char palavra[], int *pos);
int ExpressaoSimples(char palavra[], int *pos);
int SinalOpcional(char palavra[], int *pos);
int ExpressaoSimplesRep(char palavra[], int *pos);
int Termo(char palavra[], int *pos);
int FatorRep(char palavra[], int *pos);
int Operacao(char palavra[], int *pos);
int Fator(char palavra[], int *pos);
int Variavel(char palavra[], int *pos);
int Bool(char palavra[], int *pos);
int Numero(char palavra[], int *pos);

// Tipos de identificadores
#define TIPOFUNCAO    0
#define TIPOINT       1
#define TIPOBOOL      2
#define GETTIPO       3
#define PARFORMALINT  4
#define PARFORMALBOOL 5
int Identificador(char palavra[], int *pos, int tipo);
int ListaDeIdentificadores(char palavra[], int *pos, int tipo);
int ListaIdRep(char palavra[], int *pos, int tipo);

/// ============================== DECLARACAO DOS METODOS E VARIAVEIS RELATIVOS AO FUNCIONAMENTO DO ASDR

char lookahead;
int token;
int match(char c, char palavra[], int *pos);
void erro(int *pos, char *palavra);
char *leArquivo(char *nomeArquivo);
int erroLexico = 0;


/// ============================== DECLARACAO DA TAD LISTA LIGADA USADA PELO ANALISADOR LEXICO

/*
 A TAD TLista armazena os caracteres lidos no caso de identificadores, numeros e comentarios,
 a fim de guardar de forma ligada o nome das variaveis, os numeros em si ou os textos dos comentarios.
 */

typedef struct TNo TNo;
typedef struct TLista TLista;
TLista * initLista();
void insereElemento(char c);
void resetLista();
void freeLista();
char * listaToString();

TLista *l;


/// ============================== DECLARACAO DOS METODOS RELATIVOS AO SCANNER DO ANALISADOR LEXICO

void initScanner();
int scanner(char *p, int *pos);

/// ============================== TABELA DE SÍMBOLOS

// Tipos de parâmetro para as funções
#define NULO 0
#define INT  1
#define BOOL 2

typedef struct Var Var;
typedef struct Var{
    Var * prox;
    int tipo;
    char * nome;
}Var;

typedef struct Escopo Escopo;
typedef struct Escopo{ // Representa o escopo de determinada função
    Escopo * prox;
    char * nomeEscopo; // Recebe o nome da função
    int tipoParametro; // Tipo do parâmetro formal da função
    char * nomeParametro; // Nome do parâmetro de entrada
    Var * var; // Lista de variáveis do escopo
}Escopo;

typedef struct TabelaSimbolo{
    Escopo * esc;
}TabelaSimbolo;

TabelaSimbolo * initTabelaSimbolo(){
    return (TabelaSimbolo *) calloc(1, sizeof(TabelaSimbolo));
}

void printTabelaSimbolo(TabelaSimbolo * ts){
    puts("=======================================");
    puts("=========== TABELA SIMBOLOS ===========");
    puts("=======================================");
    Escopo * e;
    Var * v;
    for(e = ts->esc; e; e = e->prox){
        puts("===============================");
        printf("Escopo de %s\n", e->nomeEscopo);
        if(e->tipoParametro == INT) printf("Parametro de entrada: %s INT\n", e->nomeParametro);
        else if(e->tipoParametro == BOOL) printf("Parametro de entrada: %s BOOL\n", e->nomeParametro);
        else printf("Sem parametros de entrada.\n");

        puts("Variaveis:");
        for(v = e->var; v; v = v->prox){
            printf("%s: ", v->nome);
            if(v->tipo == INT) printf("INT\n");
            else printf("BOOL\n");
        }
    }
    puts("=======================================");
}

// Cria um novo escopo na tabela de símbolos
// Se retorno == 0, erro. Senão, sucesso.
int criaEscopo(char * nomeEscopo, TabelaSimbolo * ts){
    // Verificação se já existe escopo com o mesmo nome
    Escopo * temp;
    for(temp = ts->esc; temp; temp = temp->prox){
        if(!strcmp(temp->nomeEscopo, nomeEscopo)){
            printf("Escopo %s ja existe.\n", nomeEscopo);
            return 0; // Já existe escopo com mesmo nome
        }
    }

    // Criação de um novo escopo
    Escopo * esc = (Escopo *) calloc(1, sizeof(Escopo));
    esc->nomeEscopo = nomeEscopo;

    // Inserção do escopo na lista de escopos
    esc->prox = ts->esc;
    ts->esc = esc;

    return 1;
}

// Retorna 0 se der erro.
// Retorna 1 se OK.
int insereParametroFormal(char * nomeEscopo, char * nomeParametroFormal, int tipoParametroFormal, TabelaSimbolo * ts){
    // Verificação se já existe escopo com o mesmo nome
    Escopo * temp;
    for(temp = ts->esc; temp; temp = temp->prox){
        if(!strcmp(temp->nomeEscopo, nomeEscopo)){
            break;
        }
    }

    if(!temp){
        printf("Escopo nao encontrado para adicionar o parametro formal.\n");
        return 0;
    }

    temp->nomeParametro = nomeParametroFormal;
    temp->tipoParametro = tipoParametroFormal;
    return 1;
}

// Insere alguma variavel em determinado escopo.
// Se retorno == 1, a variavel foi inserida com sucesso.
int insereVariavel(char * nomeEscopo, char * nomeVariavel, int tipoVariavel, TabelaSimbolo * ts){
    if((tipoVariavel != INT) && (tipoVariavel != BOOL)){
        printf("Erro ao inserir variavel %s.\n", nomeVariavel);
        printf("Tipo de variavel invalido. Deve ser INT ou BOOL.\n");
        return 0;
    }

    // Procura do escopo e validação de nome de variável == nome de escopo
    Escopo * esc = 0; // caso o escopo exista, ficará salvo nessa variável
    Escopo * findEsc; // percorre todos os escopos para validacao
    for(findEsc = ts->esc; findEsc; findEsc = findEsc->prox){
        if(!strcmp(findEsc->nomeEscopo, nomeEscopo)){
            esc = findEsc;
        }

        if(!strcmp(findEsc->nomeEscopo, nomeVariavel)){
            printf("Erro ao inserir variavel %s. Ja existe um procedimento com mesmo nome.\n", nomeVariavel);
            return 0;
        }
    }

    // Se não achar o escopo passado como parâmeto:
    if(!esc) {
        printf("Escopo %s nao existe.\n", nomeEscopo);
        return 0;
    }

    // Validacao se ha alguma variavel com mesmo nome
    if(esc->nomeParametro){
        if(!strcmp(esc->nomeParametro, nomeVariavel)){
            printf("Erro: Variavel %s ja existente no escopo %s como variavel de entrada.", nomeVariavel, nomeEscopo);
            return 0;
        }
    }

    Var * v;
    for(v = esc->var; v; v = v->prox){
        if(!strcmp(v->nome, nomeVariavel)){
            printf("Erro: Variavel %s ja existente no escopo %s.\n", nomeVariavel, nomeEscopo);
            return 0;
        }
    }

    // Criacao da variavel
    v = (Var *) calloc(1, sizeof(Var));
    v->nome = nomeVariavel;
    v->tipo = tipoVariavel;

    // Insercao da variavel no escopo
    v->prox = esc->var;
    esc->var = v;

    return 1;
}

// Retorna as informações sobre determinado escopo.
// Se retorno == 0, não há escopo.
// Senão, retorna a struct Escopo.
Escopo * getEscopo(char * nomeEscopo, TabelaSimbolo * ts){
    Escopo * temp;
    for(temp = ts->esc; temp; temp = temp->prox){
        if(!strcmp(temp->nomeEscopo, nomeEscopo)){
            return temp; // Escopo encontrado
        }
    }

    return 0;
}

// Retorna as informações sobre determinada variável de certo escopo.
// Se retorno == 0, a variável não existe no escopo.
// Senão, retorna a struct Var.
Var * getVar(char * nomeVariavel, char * nomeEscopo, TabelaSimbolo * ts){
    Escopo * esc = getEscopo(nomeEscopo, ts);

    // Se escopo nao for encontrado:
    if(!esc){
        return 0;
    }

    // Caso o escopo tenha parametros de entrada
    if(esc->nomeParametro){
        if(!strcmp(esc->nomeParametro, nomeVariavel)){
            Var * v = (Var *) calloc(1, sizeof(Var));
            v->nome = esc->nomeParametro;
            v->tipo = esc->tipoParametro;
            return v;
        }
    }

    Var * v;
    for(v = esc->var; v; v = v->prox){ // Busca da variavel no escopo
        if(!strcmp(v->nome, nomeVariavel)) return v; // Variavel encontrada no escopo
    }

    printf("Variavel %s nao encontrada no escopo %s.\n", nomeVariavel, nomeEscopo);
    return 0;
}

TabelaSimbolo * ts;
char * escopo;

/// ============================== LISTA DE TOKENS PARA A ANÁLISE SEMÂNTICA
typedef struct Token Token;
struct Token{
    Token * prox;
    char * nome;
    int codToken; // Recebe o codigo do Token
};

typedef struct ListaToken ListaToken;
struct ListaToken{
    Token * primeiroToken; // Primeiro token da lista
    Token * ultimoToken;   // Ultimo token da lista
    int tamanho;
};

ListaToken * lt;

ListaToken * initListaToken(){
    return (ListaToken *) calloc(1, sizeof(ListaToken));
}

void insereToken(char * nomeToken, int codToken){
    Token * t = (Token *) calloc(1, sizeof(Token));
    t->nome = nomeToken;
    t->codToken = codToken;

    // Aumenta o tamanho da lista
    lt->tamanho++;

    // Caso não haja nenhum token na lista
    if(!lt->primeiroToken){
        lt->primeiroToken = t;
        lt->ultimoToken = t;
    }
    else{
        lt->ultimoToken->prox = t;
        lt->ultimoToken = t;
    }
}

void printListaTokens(){
    puts("Lista de tokens: ");
    puts("================================");

    Token * temp;
    for(temp = lt->primeiroToken; temp; temp = temp->prox){
        printf("Token: %s\n", temp->nome);
        printf("Codigo: %d\n", temp->codToken);
        puts("================================");
    }
}

// Transforma a lista de tokens em um vetor de tokens
Token ** getTokens(){
    int tamanho = lt->tamanho;

    // Vetor de tokens
    Token ** tokens = (Token **) calloc(tamanho, sizeof(Token *));

    Token * temp;
    int i;
    for(i = 0, temp = lt->primeiroToken; temp ; i++, temp = temp->prox){
        tokens[i] = (Token *) calloc(1, sizeof(Token));
        tokens[i]->codToken = temp->codToken;
        tokens[i]->nome = temp->nome;
    }

    return tokens;
}

/// ============================== ANALISE SEMANTICA
int isEquals(char * a, char * b){
    if(!strcmp(a, b)){
        return 1;
    }
    return 0;
}

void printErroExpressao(char * textoErro, int i, Token ** tokens){
    // Procura o inicio do comando
    for(; tokens[i]->codToken != _SINAL_IGUAL_ &&
          tokens[i]->codToken != _WHILE_       &&
          tokens[i]->codToken != _IF_; i--);

    if(tokens[i]->codToken == _SINAL_IGUAL_) i--;

    printf("Erro na expressao");
    for(; tokens[i]->codToken != _PONTO_VIRGULA_ &&
          tokens[i]->codToken != _ABRE_CHAVES_; i++){
        printf(" %s", tokens[i]->nome);
    }

    printf("\nMotivo: %s\n", textoErro);
}

// Retorna _INT_ ou _BOOL_ dependendo do tipo da expressão
int validaExpressao(int i, Token ** tokens){
    // Recebe o primeiro lexema da expressão na posição tokens[i]

    // Identifica o tipo do primeiro termo. Todos os seguintes devem ser iguais
    int tipo;
    for(; tokens[i]->codToken != _IDENTIFICADOR_ &&
          tokens[i]->codToken != _NUM_           &&
          tokens[i]->codToken != _TRUE_          &&
          tokens[i]->codToken != _FALSE_; i++){
    }

    if(tokens[i]->codToken == _IDENTIFICADOR_){ // Pegaremos o tipo da variavel
        tipo = getVar(tokens[i]->nome, escopo, ts)->tipo;
    }
    // Se tipo == _NUM_, alteramos para _INT_ para facilitar o entendimento
    else if(tokens[i]->codToken == _NUM_) tipo = TIPOINT;
    else tipo = TIPOBOOL;

    i++;
    for(; tokens[i]->codToken != _PONTO_VIRGULA_ &&
          tokens[i]->codToken != _ABRE_CHAVES_; i++){
        // Validação de expressões inteiras
        if(tipo == TIPOINT){
            if(tokens[i]->codToken == _TRUE_ || tokens[i]->codToken == _FALSE_){
                printErroExpressao("Operacao invalida.", i, tokens);
                return 0;
            }

            // Validação de tipo de variável
            if(tokens[i]->codToken == _IDENTIFICADOR_){
                // Verifica se o identificador não é uma função
                if(getEscopo(tokens[i]->nome, ts)){
                    printErroExpressao("Uma das variaveis e uma funcao.", i, tokens);
                    return 0;
                }

                if(getVar(tokens[i]->nome, escopo, ts)->tipo != TIPOINT){
                    printErroExpressao("Uma das variaveis e do tipo bool.", i, tokens);
                    return 0;
                }
            }
        }
        // Validação de expressões booleanas
        else{
            if(tokens[i]->codToken == _NUM_                 ||
               tokens[i]->codToken == _SINAL_MAIS_          ||
               tokens[i]->codToken == _SINAL_MENOS_         ||
               tokens[i]->codToken == _SINAL_MULTIPLICACAO_ ||
               tokens[i]->codToken == _DIVISAO_             ||
               tokens[i]->codToken == _MAIOR_               ||
               tokens[i]->codToken == _MENOR_               ||
               tokens[i]->codToken == TIPOINT
               ){
                printErroExpressao("Operacao invalida.", i, tokens);
                return 0;
            }

            // Validação de tipo de variável
            if(tokens[i]->codToken == _IDENTIFICADOR_){
                // Verifica se o identificador não é uma função
                if(getEscopo(tokens[i]->nome, ts)){
                    printErroExpressao("Uma das variaveis e uma funcao.", i, tokens);
                    return 0;
                }

                if(getVar(tokens[i]->nome, escopo, ts)->tipo != TIPOBOOL){
                    printErroExpressao("Uma das variaveis e do tipo int.", i, tokens);
                    return 0;
                }
            }
        }
    }
    return tipo;
}

// Valida expressões matemáticas
int validaAtribuicao(int i, Token ** tokens){
    char * nomeVar = tokens[i-1]->nome;
    int tipoVar = getVar(nomeVar, escopo, ts)->tipo;

    int resultado = validaExpressao(i, tokens);

    if(!resultado){
        return 0;
    }
    if(tipoVar != resultado){
        printErroExpressao("Divergencia de tipos.", i, tokens);
        return 0;
    }

    return 1;
}

int analiseSemantica(){
    // Recupera a lista de tokens do programa
    Token ** tokens = getTokens();
    int tamanho = lt->tamanho; // Tamanho da lista de tokens
    int i;
    for(i = 0; i < tamanho; i++){
        //printf("Nome / cod token: %s____  / %d\n", tokens[i]->nome, tokens[i]->codToken);

        // Troca de escopo
        if(isEquals(tokens[i]->nome, "void ") ||
           isEquals(tokens[i]->nome, "program ")){
            escopo = tokens[i+1]->nome;
        }

        // Validação de comandos de atribuição
        if(tokens[i]->codToken == _SINAL_IGUAL_ &&
           !validaAtribuicao(i, tokens)){
            return 0;
        }

        // Validação de expressões lógicas
        if(tokens[i]->codToken == _IF_   ||
           tokens[i]->codToken == _WHILE_){
            if(!validaExpressao(i, tokens)){
                puts("Print expressao com erro no while ou no if.");
                return 0;
            }
        }
    }

    return 1;
}

/// ============================== FUNCAO MAIN

int main(){
    char *palavra = leArquivo("entrada.txt");

    if (!palavra) {
        printf("ERRO NA LEITURA DO ARQUIVO\n");
        return 1;
    }

    // Contador que representa o caracter da string que deve ser analisado pela funcao scanner
    int pos = 0;

    // Inicializacao do scanner
    initScanner();

    // Inicialização da tabela de símbolos
    ts = initTabelaSimbolo();

    // Inicialização da lista de tokens para analise semantica
    lt = initListaToken();

    // Inicializa lookahead com o primeiro caracter
    lookahead = palavra[pos];

    // Inicializa token com a primeira chamada do scanner
    token = scanner(palavra, &pos);

    // Comeca a interpretacao sintatica pelo nao-terminal Programa
    int analisaLexSinOK = Programa(palavra, &pos);
    if (token != 0) {
        if (!analisaLexSinOK){
            erro(&pos, palavra);
            return 1;
        }
    } else {
        erroLexico = 1;
        erro(&pos, palavra);
        return 1;
    }

    int analiseSemanticaOK = analiseSemantica();
    if(analiseSemanticaOK){
        puts("SUCESSO NA LEITURA");
    }

    return 0;
}


/// ============================== IMPLEMENTACAO DOS METODOS RELATIVOS AO FUNCIONAMENTO DO ASDR

/*
 Funcao que verifica que se a proxima palavra da string eh valida
 ou nao atraves da chamada da funcao scanner. Atualiza lookahead
 e token conforme o resultado, retornando 1 caso a palavra seja valida
 ou 0 caso contrario.
 */
int match(char c, char palavra[], int *pos) {
    if (lookahead == c) {

        while(palavra[*pos] == ' ')
            (*pos)++;

        lookahead = palavra[*pos];

        token = scanner(palavra, pos);

        while (token == _COMENTARIO_) {
            while(palavra[*pos] == ' ')
                (*pos)++;

            lookahead = palavra[*pos];

            token = scanner(palavra, pos);
        }

        if (!token) {
            erroLexico = 1;
            return 0;
        }
        return 1;

    }
    return 0;
}

/*
 Funcao que imprime o tipo de erro lexico encontrado,
 juntamente com a posicao na qual o ASDR foi interrompido
 e o caracter encontrado nessa posicao.
 */
void erro(int *pos, char *palavra) {
    printf("\nENCONTRADO ERRO ");
    if (erroLexico)
        printf("LEXICO ");
    else
        printf("DE SINTAXE ");

    printf("NA POSICAO #%d: %c\n\n", *pos, lookahead);

    int i;
    for (i = 0; i < *pos; i++) {
        printf("%c", palavra[i]);
    }
    printf("\n");
}

char *leArquivo(char *nomeArquivo) {
    FILE *arq;
    arq = fopen(nomeArquivo, "rt");
    if (!arq) return NULL;
    int cont = 0, tam = 720;
    char c;
    char *resultado = malloc(tam * sizeof(char));
    if (!resultado) return NULL;

    while ((c = getc(arq)) != EOF) {
        if (cont == tam - 1) {
            tam *= 2;
            resultado = realloc(resultado, tam);
            if (!resultado) return NULL;
        }

        if (c != '\n' && c != '\t') {
            resultado[cont] = c;
            cont++;
        }
    }
    resultado[cont] = '\0';
    fclose(arq);

    return resultado;
}


/// ============================== IMPLEMENTACAO DAS FUNCOES RECURSIVAS DOS SIMBOLOS NAO-TERMINAIS

/*
 1. Programa -> DecFuncoesRep program Identificador Bloco
    DecFuncoesRep -> DeclaracoesFuncoes DecFuncoesRep
    DecFuncoesRep -> &
*/
int Programa(char palavra[], int *pos) {
    // O primeiro "first" possivel para Programa eh v,
    // entao a verificacao do lookahead comeca por essa letra
    if (lookahead == 'v') {
        if (DecFuncoesRep(palavra, pos)             &&
            match('p', palavra, pos)                &&
            Identificador(palavra, pos, TIPOFUNCAO) &&
            Bloco(palavra, pos))
            return 1;

    // A segunda possibilidade de "first" para Programa eh p,
    // entao verifica-se o lookahead para essa letra
    } else if (lookahead == 'p') {
        if (match('p', palavra, pos)                &&
            Identificador(palavra, pos, TIPOFUNCAO) &&
            Bloco(palavra, pos))
            return 1;

    }
    return 0;
}

int DecFuncoesRep(char palavra[], int *pos) {
    if (lookahead == 'v') {
        if (DeclaracoesFuncoes(palavra, pos)) {
            if (lookahead == 'v')
                return DecFuncoesRep(palavra, pos);
            return 1;
        }
    } else if (lookahead == 'p') {
        return 1;

    }
    return 0;
}


/*
 2. Bloco -> { DecVariaveisOpcional ComandoComposto }
    DecVariaveisOpcional -> ParteDeclaracoesDeVariaveis
    DecVariaveisOpcional -> &
*/
int Bloco(char palavra[], int *pos) {
    if (lookahead == '{') {
        if (match('{', palavra, pos)           &&
            DecVariaveisOpcional(palavra, pos) &&
            ComandoComposto(palavra, pos)      &&
            match('}', palavra, pos))
            return 1;
    }
    return 0;
}

int DecVariaveisOpcional(char palavra[], int *pos) {
    if (lookahead == 'i'||
        lookahead == 'b') {
        if (ParteDeclaracoesDeVariaveis(palavra, pos))
            return 1;

    } else if (lookahead == '_'                    ||
               (lookahead == 'i' && token == _IF_) ||
               lookahead == 'd'                    ||
               lookahead == 'p'                    ||
               lookahead == ';') {
        return 1;

    }
    return 0;
}


/*
 3. ParteDeclaracoesDeVariaveis -> DecVariaveis ParteDeclaracoesDeVariaveis
    ParteDeclaracoesDeVariaveis -> &
*/
int ParteDeclaracoesDeVariaveis(char palavra[], int *pos) {
    if ((lookahead == 'i' && token == _INT_) ||
        lookahead == 'b') {
        if (DecVariaveis(palavra, pos)) {
            if ((lookahead == 'i' && token == _INT_) ||
                lookahead == 'b') {
                return ParteDeclaracoesDeVariaveis(palavra, pos);
            }
            return 1;
        }
    } else if (lookahead == '_'                    ||
               (lookahead == 'i' && token == _IF_) ||
               lookahead == 'd'                    ||
               lookahead == 'p'                    ||
               lookahead == ';') {
        return 1;

    }
    return 0;
}


/*
 4. DecVariaveis -> int ListaDeIdentificadores ;
    DecVariaveis -> bool ListaDeIdentificadores ;
*/
int DecVariaveis(char palavra[], int *pos) {
    if (lookahead == 'i' && token == _INT_) {
        if (match('i', palavra, pos)                      &&
            ListaDeIdentificadores(palavra, pos, TIPOINT) &&
            match(';', palavra, pos))
            return 1;

    } else if (lookahead == 'b') {
        if (match('b', palavra, pos)                       &&
            ListaDeIdentificadores(palavra, pos, TIPOBOOL) &&
            match(';', palavra, pos))
            return 1;

    }
    return 0;
}


/*
 5. ListaDeIdentificadores -> Identificador ListaIdRep
    ListaIdRep -> , Identificador ListaIdRep
    ListaIdRep -> &
*/
int ListaDeIdentificadores(char palavra[], int *pos, int tipo) {
    if (lookahead == '_') {
        if (Identificador(palavra, pos, tipo)     &&
            ListaIdRep(palavra, pos, tipo))
            return 1;
    }
    return 0;
}

int ListaIdRep(char palavra[], int *pos, int tipo) {
    if (lookahead == ',') {
        if (match(',', palavra, pos)    &&
            Identificador(palavra, pos, tipo)) {
            if (lookahead == ',')
                return ListaIdRep(palavra, pos, tipo);

            return 1;
        }

    } else if (lookahead == '_'                    ||
               (lookahead == 'i' && token == _IF_) ||
               lookahead == 'd'                    ||
               lookahead == 'p'                    ||
               lookahead == ';') {
        return 1;

    }
    return 0;
}


/*
 6. DeclaracoesFuncoes -> DeclaraFuncao DeclaracoesFuncoes
    DeclaracoesFuncoes -> &
*/
int DeclaracoesFuncoes(char palavra[], int *pos) {
    if (lookahead == 'v') {
        if (DeclaraFuncao(palavra, pos)) {
            if (lookahead == 'v')
                return DeclaracoesFuncoes(palavra, pos);
            return 1;
        }
    } else if (lookahead == 'p') {
        return 1;

    }
    return 0;
}


/*
 7. DeclaraFuncao -> void Identificador ( ParametroFormalOpcional ) Bloco
    ParametroFormalOpcional -> ParametroFormal
    ParametroFormalOpcional -> &
*/
int DeclaraFuncao(char palavra[], int *pos) {
    if (lookahead == 'v') {
        if (match('v', palavra, pos)                &&
            Identificador(palavra, pos, TIPOFUNCAO) &&
            match('(', palavra, pos)                &&
            ParametroFormalOpcional(palavra, pos)   &&
            match(')', palavra, pos)                &&
            Bloco(palavra, pos))
            return 1;

    }
    return 0;
}

int ParametroFormalOpcional(char palavra[], int *pos) {
    if (lookahead == 'i'||
        lookahead == 'b') {
        if (ParametroFormal(palavra, pos))
            return 1;

    } else if (lookahead == ')') {
        return 1;

    }
    return 0;
}


/*
 8. ParametroFormal -> int Identificador
    ParametroFormal -> bool Identificador
*/
int ParametroFormal(char palavra[], int *pos) {
    if (lookahead == 'i' && token == _INT_) {
        if (match('i', palavra, pos) &&
            Identificador(palavra, pos, PARFORMALINT))
            return 1;

    } else if (lookahead == 'b') {
        if (match('b', palavra, pos) &&
            Identificador(palavra, pos, PARFORMALBOOL))
            return 1;

    }
    return 0;
}


/*
 9. ComandoComposto -> Comando ; ComandoCompostoRep
    ComandoCompostoRep -> Comando ; ComandoCompostoRep
    ComandoCompostoRep -> &
*/
int ComandoComposto(char palavra[], int *pos) {
    if (lookahead == '_'                    ||
        (lookahead == 'i' && token == _IF_) ||
        lookahead == 'd'                    ||
        lookahead == 'p') {
        if (Comando(palavra, pos)             &&
            match(';', palavra, pos)          &&
            ComandoCompostoRep(palavra, pos))
            return 1;

    }
    return 0;
}

int ComandoCompostoRep(char palavra[], int *pos) {
    if (lookahead == '_'                    ||
        (lookahead == 'i' && token == _IF_) ||
        lookahead == 'd'                    ||
        lookahead == 'p') {
            if (Comando(palavra, pos) &&
                match(';', palavra, pos)) {
                if (lookahead == '_'                    ||
                    (lookahead == 'i' && token == _IF_) ||
                    lookahead == 'd'                    ||
                    lookahead == 'p')
                    return ComandoCompostoRep(palavra, pos);

                return 1;
            }
    } else if (lookahead == '}') {
        return 1;

    }
    return 0;
}


/*
 10. Comando -> Identificador ComandoAuxiliar
     Comando -> ComandoCondicional
     Comando -> ComandoRepetitivo
     Comando -> print ( Identificador )
     ComandoAuxiliar -> Atribuicao
     ComandoAuxiliar -> ChamadaDeProcedimento
*/
int Comando(char palavra[], int *pos) {
    if (lookahead == '_') {
        if (Identificador(palavra, pos, GETTIPO) &&
            ComandoAuxiliar(palavra, pos))
            return 1;

    } else if (lookahead == 'i' && token == _IF_) {
        if (ComandoCondicional(palavra, pos))
            return 1;
    } else if (lookahead == 'd') {
        if (ComandoRepetitivo(palavra, pos))
            return 1;

    } else if (lookahead == 'p') {
        if (match('p', palavra, pos)             &&
            match('(', palavra, pos)             &&
            Identificador(palavra, pos, GETTIPO) &&
            match(')', palavra, pos)){
                printTabelaSimbolo(ts);
                return 1;
            }
    }
    return 0;
}

int ComandoAuxiliar(char palavra[], int *pos) {
    if (lookahead == '=' && token == _SINAL_IGUAL_) {
        if (Atribuicao(palavra, pos))
            return 1;

    } else if (lookahead == '(') {
        if (ChamadaDeProcedimento(palavra, pos))
            return 1;

    }
    return 0;
}


/*
 11. Atribuicao -> = Expressao
*/
int Atribuicao(char palavra[], int *pos) {
    if (lookahead == '=' && token == _SINAL_IGUAL_) {
        if (match('=', palavra, pos)    &&
            Expressao(palavra, pos))
            return 1;
    }
    return 0;
}


/*
 12. ChamadaDeProcedimento -> ( ParametroOpcional )
     ParametroOpcional -> Parametro
     ParametroOpcional -> &
*/
int ChamadaDeProcedimento(char palavra[], int *pos) {
    if (lookahead == '(') {
        if (match('(', palavra, pos)        &&
            ParametroOpcional(palavra, pos) &&
            match(')', palavra, pos))
            return 1;

    }
    return 0;
}

int ParametroOpcional(char palavra[], int *pos) {
    if (lookahead == '_' ||
        lookahead == '0' ||
        lookahead == '1' ||
        lookahead == '2' ||
        lookahead == '3' ||
        lookahead == '4' ||
        lookahead == '5' ||
        lookahead == '6' ||
        lookahead == '7' ||
        lookahead == '8' ||
        lookahead == '9' ||
        lookahead == 't' ||
        lookahead == 'f') {
        if (Parametro(palavra, pos))
            return 1;

    } else if (lookahead == ')') {
        return 1;

    }
    return 0;
}


/*
 13. Parametro -> Identificador
     Parametro -> Numero
     Parametro -> Bool
     Parametro -> &
*/
int Parametro(char palavra[], int *pos) {
    if (lookahead == '_') {
        if (Identificador(palavra, pos, GETTIPO))
            return 1;

    } else if (lookahead == '0' ||
               lookahead == '1' ||
               lookahead == '2' ||
               lookahead == '3' ||
               lookahead == '4' ||
               lookahead == '5' ||
               lookahead == '6' ||
               lookahead == '7' ||
               lookahead == '8' ||
               lookahead == '9') {
        if (Numero(palavra, pos))
            return 1;

    } else if (lookahead == 't'||
               lookahead == 'f') {
        if (Bool(palavra, pos))
            return 1;

    } else if (lookahead == ')') {
        return 1;
    }

    return 0;
}


/*
 14. ComandoCondicional -> if ( Expressao ) { ComandoComposto } ElseOpcional
     ElseOpcional -> else { ComandoComposto }
     ElseOpcional -> &
*/
int ComandoCondicional(char palavra[], int *pos) {
    if (lookahead == 'i' && token == _IF_) {
        if (match('i', palavra, pos)        &&
            match('(', palavra, pos)        &&
            Expressao(palavra, pos)         &&
            match(')', palavra, pos)        &&
            match('{', palavra, pos)        &&
            ComandoComposto(palavra, pos)   &&
            match('}', palavra, pos)        &&
            ElseOpcional(palavra, pos))
            return 1;

    }
    return 0;
}

int ElseOpcional(char palavra[], int *pos) {
    if (lookahead == 'e') {
        if (match('e', palavra, pos)        &&
            match('{', palavra, pos)        &&
            ComandoComposto(palavra, pos)   &&
            match('}', palavra, pos))
            return 1;

    } else if (lookahead == ';' ||
               lookahead == '}') {
        return 1;

    }
    return 0;
}


/*
 15. ComandoRepetitivo -> do { ComandoComposto } while ( Expressao )
*/
int ComandoRepetitivo(char palavra[], int *pos) {
    if (lookahead == 'd') {
        if (match('d', palavra, pos)        &&
            match('{', palavra, pos)        &&
            ComandoComposto(palavra, pos)   &&
            match('}', palavra, pos)        &&
            match('w', palavra, pos)        &&
            match('(', palavra, pos)        &&
            Expressao(palavra, pos)         &&
            match(')', palavra, pos))
            return 1;

    }
    return 0;
}


/*
 16. Expressao -> ExpressaoSimples ExpressaoOpcional
     ExpresaoOpcional -> Relacao ExpressaoSimples
*/
int Expressao(char palavra[], int *pos) {
    if (lookahead == '+' ||
        lookahead == '-' ||
        lookahead == '_' ||
        lookahead == '0' ||
        lookahead == '1' ||
        lookahead == '2' ||
        lookahead == '3' ||
        lookahead == '4' ||
        lookahead == '5' ||
        lookahead == '6' ||
        lookahead == '7' ||
        lookahead == '8' ||
        lookahead == '9' ||
        lookahead == 't' ||
        lookahead == 'f' ||
        lookahead == '(') {
        if (ExpressaoSimples(palavra, pos) &&
            ExpresaoOpcional(palavra, pos))
            return 1;
    }
    return 0;
}

int ExpresaoOpcional(char palavra[], int *pos) {
    if ((lookahead == '=' && token == _IGUAL_IGUAL_) ||
        lookahead == '<'                             ||
        lookahead == '>') {
        if (Relacao(palavra, pos) &&
            ExpressaoSimples(palavra, pos))
            return 1;

    } else if (lookahead == ')' ||
               lookahead == ';') {
        return 1;
    }
    return 0;
}


/*
 17. Relacao -> ==
     Relacao -> <>
     Relacao -> <
     Relacao -> <=
     Relacao -> >=
     Relacao -> >
*/
int Relacao(char palavra[], int *pos) {
    if (lookahead == '=' && token == _IGUAL_IGUAL_) {
        if (match('=', palavra, pos))
            return 1;

    } else if (lookahead == '<') {
        if (match('<', palavra, pos))
            return 1;
    } else if (lookahead == '>') {
        if (match('>', palavra, pos))
            return 1;
    }
    return 0;
}


/*
 18. ExpressaoSimples -> SinalOpcional Termo ExpressaoSimplesRep
     SinalOpcional -> +
     SinalOpcional -> -
     SinalOpcional -> &
     ExpressaoSimplesRep -> ExpressaoSimples ExpressaoSimplesRep
     ExpressaoSimplesRep -> &
*/
int ExpressaoSimples(char palavra[], int *pos){
    if (lookahead == 't' ||
        lookahead == 'f' ||
        lookahead == '_' ||
        lookahead == '+' ||
        lookahead == '-' ||
        lookahead == '0' ||
        lookahead == '1' ||
        lookahead == '2' ||
        lookahead == '3' ||
        lookahead == '4' ||
        lookahead == '5' ||
        lookahead == '6' ||
        lookahead == '7' ||
        lookahead == '8' ||
        lookahead == '9' ||
        lookahead == '(') {
        if (SinalOpcional(palavra, pos)         &&
            Termo(palavra, pos)                 &&
            ExpressaoSimplesRep(palavra, pos))
            return 1;
    }

    return 0;
}

int SinalOpcional(char palavra[], int *pos){
    if(lookahead == '+' && match('+', palavra, pos)){
        return 1;
    }

    else if(lookahead == '-' && match('-', palavra, pos))
        return 1;
    else if (lookahead == '_' ||
        lookahead == '0' ||
        lookahead == '1' ||
        lookahead == '2' ||
        lookahead == '3' ||
        lookahead == '4' ||
        lookahead == '5' ||
        lookahead == '6' ||
        lookahead == '7' ||
        lookahead == '8' ||
        lookahead == '9' ||
        lookahead == 't' ||
        lookahead == 'f' ||
        lookahead == '(') {
             return 1;
        }
    return 0;
}

int ExpressaoSimplesRep(char palavra[], int *pos){
    if (lookahead == 't' ||
        lookahead == 'f' ||
        lookahead == '_' ||
        lookahead == '+' ||
        lookahead == '-' ||
        lookahead == '0' ||
        lookahead == '1' ||
        lookahead == '2' ||
        lookahead == '3' ||
        lookahead == '4' ||
        lookahead == '5' ||
        lookahead == '6' ||
        lookahead == '7' ||
        lookahead == '8' ||
        lookahead == '9' ||
        lookahead == '(') {
        if (ExpressaoSimples(palavra, pos)) {
            if (lookahead == 't' ||
                lookahead == 'f' ||
                lookahead == '_' ||
                lookahead == '+' ||
                lookahead == '-' ||
                lookahead == '0' ||
                lookahead == '1' ||
                lookahead == '2' ||
                lookahead == '3' ||
                lookahead == '4' ||
                lookahead == '5' ||
                lookahead == '6' ||
                lookahead == '7' ||
                lookahead == '8' ||
                lookahead == '9' ||
                lookahead == '(')
                return ExpressaoSimplesRep(palavra, pos);
            return 1;
        }
    } else if (lookahead == ')' ||
               lookahead == '=' ||
               lookahead == '<' ||
               lookahead == '>' ||
               lookahead == ';') {
        return 1;
    }
    return 0;
}

/*
 19. Termo -> Fator FatorRep
     FatorRep -> Operacao Fator FatorRep
     FatorRep -> &
     Operacao -> *
     Operacao -> /
*/
int Termo(char palavra[], int *pos) {
    if (lookahead == '_' ||
        lookahead == '0' ||
        lookahead == '1' ||
        lookahead == '2' ||
        lookahead == '3' ||
        lookahead == '4' ||
        lookahead == '5' ||
        lookahead == '6' ||
        lookahead == '7' ||
        lookahead == '8' ||
        lookahead == '9' ||
        lookahead == 't' ||
        lookahead == 'f' ||
        lookahead == '(') {
        if (Fator(palavra, pos) &&
            FatorRep(palavra, pos))
            return 1;
    }
    return 0;
}

int FatorRep(char palavra[], int *pos) {
    if (lookahead == '*' || lookahead == '/') {
        if (Operacao(palavra, pos) &&
            Fator(palavra, pos)) {
            if (lookahead == '*' || lookahead == '/') {
                return FatorRep(palavra, pos);;
            }
            return 1;
        }
    } else if(lookahead == 't' ||
              lookahead == 'f' ||
              lookahead == '_' ||
              lookahead == '+' ||
              lookahead == '-' ||
              lookahead == '(' ||
              lookahead == ')' ||
              lookahead == ';' ||
              lookahead == '=' ||
              lookahead == '<' ||
              lookahead == '>') {
        return 1;
    }
    return 0;
}

int Operacao(char palavra[], int *pos) {
    if (lookahead == '*') {
        if (match('*', palavra, pos))
            return 1;

    } else if (lookahead == '/') {
        if (match('/', palavra, pos))
            return 1;
    }
    return 0;
}


/*
 20. Fator -> Variavel
     Fator -> Numero
     Fator -> Bool
     Fator -> ( ExpressaoSimples )
*/
int Fator(char palavra[], int *pos) {
    if(lookahead == '_' && Variavel(palavra, pos))
        return 1;
    else if((lookahead == '0' ||
             lookahead == '1' ||
             lookahead == '2' ||
             lookahead == '3' ||
             lookahead == '4' ||
             lookahead == '5' ||
             lookahead == '6' ||
             lookahead == '7' ||
             lookahead == '8' ||
             lookahead == '9') && Numero(palavra, pos))
        return 1;
    else if((lookahead == 't' ||
             lookahead == 'f') && Bool(palavra, pos))
        return 1;

    else if(lookahead == '(') {
        if (match('(', palavra, pos)        &&
            ExpressaoSimples(palavra, pos)  &&
            match(')', palavra, pos))
            return 1;
    }

    return 0;
}


/*
 21. Variavel -> Identificador
*/
int Variavel(char palavra[], int *pos) {
    if (lookahead == '_') {
        if (Identificador(palavra,pos, GETTIPO))
            return 1;
    }
    return 0;
}


/*
 22. Bool -> true
     Bool -> false
*/
int Bool(char palavra[], int *pos) {
    if (lookahead == 't') {
        if (match('t', palavra, pos))
            return 1;

    } else if (lookahead == 'f') {
        if (match('f', palavra, pos))
            return 1;
    }
    return 0;
}


/*
 23. Numero -> num
*/
int Numero(char palavra[], int *pos) {
    if(lookahead == '0'){
        if(match('0', palavra, pos))
            return 1;
    }

    else if(lookahead == '1'){
        if(match('1', palavra, pos)){
            return 1;
        }
    }

    else if(lookahead == '2'){
        if(match('2', palavra, pos))
            return 1;
    }

    else if(lookahead == '3'){
        if(match('3', palavra, pos))
            return 1;
    }

    else if(lookahead == '4'){
        if(match('4', palavra, pos))
            return 1;
    }

    else if(lookahead == '5'){
        if(match('5', palavra, pos))
            return 1;
    }

    else if(lookahead == '6'){
        if(match('6', palavra, pos))
            return 1;
    }

    else if(lookahead == '7'){
        if(match('7', palavra, pos))
            return 1;
    }

    else if(lookahead == '8'){
        if(match('8', palavra, pos))
            return 1;
    }

    else if(lookahead == '9'){
        if(match('9', palavra, pos))
            return 1;
    }
    return 0;
}

/*
 24. Identificador -> id
*/
int Identificador(char palavra[], int *pos, int tipo) {
    char * nomeIdentificador = listaToString();

    // Insere na tabela de símbolos se for != de GETTIPO
    if(tipo == TIPOINT){
        // Caso a variável ja exista no escopo
        if(!insereVariavel(escopo, nomeIdentificador, INT, ts)){
            return 0;
        };
    }
    else if(tipo == TIPOBOOL){
        if(!insereVariavel(escopo, nomeIdentificador, BOOL, ts)){
            return 0;
        };
    }
    else if(tipo == TIPOFUNCAO){
        escopo = nomeIdentificador;
        criaEscopo(nomeIdentificador, ts);
    }
    else if(tipo == PARFORMALINT){
        char * nomeParametroFormal = nomeIdentificador;
        insereParametroFormal(escopo, nomeParametroFormal, INT, ts);
    }
    else if(tipo == PARFORMALBOOL){
        char * nomeParametroFormal = nomeIdentificador;
        insereParametroFormal(escopo, nomeParametroFormal, BOOL, ts);
    }

    if (lookahead == '_') {
        if (match('_', palavra, pos))
            return 1;
    }
    return 0;
}

/// ============================== IMPLEMENTACAO DA TAD LISTA LIGADA USADA PELO ANALISADOR LEXICO

struct TNo {
    struct TNo *prox;
    char letra;
};

struct TLista {
    TNo *ini;
    TNo *fim;
    int tam;
};

TLista * initLista() {
    TLista *l = malloc(sizeof(TLista));
    l->ini = 0;
    l->fim = 0;
    l->tam = 0;
    return l;
};

void insereElemento(char c) {
    l->tam++;

    TNo *no = malloc(sizeof(TNo));
    no->letra = c;
    no->prox = 0;

    // Insercao na lista vazia
    if(l->ini == 0) {
        l->ini = no;
        l->fim = no;
    }
    // Lista com um ou mais elementos
    else {
        l->fim->prox = no;
        l->fim = no;
    }
};

void resetLista() {
    l->ini = 0;
    l->fim = 0;
    l->tam = 0;
}

void freeLista() {
    free(l);
}

char * listaToString() {
    char *resultado = calloc(l->tam + 1, sizeof(char));
    resultado[l->tam] = '\0'; // Indica fim da string

    int i;
    TNo *no;
    for (no = l->ini, i = 0; no != 0 ; no = no->prox, i++) {
        resultado[i] = no->letra;
    }
    return resultado;
}


/// ============================== IMPLEMENTACAO DOS METODOS RELATIVOS AO SCANNER DO ANALISADOR LEXICO

void initScanner() {
    l = initLista();
}

int scanner(char *p, int *pos) {
    resetLista(); // Remove todos os elementos da lista que guarda o nome do lexema

    char *palavra = &p[*pos];

    // Verifica se a string ja chegou ao fim
    if (*palavra == '\0') {
        return -1;
    }

    // Remove espacos em branco desnecessarios
    while(*palavra == ' ') {
        palavra++; (*pos)++;
        if (*palavra == '\0'){
            return -1;
        }
    }

    // Inicio Automato Finito Deterministico
    q0:
    	insereElemento(*palavra);
        switch(*palavra){
            case '<':
                palavra++; (*pos)++;
                goto q1;
            case '>':
                palavra++; (*pos)++;
                goto q2;
            case '/':
                palavra++; (*pos)++;
                goto q3;
            case '_':
                palavra++; (*pos)++;
                goto q40;
            case '{':
                palavra++; (*pos)++;
                goto q16;
            case '}':
                palavra++; (*pos)++;
                goto q15;
            case ';':
                palavra++; (*pos)++;
                goto q14;
            case ',':
                palavra++; (*pos)++;
                goto q13;
            case '(':
                palavra++; (*pos)++;
                goto q11;
            case ')':
                palavra++; (*pos)++;
                goto q12;
            case '+':
                palavra++; (*pos)++;
                goto q6;
            case '=':
                palavra++; (*pos)++;
                goto q5;
            case '-':
                palavra++; (*pos)++;
                goto q4;
            case '*':
                palavra++; (*pos)++;
                goto q38;
            case '1':
                palavra++; (*pos)++;
                goto q41;
            case '2':
                palavra++; (*pos)++;
                goto q41;
            case '3':
                palavra++; (*pos)++;
                goto q41;
            case '4':
                palavra++; (*pos)++;
                goto q41;
            case '5':
                palavra++; (*pos)++;
                goto q41;
            case '6':
                palavra++; (*pos)++;
                goto q41;
            case '7':
                palavra++; (*pos)++;
                goto q41;
            case '8':
                palavra++; (*pos)++;
                goto q41;
            case '9':
                palavra++; (*pos)++;
                goto q41;
            case '0':
                palavra++; (*pos)++;
                goto q41;
            case 'b':
                palavra++; (*pos)++;
                goto q47;
            case 'd':
                palavra++; (*pos)++;
                goto q82;
            case 'e':
                palavra++; (*pos)++;
                goto q85;
            case 'f':
                palavra++; (*pos)++;
                goto q76;
            case 'i':
                palavra++; (*pos)++;
                goto q43;
            case 'p':
                palavra++; (*pos)++;
                goto q52;
            case 't':
                palavra++; (*pos)++;
                goto q71;
            case 'v':
                palavra++; (*pos)++;
                goto q60;
            case 'w':
                palavra++; (*pos)++;
                goto q90;
            default:
                return _ERRO_LEXICO_;
        }

    q1:
    	insereElemento(*palavra);
        switch(*palavra){
            case '=':
                palavra++; (*pos)++;
                goto q7;
            case '>':
                palavra++; (*pos)++;
                goto q8;
            case ' ':
                palavra++; (*pos)++;
                goto q30;
            case '\0':
                goto q30;
            default:
                return _ERRO_LEXICO_;
        }

    q2:
    	insereElemento(*palavra);
        switch(*palavra){
            case '=':
                palavra++; (*pos)++;
                goto q9;
            case ' ':
                palavra++; (*pos)++;
                goto q19;
            case '\0':
                goto q19;
            default:
                return _ERRO_LEXICO_;
        }

    q3:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q20;
            case '\0':
                goto q20;
            case '*':
                palavra++; (*pos)++;
                goto q31;
            default:
                return _ERRO_LEXICO_;
        }

    q4:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q21;
            case '\0':
                goto q21;
            default:
                return _ERRO_LEXICO_;
        }

    q5:
    	insereElemento(*palavra);
        switch(*palavra){
            case '=':
                palavra++; (*pos)++;
                goto q32;
            case ' ':
                palavra++; (*pos)++;
                goto q22;
            case '\0':
                goto q22;
            default:
                return _ERRO_LEXICO_;
        }

    q6:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q23;
            case '\0':
                goto q23;
            default:
                return _ERRO_LEXICO_;
        }

    q7:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q10;
            case '\0':
                goto q10;
            default:
                return _ERRO_LEXICO_;
        }

    q8:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q17;
            case '\0':
                goto q17;
            default:
                return _ERRO_LEXICO_;
        }

    q9:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q18;
            case '\0':
                goto q18;
            default:
                return _ERRO_LEXICO_;
        }

    q10:
        insereToken(listaToString(), _MENOR_IGUAL_);
        return _MENOR_IGUAL_;

    q11:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q24;
            case '\0':
                goto q24;
            default:
                return _ERRO_LEXICO_;
        }

    q12:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q25;
            case '\0':
                goto q25;
            default:
                return _ERRO_LEXICO_;
        }

    q13:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q26;
            case '\0':
                goto q26;
            default:
                return _ERRO_LEXICO_;
        }

    q14:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q27;
            case '\0':
                goto q27;
            default:
                return _ERRO_LEXICO_;
        }

    q15:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q28;
            case '\0':
                goto q28;
            default:
                return _ERRO_LEXICO_;
        }

    q16:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q29;
            case '\0':
                goto q29;
            default:
                return _ERRO_LEXICO_;
        }

    q17:
        insereToken(listaToString(), _DIFERENTE_);
        return _DIFERENTE_;

    q18:
        insereToken(listaToString(), _MAIOR_IGUAL_);
        return _MAIOR_IGUAL_;

    q19:
        insereToken(listaToString(), _MAIOR_);
        return _MAIOR_;

    q20:
        insereToken(listaToString(), _DIVISAO_);
        return _DIVISAO_;

    q21:
        insereToken(listaToString(), _SINAL_MENOS_);
        return _SINAL_MENOS_;

    q22:
        insereToken(listaToString(), _SINAL_IGUAL_);
        return _SINAL_IGUAL_;

    q23:
        insereToken(listaToString(), _SINAL_MAIS_);
        return _SINAL_MAIS_;

    q24:
        insereToken(listaToString(), _ABRE_PARENTESES_);
        return _ABRE_PARENTESES_;

    q25:
        insereToken(listaToString(), _FECHA_PARENTESES_);
        return _FECHA_PARENTESES_;

    q26:
        insereToken(listaToString(), _VIRGULA_);
        return _VIRGULA_;

    q27:
        insereToken(listaToString(), _PONTO_VIRGULA_);
        return _PONTO_VIRGULA_;

    q28:
        insereToken(listaToString(), _FECHA_CHAVES_);
        return _FECHA_CHAVES_;

    q29:
        insereToken(listaToString(), _ABRE_CHAVES_);
        return _ABRE_CHAVES_;

    q30:
        insereToken(listaToString(), _MENOR_);
        return _MENOR_;

    q31:
        // Validação de comentários
        switch(*palavra){
            // Verifica se a string acabou antes de completar o comentário
            case '\0':
                return _ERRO_LEXICO_;
            default:
                goto q34;
        }

    q32:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q33;
            case '\0':
                goto q33;
            default:
                return _ERRO_LEXICO_;
        }

    q33:
        insereToken(listaToString(), _IGUAL_IGUAL_);
        return _IGUAL_IGUAL_;

    q34:
    	insereElemento(*palavra);
        switch(*palavra){
            case '\0':
                return _ERRO_LEXICO_;

            // Verifica se é fim de comentário
            case '*':
                palavra++; (*pos)++;
                goto q35;

            default:
                palavra++; (*pos)++;
                goto q34;

        }

    q35:
    	insereElemento(*palavra);
        switch(*palavra){
            case '\0':
                return _ERRO_LEXICO_;

            case '/':
                palavra++; (*pos)++;
                goto q36;

            case '*':
                palavra--;
                palavra++; palavra++; (*pos)++;
                goto q35;

            default:
                palavra--;
                palavra++;
                palavra++; (*pos)++;
                goto q34;
        }

    q36:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q37;
            case '\0':
                goto q37;
            default:
                return _ERRO_LEXICO_;
        }

    q37:
        insereToken(listaToString(), _COMENTARIO_);
        return _COMENTARIO_;

    q38:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q39;
            case '\0':
                goto q39;
            default:
                return _ERRO_LEXICO_;
        }

    q39:
        insereToken(listaToString(), _SINAL_MULTIPLICACAO_);
        return _SINAL_MULTIPLICACAO_;

    q40:
        if (((*palavra >= 65) && (*palavra <= 90)) || ((*palavra >= 97) && (*palavra <= 122))) {
            insereElemento(*palavra);
            palavra++; (*pos)++;
            goto q97;

        } else {
            return _ERRO_LEXICO_;
        }

    q41:
    	insereElemento(*palavra);
        switch(*palavra){
            case '1':
                palavra++; (*pos)++;
                goto q41;
            case '2':
                palavra++; (*pos)++;
                goto q41;
            case '3':
                palavra++; (*pos)++;
                goto q41;
            case '4':
                palavra++; (*pos)++;
                goto q41;
            case '5':
                palavra++; (*pos)++;
                goto q41;
            case '6':
                palavra++; (*pos)++;
                goto q41;
            case '7':
                palavra++; (*pos)++;
                goto q41;
            case '8':
                palavra++; (*pos)++;
                goto q41;
            case '9':
                palavra++; (*pos)++;
                goto q41;
            case '0':
                palavra++; (*pos)++;
                goto q41;
            case ' ':
                palavra++; (*pos)++;
                goto q96;
            case '\0':
                goto q96;
            default:
                return _ERRO_LEXICO_;
        }

    q42:
        insereToken(listaToString(), _IDENTIFICADOR_);
        return _IDENTIFICADOR_;

    q43:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'f':
                palavra++; (*pos)++;
                goto q69;
            case 'n':
                palavra++; (*pos)++;
                goto q44;
            default:
                return _ERRO_LEXICO_;
        }

    q44:
    	insereElemento(*palavra);
        switch(*palavra){
            case 't':
                palavra++; (*pos)++;
                goto q45;
            default:
                return _ERRO_LEXICO_;
        }

    q45:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q46;
            case '\0':
                goto q46;
            default:
                return _ERRO_LEXICO_;
        }

    q46:
        insereToken(listaToString(), _INT_);
        return _INT_;

    q47:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q48;
            default:
                return _ERRO_LEXICO_;
        }

    q48:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q49;
            default:
                return _ERRO_LEXICO_;
        }

    q49:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q50;
            default:
                return _ERRO_LEXICO_;
        }

    q50:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q51;
            case '\0':
                goto q51;
            default:
                return _ERRO_LEXICO_;
        }

    q51:
        insereToken(listaToString(), _BOOL_);
        return _BOOL_;

    q52:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'r':
                palavra++; (*pos)++;
                goto q53;
            default:
                return _ERRO_LEXICO_;
        }

    q53:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q54;
            case 'i':
                palavra++; (*pos)++;
                goto q65;
            default:
                return _ERRO_LEXICO_;
        }

    q54:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'g':
                palavra++; (*pos)++;
                goto q55;
            default:
                return _ERRO_LEXICO_;
        }

    q55:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'r':
                palavra++; (*pos)++;
                goto q56;
            default:
                return _ERRO_LEXICO_;
        }

    q56:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'a':
                palavra++; (*pos)++;
                goto q57;
            default:
                return _ERRO_LEXICO_;
        }

    q57:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'm':
                palavra++; (*pos)++;
                goto q58;
            default:
                return _ERRO_LEXICO_;
        }

    q58:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q59;
            case '\0':
                goto q59;
            default:
                return _ERRO_LEXICO_;
        }

    q59:
        insereToken(listaToString(), _PROGRAM_);
        return _PROGRAM_;

    q60:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q61;
            default:
                return _ERRO_LEXICO_;
        }

    q61:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'i':
                palavra++; (*pos)++;
                goto q62;
            default:
                return _ERRO_LEXICO_;
        }

    q62:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'd':
                palavra++; (*pos)++;
                goto q63;
            default:
                return _ERRO_LEXICO_;
        }

    q63:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q64;
            case '\0':
                goto q64;
            default:
                return _ERRO_LEXICO_;
        }

    q64:
        insereToken(listaToString(), _VOID_);
        return _VOID_;

    q65:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'n':
                palavra++; (*pos)++;
                goto q66;
            default:
                return _ERRO_LEXICO_;
        }

    q66:
    	insereElemento(*palavra);
        switch(*palavra){
            case 't':
                palavra++; (*pos)++;
                goto q67;
            default:
                return _ERRO_LEXICO_;
        }

    q67:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q68;
            case '\0':
                goto q68;
            default:
                return _ERRO_LEXICO_;
        }

    q68:
        insereToken(listaToString(), _PRINT_);
        return _PRINT_;

    q69:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q70;
            case '\0':
                goto q70;
            default:
                return _ERRO_LEXICO_;
        }

    q70:
        insereToken(listaToString(), _IF_);
        return _IF_;

    q71:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'r':
                palavra++; (*pos)++;
                goto q72;
            default:
                return _ERRO_LEXICO_;
        }

    q72:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'u':
                palavra++; (*pos)++;
                goto q73;
            default:
                return _ERRO_LEXICO_;
        }

    q73:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q74;
            default:
                return _ERRO_LEXICO_;
        }

    q74:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q75;
            case '\0':
                goto q75;
            default:
                return _ERRO_LEXICO_;
        }

    q75:
	    insereToken(listaToString(), _TRUE_);
        return _TRUE_;

    q76:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'a':
                palavra++; (*pos)++;
                goto q77;
            default:
                return _ERRO_LEXICO_;
        }

    q77:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q78;
            default:
                return _ERRO_LEXICO_;
        }

    q78:
    	insereElemento(*palavra);
        switch(*palavra){
            case 's':
                palavra++; (*pos)++;
                goto q79;
            default:
                return _ERRO_LEXICO_;
        }

    q79:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q80;
            default:
                return _ERRO_LEXICO_;
        }

    q80:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q81;
            case '\0':
                goto q81;
            default:
                return _ERRO_LEXICO_;
        }

    q81:
        insereToken(listaToString(), _FALSE_);
        return _FALSE_;

    q82:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q83;
            default:
                return _ERRO_LEXICO_;
        }

    q83:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q84;
            case '\0':
                goto q84;
            default:
                return _ERRO_LEXICO_;
        }

    q84:
        insereToken(listaToString(), _DO_);
        return _DO_;

    q85:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q86;
            default:
                return _ERRO_LEXICO_;
        }

    q86:
    	insereElemento(*palavra);
        switch(*palavra){
            case 's':
                palavra++; (*pos)++;
                goto q87;
            default:
                return _ERRO_LEXICO_;
        }

    q87:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q88;
            default:
                return _ERRO_LEXICO_;
        }

    q88:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q89;
            case '\0':
                goto q89;
            default:
                return _ERRO_LEXICO_;
        }

    q89:
        insereToken(listaToString(), _ELSE_);
        return _ELSE_;

    q90:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'h':
                palavra++; (*pos)++;
                goto q91;
            default:
                return _ERRO_LEXICO_;
        }

    q91:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'i':
                palavra++; (*pos)++;
                goto q92;
            default:
                return _ERRO_LEXICO_;
        }

    q92:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q93;
            default:
                return _ERRO_LEXICO_;
        }

    q93:
    	insereElemento(*palavra);
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q94;
            default:
                return _ERRO_LEXICO_;
        }

    q94:
    	insereElemento(*palavra);
        switch(*palavra){
            case ' ':
                palavra++; (*pos)++;
                goto q95;
            case '\0':
                goto q95;
            default:
                return _ERRO_LEXICO_;
        }

    q95:
        insereToken(listaToString(), _WHILE_);
        return _WHILE_;

    q96:
        insereToken(listaToString(), _NUM_);
        return _NUM_;

    q97:
        if (((*palavra >= 65) && (*palavra <= 90)) || ((*palavra >= 97) && (*palavra <= 122))) {
            insereElemento(*palavra);
            palavra++; (*pos)++;
            goto q97;

        } else if (*palavra == ' ') {
            palavra++; (*pos)++;
            goto q42;

        } else if (*palavra == '\0') {
            goto q42;

        } else {
            return _ERRO_LEXICO_;
        }
}
