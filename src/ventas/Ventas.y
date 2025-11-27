%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

int instrucciones_procesadas = 0;

%}

%union{
    char* str;
    int num;
}

%token <str> CADENA;
%token <num> NUMERO;

%token REGISTRAR_CLIENTE;
%token REGISTRAR_VENTA;
%token REGISTRAR_GASTO;
%token REGISTRAR_PAGO;
%token REGISTRAR_SALARIO;
%token GENERAR_REPORTE;

%token PARENTESIS_IZQ;
%token PARENTESIS_DER;
%token COMA;
%token FIN_SENTENCIA;

%start programa

%%

programa:
    lista_instrucciones
    ;

lista_instrucciones:
      instruccion
    | lista_instrucciones instruccion
    ;

instruccion:
    REGISTRAR_CLIENTE 
    PARENTESIS_IZQ CADENA COMA CADENA COMA CADENA COMA CADENA PARENTESIS_DER FIN_SENTENCIA
        {
          /* cliente(nombre,dni,correo,direccion) */
          printf("Cliente leido desde Bison\n");
          instrucciones_procesadas++;
        }

    | REGISTRAR_VENTA 
      PARENTESIS_IZQ CADENA COMA NUMERO COMA NUMERO COMA CADENA COMA CADENA COMA CADENA PARENTESIS_DER FIN_SENTENCIA
        {
          printf("Venta leida desde Bison\n");
          instrucciones_procesadas++;
        }

    | REGISTRAR_GASTO 
      PARENTESIS_IZQ CADENA COMA CADENA COMA CADENA PARENTESIS_DER FIN_SENTENCIA
        {
          printf("Gasto leido desde Bison\n");
          instrucciones_procesadas++;
        }

    | REGISTRAR_PAGO 
      PARENTESIS_IZQ CADENA COMA CADENA COMA NUMERO COMA CADENA COMA CADENA PARENTESIS_DER FIN_SENTENCIA
        {
          printf("Pago leido desde Bison\n");
          instrucciones_procesadas++;
        }

    | REGISTRAR_SALARIO 
      PARENTESIS_IZQ NUMERO COMA NUMERO COMA CADENA COMA CADENA COMA CADENA PARENTESIS_DER FIN_SENTENCIA
        {
          printf("Salario leido desde Bison\n");
          instrucciones_procesadas++;
        }

    | GENERAR_REPORTE 
      FIN_SENTENCIA
        {
          printf("Reporte leido desde Bison\n");
          instrucciones_procesadas++;
        }
    ;
%%

void yyerror(const char* s){
    fprintf(stderr, "Error sintactico: %s\n", s);
}

int main(int argc, char** argv) {
    extern FILE* yyin;
    
    printf("=== Compilador de Ventas - Nancy's Collection ===\n\n");
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: No se pudo abrir '%s'\n", argv[1]);
            return 1;
        }
        printf("Procesando: %s\n\n", argv[1]);
    } else {
        printf("Uso: %s <archivo>\n", argv[0]);
        return 1;
    }
    
    int resultado = yyparse();
    
    fclose(yyin);
    
    if (resultado == 0 && instrucciones_procesadas == 0) {
        fprintf(stderr, "\nERROR: No se encontraron instrucciones de venta en el archivo\n");
        return 1;
    }
    
    if (resultado == 0) {
        printf("\n[OK] Compilacion exitosa\n");
    } else {
        printf("\n[ERROR] Compilacion con errores\n");
    }
    
    return resultado;
}