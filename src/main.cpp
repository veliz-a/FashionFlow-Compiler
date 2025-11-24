/**
 * FashionFlow Compiler - Sistema Integrado
 * Grupo 2: Hugo Ramos, Sofia Solari, Alejandra Veliz
 * Curso: Compiladores PREISF07C01M
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

void mostrarBanner() {
    cout << "\n========================================\n";
    cout << "  FashionFlow Compiler System v1.0\n";
    cout << "  Nancy's Collection\n";
    cout << "========================================\n\n";
}

void mostrarMenu() {
    cout << "MENU PRINCIPAL\n";
    cout << "--------------------\n";
    cout << "1. Compilador de PRODUCCION\n";
    cout << "2. Compilador de INVENTARIO\n";
    cout << "3. Compilador de VENTAS\n";
    cout << "4. Informacion del proyecto\n";
    cout << "0. Salir\n";
    cout << "--------------------\n";
}

void mostrarInfo() {
    system("cls");
    cout << "\nINFORMACION DEL PROYECTO\n";
    cout << "========================\n\n";
    cout << "Proyecto: FashionFlow Compiler\n";
    cout << "Empresa: Nancy's Collection\n\n";
    cout << "MODULOS:\n";
    cout << "1. PRODUCCION (Alejandra Veliz) - Flex/Bison\n";
    cout << "   Ordenes de produccion, corte y confeccion\n\n";
    cout << "2. INVENTARIO (Sofia Solari) - C++\n";
    cout << "   Transferencias, ingresos, consultas\n\n";
    cout << "3. VENTAS (Hugo Ramos) - Flex/Bison\n";
    cout << "   Clientes, ventas, gastos, reportes\n\n";
    cout << "Curso: Compiladores PREISF07C01M\n";
    cout << "Docente: Javier Antonio Dioses Zarate\n\n";
    cout << "Presione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int ejecutarProduccion() {
    int continuar = 1;
    
    while (continuar) {
        system("cls");
        cout << "\nMODULO DE PRODUCCION\n";
        cout << "====================\n\n";
        cout << "1. Registrar nueva orden de produccion\n";
        cout << "2. Ver ejemplo de orden (prueba basica)\n";
        cout << "3. Ver ejemplo completo (prueba avanzada)\n";
        cout << "4. Ver ordenes guardadas (CSV)\n";
        cout << "0. Volver al menu principal\n";
        cout << "\nSeleccione opcion: ";
        
        string opcion;
        getline(cin, opcion);
        
        if (opcion == "0") return 0;
        
        string archivo;
        if (opcion == "1") {
            archivo = "temp_produccion_registrar.txt";
            system(("notepad.exe " + archivo).c_str());
            cout << "Presione ENTER para procesar...";
            cin.get();
        } else if (opcion == "2") {
            archivo = "src\\produccion\\casos_prueba\\caso_prueba_produccion_01.txt";
        } else if (opcion == "3") {
            archivo = "src\\produccion\\casos_prueba\\caso_prueba_produccion_02.txt";
        } else if (opcion == "4") {
            system("start notepad.exe produccion_ordenes.csv");
            cout << "\nPresione ENTER para continuar...";
            cin.get();
            continue;
        } else {
            cout << "\nOpcion invalida. Presione ENTER...";
            cin.get();
            continue;
        }
        
        cout << "\nProcesando orden...\n\n";
        string cmd = "src\\produccion\\produccion.exe \"" + archivo + "\"";
        int resultado = system(cmd.c_str());
        
        if (opcion == "1") {
            // Guardar timestamp y datos basicos en CSV
            ofstream csv("produccion_ordenes.csv", ios::app);
            time_t now = time(0);
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
            
            // Generar codigo de orden basado en timestamp
            char codigo[30];
            strftime(codigo, sizeof(codigo), "ORD_%Y%m%d_%H%M%S", localtime(&now));
            
            // Formato: Timestamp,Codigo_Orden,Estado
            if (resultado == 0) {
                csv << timestamp << "," << codigo << ",EXITO\n";
            } else {
                csv << timestamp << "," << codigo << ",ERROR\n";
            }
            csv.close();
            
            if (resultado == 0) {
                cout << "\nOrden procesada correctamente y guardada en produccion_ordenes.csv\n";
            } else {
                cout << "\nERROR: La orden tiene errores de sintaxis. Revise el archivo.\n";
            }
            
            // Esperar antes de limpiar para evitar advertencia de notepad
            this_thread::sleep_for(chrono::seconds(2));
            
            // Limpiar archivo temporal SIEMPRE
            ofstream limpiar(archivo, ios::trunc);
            if (limpiar.is_open()) {
                limpiar << "// INSTRUCCIONES: Registre su orden de produccion aqui\n";
                limpiar << "// Despues de guardar y cerrar, el sistema procesara y limpiara este archivo automaticamente\n";
                limpiar << "//\n";
                limpiar << "// EJEMPLO (puede poner las tallas y colores que necesite):\n";
                limpiar << "// ORDEN ORD-001 {\n";
                limpiar << "//     DISENO: BLUSA-VER-023\n";
                limpiar << "//     TALLAS: [S, M, L]\n";
                limpiar << "//     COLORES: [Azul, Blanco]\n";
                limpiar << "//     CANTIDADES: [10, 15, 20, 8, 12, 5]\n";
                limpiar << "// }\n";
                limpiar << "//\n";
                limpiar << "// Escriba su orden debajo de esta linea:\n";
                limpiar << "// ===============================================\n\n";
                limpiar.close();
            }
        }
        
        cout << "\nPresione ENTER para continuar...";
        cin.get();
    }
    
    return 0;
}

int ejecutarInventario() {
    int continuar = 1;
    
    while (continuar) {
        system("cls");
        cout << "\nMODULO DE INVENTARIO\n";
        cout << "====================\n\n";
        cout << "1. Registrar nueva transferencia\n";
        cout << "2. Ver ejemplo de transferencia (prueba basica)\n";
        cout << "3. Ver ejemplo completo (prueba avanzada)\n";
        cout << "4. Ver movimientos guardados (CSV)\n";
        cout << "0. Volver al menu principal\n";
        cout << "\nSeleccione opcion: ";
        
        string opcion;
        getline(cin, opcion);
        
        if (opcion == "0") return 0;
        
        string archivo;
        if (opcion == "1") {
            archivo = "temp_inventario_registrar.txt";
            system(("notepad.exe " + archivo).c_str());
            cout << "Presione ENTER para procesar...";
            cin.get();
        } else if (opcion == "2") {
            archivo = "src\\inventario\\tests\\test_inventario_01.txt";
        } else if (opcion == "3") {
            archivo = "src\\inventario\\tests\\test_inventario_02.txt";
        } else if (opcion == "4") {
            system("start notepad.exe inventario_movimientos.csv");
            cout << "\nPresione ENTER para continuar...";
            cin.get();
            continue;
        } else {
            cout << "\nOpcion invalida. Presione ENTER...";
            cin.get();
            continue;
        }
        
        cout << "\nProcesando movimiento...\n\n";
        string cmd = "src\\inventario\\inventario.exe \"" + archivo + "\"";
        int resultado = system(cmd.c_str());
        
        if (opcion == "1") {
            ofstream csv("inventario_movimientos.csv", ios::app);
            time_t now = time(0);
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
            
            // Formato: Timestamp,Tipo_Operacion,Estado
            if (resultado == 0) {
                csv << timestamp << ",Transferencia,EXITO\n";
            } else {
                csv << timestamp << ",Transferencia,ERROR\n";
            }
            csv.close();
            
            if (resultado == 0) {
                cout << "\nMovimiento procesado correctamente y guardado en inventario_movimientos.csv\n";
            } else {
                cout << "\nERROR: El movimiento tiene errores de sintaxis. Revise el archivo.\n";
            }
            
            // Esperar antes de limpiar para evitar advertencia de notepad
            this_thread::sleep_for(chrono::seconds(2));
            
            // Limpiar archivo temporal SIEMPRE
            ofstream limpiar(archivo, ios::trunc);
            if (limpiar.is_open()) {
                limpiar << "// INSTRUCCIONES: Registre su movimiento de inventario aqui\n";
                limpiar << "// Despues de guardar y cerrar, el sistema procesara y limpiara este archivo automaticamente\n";
                limpiar << "//\n";
                limpiar << "// EJEMPLO:\n";
                limpiar << "// TRANSFERIR {\n";
                limpiar << "//     PRENDA: \"Blusa Floral\"\n";
                limpiar << "//     TALLA: \"M\"\n";
                limpiar << "//     CANTIDAD: 15\n";
                limpiar << "//     DE: \"Almacen Central\"\n";
                limpiar << "//     A: \"Tienda Lima\"\n";
                limpiar << "//     FECHA: \"2025-11-23\"\n";
                limpiar << "// }\n";
                limpiar << "//\n";
                limpiar << "// Escriba su transferencia debajo de esta linea:\n";
                limpiar << "// ===============================================\n\n";
                limpiar.close();
            }
        }
        
        cout << "\nPresione ENTER para continuar...";
        cin.get();
    }
    
    return 0;
}

int ejecutarVentas() {
    int continuar = 1;
    
    while (continuar) {
        system("cls");
        cout << "\nMODULO DE VENTAS\n";
        cout << "================\n\n";
        cout << "1. Registrar nueva venta\n";
        cout << "2. Ver ejemplo de venta (prueba basica)\n";
        cout << "3. Ver ejemplo completo (prueba avanzada)\n";
        cout << "4. Ver ventas guardadas (CSV)\n";
        cout << "0. Volver al menu principal\n";
        cout << "\nSeleccione opcion: ";
        
        string opcion;
        getline(cin, opcion);
        
        if (opcion == "0") return 0;
        
        string archivo;
        if (opcion == "1") {
            archivo = "temp_ventas_registrar.txt";
            system(("notepad.exe " + archivo).c_str());
            cout << "Presione ENTER para procesar...";
            cin.get();
        } else if (opcion == "2") {
            archivo = "src\\ventas\\tests\\test_ventas_01.txt";
        } else if (opcion == "3") {
            archivo = "src\\ventas\\tests\\test_ventas_02.txt";
        } else if (opcion == "4") {
            system("start notepad.exe ventas_registro.csv");
            cout << "\nPresione ENTER para continuar...";
            cin.get();
            continue;
        } else {
            cout << "\nOpcion invalida. Presione ENTER...";
            cin.get();
            continue;
        }
        
        cout << "\nProcesando venta...\n\n";
        string cmd = "src\\ventas\\ventas.exe \"" + archivo + "\"";
        int resultado = system(cmd.c_str());
        
        if (opcion == "1") {
            ofstream csv("ventas_registro.csv", ios::app);
            time_t now = time(0);
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
            
            // Generar codigo de venta basado en timestamp
            char codigo[30];
            strftime(codigo, sizeof(codigo), "VNT_%Y%m%d_%H%M%S", localtime(&now));
            
            // Formato: Timestamp,Codigo_Venta,Estado
            if (resultado == 0) {
                csv << timestamp << "," << codigo << ",EXITO\n";
            } else {
                csv << timestamp << "," << codigo << ",ERROR\n";
            }
            csv.close();
            
            if (resultado == 0) {
                cout << "\nVenta procesada correctamente y guardada en ventas_registro.csv\n";
            } else {
                cout << "\nERROR: La venta tiene errores de sintaxis. Revise el archivo.\n";
            }
            
            // Esperar antes de limpiar para evitar advertencia de notepad
            this_thread::sleep_for(chrono::seconds(2));
            
            // Limpiar archivo temporal SIEMPRE
            ofstream limpiar(archivo, ios::trunc);
            if (limpiar.is_open()) {
                limpiar << "// INSTRUCCIONES: Registre su venta aqui\n";
                limpiar << "// Despues de guardar y cerrar, el sistema procesara y limpiara este archivo automaticamente\n";
                limpiar << "//\n";
                limpiar << "// EJEMPLO:\n";
                limpiar << "// Registrar_Cliente(\"Maria Lopez\", \"987654321\", \"maria@email.com\", \"Av. Larco 123\");\n";
                limpiar << "// Registrar_Venta(\"VNT001\", 89.90, 1, \"Blusa Floral\", \"M\", \"2025-11-23\");\n";
                limpiar << "// Registrar_Pago(\"Maria Lopez\", \"Efectivo\", 89.90, \"VNT001\", \"2025-11-23\");\n";
                limpiar << "// Generar_Reporte;\n";
                limpiar << "//\n";
                limpiar << "// Escriba su venta debajo de esta linea:\n";
                limpiar << "// ===============================================\n\n";
                limpiar.close();
            }
        }
        
        cout << "\nPresione ENTER para continuar...";
        cin.get();
    }
    
    return 0;
}


int main(int argc, char** argv) {
    // Modo linea de comandos
    if (argc > 1) {
        string modulo = argv[1];
        string archivo = (argc > 2) ? argv[2] : "";
        
        if (modulo == "produccion") {
            string cmd = "src\\produccion\\produccion.exe " + archivo;
            return system(cmd.c_str());
        } else if (modulo == "inventario") {
            string cmd = "src\\inventario\\inventario.exe " + archivo;
            return system(cmd.c_str());
        } else if (modulo == "ventas") {
            string cmd = "src\\ventas\\ventas.exe " + archivo;
            return system(cmd.c_str());
        } else {
            cerr << "Uso: " << argv[0] << " [produccion|inventario|ventas] [archivo]\n";
            return 1;
        }
    }
    
    // Modo interactivo
    int opcion;
    
    do {
        system("cls");
        mostrarBanner();
        mostrarMenu();
        
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1:
                ejecutarProduccion();
                break;
            case 2:
                ejecutarInventario();
                break;
            case 3:
                ejecutarVentas();
                break;
            case 4:
                mostrarInfo();
                break;
            case 0:
                cout << "\nGracias por usar FashionFlow Compiler\n";
                break;
            default:
                cout << "\nOpcion invalida\n";
                cout << "Presione ENTER para continuar...";
                cin.get();
        }
        
    } while (opcion != 0);
    
    return 0;
}
