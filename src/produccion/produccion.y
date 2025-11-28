/* produccion.y - Analizador Sintactico y Semantico para Produccion */
/* FashionFlow Compiler - Nancy's Collection */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int yylex();
extern void yyerror(const char *s);
extern int linea;
extern int columna;
extern FILE *yyin;

/* === ESTRUCTURAS DE DATOS === */
typedef struct {
    char id[50];
    char diseno[50];
    int num_tallas;
    int num_colores;
    int num_cantidades;
    double consumo_tela;
    char estado[20];  /* "Registrada", "Cortada", "Completada" */
} Orden;

Orden ordenes[100];
int total_ordenes = 0;

/* === CONTADORES === */
int contador_ordenes_declaradas = 0;
int contador_cortes = 0;
int contador_consultas = 0;
int contador_calculos = 0;

/* === FUNCIONES AUXILIARES === */
Orden* buscar_orden(const char* id) {
    for (int i = 0; i < total_ordenes; i++) {
        if (strcmp(ordenes[i].id, id) == 0) {
            return &ordenes[i];
        }
    }
    return NULL;
}

void validar_coherencia_dimensional(int num_tallas, int num_colores, int num_cantidades) {
    int esperado = num_tallas * num_colores;
    if (num_cantidades != esperado) {
        fprintf(stderr, "\n[ERROR SEMANTICO] Incoherencia dimensional:\n");
        fprintf(stderr, "  Tallas: %d, Colores: %d => Se esperan %d cantidades\n", 
                num_tallas, num_colores, esperado);
        fprintf(stderr, "  Pero se proporcionaron: %d cantidades\n", num_cantidades);
        exit(1);
    }
}

%}

%union {
    int entero;
    double decimal;
    char *cadena;
}

/* Tokens terminales */
%token KW_ORDEN KW_CORTE KW_CONSULTAR KW_CALCULAR_COSTO
%token KW_DISENO KW_TALLAS KW_COLORES KW_CANTIDADES KW_CONSUMO 
%token KW_PRECIO_TELA KW_ESTADO KW_ORDENES KW_DONDE
%token OP_DOS_PUNTOS OP_IGUAL_IGUAL
%token LBRACE RBRACE LBRACKET RBRACKET COMMA

%token <entero> NUM_ENTERO
%token <decimal> NUM_DECIMAL
%token <cadena> ID

/* CRITICO: Declarar tipos de retorno para no-terminales */
%type <entero> lista_valores valores
%type <cadena> valor

%%

/* === GRAMATICA PRINCIPAL === */
programa:
    lista_instrucciones
    { 
        printf("\n=== RESUMEN DE COMPILACION ===\n");
        printf("Ordenes declaradas:    %d\n", contador_ordenes_declaradas);
        printf("Cortes registrados:    %d\n", contador_cortes);
        printf("Consultas ejecutadas:  %d\n", contador_consultas);
        printf("Costos calculados:     %d\n", contador_calculos);
        printf("Total ordenes activas: %d\n", total_ordenes);
        
        if (contador_ordenes_declaradas == 0) {
            fprintf(stderr, "\n[ADVERTENCIA] No se procesaron ordenes de produccion\n");
        }
    }
    ;

lista_instrucciones:
    instruccion
    | lista_instrucciones instruccion
    ;

instruccion:
    declaracion_orden
    | registro_corte
    | consulta_ordenes
    | calculo_costo
    ;

/* === DECLARACION DE ORDEN === */
/* Posiciones: $1=ORDEN $2=ID $3=LBRACE $4=DISENO $5=: $6=ID 
               $7=TALLAS $8=: $9=lista $10=COLORES $11=: $12=lista 
               $13=CANTIDADES $14=: $15=lista $16=RBRACE */
declaracion_orden:
    KW_ORDEN ID LBRACE
        KW_DISENO OP_DOS_PUNTOS ID
        KW_TALLAS OP_DOS_PUNTOS lista_valores
        KW_COLORES OP_DOS_PUNTOS lista_valores
        KW_CANTIDADES OP_DOS_PUNTOS lista_valores
    RBRACE
    {
        /* Validacion semantica: coherencia dimensional */
        /* $9=tallas, $12=colores, $15=cantidades */
        validar_coherencia_dimensional($9, $12, $15);
        
        /* Registrar orden */
        strcpy(ordenes[total_ordenes].id, $2);
        strcpy(ordenes[total_ordenes].diseno, $6);
        ordenes[total_ordenes].num_tallas = $9;
        ordenes[total_ordenes].num_colores = $12;
        ordenes[total_ordenes].num_cantidades = $15;
        ordenes[total_ordenes].consumo_tela = 0.0;
        strcpy(ordenes[total_ordenes].estado, "Registrada");
        
        printf("\n[OK] ORDEN '%s' registrada\n", $2);
        printf("    Diseno: %s\n", $6);
        printf("    Combinaciones: %d tallas x %d colores = %d prendas\n", 
               $9, $12, $15);
        printf("    Estado: Registrada\n");
        
        total_ordenes++;
        contador_ordenes_declaradas++;
        
        free($2);
        free($6);
    }
    ;

