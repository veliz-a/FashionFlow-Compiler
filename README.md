# FashionFlow Compiler

Compilador integrado para gestión de producción, inventario y ventas en Nancy's Collection.

## Equipo - Grupo 2

- Alejandra Veliz Garcia [2311640] - Producción
- Sofia Solari Hipolito [2320632] - Inventario
- Hugo Ramos Nino Neira [2310120] - Ventas

Curso: Compiladores PREISF07C01M - Profesor Javier Antonio Dioses Zarate

## Características

- **Sistema Integrado**: Interfaz unificada para los tres módulos
- **Persistencia CSV**: Registros automáticos en archivos CSV
- **Entrada Interactiva**: Archivos temporales para registro de operaciones
- **Validación Sintáctica**: Rechaza archivos vacíos o inválidos
- **Módulos DSL**: Lenguajes específicos por dominio

## Requisitos

- Windows PowerShell
- Flex/Bison (winflexbison3)
- MinGW (gcc/g++)
- Notepad (editor predeterminado)

## Instalación y Compilación

```powershell
# Clonar repositorio
git clone https://github.com/veliz-a/FashionFlow-Compiler.git
cd FashionFlow-Compiler

# Compilar todo
./compile_all.ps1
```

## Uso

```powershell
# Ejecutar sistema integrado
./fashionflow.exe
```

### Menú Principal
1. **Producción** - Gestionar órdenes de producción
2. **Inventario** - Controlar transferencias y stock
3. **Ventas** - Registrar clientes y transacciones
4. Salir

### Operaciones por Módulo
Cada módulo permite:
- Registrar nueva operación (abre editor)
- Ver ejemplos básicos/completos
- Ver registros CSV guardados

## Estructura del Proyecto

```
src/
├── main.cpp                    # Sistema integrado
├── common/                     # Utilidades compartidas
├── produccion/                 # DSL Producción (Flex/Bison)
│   ├── produccion.l/.y
│   └── casos_prueba/
├── inventario/                 # DSL Inventario (C++ manual)
│   ├── lexer_inventario.cpp
│   └── parser_inventario.cpp
└── ventas/                     # DSL Ventas (Flex/Bison)
    ├── Ventas.l/.y
    └── tests/

temp_*.txt                      # Archivos temporales para entrada
*.csv                           # Registros persistentes
compile_all.ps1                 # Script de compilación
```

## Archivos Generados

- `produccion_ordenes.csv` - Órdenes de producción
- `inventario_movimientos.csv` - Transferencias de inventario
- `ventas_registro.csv` - Registros de ventas

## Sintaxis DSL

Ver ejemplos en archivos `temp_*.txt` y casos de prueba en cada módulo.

## Documentación

- `docs/avances_entregados/` - Gramáticas formales
- `docs/material_clase/` - Referencias del curso
