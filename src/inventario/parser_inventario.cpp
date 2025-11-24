#include "inventario.h"
#include <iostream>
using namespace std;

class Parser {
    vector<Token> tokens;
    int pos;

public:
    Parser(const vector<Token>& t) : tokens(t), pos(0) {}

    Token current() { return tokens[pos]; }

    void advance() { if (pos < tokens.size()) pos++; }

    bool match(TokenType type) {
        if (current().type == type) {
            advance();
            return true;
        }
        return false;
    }

    bool parseTransferir() {
        if (!match(TRANSFERIR)) return false;
        bool hasError = false;

        if (!match(LBRACE)) { cerr << "Falta '{' despues de TRANSFERIR.\n"; hasError = true; }

        while (current().type != RBRACE && current().type != END &&
               current().type != TRANSFERIR && current().type != INGRESAR &&
               current().type != CONSULTAR && current().type != EXPORTAR) {

            if (match(PRENDA)) { match(COLON); if (!match(STRING)) cerr << "Falta valor para PRENDA.\n"; }
            else if (match(TALLA)) { match(COLON); if (!match(STRING)) cerr << "Falta valor para TALLA.\n"; }
            else if (match(CANTIDAD)) { match(COLON); if (!match(NUMBER)) cerr << "Falta numero en CANTIDAD.\n"; }
            else if (match(DE)) { match(COLON); if (!match(STRING)) cerr << "Falta almacen origen.\n"; }
            else if (match(A)) { match(COLON); if (!match(STRING)) cerr << "Falta almacen destino.\n"; }
            else if (match(FECHA)) { match(COLON); if (!match(STRING)) cerr << "Falta fecha.\n"; }
            else { cerr << "Token inesperado dentro de TRANSFERIR: " << current().value << endl; advance(); hasError = true; }
        }

        if (!match(RBRACE)) { cerr << "Falta '}' al final de TRANSFERIR.\n"; hasError = true; }

        cout << (hasError ? "TRANSFERIR con errores internos\n" : "TRANSFERIR valido\n");
        return !hasError;
    }

    bool parseIngresar() {
        if (!match(INGRESAR)) return false;
        bool hasError = false;

        if (!match(LBRACE)) { cerr << "Falta '{' despues de INGRESAR.\n"; hasError = true; }

        while (current().type != RBRACE && current().type != END &&
               current().type != TRANSFERIR && current().type != INGRESAR &&
               current().type != CONSULTAR && current().type != EXPORTAR) {

            if (match(CODIGO)) { match(COLON); if (!match(STRING)) cerr << "Falta valor para CODIGO.\n"; }
            else if (match(PRENDA)) { match(COLON); if (!match(STRING)) cerr << "Falta valor para PRENDA.\n"; }
            else if (match(DESCRIPCION)) { match(COLON); if (!match(STRING)) cerr << "Falta valor para DESCRIPCION.\n"; }
            else if (match(TALLA)) { match(COLON); if (!match(STRING)) cerr << "Falta valor para TALLA.\n"; }
            else if (match(A)) { match(COLON); if (!match(STRING)) cerr << "Falta destino en A.\n"; }
            else { cerr << "Token inesperado dentro de INGRESAR: " << current().value << endl; advance(); hasError = true; }
        }

        if (!match(RBRACE)) { cerr << "Falta '}' al final de INGRESAR.\n"; hasError = true; }

        cout << (hasError ? "INGRESAR con errores internos\n" : "INGRESAR valido\n");
        return !hasError;
    }

    bool parseConsultar() {
        if (!match(CONSULTAR)) return false;
        bool hasError = false;

        if (!match(LBRACE)) { cerr << "Falta '{' despues de CONSULTAR.\n"; hasError = true; }

        while (current().type != RBRACE && current().type != END &&
               current().type != TRANSFERIR && current().type != INGRESAR &&
               current().type != CONSULTAR && current().type != EXPORTAR) {

            if (match(PRENDA)) { match(COLON); if (!match(STRING)) cerr << "Falta valor para PRENDA.\n"; }
            else if (match(EN)) { match(COLON); if (!match(STRING)) cerr << "Falta ubicacion en EN.\n"; }
            else { cerr << "Token inesperado dentro de CONSULTAR: " << current().value << endl; advance(); hasError = true; }
        }

        if (!match(RBRACE)) { cerr << "Falta '}' al final de CONSULTAR.\n"; hasError = true; }

        cout << (hasError ? "CONSULTAR con errores internos\n" : "CONSULTAR valido\n");
        return !hasError;
        return true;
    }

    bool parseExportar() {
        if (!match(EXPORTAR)) return false;
        bool hasError = false;

        if (!match(LBRACE)) { cerr << "Falta '{' despues de EXPORTAR.\n"; hasError = true; }

        while (current().type != RBRACE && current().type != END &&
               current().type != TRANSFERIR && current().type != INGRESAR &&
               current().type != CONSULTAR && current().type != EXPORTAR) {

            if (match(FORMATO)) { match(COLON); if (!match(STRING)) cerr << "Falta formato de exportacion.\n"; }
            else if (match(FECHA)) { match(COLON); if (!match(STRING)) cerr << "Falta fecha de exportacion.\n"; }
            else { cerr << "Token inesperado dentro de EXPORTAR: " << current().value << endl; advance(); hasError = true; }
        }

        if (!match(RBRACE)) { cerr << "Falta '}' al final de EXPORTAR.\n"; hasError = true; }

        cout << (hasError ? "EXPORTAR con errores internos\n" : "EXPORTAR valido\n");
        return !hasError;
    }

    void parse() {
        bool errorFound = false;

        while (current().type != END) {
            bool result = false;
            if (current().type == TRANSFERIR) result = parseTransferir();
            else if (current().type == INGRESAR) result = parseIngresar();
            else if (current().type == CONSULTAR) result = parseConsultar();
            else if (current().type == EXPORTAR) result = parseExportar();
            else {
                cerr << "Error de sintaxis cerca de: " << current().value << endl;
                errorFound = true;
                while (current().type != TRANSFERIR && current().type != INGRESAR &&
                       current().type != CONSULTAR && current().type != EXPORTAR &&
                       current().type != END) advance();
                continue;
            }
            
            if (!result) errorFound = true;
        }

        if (errorFound) {
            cout << "Se detectaron errores durante el analisis.\n";
            exit(1);
        } else {
            cout << "Analisis completado sin errores.\n";
        }
    }
};

int main() {
    string filename = "src/inventario/tests/test_inventario_02.txt";
    vector<Token> tokens = lexerInventario(filename);

    cout << "=== TOKENS ===\n";
    for (auto &t : tokens)
        cout << t.value << " -> " << tokenTypeToString(t.type) << endl;

    cout << "\n=== ANALISIS SINTACTICO ===\n";
    Parser parser(tokens);
    parser.parse();

    return 0;
}