/* === REGISTRO DE CORTE === */
registro_corte:
    KW_CORTE ID LBRACE
        KW_CONSUMO OP_DOS_PUNTOS NUM_DECIMAL
    RBRACE
    {
        Orden* orden = buscar_orden($2);
        if (orden == NULL) {
            fprintf(stderr, "\n[ERROR] Orden '%s' no existe\n", $2);
            exit(1);
        }
        
        if ($6 <= 0) {
            fprintf(stderr, "\n[ERROR SEMANTICO] Consumo de tela debe ser > 0 (recibido: %.2f)\n", $6);
            exit(1);
        }
        
        orden->consumo_tela = $6;
        strcpy(orden->estado, "Cortada");
        
        printf("\n[OK] CORTE registrado para orden '%s'\n", $2);
        printf("    Consumo de tela: %.2f metros\n", $6);
        printf("    Estado actualizado: Cortada\n");
        
        contador_cortes++;
        free($2);
    }
    ;

/* === CONSULTA DE ORDENES === */
consulta_ordenes:
    KW_CONSULTAR KW_ORDENES KW_DONDE KW_ESTADO OP_IGUAL_IGUAL ID
    {
        printf("\n[OK] CONSULTA: Ordenes con estado '%s'\n", $6);
        printf("----------------------------------------------------\n");
        
        int encontradas = 0;
        for (int i = 0; i < total_ordenes; i++) {
            if (strcmp(ordenes[i].estado, $6) == 0) {
                printf("  * %s | Diseno: %s | Tela: %.2f m | %d prendas\n",
                       ordenes[i].id,
                       ordenes[i].diseno,
                       ordenes[i].consumo_tela,
                       ordenes[i].num_cantidades);
                encontradas++;
            }
        }
        
        if (encontradas == 0) {
            printf("  (No se encontraron ordenes)\n");
        }
        printf("----------------------------------------------------\n");
        printf("Total encontradas: %d\n", encontradas);
        
        contador_consultas++;
        free($6);
    }
    ;

/* === CALCULO DE COSTO === */
calculo_costo:
    KW_CALCULAR_COSTO ID KW_PRECIO_TELA OP_DOS_PUNTOS NUM_DECIMAL
    {
        Orden* orden = buscar_orden($2);
        if (orden == NULL) {
            fprintf(stderr, "\n[ERROR] Orden '%s' no existe\n", $2);
            exit(1);
        }
        
        if (orden->consumo_tela == 0) {
            fprintf(stderr, "\n[ERROR] Orden '%s' no tiene corte registrado\n", $2);
            exit(1);
        }
        
        if ($5 <= 0) {
            fprintf(stderr, "\n[ERROR SEMANTICO] Precio de tela debe ser > 0 (recibido: %.2f)\n", $5);
            exit(1);
        }
        
        double costo_total = orden->consumo_tela * $5;
        double costo_unitario = costo_total / orden->num_cantidades;
        
        printf("\n[OK] COSTO calculado para orden '%s'\n", $2);
        printf("    Consumo: %.2f m x S/ %.2f/m = S/ %.2f\n", 
               orden->consumo_tela, $5, costo_total);
        printf("    Costo por prenda: S/ %.2f (%d prendas)\n", 
               costo_unitario, orden->num_cantidades);
        
        contador_calculos++;
        free($2);
    }
    ;

/* === LISTA DE VALORES (retorna contador) === */
lista_valores:
    LBRACKET valores RBRACKET
    { $$ = $2; }
    ;

valores:
    valor
    { $$ = 1; free($1); }
    | valores COMMA valor
    { $$ = $1 + 1; free($3); }
    ;

valor:
    ID          
    { $$ = $1; }
    | NUM_ENTERO 
    { 
        char* temp = malloc(20);
        sprintf(temp, "%d", $1);
        $$ = temp;
    }
    | NUM_DECIMAL
    {
        char* temp = malloc(20);
        sprintf(temp, "%.2f", $1);
        $$ = temp;
    }
    ;

%%

/* === FUNCIONES PRINCIPALES === */
int main(int argc, char **argv) {
    printf("========================================================\n");
    printf("  FashionFlow Compiler - Modulo de Produccion v2.0\n");
    printf("  Nancy's Collection\n");
    printf("========================================================\n\n");

    if (argc > 1) {
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo) {
            fprintf(stderr, "Error: No se pudo abrir '%s'\n", argv[1]);
            return 1;
        }
        yyin = archivo;
        printf("Procesando: %s\n", argv[1]);
    } else {
        printf("Modo interactivo (Ctrl+D para terminar)\n");
        yyin = stdin;
    }

    int resultado = yyparse();

    if (argc > 1) {
        fclose(yyin);
    }

    if (resultado == 0) {
        printf("\n[OK] Compilacion exitosa\n");
    } else {
        printf("\n[ERROR] Compilacion fallida\n");
    }

    return resultado;
}

void yyerror(const char *s) {
    fprintf(stderr, "\n[ERROR] Sintaxis [linea %d, col %d]: %s\n", linea, columna, s);
}
