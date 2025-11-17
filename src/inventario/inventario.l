%{
#include "inventario.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

"TRANSFERIR"        { return TRANSFERIR; }
"INGRESAR"          { return INGRESAR; }
"CONSULTAR"         { return CONSULTAR; }
"EXPORTAR"          { return EXPORTAR; }
"PRENDA"            { return PRENDA; }
"TALLA"             { return TALLA; }
"CANTIDAD"          { return CANTIDAD; }
"DE"                { return DE; }
"A"                 { return A; }
"EN"                { return EN; }
"FORMATO"           { return FORMATO; }
"FECHA"             { return FECHA; }
"CODIGO"            { return CODIGO; }
"DESCRIPCION"       { return DESCRIPCION; }

"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
":"                 { return COLON; }

\"([^"\n]*)\" {
    char *raw = strdup(yytext + 1);
    raw[strlen(raw) - 1] = '\0';
    yylval.text = raw;
    return STRING;
}

[0-9]+ {
    yylval.number = atoi(yytext);
    return NUMBER;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.text = strdup(yytext);
    return UNKNOWN;
}

[ \t\r\n]+    ;

.  {
    printf("Caracter inesperado: %s\n", yytext);
}

%%

int yywrap() { return 1; }
