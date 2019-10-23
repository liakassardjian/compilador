
/*
 
 + _var * ( - 12 )
 
 Implementacao do Analisador Sintatico Descendente Recursivo para a gramatica:

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

 5. ListaDeIdentificadores -> Identificador ListaIdOpcional
    ListaIdOpcional -> , Identificador
    ListaIdOpcional -> &

 6. DeclaracoesFuncoes -> DeclaraFuncao DeclaracoesFuncoes
    DeclaracoesFuncoes -> &

 7. DeclaraFuncao -> void Identificador ( ParametroFormalOpcional ) Bloco
    ParametroFormalOpcional -> ParametroFormal
    ParametroFormalOpcional -> &

 8. ParametroFormal -> int Identificador
    ParametroFormal -> bool Identificador

 9. ComandoComposto -> Comando ; ComandoCompostoOpcional
    ComandoCompostoOpcional -> Comando ;
    ComandoCompostoOpcional -> &

 10. Comando -> Atribuicao
     Comando -> ChamadaDeProcedimento
     Comando -> ComandoCondicional
     Comando -> ComandoRepetitivo
     Comando -> print Identificador

 11. Atribuicao -> Variavel = Expressao

 12. ChamadaDeProcedimento -> Identificador ( ParametroOpcional )
     ParametroOpcional -> Parametro
     ParametroOpcional -> &

 13. Parametro -> Identificador
     Parametro -> Numero
     Parametro -> Bool
     Parametro -> &

 14. ComandoCondicional -> if ( Expressao ) { ComandoComposto } ElseOpcional
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


/// ============================== TOKENS

#define _ERRO_LEXICO_         0
#define _MENOR_IGUAL_         1   // <=
#define _DIFERENTE_           2   // <>
#define _MENOR_               3   // <
#define _DIVISAO_             4   // /
#define _COMENTARIO_          5   // /*...*/
#define _IDENTIFICADOR_       6   // _identificador
#define _IF_                  7   // if
#define _INT_                 8   // int
#define _BOOL_                9   // bool
#define _PROGRAM_             10  // program
#define _PRINT_               11  // print
#define _VOID_                12  // void
#define _TRUE_                13  // true
#define _FALSE_               14  // false
#define _DO_                  15  // do
#define _ELSE_                16  // else
#define _WHILE_               17  // while
#define _ABRE_CHAVES_         18  // {
#define _FECHA_CHAVES_        19  // }
#define _PONTO_VIRGULA_       20 // ;
#define _VIRGULA_             21 // ,
#define _ABRE_PARENTESES_     22 // (
#define _FECHA_PARENTESES_    23 // )
#define _SINAL_MAIS_          24 // +
#define _SINAL_IGUAL_         25 // =
#define _IGUAL_IGUAL_         26 // ==
#define _MAIOR_               27 // >
#define _MAIOR_IGUAL_         28 // >=
#define _SINAL_MENOS_         29 // -
#define _SINAL_MULTIPLICACAO_ 30 // *
#define _NUM_                 31 // 0123456789


/// ============================== DECLARACAO DAS FUNCOES RECURSIVAS DOS SIMBOLOS NAO TERMINAIS

int Programa(char palavra[], int *pos);
int DecFuncoesRep(char palavra[], int *pos);
int Bloco(char palavra[], int *pos);
int DecVariaveisOpcional(char palavra[], int *pos);
int ParteDeclaracoesDeVariaveis(char palavra[], int *pos);
int DecVariaveis(char palavra[], int *pos);
int ListaDeIdentificadores(char palavra[], int *pos);
int ListaIdOpcional(char palavra[], int *pos);
int DeclaracoesFuncoes(char palavra[], int *pos);
int DeclaraFuncao(char palavra[], int *pos);
int ParametroFormalOpcional(char palavra[], int *pos);
int ParametroFormal(char palavra[], int *pos);
int ComandoComposto(char palavra[], int *pos);
int ComandoCompostoOpcional(char palavra[], int *pos);
int Comando(char palavra[], int *pos);
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
int Identificador(char palavra[], int *pos);


/// ============================== DECLARACAO DOS METODOS E VARIAVEIS RELATIVOS AO FUNCIONAMENTO DO ASDR

char lookahead;
int token;
int match(char c, char palavra[], int *pos);
void erro(int *pos);
int erroLexico = 0;


