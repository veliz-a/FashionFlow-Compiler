#include "inventario.h"
#include <iostream>
using namespace std;

class ParserInventario {
    vector<Token> tokens;
    int pos;

public:
    ParserInventario(const vector<Token>& t) : tokens(t), pos(0) {}

    Token current() { return tokens[pos]; }
    void advance() { if (pos < tokens.size()) pos++; }
    bool match(TokenType type) {
        if (current().type == type) { advance(); return true; }
        return false;
    }

    bool parseBloque() {
        if (!match(LBRACE)) return false;
        while (current().type != RBRACE && current().type != END) {
            if (!parseAtributo()) return false;
        }
        return match(RBRACE);
    }

    bool parseAtributo() {
        if (match(PRENDA) || match(TALLA) || match(CANTIDAD) ||
            match(DE) || match(A) || match(EN) ||
            match(FORMATO) || match(FECHA)) {
            if (!match(COLON)) return false;
            if (match(STRING) || match(NUMBER)) return true;
        }
        return false;
    }

    bool parseTransferir() {
        if (match(TRANSFERIR)) return parseBloque();
        return false;
    }

    bool parseIngresar() {
        if (match(INGRESAR)) return parseBloque();
        return false;
    }

    bool parseConsultar() {
        if (match(CONSULTAR)) return parseBloque();
        return false;
    }

    bool parseExportar() {
        if (match(EXPORTAR)) return parseBloque();
        return false;
    }

    void parse() {
        while (current().type != END) {
            if (parseTransferir()) cout << " TRANSFERIR valido\n";
            else if (parseIngresar()) cout << " INGRESAR valido\n";
            else if (parseConsultar()) cout << " CONSULTAR valido\n";
            else if (parseExportar()) cout << " EXPORTAR valido\n";
            else {
                cerr << " Error de sintaxis cerca de: " << current().value << endl;
                break;
            }
        }
    }
};

// Main
int main() {
    string filename = "src/inventario/tests/test_inventario_01.txt";
    vector<Token> tokens = lexerInventario(filename);

    cout << "=== TOKENS ===\n";
    for (auto &t : tokens)
        cout << t.value << " -> " << tokenTypeToString(t.type) << endl;

    cout << "\n=== ANALISIS SINTACTICO ===\n";
    ParserInventario parser(tokens);
    parser.parse();

    return 0;
}