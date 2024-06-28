#!/bin/bash

# - - - - - - - - - - - - - - - - - - - - - - - - - -+
#                                                    |
#   Pontificia Universidad Católica de Valparaíso    |
#         Taller 2 - Script chgogpxpal.sh            |
#       Giovanni Ahumada Tapia - 21.523.921-7        |
#                                                    |
# - - - - - - - - - - - - - - - - - - - - - - - - - -+ 

# Validar que se pasen al menos 4 argumentos
if [ $# -lt 4 ]; then
  echo "Uso: $0 palabra_a_buscar num_ocurrencias ruta_inicial [-g grupo] [-o dueño] [-p permisos]"
  exit 1
fi

# Validar que el script se ejecute con los permisos requeridos
# Arriba se oblga a que el script se ejecute con permisos de administrador de igual forma.
if [[ $EUID -ne 0 ]]; then
    echo "Este script debe ejecutarse como root (privilegios de administrador)" 
    exit 1
fi

# Asignar argumentos a variables
palabra_a_buscar=$1
num_ocurrencias=$2
ruta_inicial=$3
shift 3 # Se eliminan los 3 primeros argumentos para que los argumentos opcionales queden en la posición 1, 2 y 3

# Se inicializan variables para las opciones opcionales (valga la redondancia)
grupo=""
dueno="" # Inicializan como cadena vacía para que no se apliquen cambios si no se pasan los argumentos
permisos=""

# Procesar opciones
while [[ "$#" -gt 0 ]]; do # Bucle while para procesar las opciones
  case $1 in
    -g)
      grupo=$2
      shift 2
      ;;
    -o)
      dueno=$2
      shift 2
      ;;
    -p)
      permisos=$2
      shift 2
      ;;
    *) # Si se encuentra una opción no válida, se muestra un mensaje de error 
      echo "Opción no válida: $1"
      echo "Uso: $0 palabra_a_buscar num_ocurrencias ruta_inicial [-g grupo] [-o dueño] [-p permisos]"
      exit 1
      ;;
  esac
done

# Buscar archivos que contengan la palabra al menos num_ocurrencias veces
archivos=$(grep -rl "$palabra_a_buscar" "$ruta_inicial" | xargs grep -l -E "($palabra_a_buscar.*){$num_ocurrencias,}")
# Se usa grep -rl para encontrar archivos en ruta_inicial 
#          |-> esto es compatible con macOS y Linux

# Se usa xargs para pasar los archivos encontrados a grep

# Cambiar permisos, dueño y/o grupo 
for archivo in $archivos; do # Ciclo for iterando con los archivos encontrados
  if [ -n "$grupo" ]; then # Si 'grupo' no está vacío, se cambia el grupo del archivo
    chgrp "$grupo" "$archivo"
  fi
  if [ -n "$dueno" ]; then # Si 'dueño' no está vacío, se cambia el dueño del archivo
    chown "$dueno" "$archivo"
  fi
  if [ -n "$permisos" ]; then # Si 'permisos' no está vacío, se cambian los permisos del archivo
    chmod "$permisos" "$archivo"
  fi
done # Fin del ciclo ciclo / script