/// ============================== DECLARACAO DA TAD LISTA LIGADA USADA PELO ANALISADOR LEXICO

typedef struct TNo TNo;
typedef struct TLista TLista;
TLista * initLista();
void insereElemento(char c);
void resetLista();
void freeLista();
char * listaToString();

TLista *l;


/// ============================== DECLARACAO DA TAD LISTA LIGADA USADA PELO ANALISADOR LEXICO PARA ARMAZENAR O CONTEUDO

typedef struct TNoConteudo TNoConteudo;
typedef struct TListaConteudo TListaConteudo;
TListaConteudo * initListaConteudo();
void insereElementoListaConteudo(int t, char *c);
void freeListaConteudo();

TListaConteudo *lc;


/// ============================== DECLARACAO DOS METODOS RELATIVOS AO SCANNER DO ANALISADOR LEXICO

void initScanner();
int scanner(char *p, int *pos);
void atualizaOutput(int t);
void escreveArq();
char * traduzToken(int t);


/// ============================== FUNCAO MAIN

int main(){
//  A PALAVRA A SEGUIR EH UMA TRANSCRICAO DE UM PROGRAMA DENTRO DE UMA UNICA STRING PARA TESTE DO SISTEMA COMO UM TODO
//    char *palavra = "void _proc ( int _a ) { int _a ; _a = 1 ; if ( _a < 1 ) { _a = 12 ; } } program _correto { int _a , _b , _c ; bool _d , _e , _f ; /* comentario */ _a = 2 ; _b = 10 ; _c = 11 ; _a = _b + _c ; _d = true ; _e = false ; _f = true ; print ( _b ) ; /* outro comentario */ if ( _d ) { _a = 20 ; _b = 10 * _c ; _c = _a / _b ; } do { if ( _b > 10 ) { _b = 2 ; _a = _a - 1 ; } else { _a = _a - 1 ; } } while ( _a > 1 ) ; } $";


    char *palavra = "+ _var * ( - 12 ) < ( _abcd / ( - 24 ) ) ;";

    // Contador que representa o caracter da string que deve ser analisado pela funcao scanner
    int pos = 0;

    // Inicializacao do scanner
    initScanner();

    // Inicializa lookahead com o primeiro caracter
    lookahead = palavra[pos];

    // Inicializa token com a primeira chamada do scanner
    token = scanner(palavra, &pos);

    // Comeca a interpretacao sintatica pelo nao-terminal Programa
    if (token != 0) {
        if (Expressao(palavra, &pos))
            printf("\nSUCESSO NA LEITURA\n");
        else
            erro(&pos);
    } else {
        erroLexico = 1;
        erro(&pos);
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
    // Verifica se o lookahed eh igual ao caracter recebido
    if (lookahead == c) {

        // Atualiza o lookahed com o proximo caracter
        lookahead = palavra[*pos];

        // Atualiza o token com o resultado da chamada de scanner,
        // que ja atualiza pos para o primeiro caracter da proxima palavra
        token = scanner(palavra, pos);

        // Verifica que o token retornou erro lexico.
        if (!token) {
            // A variavel global de erro lexico eh atualizada para possibilitar
            // tratamento mais efetivo de erros. Retorna 0 nesse caso.
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
void erro(int *pos) {
    if (erroLexico)
        printf("\nERRO LEXICO\n");
    else
        printf("\nERRO DE SINTAXE\n");

    printf("POSICAO #%d: %c\n", *pos, lookahead);
}


/// ============================== IMPLEMENTACAO DAS FUNCOES RECURSIVAS DOS SIMBOLOS NAO TERMINAIS

/*
 1. Programa -> DecFuncoesRep program Identificador Bloco
    DecFuncoesRep -> DeclaracoesFuncoes DecFuncoesRep
    DecFuncoesRep -> &
*/
int Programa(char palavra[], int *pos) {
    printf("Programa\n");
    // O primeiro "first" possivel para Programa eh v,
    // entao a verificacao do lookahead comeca por essa letra
    if (lookahead == 'v') {
        if (DecFuncoesRep(palavra, pos) &&
            match('v', palavra, pos)    &&
            Identificador(palavra, pos) &&
            Bloco(palavra, pos))
            return 1;

    // A segunda possibilidade de "first" para Programa eh p,
    // entao verifica-se o lookahead para essa letra
    } else if (lookahead == 'p') {
        if (match('p', palavra, pos)    &&
            Identificador(palavra, pos) &&
            Bloco(palavra, pos))
            return 1;

    }
    return 0;
}

int DecFuncoesRep(char palavra[], int *pos) {
    printf("DecFuncoesRep\n");
//    if (DeclaracoesFuncoes(palavra, pos) &&
//        DecFuncoesRep(palavra, pos))
//        return 1;
    return 1;
}


/*
 2. Bloco -> { DecVariaveisOpcional ComandoComposto }
    DecVariaveisOpcional -> ParteDeclaracoesDeVariaveis
    DecVariaveisOpcional -> &
*/
int Bloco(char palavra[], int *pos) {
    printf("Bloco\n");
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
    return 1;
}


/*
 3. ParteDeclaracoesDeVariaveis -> DecVariaveis ParteDeclaracoesDeVariaveis
    ParteDeclaracoesDeVariaveis -> &
*/
int ParteDeclaracoesDeVariaveis(char palavra[], int *pos);


/*
 4. DecVariaveis -> int ListaDeIdentificadores ;
    DecVariaveis -> bool ListaDeIdentificadores ;
*/
int DecVariaveis(char palavra[], int *pos);


/*
 5. ListaDeIdentificadores -> Identificador ListaIdOpcional
    ListaIdOpcional -> , Identificador
    ListaIdOpcional -> &
*/
int ListaDeIdentificadores(char palavra[], int *pos);
int ListaIdOpcional(char palavra[], int *pos);


/*
 6. DeclaracoesFuncoes -> DeclaraFuncao DeclaracoesFuncoes
    DeclaracoesFuncoes -> &
*/
int DeclaracoesFuncoes(char palavra[], int *pos) {
    printf("Declaracoes Funcoes\n");
    return 1;
}


/*
 7. DeclaraFuncao -> void Identificador ( ParametroFormalOpcional ) Bloco
    ParametroFormalOpcional -> ParametroFormal
    ParametroFormalOpcional -> &
*/
int DeclaraFuncao(char palavra[], int *pos) {
    if (lookahead == 'v') {
        if (match('v', palavra, pos)    &&
            Identificador(palavra, pos) &&
            match('(', palavra, pos)    &&
            ParametroFormalOpcional     &&
            match(')', palavra, pos)    &&
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
        
    } else if (lookahed == ')') {
        return 1;
        
    }
    return 0;
}


/*
 8. ParametroFormal -> int Identificador
    ParametroFormal -> bool Identificador
*/
int ParametroFormal(char palavra[], int *pos) {
    printf("ParametroFormal\n");
    if (lookahead == 'i') {
        if (match('i', palavra, pos) &&
            Identificador(palavra, pos))
            return 1;
        
    } else if (lookahead == 'b') {
        if (match('b', palavra, pos) &&
            Identificador(palavra, pos))
            return 1;
        
    }
    return 0;
}


/*
 9. ComandoComposto -> Comando ; ComandoCompostoOpcional
    ComandoCompostoOpcional -> Comando ;
    ComandoCompostoOpcional -> &
*/
int ComandoComposto(char palavra[], int *pos) {
    return 1;
}
int ComandoCompostoOpcional(char palavra[], int *pos);


/*
 10. Comando -> Atribuicao
     Comando -> ChamadaDeProcedimento
     Comando -> ComandoCondicional
     Comando -> ComandoRepetitivo
     Comando -> print Identificador
*/
int Comando(char palavra[], int *pos) {
//    if (lookahead == '_') {
//
//    }
}


/*
 11. Atribuicao -> Variavel = Expressao
*/
int Atribuicao(char palavra[], int *pos) {
    printf("Atribuicao\n");
    if (lookahead == '_') {
        if (Variavel(palavra, pos)      &&
            token = _SINAL_IGUAL_       &&
            match('=', palavra, pos)    &&
            Expressao(palavra, pos))
            return 1;
    }
    return 0;
}


/*
 12. ChamadaDeProcedimento -> Identificador ( ParametroOpcional )
     ParametroOpcional -> Parametro
     ParametroOpcional -> &
*/
int ChamadaDeProcedimento(char palavra[], int *pos) {
    printf("ChamadaDeProcedimento\n");
    if (lookahead == '_') {
        if (Identificador(palavra, pos)     &&
            match('(', palavra, pos)        &&
            ParametroOpcional(palavra, pos) &&
            match(')', palavra, pos))
            return 1;
            
    }
    return 0;
}

int ParametroOpcional(char palavra[], int *pos) {
    printf("ParametroOpcional\n");
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
    printf("Parametro\n");
    if (lookahead == '_') {
        if (Identificador(palavra, pos))
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
int ComandoCondicional(char palavra[], int *pos);
int ElseOpcional(char palavra[], int *pos);


/*
 15. ComandoRepetitivo -> do { ComandoComposto } while ( Expressao )
*/
int ComandoRepetitivo(char palavra[], int *pos);


/*
 16. Expressao -> ExpressaoSimples ExpressaoOpcional
     ExpresaoOpcional -> Relacao ExpressaoSimples
*/
int Expressao(char palavra[], int *pos) {
    printf("Expressao\n");
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
    printf("ExpressaoOpcional\n");
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
    printf("Relacao\n");
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
    printf("Expressao Simples\n");
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
    printf("SinalOpcional\n");
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
    printf("Expressao Simples Rep\n");
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
    printf("Termo\n");
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
    printf("FatorRep\n");
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
              lookahead == ';') {
        return 1;
    }
    return 0;
}

int Operacao(char palavra[], int *pos) {
    printf("Operacao\n");
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
    printf("Fator\n");
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
    printf("Variavel\n");
    if (lookahead == '_') {
        if (Identificador(palavra,pos))
            return 1;
    }
    return 0;
}


/*
 22. Bool -> true
     Bool -> false
*/
int Bool(char palavra[], int *pos) {
    printf("Bool\n");
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
int Numero(char palavra[], int *pos){
    printf("Numero\n");
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

    printf("erro\n");
    return 0;
}


/*
 24. Identificador -> id
*/
int Identificador(char palavra[], int *pos) {
    printf("Identificador\n");
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


/// ============================== IMPLEMENTACAO DA TAD LISTA LIGADA USADA PELO ANALISADOR LEXICO PARA ARMAZENAR O CONTEUDO

struct TNoConteudo {
    struct TNoConteudo *prox;
    char *c; // Nome da variável ou número
    int t;    // Token do lexema
};

struct TListaConteudo {
    TNoConteudo *ini;
    TNoConteudo *fim;
};

TListaConteudo * initListaConteudo() {
    TListaConteudo *l = malloc(sizeof(TListaConteudo));
    l->ini = 0;
    l->fim = 0;
    return l;
};

void insereElementoListaConteudo(int t, char *c) {
    TNoConteudo *no = malloc(sizeof(TNoConteudo));
    no->c = c;
    no->t = t;
    no->prox = 0;

    // Insersao na lista vazia
    if(lc->ini == 0) {
        lc->ini = no;
        lc->fim = no;
    }
    // Lista com um ou mais elementos
    else {
        lc->fim->prox = no;
        lc->fim = no;
    }
};

void freeListaConteudo() {
    free(lc);
}


/// ============================== IMPLEMENTACAO DOS METODOS RELATIVOS AO SCANNER DO ANALISADOR LEXICO

void atualizaOutput(int t) {
    char *texto = traduzToken(t);

    if ((t == _NUM_) || (t == _IDENTIFICADOR_) || (t == _COMENTARIO_)) {
        char *conteudo = listaToString();
        insereElementoListaConteudo(t, conteudo);
    }
    else {
        insereElementoListaConteudo(t, 0);
    }
}

void initScanner() {
    l = initLista();
    lc = initListaConteudo();
}

char * traduzToken(int t) {
    switch(t) {
        case _ERRO_LEXICO_:
            return "ERRO_LEXICO";
        case _MENOR_IGUAL_:
            return "MENOR_IGUAL";
        case _DIFERENTE_:
            return "DIFERENTE";
        case _MENOR_:
            return "MENOR";
        case _DIVISAO_:
            return "DIVISAO";
        case _COMENTARIO_:
            return "COMENTARIO";
        case _IDENTIFICADOR_:
            return "IDENTIFICADOR";
        case _IF_:
            return "IF";
        case _INT_:
            return "INT";
        case _BOOL_:
            return "BOOL";
        case _PROGRAM_:
            return "PROGRAM";
        case _PRINT_:
            return "PRINT";
        case _VOID_:
            return "VOID";
        case _TRUE_:
            return "TRUE";
        case _FALSE_:
            return "FALSE";
        case _DO_:
            return "DO";
        case _ELSE_:
            return "ELSE";
        case _WHILE_:
            return "WHILE";
        case _ABRE_CHAVES_:
            return "ABRE_CHAVES";
        case _FECHA_CHAVES_:
            return "FECHA_CHAVES";
        case _PONTO_VIRGULA_:
            return "PONTO_VIRGULA";
        case _VIRGULA_:
            return "VIRGULA";
        case _ABRE_PARENTESES_:
            return "ABRE_PARENTESES";
        case _FECHA_PARENTESES_:
            return "FECHA_PARENTESES";
        case _SINAL_MAIS_:
            return "SINAL_MAIS";
        case _SINAL_IGUAL_:
            return "SINAL_IGUAL";
        case _IGUAL_IGUAL_:
            return "IGUAL_IGUAL";
        case _MAIOR_:
            return "MAIOR";
        case _MAIOR_IGUAL_:
            return "MAIOR_IGUAL";
        case _SINAL_MENOS_:
            return "SINAL_MENOS";
        case _SINAL_MULTIPLICACAO_:
            return "SINAL_MULTIPLICACAO";
        case _NUM_:
            return "NUM";
        default:
            return "";
    }
}

void escreveArq() {
    FILE *arq = fopen("output.txt", "w");

    TNoConteudo *no;
    for (no = lc->ini; no != 0; no = no->prox) {
        if(no->c == 0) {
            fprintf(arq, "<%s>\n", traduzToken(no->t));
        }
        else {
            fprintf(arq, "<%s, %s>\n", traduzToken(no->t), no->c);
        }
    }

    fclose(arq);
}

int scanner(char *p, int *pos) {
    resetLista(); // Remove todos os elementos da lista

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
        switch(*palavra) {
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
                insereElemento(*palavra);
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
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '2':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '3':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '4':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '5':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '6':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '7':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '8':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '9':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '0':
                insereElemento(*palavra);
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
        return _MENOR_IGUAL_;

    q11:
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
        return _DIFERENTE_;

    q18:
        return _MAIOR_IGUAL_;

    q19:
        return _MAIOR_;

    q20:
        return _DIVISAO_;

    q21:
        return _SINAL_MENOS_;

    q22:
        return _SINAL_IGUAL_;

    q23:
        return _SINAL_MAIS_;

    q24:
        return _ABRE_PARENTESES_;

    q25:
        return _FECHA_PARENTESES_;

    q26:
        return _VIRGULA_;

    q27:
        return _PONTO_VIRGULA_;

    q28:
        return _FECHA_CHAVES_;

    q29:
        return _ABRE_CHAVES_;

    q30:
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
        return _IGUAL_IGUAL_;

    q34:
        switch(*palavra){
            case '\0':
                return _ERRO_LEXICO_;

            // Verifica se é fim de comentário
            case '*':
                palavra++; (*pos)++;
                goto q35;

            default:
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q34;

        }

    q35:
        switch(*palavra){
            case '\0':
                return _ERRO_LEXICO_;

            case '/':
                palavra++; (*pos)++;
                goto q36;

            case '*':
                palavra--;
                insereElemento(*palavra);
                palavra++; palavra++; (*pos)++;
                goto q35;

            default:
                palavra--;
                insereElemento(*palavra);
                palavra++;
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q34;
        }

    q36:
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
        return _COMENTARIO_;

    q38:
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
        switch(*palavra){
            case '1':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '2':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '3':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '4':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '5':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '6':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '7':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '8':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '9':
                insereElemento(*palavra);
                palavra++; (*pos)++;
                goto q41;
            case '0':
                insereElemento(*palavra);
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
        return _IDENTIFICADOR_;

    q43:
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
        switch(*palavra){
            case 't':
                palavra++; (*pos)++;
                goto q45;
            default:
                return _ERRO_LEXICO_;
        }

    q45:
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
        return _INT_;

    q47:
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q48;
            default:
                return _ERRO_LEXICO_;
        }

    q48:
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q49;
            default:
                return _ERRO_LEXICO_;
        }

    q49:
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q50;
            default:
                return _ERRO_LEXICO_;
        }

    q50:
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
        return _BOOL_;

    q52:
        switch(*palavra){
            case 'r':
                palavra++; (*pos)++;
                goto q53;
            default:
                return _ERRO_LEXICO_;
        }

    q53:
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
        switch(*palavra){
            case 'g':
                palavra++; (*pos)++;
                goto q55;
            default:
                return _ERRO_LEXICO_;
        }

    q55:
        switch(*palavra){
            case 'r':
                palavra++; (*pos)++;
                goto q56;
            default:
                return _ERRO_LEXICO_;
        }

    q56:
        switch(*palavra){
            case 'a':
                palavra++; (*pos)++;
                goto q57;
            default:
                return _ERRO_LEXICO_;
        }

    q57:
        switch(*palavra){
            case 'm':
                palavra++; (*pos)++;
                goto q58;
            default:
                return _ERRO_LEXICO_;
        }

    q58:
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
        return _PROGRAM_;

    q60:
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q61;
            default:
                return _ERRO_LEXICO_;
        }

    q61:
        switch(*palavra){
            case 'i':
                palavra++; (*pos)++;
                goto q62;
            default:
                return _ERRO_LEXICO_;
        }

    q62:
        switch(*palavra){
            case 'd':
                palavra++; (*pos)++;
                goto q63;
            default:
                return _ERRO_LEXICO_;
        }

    q63:
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
        return _VOID_;

    q65:
        switch(*palavra){
            case 'n':
                palavra++; (*pos)++;
                goto q66;
            default:
                return _ERRO_LEXICO_;
        }

    q66:
        switch(*palavra){
            case 't':
                palavra++; (*pos)++;
                goto q67;
            default:
                return _ERRO_LEXICO_;
        }

    q67:
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
        return _PRINT_;

    q69:
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
        return _IF_;

    q71:
        switch(*palavra){
            case 'r':
                palavra++; (*pos)++;
                goto q72;
            default:
                return _ERRO_LEXICO_;
        }

    q72:
        switch(*palavra){
            case 'u':
                palavra++; (*pos)++;
                goto q73;
            default:
                return _ERRO_LEXICO_;
        }

    q73:
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q74;
            default:
                return _ERRO_LEXICO_;
        }

    q74:
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
        return _TRUE_;

    q76:
        switch(*palavra){
            case 'a':
                palavra++; (*pos)++;
                goto q77;
            default:
                return _ERRO_LEXICO_;
        }

    q77:
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q78;
            default:
                return _ERRO_LEXICO_;
        }

    q78:
        switch(*palavra){
            case 's':
                palavra++; (*pos)++;
                goto q79;
            default:
                return _ERRO_LEXICO_;
        }

    q79:
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q80;
            default:
                return _ERRO_LEXICO_;
        }

    q80:
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
        return _FALSE_;

    q82:
        switch(*palavra){
            case 'o':
                palavra++; (*pos)++;
                goto q83;
            default:
                return _ERRO_LEXICO_;
        }

    q83:
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
        return _DO_;

    q85:
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q86;
            default:
                return _ERRO_LEXICO_;
        }

    q86:
        switch(*palavra){
            case 's':
                palavra++; (*pos)++;
                goto q87;
            default:
                return _ERRO_LEXICO_;
        }

    q87:
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q88;
            default:
                return _ERRO_LEXICO_;
        }

    q88:
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
        return _ELSE_;

    q90:
        switch(*palavra){
            case 'h':
                palavra++; (*pos)++;
                goto q91;
            default:
                return _ERRO_LEXICO_;
        }

    q91:
        switch(*palavra){
            case 'i':
                palavra++; (*pos)++;
                goto q92;
            default:
                return _ERRO_LEXICO_;
        }

    q92:
        switch(*palavra){
            case 'l':
                palavra++; (*pos)++;
                goto q93;
            default:
                return _ERRO_LEXICO_;
        }

    q93:
        switch(*palavra){
            case 'e':
                palavra++; (*pos)++;
                goto q94;
            default:
                return _ERRO_LEXICO_;
        }

    q94:
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
        return _WHILE_;

    q96:
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

