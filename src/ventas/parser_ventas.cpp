#include "Gestion de Clientes y Ventas.cpp"
#include <iostream>
#include <string>
#include <vector>
#include "Token.cpp"
#include "Lexer.cpp"

using namespace std;

class ParserVentas {
private:
    LexerVentas lexer;
    Token actual;
    vector<cliente> clientes;
    vector<ventas> ventas_reg;
    vector<gastos_realizados> gastos;
    vector<pagos_realizados> pagos;
    vector<salarios> salarios_list;
public:
    ParserVentas(const string& input) : lexer(input) {
        actual = lexer.siguiente();
    }
    void avanzar() {
        actual = lexer.siguiente();
    }
    bool coincidir(TokenType tipo) {
        if (actual.tipo == tipo) {
            avanzar();
            return true;
        }
        return false;
    }
    void error(const string& msg) {
        cout << "Error Sintactico: " << msg << " en linea " << actual.linea << endl;
        exit(1);
    }

    string consumirCadena() {
        if (actual.tipo == TokenType::CADENA) {
            string val = actual.lexema;
            avanzar();
            return val;
        }
        error("No hay cadena");
        return "";
    }

    double consumirNumero() {
        if (actual.tipo == TokenType::NUMERO) {
            double val = stod(actual.lexema)
                avanzar();
            return valor;
        }
        error("No hya numero");
        return 0;
    }

    void parsear() {
        while (actual.tipo != TokenType::FIN_ARCHIVO) {
            if (actual.tipo == TokenType::REGISTRAR_CLIENTE) {
                parsearRegistrarCliente();
            }
            else if (actual.tipo == TokenType::REGISTRAR_VENTA) {
                parsearRegistrarVenta();
            }
            else if (actual.tipo == TokenType::REGISTRAR_GASTO) {
                parsearRegistrarGasto();
            }
            else if (actual.tipo == TokenType::REGISTRAR_PAGO) {
                parsearRegistrarPago();
            }
            else if (actual.tipo == TokenType::REGISTRAR_SALARIO) {
                parsearRegistrarSalario();
            }
            else if (actual.tipo == TokenType::GENERAR_REPORTE) {
                parsearGenerarReporte();
            }
            else {
                error("Instrucci�n no reconocida");
            }
        }
    }

    void parsearRegistrarCliente() {
        avanzar();
        if (!coincidir(TokenType::PARENTESIS_IZQ)) {
            error("Falta '('");
        }
        string nom = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string dni = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string correo = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string direccion = consumirCadena();
        if (!coincidir(TokenType::PARENTESIS_DER)) {
            error("Falta ')'");
        }
        if (!coincidir(TokenType::FIN_SENTENCIA)) {
            error("Falta ';'");
        }
        cliente c(clientes.size() + 1, nom, dni, correo, direccion);
        clientes.push_back(c);
        cout << "Cliente registrado: " << nom << endl;
    }
    void parsearRegistrarVenta() {
        avanzar();
        if (!coincidir(TokenType::PARENTESIS_IZQ)) {
            error("Falta '('");
        }
        string nom = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        double precio = consumirNumero();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        double desc = consumirNumero();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string metodo = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string fecha = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string estado = consumirCadena();
        if (!coincidir(TokenType::PARENTESIS_DER)) {
            error("Falta ')'");
        }
        if (!coincidir(TokenType::FIN_SENTENCIA)) {
            error("Falta ';'");
        }
        ventas c(ventas_reg.size() + 1, nom, precio, desc, metodo, fecha, estado);
        ventas_reg.push_back(c);
        cout << "Venta registrada: " << nom << endl;
    }
    void parsearRegistrarGasto() {
        avanzar();
        if (!coincidir(TokenType::PARENTESIS_IZQ)) {
            error("Falta '('");
        }
        string detalle = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string fecha = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string estado = consumirCadena();
        if (!coincidir(TokenType::PARENTESIS_DER)) {
            error("Falta ')'");
        }
        if (!coincidir(TokenType::FIN_SENTENCIA)) {
            error("Falta ';'");
        }
        gastos_realizados c(gastos.size() + 1, detalle, fecha, estado);
        gastos.push_back(c);
        cout << "Gasto registrado: " << detalle << endl;
    }
    void parsearRegistrarPago() {
        avanzar();
        if (!coincidir(TokenType::PARENTESIS_IZQ)) {
            error("Falta '('");
        }
        string detalle = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string tipo = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        double monto = consumirNumero();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string fecha = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string estado = consumirCadena();
        if (!coincidir(TokenType::PARENTESIS_DER)) {
            error("Falta ')'");
        }
        if (!coincidir(TokenType::FIN_SENTENCIA)) {
            error("Falta ';'");
        }
        pagos_realizados c(pagos.size() + 1, detalle, tipo, monto, fecha, estado);
        pagos.push_back(c);
        cout << "Pago registrado: " << detalle << endl;
    }
    void parsearRegistrarSalario() {
        avanzar();
        if (!coincidir(TokenType::PARENTESIS_IZQ)) {
            error("Falta '('");
        }
        double monto = consumirNumero();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        double bono = consumirNumero();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string nom = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string detalle = consumirCadena();
        if (!coincidir(TokenType::COMA)) {
            error("Falta ','");
        }
        string estado = consumirCadena();
        if (!coincidir(TokenType::PARENTESIS_DER)) {
            error("Falta ')'");
        }
        if (!coincidir(TokenType::FIN_SENTENCIA)) {
            error("Falta ';'");
        }
        salarios c(salarios_list() + 1, monto, bono, nom, detalle, estado);
        salarios_list.push_back(c);
        cout << "Salario registrado: " << monto << " a " << nom << " con un " << bono << endl;
    }
    void parsearGenerarReporte() {
        avanzar();
        cout << "Generando reporte general..." << endl;
    }

};

int parse_ventas() {
    ParserVentas parser(input);
    parser.parsear();
    return 0;
}
