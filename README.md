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
│   │   └── CompiladorFlex/            # Ejemplo de compilador del docente
│   │       ├── lexer.l                # Analizador léxico en Flex
│   │       └── lex.yy.c               # Código C generado
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
│   │   └── casos_prueba/              # Programas demostrativos DSL
│   │       ├── caso_prueba_produccion_01.txt
│   │       └── caso_prueba_produccion_02.txt
│   │
│   ├── inventario/                    # Módulo Inventario
│   │   ├── lexer_inventario.cpp
│   │   ├── parser_inventario.cpp
│   │   ├── inventario.h
│   │   └── casos_prueba/              # Programas demostrativos DSL
│   │       ├── caso_prueba_inventario_01.txt
│   │       └── caso_prueba_inventario_02.txt
│   │
│   ├── ventas/                        # Módulo Ventas
│   │   ├── lexer_ventas.cpp
│   │   ├── parser_ventas.cpp
│   │   ├── ventas.h
│   │   └── casos_prueba/              # Programas demostrativos DSL
│   │       ├── caso_prueba_ventas_01.txt
│   │       └── caso_prueba_ventas_02.txt
│   │
│   ├── common/                        # Componentes compartidos
│   │   ├── token.h                    # Definición de tokens
│   │   └── utils.h                    # Utilidades comunes
│   │
│   └── main.cpp                       # Punto de entrada principal
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

Los compiladores procesan archivos de texto (`.txt`) con código fuente de cada lenguaje DSL.

### Ejecutar con casos de prueba:

Cada módulo incluye programas demostrativos en `src/<modulo>/casos_prueba/`:

```bash
# Pruebas del módulo Producción
./produccion src/produccion/casos_prueba/caso_prueba_produccion_01.txt
./produccion src/produccion/casos_prueba/caso_prueba_produccion_02.txt

# Pruebas del módulo Inventario
./inventario src/inventario/casos_prueba/caso_prueba_inventario_01.txt
./inventario src/inventario/casos_prueba/caso_prueba_inventario_02.txt

# Pruebas del módulo Ventas
./ventas src/ventas/casos_prueba/caso_prueba_ventas_01.txt
./ventas src/ventas/casos_prueba/caso_prueba_ventas_02.txt
```

Estos programas demostrativos evidencian situaciones reales de Nancy's Collection.

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
- **CompiladorFlex/**: Ejemplo de compilador usando Flex
  - Implementación de referencia de analizador léxico
  - Código fuente `.l` y código C generado `.c`

#### 3. `referencias/`
Documentación de contexto del proyecto:
- **caso_estudio_nancys.pdf**: Análisis del caso de estudio
- **entrevista_nancys.pdf**: Requerimientos obtenidos de Nancy's Collection

## Curso

**Compiladores** - Profesor Javier Antonio Dioses Zárate  
Facultad de Ingeniería - Universidad San Ignacio de Loyola  
Ciclo 2025-02
