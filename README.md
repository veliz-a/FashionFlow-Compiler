# FashionFlow Compiler

Compilador de lenguajes específicos de dominio (DSL) para automatizar procesos operativos en Nancy's Collection.

## Equipo - Grupo 2

- Alejandra Veliz Garcia [2311640] - Lenguaje de Producción
- María Sofía Solari Hipólito [2320632] - Lenguaje de Inventario  
- Hugo Alexander Ramos Niño Neira [2310120] - Lenguaje de Ventas

## Descripción del Proyecto

Proyecto de la asignatura Compiladores (PREISF07C01M) - Universidad San Ignacio de Loyola.

Este proyecto implementa tres lenguajes específicos de dominio diseñados para automatizar los procesos operativos de Nancy's Collection, una empresa del sector textil:

1. **Lenguaje de Producción**: Control y seguimiento de procesos de corte y confección de prendas
2. **Lenguaje de Inventario**: Gestión de ingreso, salida y disponibilidad de mercadería
3. **Lenguaje de Ventas**: Registro y análisis de transacciones comerciales

Cada lenguaje cuenta con su propio analizador léxico (lexer) y sintáctico (parser), permitiendo procesar instrucciones específicas del dominio de manera eficiente.

## Estructura del Proyecto

```
FashionFlow-Compiler/
├── docs/                           # Documentación y materiales del curso
│   ├── avances_entregados/        # Entregables y gramáticas formales
│   ├── material_clase/            # Guía del curso y ejemplos del profesor
│   └── referencias/               # Caso de estudio Nancy's
├── src/                           # Código fuente
│   ├── produccion/                # Compilador de producción
│   ├── inventario/                # Compilador de inventario
│   ├── ventas/                    # Compilador de ventas
│   ├── common/                    # Componentes compartidos (tokens, utilidades)
│   └── main.cpp                   # Punto de entrada principal
└── examples/                      # Archivos de prueba (.ffs)
```

## Compilación

### Compilar cada módulo individualmente:

```bash
# Lenguaje de Producción
g++ -o produccion src/produccion/lexer_produccion.cpp src/produccion/parser_produccion.cpp

# Lenguaje de Inventario
g++ -o inventario src/inventario/lexer_inventario.cpp src/inventario/parser_inventario.cpp

# Lenguaje de Ventas
g++ -o ventas src/ventas/lexer_ventas.cpp src/ventas/parser_ventas.cpp
```

### Compilar el programa principal:

```bash
g++ -o fashionflow src/main.cpp
```

## Uso

Ejecutar los compiladores con archivos de ejemplo:

```bash
# Procesar archivo de producción
./produccion examples/ejemplo_produccion.ffs

# Procesar archivo de inventario
./inventario examples/ejemplo_inventario.ffs

# Procesar archivo de ventas
./ventas examples/ejemplo_ventas.ffs
```

## Pruebas

Cada módulo incluye casos de prueba en `src/<modulo>/tests/`:

```bash
./produccion src/produccion/tests/test_produccion_01.txt
./inventario src/inventario/tests/test_inventario_01.txt
./ventas src/ventas/tests/test_ventas_01.txt
```

## Documentación

La carpeta `docs/` contiene:

- **avances_entregados/**: Entregas parciales, informe final y gramáticas formales (BNF/EBNF) de cada lenguaje
- **material_clase/**: Guía final del curso y ejemplos del profesor
- **referencias/**: Caso de estudio y entrevista a Nancy's Collection

## Curso

**Compiladores** - Profesor Javier Antonio Dioses Zárate  
Facultad de Ingeniería - Universidad San Ignacio de Loyola  
Ciclo 2025-02
