/*
    ANALISADOR LEXICO
 
    Caio Augusto     31782809
    Leandro Soares   31715125
    Lia Kassardjian  31750370
    Vitor Barbosa    31780881
    TURMA 6G
*/

#include <stdio.h>
#include <stdlib.h>

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

struct lista *l;

// ------------------------ IMPLEMENTACAO LISTA LIGADA
struct no {
    struct no *prox;
    char letra;
};

struct lista {
    struct no *ini;
    struct no *fim;
    int tam;
};

struct lista * initLista() {
    struct lista *l = malloc(sizeof(struct lista));
    l->ini = 0;
    l->fim = 0;
    l->tam = 0;
    return l;
};

void insereElemento(char c) {
    l->tam++;

    struct no *no = malloc(sizeof(struct no));
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

void printLista() {
    struct no *temp;
    for (temp = l->ini; temp != 0; temp = temp->prox) {
        printf("%c ", temp->letra);
    }
}

char * listaToString() {
    char *resultado = calloc(l->tam + 1, sizeof(char));
    resultado[l->tam] = '\0'; // Indica fim da string

    int i;
    struct no *no;
    for (no = l->ini, i = 0; no != 0 ; no = no->prox, i++) {
        resultado[i] = no->letra;
    }
    return resultado;
}

// ------------------------ FIM IMPLEMENTAÇÃO LISTA LIGADA

// ------------------------ IMPLEMENTAÇÃO LISTA LIGADA 2
struct listaConteudo * lc;

struct noConteudo {
    struct noConteudo *prox;
    char *c; // Nome da variável ou número
    int t;    // Token do lexema
};

struct listaConteudo {
    struct noConteudo *ini;
    struct noConteudo *fim;
};

struct listaConteudo * initListaConteudo() {
    struct listaConteudo *l = malloc(sizeof(struct listaConteudo));
    l->ini = 0;
    l->fim = 0;
    return l;
};

void insereElementoListaConteudo(int t, char *c) {
    struct noConteudo *no = malloc(sizeof(struct noConteudo));
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

void printListaConteudo() {
    struct noConteudo *temp;
    puts("LISTA CONTEUDO:");
    for (temp = lc->ini; temp != 0; temp = temp->prox) {
        printf("c = %s\n", temp->c);
        printf("t = %d\n", temp->t);
        puts("==========================");
    }
}

// ------------------------ FIM IMPLEMENTACAO LISTA LIGADA 2

// Lista para armazenar o identificador de variaveis, numeros, comentarios
void initScanner();
int scanner(char *);
void atualizaOutput(int);
void escreveArq();
char * traduzToken(int);

int cont = 0;

int main() {
    char *palavra = "void _proc ( int _a ) { int _a ; _a = 1 ; if ( _a < 1 ) { _a = 12 ; } } program _correto { int _a , _b , _c ; bool _d , _e , _f ; /* comentario */ _a = 2 ; _b = 10 ; _c = 11 ; _a = _b + _c ; _d = true ; _e = false ; _f = true ; print ( _b ) ; /* outro comentario */ if ( _d ) { _a = 20 ; _b = 10 * _c ; _c = _a / _b ; } do { if ( _b > 10 ) { _b = 2 ; _a = _a - 1 ; } else { _a = _a - 1 ; } } while ( _a > 1 ) ; }";
    
    // Contador que representa o caracter da string que deve ser analisado pela funcao scanner
    int token;
    initScanner();
    while(1) {
        token = scanner(palavra);
        if(token >= 0) {
            atualizaOutput(token);
            if (token == 0) break;
            
        } else {
            // token < 0 indica fim da string
            break;
        }
    }
    
    escreveArq();
    
    puts("Gerado arquivo de saida (output.txt).");
    
    return 0;
}


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

    struct noConteudo *no;
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

int scanner(char *p) {
    resetLista(); // Remove todos os elementos da lista

    char *palavra = &p[cont];

    // Verifica se a string ja chegou ao fim
    if (*palavra == '\0') {
        return -1;
    }

    // Remove espacos em branco desnecessarios
    while(*palavra == ' ') {
        palavra++; cont++;
        if (*palavra == '\0'){
            return -1;
        }
    }

    // Inicio Automato Finito Deterministico
	q0:
		switch(*palavra) {
		    case '<':
                palavra++; cont++;
                goto q1;
		    case '>':
                palavra++; cont++;
                goto q2;
            case '/':
                palavra++; cont++;
                goto q3;
            case '_':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q40;
		    case '{':
                palavra++; cont++;
                goto q16;
		    case '}':
                palavra++; cont++;
                goto q15;
		    case ';':
                palavra++; cont++;
                goto q14;
		    case ',':
                palavra++; cont++;
                goto q13;
		    case '(':
                palavra++; cont++;
                goto q11;
		    case ')':
                palavra++; cont++;
                goto q12;
		    case '+':
                palavra++; cont++;
                goto q6;
		    case '=':
                palavra++; cont++;
                goto q5;
		    case '-':
                palavra++; cont++;
                goto q4;
		    case '*':
                palavra++; cont++;
                goto q38;
		    case '1':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '2':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '3':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '4':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '5':
                insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '6':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '7':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '8':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '9':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '0':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
            case 'b':
                palavra++; cont++;
                goto q47;
		    case 'd':
                palavra++; cont++;
                goto q82;
			case 'e':
			    palavra++; cont++;
				goto q85;
		    case 'f':
                palavra++; cont++;
                goto q76;
			case 'i':
				palavra++; cont++;
                goto q43;
            case 'p':
                palavra++; cont++;
                goto q52;
            case 't':
                palavra++; cont++;
                goto q71;
		    case 'v':
                palavra++; cont++;
                goto q60;
			case 'w':
				palavra++; cont++;
                goto q90;
			default:
				puts("Erro no estado q0!");
				return _ERRO_LEXICO_;
		}

	q1:
		switch(*palavra){
		    case '=':
                palavra++; cont++;
                goto q7;
            case '>':
                palavra++; cont++;
                goto q8;
			case ' ':
                palavra++; cont++;
                goto q30;
            case '\0':
				goto q30;
			default:
				puts("Erro no estado q1!");
				return _ERRO_LEXICO_;
		}

	q2:
		switch(*palavra){
			case '=':
			    palavra++; cont++;
				goto q9;
			case ' ':
                palavra++; cont++;
                goto q19;
            case '\0':
				goto q19;
			default:
				puts("Erro no estado q2!");
				return _ERRO_LEXICO_;
		}

	q3:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
                goto q20;
            case '\0':
				goto q20;
            case '*':
                palavra++; cont++;
                goto q31;
			default:
				puts("Erro no estado q3!");
				return _ERRO_LEXICO_;
		}

	q4:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
                goto q21;
            case '\0':
				goto q21;
			default:
				puts("Erro no estado q4!");
				return _ERRO_LEXICO_;
		}

	q5:
		switch(*palavra){
			case '=':
				palavra++; cont++;
				goto q32;
			case ' ':
                palavra++; cont++;
				goto q22;
			case '\0':
				goto q22;
			default:
				puts("Erro no estado q5!");
				return _ERRO_LEXICO_;
		}

	q6:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q23;
			case '\0':
				goto q23;
			default:
				puts("Erro no estado q6!");
				return _ERRO_LEXICO_;
		}

	q7:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
                goto q10;
            case '\0':
				goto q10;
			default:
				puts("Erro no estado q7!");
				return _ERRO_LEXICO_;
		}

	q8:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q17;
			case '\0':
				goto q17;
			default:
				puts("Erro no estado q8!");
				return _ERRO_LEXICO_;
		}

	q9:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
                goto q18;
            case '\0':
				goto q18;
			default:
				puts("Erro no estado q9!");
				return _ERRO_LEXICO_;
		}

	q10:
        return _MENOR_IGUAL_;

	q11:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q24;
			case '\0':
				goto q24;
			default:
				puts("Erro no estado q11!");
				return _ERRO_LEXICO_;
		}

	q12:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q25;
			case '\0':
				goto q25;
			default:
				puts("Erro no estado q12!");
				return _ERRO_LEXICO_;
		}

	q13:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q26;
			case '\0':
				goto q26;
			default:
				puts("Erro no estado q13!");
				return _ERRO_LEXICO_;
		}

	q14:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q27;
			case '\0':
				goto q27;
			default:
				puts("Erro no estado q14!");
				return _ERRO_LEXICO_;
		}

	q15:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q28;
			case '\0':
				goto q28;
			default:
				puts("Erro no estado q15!");
				return _ERRO_LEXICO_;
		}

	q16:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q29;
			case '\0':
				goto q29;
			default:
				puts("Erro no estado q16!");
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
                puts("Erro no estado q31!");
                return _ERRO_LEXICO_;
            default:
                goto q34;
	    }

	q32:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q33;
			case '\0':
				goto q33;
			default:
				puts("Erro no estado q32!");
				return _ERRO_LEXICO_;
		}

	q33:
        return _IGUAL_IGUAL_;

	q34:
		switch(*palavra){
            case '\0':
                puts("Erro no estado q34!");
                return _ERRO_LEXICO_;
                
            // Verifica se é fim de comentário
            case '*':
                palavra++; cont++;
                goto q35;

            default:
                insereElemento(*palavra);
                palavra++; cont++;
                goto q34;

		}

	q35:
		switch(*palavra){
            case '\0':
                puts("Erro no estado q35!");
                return _ERRO_LEXICO_;
            
            case '/':
                palavra++; cont++;
                goto q36;
            
            case '*':
                palavra--;
                insereElemento(*palavra);
                palavra++; palavra++; cont++;
                goto q35;
            
            default:
                palavra--;
                insereElemento(*palavra);
                palavra++;
                insereElemento(*palavra);
                palavra++; cont++;
                goto q34;
		}

	q36:
		switch(*palavra){
            case ' ':
                palavra++; cont++;
                goto q37;
            case '\0':
                goto q37;
			default:
				puts("Erro no estado q36!");
				return _ERRO_LEXICO_;
		}

	q37:
        return _COMENTARIO_;

	q38:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q39;
			case '\0':
				goto q39;
			default:
				puts("Erro no estado q38!");
				return _ERRO_LEXICO_;
		}

	q39:
        return _SINAL_MULTIPLICACAO_;

	q40:
        if (((*palavra >= 65) && (*palavra <= 90)) || ((*palavra >= 97) && (*palavra <= 122))) {
            insereElemento(*palavra);
            palavra++; cont++;
            goto q97;
            
        } else {
            return _ERRO_LEXICO_;
        }
    
	q41:
		switch(*palavra){
		    case '1':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '2':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '3':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '4':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '5':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '6':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '7':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '8':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '9':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
		    case '0':
		        insereElemento(*palavra);
                palavra++; cont++;
                goto q41;
			case ' ':
                palavra++; cont++;
				goto q96;
			case '\0':
				goto q96;
			default:
				puts("Erro no estado q41!");
				return _ERRO_LEXICO_;
		}

	q42:
        return _IDENTIFICADOR_;

	q43:
		switch(*palavra){
            case 'f':
                palavra++; cont++;
                goto q69;
			case 'n':
				palavra++; cont++;
                goto q44;
			default:
				puts("Erro no estado q43!");
				return _ERRO_LEXICO_;
		}

	q44:
		switch(*palavra){
			case 't':
				palavra++; cont++;
				goto q45;
			default:
				puts("Erro no estado q44!");
				return _ERRO_LEXICO_;
		}

	q45:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q46;
			case '\0':
				goto q46;
			default:
				puts("Erro no estado q45!");
				return _ERRO_LEXICO_;
		}

	q46:
        return _INT_;

	q47:
		switch(*palavra){
            case 'o':
                palavra++; cont++;
                goto q48;
			default:
				puts("Erro no estado q47!");
				return _ERRO_LEXICO_;
		}

	q48:
		switch(*palavra){
            case 'o':
                palavra++; cont++;
                goto q49;
			default:
				puts("Erro no estado q48!");
				return _ERRO_LEXICO_;
		}

	q49:
		switch(*palavra){
            case 'l':
                palavra++; cont++;
                goto q50;
			default:
				puts("Erro no estado q49!");
				return _ERRO_LEXICO_;
		}

	q50:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q51;
			case '\0':
				goto q51;
			default:
				puts("Erro no estado q50!");
				return _ERRO_LEXICO_;
		}

	q51:
        return _BOOL_;

	q52:
		switch(*palavra){
            case 'r':
                palavra++; cont++;
                goto q53;
			default:
				puts("Erro no estado q52!");
				return _ERRO_LEXICO_;
		}

	q53:
		switch(*palavra){
            case 'o':
                palavra++; cont++;
                goto q54;
            case 'i':
                palavra++; cont++;
                goto q65;
			default:
				puts("Erro no estado q53!");
				return _ERRO_LEXICO_;
		}

	q54:
		switch(*palavra){
            case 'g':
                palavra++; cont++;
                goto q55;
			default:
				puts("Erro no estado q54!");
				return _ERRO_LEXICO_;
		}

	q55:
		switch(*palavra){
            case 'r':
                palavra++; cont++;
                goto q56;
			default:
				puts("Erro no estado q55!");
				return _ERRO_LEXICO_;
		}

	q56:
		switch(*palavra){
            case 'a':
                palavra++; cont++;
                goto q57;
			default:
				puts("Erro no estado q56!");
				return _ERRO_LEXICO_;
		}

	q57:
		switch(*palavra){
            case 'm':
                palavra++; cont++;
                goto q58;
			default:
				puts("Erro no estado q57!");
				return _ERRO_LEXICO_;
		}

	q58:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q59;
			case '\0':
				goto q59;
			default:
				puts("Erro no estado q58!");
				return _ERRO_LEXICO_;
		}

	q59:
        return _PROGRAM_;

	q60:
		switch(*palavra){
		    case 'o':
                palavra++; cont++;
                goto q61;
			default:
				puts("Erro no estado q60!");
				return _ERRO_LEXICO_;
		}

	q61:
		switch(*palavra){
		    case 'i':
                palavra++; cont++;
                goto q62;
			default:
				puts("Erro no estado q61!");
				return _ERRO_LEXICO_;
		}

	q62:
		switch(*palavra){
		    case 'd':
                palavra++; cont++;
                goto q63;
            default:
				puts("Erro no estado q62!");
				return _ERRO_LEXICO_;
		}

	q63:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q64;
			case '\0':
				goto q64;
			default:
				puts("Erro no estado q63!");
				return _ERRO_LEXICO_;
		}

	q64:
        return _VOID_;

	q65:
		switch(*palavra){
            case 'n':
                palavra++; cont++;
                goto q66;
			default:
				puts("Erro no estado q65!");
				return _ERRO_LEXICO_;
		}

	q66:
		switch(*palavra){
            case 't':
                palavra++; cont++;
                goto q67;
			default:
				puts("Erro no estado q66!");
				return _ERRO_LEXICO_;
		}

	q67:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q68;
			case '\0':
				goto q68;
			default:
				puts("Erro no estado q67!");
				return _ERRO_LEXICO_;
		}

	q68:
        return _PRINT_;
    
	q69:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q70;
			case '\0':
				goto q70;
			default:
				puts("Erro no estado q69!");
				return _ERRO_LEXICO_;
		}

	q70:
        return _IF_;

	q71:
		switch(*palavra){
            case 'r':
                palavra++; cont++;
                goto q72;
			default:
				puts("Erro no estado q71!");
				return _ERRO_LEXICO_;
		}

	q72:
		switch(*palavra){
            case 'u':
                palavra++; cont++;
                goto q73;
			default:
				puts("Erro no estado q72!");
				return _ERRO_LEXICO_;
		}

	q73:
		switch(*palavra){
            case 'e':
                palavra++; cont++;
                goto q74;
			default:
				puts("Erro no estado q73!");
				return _ERRO_LEXICO_;
		}

	q74:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q75;
			case '\0':
				goto q75;
			default:
				puts("Erro no estado q74!");
				return _ERRO_LEXICO_;
		}

	q75:
        return _TRUE_;

	q76:
		switch(*palavra){
		    case 'a':
                palavra++; cont++;
                goto q77;
			default:
				puts("Erro no estado q76!");
				return _ERRO_LEXICO_;
		}

	q77:
		switch(*palavra){
		    case 'l':
                palavra++; cont++;
                goto q78;
			default:
				puts("Erro no estado q77!");
				return _ERRO_LEXICO_;
		}

	q78:
		switch(*palavra){
		    case 's':
                palavra++; cont++;
                goto q79;
			default:
				puts("Erro no estado q78!");
				return _ERRO_LEXICO_;
		}

	q79:
		switch(*palavra){
		    case 'e':
                palavra++; cont++;
                goto q80;
			default:
				puts("Erro no estado q79!");
				return _ERRO_LEXICO_;
		}

	q80:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q81;
			case '\0':
				goto q81;
			default:
				puts("Erro no estado q80!");
				return _ERRO_LEXICO_;
		}

	q81:
        return _FALSE_;
    
	q82:
		switch(*palavra){
		    case 'o':
                palavra++; cont++;
                goto q83;
			default:
				puts("Erro no estado q82!");
				return _ERRO_LEXICO_;
		}

	q83:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q84;
			case '\0':
				goto q84;
			default:
				puts("Erro no estado q83!");
				return _ERRO_LEXICO_;
		}

	q84:
        return _DO_;
    
	q85:
		switch(*palavra){
			case 'l':
			    palavra++; cont++;
				goto q86;
			default:
				puts("Erro no estado q85!");
				return _ERRO_LEXICO_;
		}

	q86:
		switch(*palavra){
			case 's':
			    palavra++; cont++;
				goto q87;
			default:
				puts("Erro no estado q86!");
				return _ERRO_LEXICO_;
		}

	q87:
		switch(*palavra){
			case 'e':
			    palavra++; cont++;
				goto q88;
			default:
				puts("Erro no estado q87!");
				return _ERRO_LEXICO_;
		}

	q88:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q89;
			case '\0':
				goto q89;
			default:
				puts("Erro no estado q88!");
				return _ERRO_LEXICO_;
		}

	q89:
        return _ELSE_;
    
	q90:
		switch(*palavra){
			case 'h':
				palavra++; cont++;
                goto q91;
			default:
				puts("Erro no estado q90!");
				return _ERRO_LEXICO_;
		}

	q91:
		switch(*palavra){
			case 'i':
				palavra++; cont++;
                goto q92;
			default:
				puts("Erro no estado q91!");
				return _ERRO_LEXICO_;
		}

	q92:
		switch(*palavra){
			case 'l':
				palavra++; cont++;
                goto q93;
			default:
				puts("Erro no estado q92!");
				return _ERRO_LEXICO_;
		}

	q93:
		switch(*palavra){
			case 'e':
				palavra++; cont++;
                goto q94;
			default:
				puts("Erro no estado q93!");
				return _ERRO_LEXICO_;
		}

	q94:
		switch(*palavra){
			case ' ':
                palavra++; cont++;
				goto q95;
			case '\0':
				goto q95;
			default:
				puts("Erro no estado q94!");
				return _ERRO_LEXICO_;
		}

	q95:
        return _WHILE_;

	q96:
        return _NUM_;
    
    q97:
        if (((*palavra >= 65) && (*palavra <= 90)) || ((*palavra >= 97) && (*palavra <= 122))) {
            insereElemento(*palavra);
            palavra++; cont++;
            goto q97;
            
        } else if (*palavra == ' ') {
            palavra++; cont++;
            goto q42;
            
        } else if (*palavra == '\0') {
            goto q42;
            
        } else {
            return _ERRO_LEXICO_;
        }
}

