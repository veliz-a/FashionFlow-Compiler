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
│   │   ├── Avance1_Grupo2.pdf         # Primer entregable
│   │   ├── Avance2_Grupo2.pdf         # Segundo entregable
│   │   ├── InformeFinal_Grupo2.pdf    # Informe final del proyecto
│   │   ├── produccion_grammar.txt     # Gramática formal BNF/EBNF - Producción
│   │   ├── inventario_grammar.txt     # Gramática formal BNF/EBNF - Inventario
│   │   └── ventas_grammar.txt         # Gramática formal BNF/EBNF - Ventas
│   │
│   ├── material_clase/                # Material del curso
│   │   ├── Guía - Trabajo Final.pdf   # Guía oficial del proyecto
│   │   └── ejemplos_profesor/         # Ejemplos de código del docente
│   │       └── laboratorio_s11/       # Laboratorios de clase
│   │
│   └── referencias/                   # Documentación de referencia
│       ├── caso_estudio_nancys.pdf    # Caso de estudio Nancy's Collection
│       └── entrevista_nancys.pdf      # Entrevista y requerimientos
│
├── src/                               # Código fuente del compilador
│   ├── produccion/                    # Módulo Producción
│   │   ├── lexer_produccion.cpp       # Analizador léxico
│   │   ├── parser_produccion.cpp      # Analizador sintáctico
│   │   ├── produccion.h               # Definiciones y estructuras
│   │   └── tests/                     # Casos de prueba
│   │       ├── test_produccion_01.txt
│   │       └── test_produccion_02.txt
│   │
│   ├── inventario/                    # Módulo Inventario
│   │   ├── lexer_inventario.cpp
│   │   ├── parser_inventario.cpp
│   │   ├── inventario.h
│   │   └── tests/
│   │       ├── test_inventario_01.txt
│   │       └── test_inventario_02.txt
│   │
│   ├── ventas/                        # Módulo Ventas
│   │   ├── lexer_ventas.cpp
│   │   ├── parser_ventas.cpp
│   │   ├── ventas.h
│   │   └── tests/
│   │       ├── test_ventas_01.txt
│   │       └── test_ventas_02.txt
│   │
│   ├── common/                        # Componentes compartidos
│   │   ├── token.h                    # Definición de tokens
│   │   └── utils.h                    # Utilidades comunes
│   │
│   └── main.cpp                       # Punto de entrada principal
│
└── examples/                          # Archivos de ejemplo .txt
    ├── ejemplo_produccion.txt         # Programa de ejemplo - Producción
    ├── ejemplo_inventario.txt         # Programa de ejemplo - Inventario
    └── ejemplo_ventas.txt             # Programa de ejemplo - Ventas
```

## Compilación

Los compiladores están implementados en C++ puro, sin dependencias externas de generadores automáticos.

### Compilar cada módulo individualmente:

```bash
# Lenguaje de Producción
g++ -o produccion src/produccion/lexer_produccion.cpp src/produccion/parser_produccion.cpp -I src/common

# Lenguaje de Inventario
g++ -o inventario src/inventario/lexer_inventario.cpp src/inventario/parser_inventario.cpp -I src/common

# Lenguaje de Ventas
g++ -o ventas src/ventas/lexer_ventas.cpp src/ventas/parser_ventas.cpp -I src/common
```

### Compilar el programa principal (todos los módulos):

```bash
g++ -o fashionflow src/main.cpp src/produccion/*.cpp src/inventario/*.cpp src/ventas/*.cpp -I src/common
```

## Uso

Los compiladores procesan archivos de texto (`.txt`) con código fuente de cada lenguaje.

### Ejecutar con archivos de ejemplo:

```bash
# Procesar archivo de producción
./produccion examples/ejemplo_produccion.txt

# Procesar archivo de inventario
./inventario examples/ejemplo_inventario.txt

# Procesar archivo de ventas
./ventas examples/ejemplo_ventas.txt
```

### Ejecutar con casos de prueba:

Cada módulo incluye casos de prueba en `src/<modulo>/tests/`:

```bash
# Pruebas del módulo Producción
./produccion src/produccion/tests/test_produccion_01.txt
./produccion src/produccion/tests/test_produccion_02.txt

# Pruebas del módulo Inventario
./inventario src/inventario/tests/test_inventario_01.txt
./inventario src/inventario/tests/test_inventario_02.txt

# Pruebas del módulo Ventas
./ventas src/ventas/tests/test_ventas_01.txt
./ventas src/ventas/tests/test_ventas_02.txt
```

## Documentación

### Carpeta `docs/`

La documentación del proyecto está organizada en tres secciones:

#### 1. `avances_entregados/`
Contiene los entregables académicos del curso:
- **PDFs de avances**: Avance1, Avance2 e Informe Final
- **Gramáticas formales**: Especificaciones BNF/EBNF de cada lenguaje (`.txt`)
  - `produccion_grammar.txt`
  - `inventario_grammar.txt`
  - `ventas_grammar.txt`

Nota: Las gramáticas en esta carpeta son documentación formal. La implementación real del compilador (lexer y parser) está en `src/` codificada manualmente en C++.

#### 2. `material_clase/`
Material proporcionado por el docente:
- **Guía del Trabajo Final**: Especificaciones y requerimientos del proyecto
- **ejemplos_profesor/**: Código de ejemplo y laboratorios de clase
  - Implementaciones de referencia para lexer y parser
  - Casos de uso demostrados durante el curso

#### 3. `referencias/`
Documentación de contexto del proyecto:
- **caso_estudio_nancys.pdf**: Análisis del caso de estudio
- **entrevista_nancys.pdf**: Requerimientos obtenidos de Nancy's Collection

## Curso

**Compiladores** - Profesor Javier Antonio Dioses Zárate  
Facultad de Ingeniería - Universidad San Ignacio de Loyola  
Ciclo 2025-02
