// lexer_ventas.cpp - placeholder
#include "ventas.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <src/common/token.h>

using namespace std;

class Lexercliente{
    private:
        int pos = 0;
        int linea = 1;
        int colum = 1;
    public:
        Lexercliente(const string& input) : fuente(input) {}

        char peek(){
            if(pos >= fuente.size()){
                return 0;
            }
            return fuente[pos];
        }
        char advance() {
            char c = peak();
            pos++;
            colum++;
            if(c == '\n'){
                linea++;
                colum = 1;
            }
            return c;
        }
};

int main_lexer_ventas() {
    // TODO: implementar
    return 0;
}
