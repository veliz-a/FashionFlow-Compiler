# FashionFlow Compiler

Sistema de compiladores para automatizar procesos de produccion, inventario y ventas en Nancy's Collection.

## Equipo - Grupo 2

- Alejandra Veliz Garcia [2311640] - Produccion
- Sofia Solari Hipolito [2320632] - Inventario
- Hugo Ramos Nino Neira [2310120] - Ventas

Curso: Compiladores PREISF07C01M - Profesor Javier Antonio Dioses Zarate

## Estructura

```
src/
├── produccion/     # Modulo de produccion (Flex/Bison)
├── inventario/     # Modulo de inventario (C++)
├── ventas/         # Modulo de ventas (Flex/Bison)
└── main.cpp        # Sistema integrado
```

## Compilacion

```powershell
./compile_all.ps1
```

## Ejecucion

```powershell
./fashionflow.exe
```

Cada modulo ofrece:
1. **Registrar nueva operacion** - Abre editor para ingresar datos (Opcion principal)
2. Ver ejemplo basico - Ejecuta caso de prueba simple
3. Ver ejemplo completo - Ejecuta caso de prueba avanzado
4. **Ver registros guardados (CSV)** - Abre el archivo CSV con todas las operaciones

Archivos CSV generados:
- `produccion_ordenes.csv` - Ordenes de produccion
- `inventario_movimientos.csv` - Transferencias e ingresos
- `ventas_registro.csv` - Ventas y transacciones

Ver EJEMPLOS.md para sintaxis de cada lenguaje.
Ver BUILD.md para instrucciones de compilacion.

## Modulos

### 1. Produccion (Alejandra)
Ordenes de produccion, control de corte y confeccion.
- Archivos: `produccion.l`, `produccion.y`
- Pruebas: `casos_prueba/`

### 2. Inventario (Sofia)
Transferencias, ingresos y consultas de stock.
- Archivos: `lexer_inventario.cpp`, `parser_inventario.cpp`
- Pruebas: `tests/`

### 3. Ventas (Hugo)
Registro de clientes, ventas, gastos, pagos y salarios.
- Archivos: `Ventas.l`, `Ventas.y`
- Pruebas: `tests/`

## Documentacion

- `docs/avances_entregados/` - Gramaticas formales
- `BUILD.md` - Instrucciones de compilacion
