# FashionFlow Compiler - Script de Compilacion
# Grupo 2: Hugo Ramos, Sofia Solari, Alejandra Veliz

Write-Host "`nFashionFlow Compiler - Compilacion Completa" -ForegroundColor Cyan
Write-Host "============================================`n" -ForegroundColor Cyan

$ErrorActionPreference = "Continue"
$errores = 0

# Verificar herramientas
Write-Host "Verificando herramientas..." -ForegroundColor Yellow
$tools = @("flex", "bison", "gcc", "g++")
foreach ($tool in $tools) {
    if (Get-Command $tool -ErrorAction SilentlyContinue) {
        Write-Host "  OK: $tool" -ForegroundColor Green
    } else {
        Write-Host "  ERROR: $tool no encontrado" -ForegroundColor Red
        Write-Host "  Instale con: choco install winflexbison3 mingw" -ForegroundColor Yellow
        $errores++
    }
}

if ($errores -gt 0) {
    Write-Host "`nFaltan herramientas. Abortando." -ForegroundColor Red
    exit 1
}

# 1. Produccion
Write-Host "`n[1/4] Compilando Produccion..." -ForegroundColor Yellow
Push-Location src\produccion
flex produccion.l
bison -d produccion.y
gcc -o produccion.exe lex.yy.c produccion.tab.c
if (-not (Test-Path "produccion.exe")) { $errores++ }
Pop-Location

# 2. Inventario
Write-Host "[2/4] Compilando Inventario..." -ForegroundColor Yellow
Push-Location src\inventario
flex inventario.l
bison -d inventario.y
gcc -o inventario.exe lex.yy.c inventario.tab.c
if (-not (Test-Path "inventario.exe")) { $errores++ }
Pop-Location

# 3. Ventas
Write-Host "[3/4] Compilando Ventas..." -ForegroundColor Yellow
Push-Location src\ventas
flex Ventas.l
bison -d Ventas.y
gcc -o ventas.exe lex.yy.c Ventas.tab.c
if (-not (Test-Path "ventas.exe")) { $errores++ }
Pop-Location

# 4. Main
Write-Host "[4/4] Compilando Sistema Integrado..." -ForegroundColor Yellow
g++ -o fashionflow.exe src\main.cpp -std=c++11
if (-not (Test-Path "fashionflow.exe")) { $errores++ }

# Resumen
Write-Host "`n============================================" -ForegroundColor Cyan
if ($errores -eq 0) {
    Write-Host "COMPILACION EXITOSA" -ForegroundColor Green
    Write-Host "`nEjecutables generados:"
    Write-Host "  - src/produccion/produccion.exe"
    Write-Host "  - src/inventario/inventario.exe"
    Write-Host "  - src/ventas/ventas.exe"
    Write-Host "  - fashionflow.exe"
    Write-Host "`nEjecutar: .\fashionflow.exe" -ForegroundColor Cyan
} else {
    Write-Host "COMPILACION CON ERRORES: $errores" -ForegroundColor Red
    exit 1
}
Write-Host "============================================`n" -ForegroundColor Cyan
