/* produccion.l - Analizador Léxico para el Lenguaje de Producción */
/* FashionFlow Compiler - Nancy's Collection */
/* Módulo: Producción */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produccion.tab.h"  /* Generado por Bison */

int linea = 1;
int columna = 1;

/* Actualizar posición */
void actualizar_columna() {
    columna += yyleng;
}

void nueva_linea() {
    linea++;
    columna = 1;
}

%}

%option noyywrap

/* Definiciones de patrones */
DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          {LETRA}({LETRA}|{DIGITO}|[_-])*
ENTERO      {DIGITO}+
DECIMAL     {DIGITO}+\.{DIGITO}{1,2}
ESPACIO     [ \t]+
COMENTARIO  \/\/.*

%%

    /* Palabras reservadas - Instrucciones principales */
"ORDEN"             { actualizar_columna(); return KW_ORDEN; }

    /* Palabras reservadas - Atributos */
"DISEÑO"            { actualizar_columna(); return KW_DISENO; }
"TALLAS"            { actualizar_columna(); return KW_TALLAS; }
"COLORES"           { actualizar_columna(); return KW_COLORES; }
"CANTIDADES"        { actualizar_columna(); return KW_CANTIDADES; }

    /* Operadores */
":"                 { actualizar_columna(); return OP_DOS_PUNTOS; }

    /* Delimitadores */
"{"                 { actualizar_columna(); return LBRACE; }
"}"                 { actualizar_columna(); return RBRACE; }
"["                 { actualizar_columna(); return LBRACKET; }
"]"                 { actualizar_columna(); return RBRACKET; }
","                 { actualizar_columna(); return COMMA; }

    /* Literales */
{DECIMAL}           { 
                      actualizar_columna(); 
                      yylval.decimal = atof(yytext); 
                      return NUM_DECIMAL; 
                    }

{ENTERO}            { 
                      actualizar_columna(); 
                      yylval.entero = atoi(yytext); 
                      return NUM_ENTERO; 
                    }

{ID}                { 
                      actualizar_columna(); 
                      yylval.cadena = strdup(yytext); 
                      return ID; 
                    }

    /* Ignorar espacios en blanco */
{ESPACIO}           { actualizar_columna(); }

    /* Ignorar comentarios */
{COMENTARIO}        { actualizar_columna(); }

    /* Nueva línea */
\n                  { nueva_linea(); }

    /* Caracteres inválidos */
.                   { 
                      printf("Error léxico [línea %d, col %d]: Carácter '%s' no reconocido\n", 
                             linea, columna, yytext);
                      actualizar_columna();
                    }

%%
