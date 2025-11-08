%{
#include<stdio.h>
%}


DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          {LETRA}({LETRA}|{DIGITO})*
NUM         {DIGITO}+(\.{DIGITO}+)?
STRING      \"([^\"\\]|\\.)*\"
COMMENT1    "//".*
COMMENT2    "/*"([^*]|[\*+[^*/]])*\*+"/"


%%

"if"        {printf("palabra clave: if\n");}
"else"      {printf("palabra clave: else\n");}
"while"     {printf("palabra clave: while\n");}
"for"       {printf("palabra clave: for\n");}
"return"    {printf("palabra clave: return\n");}
"int"       {printf("palabra clave: int\n");}
"float"     {printf("palabra clave: float\n");}
"char"      {printf("palabra clave: char\n");}
"void"      {printf("palabra clave: void\n");}

{NUM}       {printf("Numero: %s\n", yytext);}
{ID}        {printf("Identificador: %s\n", yytext);}
{STRING}    {printf("Cadena: %s\n", yytext);}
{COMMENT1}  {printf("Comentario en linea\n");}
{COMMENT2}  {printf("Comentario en linea\n");}

"<="        {printf("Operador: <=\n");}
">="        {printf("Operador: >=\n");}
"=="        {printf("Operador: ==\n");}
"!="        {printf("Operador: !=\n");}
"="        {printf("Operador: =\n");}
">"        {printf("Operador: >\n");}
"<"        {printf("Operador: <\n");}
"+"        {printf("Operador: +\n");}
"-"        {printf("Operador: -\n");}
"*"        {printf("Operador: *\n");}
"/"        {printf("Operador: /\n");}

"("        {printf("Simbolos: (\n");}
")"        {printf("Simbolos: )\n");}
"{"        {printf("Simbolos: {\n");}
"}"        {printf("Simbolos: }\n");}
";"        {printf("Simbolos: ;\n");}
","        {printf("Simbolos: ,\n");}

[ \t\n]    {/*Ignorar espacios*/}
.          {printf("caracter desconocido: %s\n", yytext);}

%%

int main(){
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}