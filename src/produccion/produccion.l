/* produccion.l - Analizador Lexico para el Lenguaje de Produccion */
/* FashionFlow Compiler - Nancy's Collection */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produccion.tab.h"

int linea = 1;
int columna = 1;

void actualizar_columna() {
    columna += yyleng;
}

void nueva_linea() {
    linea++;
    columna = 1;
}
%}

%option noyywrap

DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          {LETRA}({LETRA}|{DIGITO}|[_-])*
ENTERO      {DIGITO}+
DECIMAL     {DIGITO}+\.{DIGITO}{1,2}
ESPACIO     [ \t]+
COMENTARIO  \/\/.*

%%

    /* Palabras reservadas - Instrucciones */
"ORDEN"             { actualizar_columna(); return KW_ORDEN; }
"CORTE"             { actualizar_columna(); return KW_CORTE; }
"CONSULTAR"         { actualizar_columna(); return KW_CONSULTAR; }
"CALCULAR_COSTO"    { actualizar_columna(); return KW_CALCULAR_COSTO; }

    /* Palabras reservadas - Atributos */
"DISENO"            { actualizar_columna(); return KW_DISENO; }
"TALLAS"            { actualizar_columna(); return KW_TALLAS; }
"COLORES"           { actualizar_columna(); return KW_COLORES; }
"CANTIDADES"        { actualizar_columna(); return KW_CANTIDADES; }
"CONSUMO"           { actualizar_columna(); return KW_CONSUMO; }
"PRECIO_TELA"       { actualizar_columna(); return KW_PRECIO_TELA; }
"ESTADO"            { actualizar_columna(); return KW_ESTADO; }
"ORDENES"           { actualizar_columna(); return KW_ORDENES; }
"DONDE"             { actualizar_columna(); return KW_DONDE; }

    /* Operadores */
":"                 { actualizar_columna(); return OP_DOS_PUNTOS; }
"=="                { actualizar_columna(); return OP_IGUAL_IGUAL; }

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

    /* Ignorar espacios y comentarios */
{ESPACIO}           { actualizar_columna(); }
{COMENTARIO}        { actualizar_columna(); }
\n                  { nueva_linea(); }

    /* Caracteres invalidos */
.                   { 
                      fprintf(stderr, "Error lexico [linea %d, col %d]: Caracter '%s' no reconocido\n", 
                             linea, columna, yytext);
                      actualizar_columna();
                    }

%%
