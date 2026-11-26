# Comparación experimental de algoritmos de ordenamiento

Programa en C++ que mide el tiempo de ejecución de seis algoritmos de ordenamiento sobre arreglos de enteros pseudoaleatorios y guarda los resultados en un archivo CSV para su análisis.

| Algoritmo      | Clave       | Complejidad promedio |
| -------------- | ----------- | -------------------- |
| Selection Sort | `selection` | O(n²)                |
| Insertion Sort | `insertion` | O(n²)                |
| Bubble Sort    | `bubble`    | O(n²)                |
| Quick Sort     | `quick`     | O(n log n)           |
| Heap Sort      | `heap`      | O(n log n)           |
| Merge Sort     | `merge`     | O(n log n)           |

## Contenido del repositorio

| Archivo                                       | Descripción                                                                                                                         |
| --------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| `main.cpp`                                    | Punto de entrada. Lee los argumentos, genera el arreglo, ejecuta el algoritmo, verifica el orden y agrega una fila a `results.csv`. |
| `SortsT.cpp` / `SortsT.hpp`                   | Implementación de los seis algoritmos y el contador de "rondas".                                                                    |
| `GenerateArray.cpp` / `GenerateArray.hpp`     | Generador de arreglos con `std::mt19937`; la misma semilla produce el mismo arreglo.                                                |
| `TimeMeasurement.cpp` / `TimeMeasurement.hpp` | Medición del tiempo con `std::chrono::steady_clock`, en milisegundos.                                                               |
| `results_backup.csv`                          | Copia de respaldo de los resultados de las pruebas.                                                                                 |
| `Results/`                                    | Salidas del análisis (gráficas y libro de Excel).                                                                                   |
| `.gitignore`                                  | Archivos excluidos del repositorio (ejecutable y `results.csv`).                                                                    |

## Cómo funciona

Una **ejecución** corre un algoritmo una vez sobre un arreglo:

```
./sorts <algoritmo> <n> <repeticion>
```

- `<algoritmo>`: `selection`, `insertion`, `bubble`, `quick`, `heap` o `merge`.
- `<n>`: cantidad de elementos (entero mayor que 0).
- `<repeticion>`: número de la prueba. Se usa como **semilla**, así que todos los algoritmos reciben exactamente el mismo arreglo en la misma repetición.

Los valores son enteros uniformes en el rango [0, 1 000 000 000]. Solo se mide la llamada al ordenamiento (no la generación del arreglo ni la escritura del archivo). Después de ordenar se comprueba con `std::is_sorted`; si falla, no se guarda el dato.

Cada ejecución agrega una fila a `results.csv` (se crea con encabezado si no existe):

```
algorithm,n,trial,time_ms,rounds
merge,100000,1,9.36,99999
```

`rounds` cuenta: pasadas (Bubble), iteraciones del bucle externo (Selection), elementos insertados (Insertion), mezclas (Merge), particiones (Quick) y extracciones de la raíz (Heap).

> Para n ≥ 100 000 el programa muestra el porcentaje de avance en la terminal.

## Requisitos

Un compilador de C++ con soporte para C++11 o superior (se recomienda g++ 13 o similar).

Memoria aproximada: `4 · n` bytes para el arreglo, más otros `4 · n` bytes para Merge Sort. Por ejemplo, n = 80 000 000 necesita unos 320 MB (640 MB con Merge Sort).

## Compilar y ejecutar

Todos los comandos se ejecutan dentro de la carpeta del proyecto.

### Linux

```bash
sudo apt update && sudo apt install g++        # Debian/Ubuntu
g++ -O2 -std=c++17 main.cpp GenerateArray.cpp SortsT.cpp TimeMeasurement.cpp -o sorts
./sorts merge 100000 1
```

### macOS

```bash
xcode-select --install                         # instala clang++ (una sola vez)
clang++ -O2 -std=c++17 main.cpp GenerateArray.cpp SortsT.cpp TimeMeasurement.cpp -o sorts
./sorts merge 100000 1
```

### Windows

**Opción A: WSL (recomendada, igual que Linux).** En PowerShell: `wsl --install`. Luego, dentro de Ubuntu, sigue los pasos de Linux.

**Opción B: MinGW-w64 con MSYS2.** Instala [MSYS2](https://www.msys2.org/), abre la terminal "MSYS2 UCRT64" y ejecuta:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Luego, en PowerShell o CMD dentro de la carpeta del proyecto:

```powershell
g++ -O2 -std=c++17 main.cpp GenerateArray.cpp SortsT.cpp TimeMeasurement.cpp -o sorts.exe
.\sorts.exe merge 100000 1
```

> Las banderas de compilación afectan mucho los tiempos. Para que los resultados sean comparables, usa siempre las mismas (`-O2` en los ejemplos) y anótalas junto con tu hardware.

### Ejemplo de salida

```
merge n=100000 trial 1: 9.36 ms, 99999 rounds
```

## Correr todas las pruebas

Para repetir el experimento (20 repeticiones para n ≤ 100 000 y 5 para tamaños mayores), ejemplo con un tamaño:

**Linux / macOS / WSL**

```bash
for algo in selection insertion bubble quick heap merge; do
  for t in $(seq 1 20); do ./sorts $algo 10000 $t; done
done
```

**Windows (PowerShell)**

```powershell
foreach ($algo in "selection","insertion","bubble","quick","heap","merge") {
  foreach ($t in 1..20) { .\sorts.exe $algo 10000 $t }
}
```

Recomendaciones:

- **Borra o renombra `results.csv` antes de empezar** una tanda nueva: el programa siempre agrega filas al final.
- Bubble, Selection e Insertion son O(n²): con n = 1 000 000 cada ejecución puede tardar de minutos a decenas de minutos.
- Cierra otros programas pesados durante las pruebas para reducir el ruido en las mediciones.

## Análisis de resultados

Los datos de `results.csv` se analizan en un libro de Excel con las hojas: Información, Datos originales, Resultados (promedios con fórmulas), Merge Sort, Quick y Heap Sort, Algoritmos cuadráticos y Comparativa general. Los registros duplicados (misma combinación algoritmo, n y repetición) se excluyen de los promedios.
