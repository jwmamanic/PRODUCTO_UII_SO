# Proyecto – Unidad II: Extensiones al Sistema Operativo XV6

## Integrantes
- Jhon William Mamani Condori	  2020-119018
- Juan Luis Mamani Mullo		    2021-119123

---

## Descripción del proyecto

Este proyecto extiende el sistema operativo educativo **XV6** implementando tres componentes principales:

### **1. Instrumentación del sistema**
Se implementa un comando `trace` y una syscall asociada que permite activar o desactivar la traza de llamadas al sistema del proceso actual.  
Cuando está activado, cada syscall ejecutada se imprime en pantalla.

### **2. Comandos relacionados con planificación y procesos**
Se implementan dos nuevos comandos:

- **`uptime2`**  
  Muestra información extendida del sistema:  
  - ticks desde el arranque  
  - tiempo en segundos  
  - procesos RUNNING, RUNNABLE y SLEEPING  
  - número de cambios de contexto del scheduler

- **`psmen`**  
  Lista los procesos en ejecución mostrando PID, estado, memoria y nombre.

Estas funciones requieren nuevas syscalls del kernel.

### **3. Contador de invocaciones por syscall**
Se implementa:

- un arreglo en el kernel que contabiliza cuántas veces se llama cada syscall  
- una nueva syscall `getsyscount`  
- un comando de usuario `syscount`, que:
  - sin parámetros → muestra todas las syscalls y su contador  
  - con un id → muestra solo ese contador

---

## Instrucciones para compilar y ejecutar

### **1. Clonar el repositorio**
```bash
git clone https://github.com/jwmamanic/PRODUCTO_UII_SO.git
cd xv6
```
### **2. Compilar el xv6**
```bash
make clean
make qemu
```
### **3. Ejecutar los comandos dentro de XV6**
#### **Traza de syscalls**
```bash
$ trace 1
$ ls
$ trace 0
```
#### **Información extendida del sistema**
```bash
$ uptime2
$ spin &
$ uptime2
```
#### **Lista de procesos**
```bash
$ psmen
```
#### **Eliminar de proceso spin**
```bash
$ kill 5 (o otro numero donde se encuentre el PID del spin)
$ uptime2
$ psmen
```
#### **Contador de syscalls**
```bash
$ syscount
$ syscount 5
```
