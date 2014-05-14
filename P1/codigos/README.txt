Proyecto 1
Comparación de heurísticas

Elaborado por:

Gamar Azuaje      10-10051
Wilmer Bandres    10-10055
Juan A. Escalante 10-10227

Ejecutables

./15-manhattan para solución con manhattan
./15-manhattan-pairwise para solución con manhattan + colisiones lineales
./24-solver para solución con pdb 5-5-5-5-4
./15-pdb-solver para solución con pdb 5-5-5
./15-pdb-ineffective-solver para solución con pdb 5-5-5 con división poco efectiva.
./15-pdb-663-solver para solución con pdb 6-6-3.

Para que sea efectivo debe correrse

ejecutable < caso.txt

Donde los casos para el 15-puzzle deben tener un 16 en la última línea, asimismo
un 25 en el caso del 24-puzzle.

Carpetas incluídas:

- pdbs : que contiene costo para cada entrada de cada base de datos de cada pdb hecha.
- casos : casos de usos usados y casos de usos oficiales.
- resultados : que contiene la traza completa de la solución de cada instancia con cada heurística.

