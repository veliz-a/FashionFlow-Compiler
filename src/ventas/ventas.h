#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

enum class TokenType {
    //Palabras clave
    REGISTRAR_CLIENTE, REGISTRAR_VENTA, REGISTRAR_GASTO, REGISTRAR_PAGO, REGISTRAR_SALARIO, GENERAR_REPORTE,
    //Simbolos
    PARENTESIS_IZQ, PERENTESIS_DER, COMA, FIN_SETENCIA,
    //Literales
    CADENA, NUMERO,
    //Control
    FIN_ARCHIVO, ERROR
};

struct Token {
    TokenType type;
    string lexema;
    int fila;
    int columna;

    string tostring() const {
        cout << "Token(" + lexema + ")";
    }
};
