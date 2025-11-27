%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

int has_prenda_t, has_talla_t, has_cantidad_t, has_de_t, has_a_t, has_fecha_t;
int repeated_t;


int has_codigo_i, has_prenda_i, has_descripcion_i, has_talla_i,
    has_destino_i, has_fecha_i, has_cantidad_i;
int repeated_i;


int has_prenda_c, has_en_c;
int repeated_c;

int has_formato_e, has_fecha_e;
int repeated_e;

%}

%union {
    char* text;
    int number;
}

%token TRANSFERIR INGRESAR CONSULTAR EXPORTAR
%token PRENDA TALLA CANTIDAD DE A EN FORMATO FECHA CODIGO DESCRIPCION
%token LBRACE RBRACE COLON
%token <text> STRING
%token <number> NUMBER
%token <text> UNKNOWN
%token END

%%

programa:
    | programa instruccion
    ;

instruccion:
      transferir_block
    | ingresar_block
    | consultar_block
    | exportar_block
    ;

transferir_block:
    TRANSFERIR LBRACE {
        has_prenda_t = has_talla_t = has_cantidad_t =
        has_de_t = has_a_t = has_fecha_t = 0;
        repeated_t = 0;
    }
    transferir_items RBRACE {
        int ok = 1;

        if (repeated_t) { printf("Error: hay atributos repetidos en TRANSFERIR\n"); ok = 0; }
        if (!has_prenda_t)   { printf("Error: falta PRENDA en TRANSFERIR\n"); ok = 0; }
        if (!has_talla_t)    { printf("Error: falta TALLA en TRANSFERIR\n"); ok = 0; }
        if (!has_cantidad_t) { printf("Error: falta CANTIDAD en TRANSFERIR\n"); ok = 0; }
        if (!has_de_t)       { printf("Error: falta DE en TRANSFERIR\n"); ok = 0; }
        if (!has_a_t)        { printf("Error: falta A en TRANSFERIR\n"); ok = 0; }
        if (!has_fecha_t)    { printf("Error: falta FECHA en TRANSFERIR\n"); ok = 0; }

        printf(ok ? "[OK] TRANSFERIR valido\n"
                   : "[ERROR] TRANSFERIR invalido\n");
    }
    ;

transferir_items:
    | transferir_items PRENDA COLON STRING {
        if (has_prenda_t) { printf("Error: PRENDA repetido.\n"); repeated_t = 1; }
        printf("  PRENDA = %s\n", $4);
        has_prenda_t = 1;
    }
    | transferir_items TALLA COLON STRING {
        if (has_talla_t) { printf("Error: TALLA repetido.\n"); repeated_t = 1; }
        printf("  TALLA = %s\n", $4);
        has_talla_t = 1;
    }
    | transferir_items CANTIDAD COLON NUMBER {
        if (has_cantidad_t) { printf("Error: CANTIDAD repetido.\n"); repeated_t = 1; }
        printf("  CANTIDAD = %d\n", $4);
        has_cantidad_t = 1;
    }
    | transferir_items DE COLON STRING {
        if (has_de_t) { printf("Error: DE repetido.\n"); repeated_t = 1; }
        printf("  DE = %s\n", $4);
        has_de_t = 1;
    }
    | transferir_items A COLON STRING {
        if (has_a_t) { printf("Error: A repetido.\n"); repeated_t = 1; }
        printf("  A = %s\n", $4);
        has_a_t = 1;
    }
    | transferir_items FECHA COLON STRING {
        if (has_fecha_t) { printf("Error: FECHA repetido.\n"); repeated_t = 1; }
        printf("  FECHA = %s\n", $4);
        has_fecha_t = 1;
    }
    ;


ingresar_block:
    INGRESAR LBRACE {
        has_codigo_i = has_prenda_i = has_descripcion_i =
        has_talla_i = has_destino_i = has_fecha_i = has_cantidad_i = 0;
        repeated_i = 0;
    }
    ingresar_items RBRACE {
        int ok = 1;

        if (repeated_i) { printf("Error: hay atributos repetidos en INGRESAR\n"); ok = 0; }
        if (!has_codigo_i)  { printf("Error: falta CODIGO en INGRESAR\n"); ok = 0; }
        if (!has_prenda_i)  { printf("Error: falta PRENDA en INGRESAR\n"); ok = 0; }
        if (!has_talla_i)   { printf("Error: falta TALLA en INGRESAR\n"); ok = 0; }
        if (!has_destino_i) { printf("Error: falta A (DESTINO) en INGRESAR\n"); ok = 0; }
        if (!has_fecha_i)   { printf("Error: falta FECHA en INGRESAR\n"); ok = 0; }
        if (!has_cantidad_i){ printf("Error: falta CANTIDAD en INGRESAR\n"); ok = 0; }

        printf(ok ? "[OK] INGRESAR valido\n"
                   : "[ERROR] INGRESAR invalido\n");
    }
    ;

