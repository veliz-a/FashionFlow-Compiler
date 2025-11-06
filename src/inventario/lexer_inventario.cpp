// lexer_inventario.cpp - placeholder
#include "inventario.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// === Tipos de Tokens ===

string tokenTypeToString(TokenType type) {
    switch (type) {
        case TRANSFERIR: return "TRANSFERIR";
        case INGRESAR: return "INGRESAR";
        case CONSULTAR: return "CONSULTAR";
        case EXPORTAR: return "EXPORTAR";
        case AJUSTAR: return "AJUSTAR";
        case TALLA: return "TALLA";
        case CANTIDAD: return "CANTIDAD";
        case DE: return "DE";
        case A: return "A";
        case EN: return "EN";
        case FORMATO: return "FORMATO";
        case FECHA: return "FECHA";
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";
        case END: return "END";
        default: return "UNKNOWN";
    }
}

// === Lexer ===
vector<Token> lexerInventario(const string& filename) {
    ifstream in(filename);
    vector<Token> tokens;

    if (!in.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << filename << endl;
        return tokens;
    }

    char c;
    while (in.get(c)) {
        if (isspace(c)) continue;

        // Palabras clave
        if (isalpha(c)) {
            string word(1, toupper(c));
            while (isalnum(in.peek())) {
                in.get(c);
                word += toupper(c);
            }

            if (word == "TRANSFERIR") tokens.push_back({TRANSFERIR, word});
            else if (word == "INGRESAR") tokens.push_back({INGRESAR, word});
            else if (word == "CONSULTAR") tokens.push_back({CONSULTAR, word});
            else if (word == "EXPORTAR") tokens.push_back({EXPORTAR, word});
            else if (word == "AJUSTAR") tokens.push_back({AJUSTAR, word});
            else if (word == "TALLA") tokens.push_back({TALLA, word});
            else if (word == "CANTIDAD") tokens.push_back({CANTIDAD, word});
            else if (word == "DE") tokens.push_back({DE, word});
            else if (word == "A") tokens.push_back({A, word});
            else if (word == "EN") tokens.push_back({EN, word});
            else if (word == "FORMATO") tokens.push_back({FORMATO, word});
            else if (word == "FECHA") tokens.push_back({FECHA, word});
            else tokens.push_back({UNKNOWN, word});
        }
        // Cadenas entre comillas
        else if (c == '"') {
            string str;
            while (in.peek() != '"' && in.peek() != EOF) {
                in.get(c);
                str += c;
            }
            in.get(); // consumir comilla final
            tokens.push_back({STRING, str});
        }
        // Números
        else if (isdigit(c)) {
            string num(1, c);
            while (isdigit(in.peek())) {
                in.get(c);
                num += c;
            }
            tokens.push_back({NUMBER, num});
        }
        else {
            tokens.push_back({UNKNOWN, string(1, c)});
        }
    }

    tokens.push_back({END, ""});
    return tokens;
}