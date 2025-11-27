/* produccion.y - Analizador Sintáctico para el Lenguaje de Producción */
/* FashionFlow Compiler - Nancy's Collection */
/* Módulo: Producción */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern void yyerror(const char *s);
extern int linea;
extern int columna;
extern FILE *yyin;

/* Contador de instrucciones procesadas */
int contador_ordenes = 0;

%}

/* Definición de tipos para valores semánticos */
%union {
    int entero;
    double decimal;
    char *cadena;
}

/* Tokens terminales */
%token KW_ORDEN
%token KW_DISENO KW_TALLAS KW_COLORES KW_CANTIDADES
%token OP_DOS_PUNTOS
%token LBRACE RBRACE LBRACKET RBRACKET COMMA

/* Tokens con valores */
%token <entero> NUM_ENTERO
%token <decimal> NUM_DECIMAL
%token <cadena> ID

/* Precedencia (no necesaria en esta versión básica) */

%%

/* Simbolo inicial: Programa */
programa:
    lista_instrucciones
    { 
        printf("\n=== ANALISIS COMPLETADO ===\n");
        printf("Total de ordenes procesadas: %d\n", contador_ordenes);
        if (contador_ordenes == 0) {
            fprintf(stderr, "\nERROR: No se encontraron ordenes de produccion en el archivo\n");
            exit(1);
        }
    }
    ;

lista_instrucciones:
    instruccion
    | lista_instrucciones instruccion
    ;

instruccion:
    declaracion_orden
    ;

/* Regla: ORDEN <id> { DISEÑO: <id> TALLAS: [...] COLORES: [...] CANTIDADES: [...] } */
declaracion_orden:
    KW_ORDEN ID LBRACE
        KW_DISENO OP_DOS_PUNTOS ID
        KW_TALLAS OP_DOS_PUNTOS lista_valores
        KW_COLORES OP_DOS_PUNTOS lista_valores
        KW_CANTIDADES OP_DOS_PUNTOS lista_valores
    RBRACE
    {
        contador_ordenes++;
        printf("[OK] Orden '%s' declarada correctamente (Diseno: %s)\n", $2, $6);
        free($2);
        free($6);
    }
    ;

/* Regla: [ valor, valor, ... ] */
lista_valores:
    LBRACKET valores RBRACKET
    ;

valores:
    valor
    | valores COMMA valor
    ;

valor:
    ID          { free($1); }
    | NUM_ENTERO
    | NUM_DECIMAL
    ;

%%

/* Función principal */
int main(int argc, char **argv) {
    printf("=== FashionFlow Compiler - Módulo de Producción ===\n");
    printf("=== Analizador Léxico y Sintáctico (v1.0) ===\n\n");

    if (argc > 1) {
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo) {
            fprintf(stderr, "Error: No se pudo abrir el archivo '%s'\n", argv[1]);
            return 1;
        }
        yyin = archivo;
        printf("Procesando archivo: %s\n\n", argv[1]);
    } else {
        printf("Modo interactivo (Ctrl+D para terminar)\n\n");
        yyin = stdin;
    }

    int resultado = yyparse();

    if (argc > 1) {
        fclose(yyin);
    }

    if (resultado == 0) {
        printf("\n[OK] Compilacion exitosa\n");
    } else {
        printf("\n[ERROR] Compilacion fallida con errores\n");
    }

    return resultado;
}

/* Implementación de yyerror */
void yyerror(const char *s) {
    fprintf(stderr, "Error sintáctico [línea %d, col %d]: %s\n", linea, columna, s);
}