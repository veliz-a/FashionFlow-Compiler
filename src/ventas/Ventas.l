%{
#include "Ventas.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

"Registrar_Cliente"  { return REGISTRAR_CLIENTE; }
"Registrar_Venta"    { return REGISTRAR_VENTA;   }
"Registrar_Gasto"    { return REGISTRAR_GASTO;   }
"Registrar_Pago"     { return REGISTRAR_PAGO;    }
"Registrar_Salario"  { return REGISTRAR_SALARIO; }
"Generar_Reporte"    { return GENERAR_REPORTE;   }

"("                  { return PARENTESIS_IZQ; }
")"                  { return PARENTESIS_DER; }
","                  { return COMA; }
";"                  { return FIN_SENTENCIA; }

\"[^\"]*\"            { yylval.str = strdup(yytext + 1); yylval.str[strlen(yylval.str)-1] = '\0'; return CADENA; }
[0-9]+(\.[0-9]+)?     { yylval.num = atoi(yytext);  return NUMERO; }

[ \t\r\n]+      { /* ignorar espacios */ }
\/\/.*          { /* ignorar comentarios */ }

.               { printf("Caracter inesperado: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
