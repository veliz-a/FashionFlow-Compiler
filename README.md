# FashionFlow Compiler

Compilador de lenguajes específicos de dominio (DSL) para automatizar procesos operativos en Nancy's Collection.

## Equipo - Grupo 2

- **Alejandra Veliz Garcia** [2311640] - Lenguaje de Producción
- **María Sofía Solari Hipólito** [2320632] - Lenguaje de Inventario  
- **Hugo Alexander Ramos Niño Neira** [2310120] - Lenguaje de Ventas

## Descripción del Proyecto

Proyecto de la asignatura Compiladores (PREISF07C01M) - Universidad San Ignacio de Loyola.

Este proyecto implementa tres lenguajes específicos de dominio diseñados para automatizar los procesos operativos de Nancy's Collection, una empresa del sector textil:

1. **Lenguaje de Producción**: Control y seguimiento de procesos de corte y confección de prendas
2. **Lenguaje de Inventario**: Gestión de ingreso, salida y disponibilidad de mercadería
3. **Lenguaje de Ventas**: Registro y análisis de transacciones comerciales

Cada lenguaje cuenta con su propio analizador léxico (lexer) y sintáctico (parser) implementados manualmente en C++, procesando archivos de texto (`.txt`).

## Estructura del Proyecto

```
FashionFlow-Compiler/
│
├── docs/                               # Documentación y materiales académicos
│   ├── avances_entregados/            # Entregables del curso
│   │   ├── produccion_grammar.txt     # Gramática formal BNF/EBNF - Producción
│   │   ├── inventario_grammar.txt     # Gramática formal BNF/EBNF - Inventario
│   │   └── ventas_grammar.txt         # Gramática formal BNF/EBNF - Ventas
│   │
│   ├── material_clase/                # Material del curso
│   │   ├── CompiladorFlex/            # Ejemplo de compilador del docente
│   │   └── ejemplos_profesor/         # Ejemplos adicionales
│   │
│   └── referencias/                   # Documentación de referencia
│
├── examples/                          # Ejemplos de uso de los lenguajes DSL
│   └── ejemplo_ventas.txt             # Ejemplo del lenguaje de ventas
│
├── src/                               # Código fuente del compilador
│   ├── produccion/                    # Módulo Producción (Flex/Bison)
│   │   ├── produccion.l               # Analizador léxico en Flex
│   │   ├── produccion.y               # Analizador sintáctico en Bison
│   │   ├── lex.yy.c                   # Código C generado por Flex
│   │   ├── produccion.tab.c           # Código C generado por Bison
│   │   ├── produccion.tab.h           # Headers generados por Bison
│   │   ├── compilador_produccion.exe  # Ejecutable compilado
│   │   ├── README_COMPILACION.md      # Instrucciones de compilación
│   │   └── casos_prueba/              # Programas demostrativos DSL
│   │       ├── caso_prueba_produccion_01.txt
│   │       └── caso_prueba_produccion_02.txt
│   │
│   ├── inventario/                    # Módulo Inventario (C++)
│   │   ├── lexer_inventario.cpp       # Analizador léxico
│   │   ├── parser_inventario.cpp      # Analizador sintáctico
│   │   ├── inventario.h               # Definiciones y estructuras
│   │   └── tests/                     # Casos de prueba
│   │       ├── test_inventario_01.txt
│   │       └── test_inventario_02.txt
│   │
│   ├── ventas/                        # Módulo Ventas (C++)
│   │   ├── lexer_ventas.cpp           # Analizador léxico
│   │   ├── parser_ventas.cpp          # Analizador sintáctico
│   │   ├── ventas.h                   # Definiciones y estructuras
│   │   └── tests/                     # Casos de prueba
│   │       ├── test_ventas_01.txt
│   │       └── test_ventas_02.txt
│   │
│   ├── common/                        # Componentes compartidos
│   │   ├── token.h                    # Definición de tokens
│   │   └── utils.h                    # Utilidades comunes
│   │
│   ├── main.cpp                       # Punto de entrada principal
│   └── ventas_main.cpp                # Ejecutable independiente de ventas
```

## Compilación

### Módulo de Producción (Flex/Bison)

El módulo de producción utiliza Flex y Bison para generar el analizador léxico y sintáctico:

```bash
cd src/produccion

# 1. Generar el parser con Bison
bison -d produccion.y

# 2. Generar el lexer con Flex
flex produccion.l

# 3. Compilar todo junto
gcc lex.yy.c produccion.tab.c -o compilador_produccion
```

### Módulo de Inventario (C++)

```bash
# Lenguaje de Inventario
g++ -o inventario src/inventario/lexer_inventario.cpp src/inventario/parser_inventario.cpp -I src/common
```

### Módulo de Ventas (C++)

```bash
# Lenguaje de Ventas
g++ -o ventas src/ventas/lexer_ventas.cpp src/ventas/parser_ventas.cpp -I src/common
```

## Uso

Los compiladores procesan archivos de texto (`.txt`) con código fuente de cada lenguaje DSL.

### Módulo de Producción

```bash
# Ejecutar con casos de prueba
./compilador_produccion casos_prueba/caso_prueba_produccion_01.txt
./compilador_produccion casos_prueba/caso_prueba_produccion_02.txt
```

**Estado actual**: Primera iteración implementada con Flex/Bison
- ✅ Declaración de órdenes de producción con diseño, tallas, colores y cantidades
- ✅ Análisis léxico completo
- ✅ Análisis sintáctico con validación gramatical
- ⏳ Funcionalidades pendientes: CORTE, CONSULTAR, CALCULAR_COSTO (próximas iteraciones)

### Módulo de Inventario

```bash
# Pruebas del módulo Inventario
./inventario src/inventario/tests/test_inventario_01.txt
./inventario src/inventario/tests/test_inventario_02.txt
```

### Módulo de Ventas

```bash
# Pruebas del módulo Ventas
./ventas src/ventas/tests/test_ventas_01.txt
./ventas src/ventas/tests/test_ventas_02.txt
```

## Documentación

### Carpeta `docs/`

La documentación del proyecto está organizada en tres secciones:

#### 1. `avances_entregados/`
Contiene las gramáticas formales de cada lenguaje:
- **Gramáticas BNF/EBNF** (`.txt`):
  - `produccion_grammar.txt` - Especificación formal del lenguaje de producción
  - `inventario_grammar.txt` - Especificación formal del lenguaje de inventario
  - `ventas_grammar.txt` - Especificación formal del lenguaje de ventas

#### 2. `material_clase/`
Material proporcionado por el docente:
- **CompiladorFlex/**: Ejemplo de referencia de compilador usando Flex
- **ejemplos_profesor/**: Ejemplos adicionales de implementación

#### 3. `referencias/`
Documentación de contexto del proyecto relacionada con Nancy's Collection

## Curso

**Compiladores** - Profesor Javier Antonio Dioses Zárate  
Facultad de Ingeniería - Universidad San Ignacio de Loyola  
Ciclo 2025-02
