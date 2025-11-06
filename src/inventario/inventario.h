#ifndef INVENTARIO_H
#define INVENTARIO_H

// Cabeceras y tipos para módulo Inventario (placeholder)
#include <string>
#include <vector>
using namespace std;

enum TokenType {
    TRANSFERIR, INGRESAR, CONSULTAR, EXPORTAR,
    PRENDA, TALLA, CANTIDAD, DE, A, EN, FORMATO, FECHA,
    LBRACE, RBRACE, COLON,
    STRING, NUMBER,
    END, UNKNOWN
};

struct Token {
    TokenType type;
    string value;
};

vector<Token> lexerInventario(const string& filename);
string tokenTypeToString(TokenType type);

#endif // INVENTARIO_H
