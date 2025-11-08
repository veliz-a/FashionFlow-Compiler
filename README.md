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
│   ├── avances_entregados/            # Entregables del curso y gramáticas
│   ├── material_clase/                # Material del curso y ejemplos
│   └── referencias/                   # Documentación de referencia
│
├── examples/                          # Ejemplos de uso de los lenguajes DSL
│
├── src/                               # Código fuente del compilador
│   ├── produccion/                    # Módulo Producción
│   │   ├── produccion.l               # Analizador léxico (Flex)
│   │   ├── produccion.y               # Analizador sintáctico (Bison)
│   │   └── casos_prueba/              # Programas de prueba
│   │
│   ├── inventario/                    # Módulo Inventario
│   │   ├── lexer_inventario.cpp       # Analizador léxico
│   │   ├── parser_inventario.cpp      # Analizador sintáctico
│   │   ├── inventario.h               # Definiciones
│   │   └── tests/                     # Casos de prueba
│   │
│   ├── ventas/                        # Módulo Ventas
│   │   ├── lexer_ventas.cpp           # Analizador léxico
│   │   ├── parser_ventas.cpp          # Analizador sintáctico
│   │   ├── ventas.h                   # Definiciones
│   │   └── tests/                     # Casos de prueba
│   │
│   ├── common/                        # Componentes compartidos
│   └── main.cpp                       # Punto de entrada principal
```

## Compilación

Cada módulo puede compilarse de forma independiente según su implementación.

### Módulo de Producción (Flex/Bison)

```bash
cd src/produccion
bison -d produccion.y
flex produccion.l
gcc lex.yy.c produccion.tab.c -o compilador_produccion
```

### Módulos de Inventario y Ventas (C++)

Consultar las instrucciones específicas en cada módulo.

## Uso

Cada módulo procesa archivos de texto (`.txt`) con código fuente en su respectivo lenguaje DSL.

### Ejemplo - Módulo de Producción

```bash
cd src/produccion
./compilador_produccion casos_prueba/caso_prueba_produccion_01.txt
```

Consultar cada módulo para instrucciones específicas de uso y ejemplos de código.

## Documentación

La documentación del proyecto está organizada en la carpeta `docs/`:

- **avances_entregados/**: Gramáticas formales y entregables del curso
- **material_clase/**: Material proporcionado por el docente
- **referencias/**: Documentación de contexto del proyecto

Cada módulo en `src/` contiene su propia documentación específica.

## Curso

**Compiladores** - Profesor Javier Antonio Dioses Zárate  
Facultad de Ingeniería - Universidad San Ignacio de Loyola  
Ciclo 2025-02
