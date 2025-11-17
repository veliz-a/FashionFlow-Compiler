%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char* text;
    int number;
}

/* TOKENS */
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
    TRANSFERIR LBRACE transferir_items RBRACE {
        printf("\n[OK] TRANSFERIR válido\n");
    }
    ;

transferir_items:
     
    | transferir_items PRENDA COLON STRING {
        printf("  PRENDA = %s\n", $4);
    }
    | transferir_items TALLA COLON STRING {
        printf("  TALLA = %s\n", $4);
    }
    | transferir_items CANTIDAD COLON NUMBER {
        printf("  CANTIDAD = %d\n", $4);
    }
    | transferir_items DE COLON STRING {
        printf("  DE = %s\n", $4);
    }
    | transferir_items A COLON STRING {
        printf("  A = %s\n", $4);
    }
    | transferir_items FECHA COLON STRING {
        printf("  FECHA = %s\n", $4);
    }
    ;

ingresar_block:
    INGRESAR LBRACE ingresar_items RBRACE {
        printf("\n[OK] INGRESAR válido\n");
    }
    ;

ingresar_items:
     
    | ingresar_items CODIGO COLON STRING {
        printf("  CODIGO = %s\n", $4);
    }
    | ingresar_items PRENDA COLON STRING {
        printf("  PRENDA = %s\n", $4);
    }
    | ingresar_items DESCRIPCION COLON STRING {
        printf("  DESCRIPCION = %s\n", $4);
    }
    | ingresar_items TALLA COLON STRING {
        printf("  TALLA = %s\n", $4);
    }
    | ingresar_items A COLON STRING {
        printf("  DESTINO = %s\n", $4);
    }
    ;


consultar_block:
    CONSULTAR LBRACE consultar_items RBRACE {
        printf("\n[OK] CONSULTAR válido\n");
    }
    ;

consultar_items:
    
    | consultar_items PRENDA COLON STRING {
        printf("  PRENDA = %s\n", $4);
    }
    | consultar_items EN COLON STRING {
        printf("  UBICACION = %s\n", $4);
    }
    ;

exportar_block:
    EXPORTAR LBRACE exportar_items RBRACE {
        printf("\n[OK] EXPORTAR válido\n");
    }
    ;

exportar_items:
     
    | exportar_items FORMATO COLON STRING {
        printf("  FORMATO = %s\n", $4);
    }
    | exportar_items FECHA COLON STRING {
        printf("  FECHA = %s\n", $4);
    }
    ;

%%

int main() {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error de sintaxis: %s\n", s);
}
