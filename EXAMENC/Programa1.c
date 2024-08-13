#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50

struct Empleado {
    char nombre[MAX_NOMBRE];
    int codigo;
    float sueldo;
    int horas_trabajadas;
};

void ingresarT(struct Empleado **empleados, int *num_empleados);
void consultasG(struct Empleado *empleados, int num_empleados);
void consultasPC(struct Empleado *empleados, int num_empleados);
void consultasPN(struct Empleado *empleados, int num_empleados);
int compararE(const void *a, const void *b);

int main() {
    struct Empleado *empleados = NULL;
    int num_empleados = 0;
    int opcion;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("----------------------\n");
        printf("1. Ingresar Trabajadores\n");
        printf("2. Consultas generales\n");
        printf("3. Consultas por clave\n");
        printf("4. Consultas por nombre\n");
        printf("5. Salir\n");
        printf("----------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: ingresarT(&empleados, &num_empleados); break;
            case 2: consultasG(empleados, num_empleados); break;
            case 3: consultasPC(empleados, num_empleados); break;
            case 4: consultasPN(empleados, num_empleados); break;
            case 5: printf("Saliendo del programa...\n"); break;
            default: printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    free(empleados);
    return 0;
}

void ingresarT(struct Empleado **empleados, int *num_empleados) {
    int n;
    printf("Cuantos empleados desea ingresar ");
    scanf("%d", &n);

    *empleados = realloc(*empleados, (*num_empleados + n) * sizeof(struct Empleado));

    for (int i = 0; i < n; i++) {
        printf("\nEmpleado %d:\n", *num_empleados + i + 1);
        printf("Nombre: ");
        scanf(" %[^\n]", (*empleados)[*num_empleados + i].nombre);
        printf("Codigo de empleado: ");
        scanf("%d", &(*empleados)[*num_empleados + i].codigo);
        printf("Sueldo: ");
        scanf("%f", &(*empleados)[*num_empleados + i].sueldo);
        printf("Horas trabajadas: ");
        scanf("%d", &(*empleados)[*num_empleados + i].horas_trabajadas);
    }

    *num_empleados += n;
}

void consultasG(struct Empleado *empleados, int num_empleados) {
    if (num_empleados == 0) {
        printf("No hay empleados registrados.\n");
        return;
    }

    qsort(empleados, num_empleados, sizeof(struct Empleado), compararE);

    printf("\n--- Listado de Empleados ---\n");
    for (int i = 0; i < num_empleados; i++) {
        printf("Nombre: %s\n", empleados[i].nombre);
        printf("Codigo: %d\n", empleados[i].codigo);
        printf("Sueldo: %.2f\n", empleados[i].sueldo);
        printf("Horas trabajadas: %d\n\n", empleados[i].horas_trabajadas);
    }
}

void consultasPC(struct Empleado *empleados, int num_empleados) {
    int codigo;
    printf("Ingrese el codigo del empleado a buscar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < num_empleados; i++) {
        if (empleados[i].codigo == codigo) {
            printf("\nEmpleado encontrado:\n");
            printf("Nombre: %s\n", empleados[i].nombre);
            printf("Codigo: %d\n", empleados[i].codigo);
            printf("Sueldo: %.2f\n", empleados[i].sueldo);
            printf("Horas trabajadas: %d\n", empleados[i].horas_trabajadas);
            return;
        }
    }

    printf("No se encontro ningun empleado con ese codigo.\n");
}

void consultasPN(struct Empleado *empleados, int num_empleados) {
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del empleado a buscar: ");
    scanf(" %[^\n]", nombre);

    for (int i = 0; i < num_empleados; i++) {
        if (strcmp(empleados[i].nombre, nombre) == 0) {
            printf("\nEmpleado encontrado:\n");
            printf("Nombre: %s\n", empleados[i].nombre);
            printf("Codigo: %d\n", empleados[i].codigo);
            printf("Sueldo: %.2f\n", empleados[i].sueldo);
            printf("Horas trabajadas: %d\n", empleados[i].horas_trabajadas);
            return;
        }
    }

    printf("No se encontro ningun empleado con ese nombre.\n");
}

int compararE(const void *a, const void *b) {
    return strcmp(((struct Empleado *)a)->nombre, ((struct Empleado *)b)->nombre);
}