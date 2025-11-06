// parser_inventario.cpp - placeholder
#include <iostream>
#include <vector>
#include "inventario.h"
using namespace std;

class ParserInventario {
    vector<Token> tokens;
    int pos;

public:
    ParserInventario(const vector<Token>& t) : tokens(t), pos(0) {}

    Token current() { return tokens[pos]; }
    void advance() { if (pos < tokens.size()) pos++; }

    bool match(TokenType type) {
        if (current().type == type) {
            advance();
            return true;
        }
        return false;
    }

    // === Reglas de Producción ===
    bool parseTransferencia() {
        if (match(TRANSFERIR)) {
            if (match(STRING) && match(TALLA) && match(STRING) && match(CANTIDAD)
                && match(NUMBER) && match(DE) && match(STRING)
                && match(A) && match(STRING) && match(FECHA) && match(STRING)) {
                cout << "Instruccion TRANSFERIR valida\n";
                return true;
            }
        }
        return false;
    }

    bool parseIngreso() {
        if (match(INGRESAR)) {
            if (match(STRING) && match(TALLA) && match(STRING) &&
                match(CANTIDAD) && match(NUMBER) && match(A) && match(STRING)) {
                cout << "Instruccion INGRESAR valida\n";
                return true;
            }
        }
        return false;
    }

    bool parseConsulta() {
        if (match(CONSULTAR)) {
            if (match(STRING) && match(EN) && match(STRING)) {
                cout << "Instruccion CONSULTAR valida\n";
                return true;
            }
        }
        return false;
    }

    bool parseExportar() {
        if (match(EXPORTAR)) {
            if (match(FORMATO) && match(STRING) && match(FECHA) && match(STRING)) {
                cout << "Instruccion EXPORTAR valida\n";
                return true;
            }
        }
        return false;
    }

    bool parseAjuste() {
        if (match(AJUSTAR)) {
            if (match(STRING) && match(TALLA) && match(STRING)
                && match(CANTIDAD) && match(NUMBER) && match(EN) && match(STRING)) {
                cout << "Instruccion AJUSTAR valida\n";
                return true;
            }
        }
        return false;
    }

    void parse() {
        while (current().type != END) {
            if (parseTransferencia() || parseIngreso() || parseConsulta()
                || parseExportar() || parseAjuste()) {
                continue;
            } else {
                cerr << "Error de sintaxis cerca de: " << current().value << endl;
                break;
            }
        }
    }
};

// === Main para pruebas ===
int main() {
    string filename = "src/inventario/tests/test_inventario_02.txt";
    vector<Token> tokens = lexerInventario(filename);

    cout << "=== TOKENS ===\n";
    for (const auto& t : tokens)
        cout << t.value << " -> " << tokenTypeToString(t.type) << endl;

    cout << "\n=== ANALISIS SINTACTICO ===\n";
    ParserInventario parser(tokens);
    parser.parse();

    return 0;
}