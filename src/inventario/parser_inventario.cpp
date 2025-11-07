#include "inventario.h"
#include <iostream>
using namespace std;

class Parser {
    vector<Token> tokens;
    int pos;

public:
    Parser(const vector<Token>& t) : tokens(t), pos(0) {}

    Token current() { return tokens[pos]; }

    void advance() {
        if (pos < tokens.size()) pos++;
    }

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

        if (!match(LBRACE)) {
            cerr << "Falta '{' despues de TRANSFERIR.\n";
            hasError = true;
        }

        while (current().type != RBRACE &&
               current().type != END &&
               current().type != TRANSFERIR &&
               current().type != INGRESAR &&
               current().type != CONSULTAR &&
               current().type != EXPORTAR) {

            if (match(PRENDA)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta valor para PRENDA.\n";
            }
            else if (match(TALLA)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta valor para TALLA.\n";
            }
            else if (match(CANTIDAD)) {
                match(COLON);
                if (!match(NUMBER)) cerr << "Falta numero en CANTIDAD.\n";
            }
            else if (match(DE)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta almacen origen.\n";
            }
            else if (match(A)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta almacen destino.\n";
            }
            else if (match(FECHA)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta fecha.\n";
            }
            else {
                cerr << "Token inesperado dentro de TRANSFERIR: " << current().value << endl;
                advance();
                hasError = true;
            }
        }

        if (!match(RBRACE)) {
            cerr << "Falta '}' al final de TRANSFERIR.\n";
            hasError = true;
        }

        if (!hasError)
            cout << "TRANSFERIR valido\n";
        else
            cout << "TRANSFERIR con errores internos\n";

        return true;
    }

    bool parseIngresar() {
        if (!match(INGRESAR)) return false;
        bool hasError = false;

        if (!match(LBRACE)) {
            cerr << "Falta '{' despues de INGRESAR.\n";
            hasError = true;
        }

        while (current().type != RBRACE &&
               current().type != END &&
               current().type != TRANSFERIR &&
               current().type != INGRESAR &&
               current().type != CONSULTAR &&
               current().type != EXPORTAR) {

            if (match(PRENDA)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta valor para PRENDA.\n";
            }
            else if (match(TALLA)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta valor para TALLA.\n";
            }
            else if (match(CANTIDAD)) {
                match(COLON);
                if (!match(NUMBER)) cerr << "Falta numero en CANTIDAD.\n";
            }
            else if (match(A)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta destino en A.\n";
            }
            else {
                cerr << "Token inesperado dentro de INGRESAR: " << current().value << endl;
                advance();
                hasError = true;
            }
        }

        if (!match(RBRACE)) {
            cerr << "Falta '}' al final de INGRESAR.\n";
            hasError = true;
        }

        if (!hasError)
            cout << "INGRESAR valido\n";
        else
            cout << "INGRESAR con errores internos\n";

        return true;
    }

    bool parseConsultar() {
        if (!match(CONSULTAR)) return false;
        bool hasError = false;

        if (!match(LBRACE)) {
            cerr << "Falta '{' despues de CONSULTAR.\n";
            hasError = true;
        }

        while (current().type != RBRACE &&
               current().type != END &&
               current().type != TRANSFERIR &&
               current().type != INGRESAR &&
               current().type != CONSULTAR &&
               current().type != EXPORTAR) {

            if (match(PRENDA)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta valor para PRENDA.\n";
            }
            else if (match(EN)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta ubicacion en EN.\n";
            }
            else {
                cerr << "Token inesperado dentro de CONSULTAR: " << current().value << endl;
                advance();
                hasError = true;
            }
        }

        if (!match(RBRACE)) {
            cerr << "Falta '}' al final de CONSULTAR.\n";
            hasError = true;
        }

        if (!hasError)
            cout << "CONSULTAR valido\n";
        else
            cout << "CONSULTAR con errores internos\n";

        return true;
    }

    bool parseExportar() {
        if (!match(EXPORTAR)) return false;
        bool hasError = false;

        if (!match(LBRACE)) {
            cerr << "Falta '{' despues de EXPORTAR.\n";
            hasError = true;
        }

        while (current().type != RBRACE &&
               current().type != END &&
               current().type != TRANSFERIR &&
               current().type != INGRESAR &&
               current().type != CONSULTAR &&
               current().type != EXPORTAR) {

            if (match(FORMATO)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta formato de exportacion.\n";
            }
            else if (match(FECHA)) {
                match(COLON);
                if (!match(STRING)) cerr << "Falta fecha de exportacion.\n";
            }
            else {
                cerr << "Token inesperado dentro de EXPORTAR: " << current().value << endl;
                advance();
                hasError = true;
            }
        }

        if (!match(RBRACE)) {
            cerr << "Falta '}' al final de EXPORTAR.\n";
            hasError = true;
        }

        if (!hasError)
            cout << "EXPORTAR valido\n";
        else
            cout << "EXPORTAR con errores internos\n";

        return true;
    }

    void parse() {
        bool errorFound = false;

        while (current().type != END) {
            if (parseTransferir()) {}
            else if (parseIngresar()) {}
            else if (parseConsultar()) {}
            else if (parseExportar()) {}
            else {
                cerr << "Error de sintaxis cerca de: " << current().value << endl;
                errorFound = true;

                while (current().type != TRANSFERIR &&
                       current().type != INGRESAR &&
                       current().type != CONSULTAR &&
                       current().type != EXPORTAR &&
                       current().type != END) {
                    advance();
                }
            }
        }

        if (!errorFound)
            cout << "Analisis completado sin errores.\n";
        else
            cout << "Se detectaron errores durante el analisis.\n";
    }
};

int main() {
    string filename = "src/inventario/tests/test_inventario_02.txt";

    vector<Token> tokens = lexerInventario(filename);

    cout << "=== TOKENS ===" << endl;
    for (auto &t : tokens)
        cout << t.value << " -> " << tokenTypeToString(t.type) << endl;

    cout << "\n=== ANALISIS SINTACTICO ===" << endl;
    Parser parser(tokens);
    parser.parse();

    return 0;
}