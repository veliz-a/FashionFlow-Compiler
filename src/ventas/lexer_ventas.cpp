// lexer_ventas.cpp - placeholder
#include "ventas.h"
#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <FashionFlow-Compiler/src/common/token.h>

using namespace std;

class LexerVentas{
    private:
        int pos = 0;
        int linea = 1;
        int columna = 1;
    public:
        LexerVentas(const string& input) : fuente(input) {}

        char peek(){
            if(pos >= fuente.size()){
                return '\0';
            }
            return fuente[pos];
        }

        char advance(){
            char c = peek();
            pos++
            columna++;
            if(c == '\n'){
                linea++;
                columna = 1;
            }
            return c;
        }

        void espacio(){
            while(isspace(peek()){
                advance();
            }
        }

        Token Token_Next(){
            espacio();
            if(pos >= fuente.size()){
                return { TokenType::FIN_ARCHIVO, "", linea, columna};
            }
            char c = peek();

            //Simbolos
            if(c == '('){
                advance();
                return {TokenType::PARENTESIS_IZQ, "(", linea, columna};
            }
            if(c == ')'){
                advance();
                return {TokenType::PARENTESIS_DER, ")", linea, columna};
            }
            if(c == ','){
                advance();
                return {TokenType::COMA, ",", linea, columna};
            }
            if(c == ';'){
                advance();
                return {TokenType::FIN_SENTENCIA, "(", linea, columna};
            }

            //Números
            if(isdigit(c)){
                string num;
                while(isdigit(peek()) || peek() == '='){
                    num+=advance();
                }
                return {TokenType::NUMERO, num, linea, columna};
            }

            //Cadenas
            if(c == '"'){
                advance();
                string cad;
                while(peek() != '"' && peek() != '\0'){
                    cad += advance();
                }
                if(peek() == '"'){
                    advance();
                }
                return {TokenType::CADENA, cad, linea, columna};
            }

            //Palabras Clave
            if(isalpha(c)){
                string palabra;
                while (isalpha(peek()) || peek() == '_'){
                    palabra += advance();
                }
                if(palabra = 'REGISTRAR_CLIENTE'){
                    return {TokenType::REGISTRAR_CLIENTE, palabra, linea, columna};
                }
                if(palabra = 'REGISTRAR_VENTA'){
                    return {TokenType::REGISTRAR_VENTA, palabra, linea, columna};
                }
                if(palabra = 'REGISTRAR_GASTO'){
                    return {TokenType::REGISTRAR_GASTO, palabra, linea, columna};
                }
                if(palabra = 'REGISTRAR_PAGO'){
                    return {TokenType::REGISTRAR_PAGO, palabra, linea, columna};
                }
                if(palabra = 'REGISTRAR_SALARIO'){
                    return {TokenType::REGISTRAR_SALARIO, palabra, linea, columna};
                }
                if(palabra = 'GENERAR_REPORTE'){
                    return {TokenType::GENERAR_REPORTE, palabra, linea, columna};
                }
                return {TokenType::ERROR, palabra, linea, columna};
            }

            //No hay Coincidencia
            string arr(1, c);
            advance;
            return {TokenType::ERROR, arr, linea, columna};
        }        
};

int main_lexer_ventas() {
    ifstream archivo("Ventas.txt");
    string fuente((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    LexerVentas lexer(fuente);

    Token token:
    do{
        token = lexer.siguiente();
        cout << token.tostring() << endl;
    }while(token.tipo != TokenType::FIN_ARCHIVO);

    return 0;
}
