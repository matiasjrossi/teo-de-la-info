# escape.log  estacionaria_bond.log  estacionaria_drno.log  tiempo_bond.log  tiempo_drno.log

set terminal png size 800,600

set output "escape.png"
plot [t=1:1000] "escape.log" with lines lw 2 lc 3

set output "estacionaria_bond.png"
plot [t=1:1000] "estacionaria_bond.log" using 1 smooth csplines title "estado 0", "estacionaria_bond.log" using 2 smooth csplines title "estado 1", "estacionaria_bond.log" using 3 smooth csplines title "estado 2", "estacionaria_bond.log" using 4 smooth csplines title "estado 3", "estacionaria_bond.log" using 5 smooth csplines title "estado 4", "estacionaria_bond.log" using 6 smooth csplines title "estado 5", "estacionaria_bond.log" using 7 smooth csplines title "estado 6", "estacionaria_bond.log" using 8 smooth csplines title "estado 7", "estacionaria_bond.log" using 9 smooth csplines title "estado 8", "estacionaria_bond.log" using 10 smooth csplines title "estado 9"

set output "estacionaria_drno.png"
plot [t=1:1000] "estacionaria_drno.log" using 1 smooth csplines title "estado 0", "estacionaria_drno.log" using 2 smooth csplines title "estado 1", "estacionaria_drno.log" using 3 smooth csplines title "estado 2", "estacionaria_drno.log" using 4 smooth csplines title "estado 3", "estacionaria_drno.log" using 5 smooth csplines title "estado 4", "estacionaria_drno.log" using 6 smooth csplines title "estado 5", "estacionaria_drno.log" using 7 smooth csplines title "estado 6", "estacionaria_drno.log" using 8 smooth csplines title "estado 7", "estacionaria_drno.log" using 9 smooth csplines title "estado 8", "estacionaria_drno.log" using 10 smooth csplines title "estado 9"

set output "tiempo_bond.png"
plot [t=1:1000] "tiempo_bond.log" with lines lw 2 lc 3

set output "tiempo_drno.png"
plot [t=1:1000] "tiempo_drno.log" with lines lw 2 lc 3

set output "correlacion_cruzada.png"
plot "correlacion_cruzada.log" with lines lw 2 lc 3