ingresar_items:
    | ingresar_items CODIGO COLON STRING {
        if (has_codigo_i) { printf("Error: CODIGO repetido.\n"); repeated_i = 1; }
        printf("  CODIGO = %s\n", $4);
        has_codigo_i = 1;
    }
    | ingresar_items PRENDA COLON STRING {
        if (has_prenda_i) { printf("Error: PRENDA repetido.\n"); repeated_i = 1; }
        printf("  PRENDA = %s\n", $4);
        has_prenda_i = 1;
    }
    | ingresar_items DESCRIPCION COLON STRING {
        if (has_descripcion_i) { printf("Error: DESCRIPCION repetido.\n"); repeated_i = 1; }
        printf("  DESCRIPCION = %s\n", $4);
        has_descripcion_i = 1;
    }
    | ingresar_items TALLA COLON STRING {
        if (has_talla_i) { printf("Error: TALLA repetido.\n"); repeated_i = 1; }
        printf("  TALLA = %s\n", $4);
        has_talla_i = 1;
    }
    | ingresar_items A COLON STRING {
        if (has_destino_i) { printf("Error: A repetido.\n"); repeated_i = 1; }
        printf("  DESTINO = %s\n", $4);
        has_destino_i = 1;
    }
    | ingresar_items FECHA COLON STRING {
        if (has_fecha_i) { printf("Error: FECHA repetido.\n"); repeated_i = 1; }
        printf("  FECHA = %s\n", $4);
        has_fecha_i = 1;
    }
    | ingresar_items CANTIDAD COLON NUMBER {
        if (has_cantidad_i) { printf("Error: CANTIDAD repetido.\n"); repeated_i = 1; }
        printf("  CANTIDAD = %d\n", $4);
        has_cantidad_i = 1;
    }
    ;


consultar_block:
    CONSULTAR LBRACE {
        has_prenda_c = has_en_c = 0;
        repeated_c = 0;
    }
    consultar_items RBRACE {
        int ok = 1;

        if (repeated_c) { printf("Error: hay atributos repetidos en CONSULTAR\n"); ok = 0; }
        if (!has_prenda_c && !has_en_c)
            { printf("Error: CONSULTAR requiere PRENDA o EN\n"); ok = 0; }

        printf(ok ? "[OK] CONSULTAR valido\n"
                   : "[ERROR] CONSULTAR invalido\n");
    }
    ;

consultar_items:
    | consultar_items PRENDA COLON STRING {
        if (has_prenda_c) { printf("Error: PRENDA repetido.\n"); repeated_c = 1; }
        printf("  PRENDA = %s\n", $4);
        has_prenda_c = 1;
    }
    | consultar_items EN COLON STRING {
        if (has_en_c) { printf("Error: EN repetido.\n"); repeated_c = 1; }
        printf("  UBICACION = %s\n", $4);
        has_en_c = 1;
    }
    ;


exportar_block:
    EXPORTAR LBRACE {
        has_formato_e = has_fecha_e = 0;
        repeated_e = 0;
    }
    exportar_items RBRACE {
        int ok = 1;

        if (repeated_e) { printf("Error: hay atributos repetidos en EXPORTAR\n"); ok = 0; }
        if (!has_formato_e) printf("Error: falta FORMATO en EXPORTAR\n"), ok = 0;
        if (!has_fecha_e)   printf("Error: falta FECHA en EXPORTAR\n"), ok = 0;

        printf(ok ? "[OK] EXPORTAR valido\n"
                   : "[ERROR] EXPORTAR invalido\n");
    }
    ;

exportar_items:
    | exportar_items FORMATO COLON STRING {
        if (has_formato_e) { printf("Error: FORMATO repetido.\n"); repeated_e = 1; }
        printf("  FORMATO = %s\n", $4);
        has_formato_e = 1;
    }
    | exportar_items FECHA COLON STRING {
        if (has_fecha_e) { printf("Error: FECHA repetido.\n"); repeated_e = 1; }
        printf("  FECHA = %s\n", $4);
        has_fecha_e = 1;
    }
    ;

%%

int main() { return yyparse(); }

void yyerror(const char *s) {
    fprintf(stderr, "Error de sintaxis: %s\n", s);
}
