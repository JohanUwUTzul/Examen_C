#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_DEPARTAMENTO 30

struct Estudiante {
    int carnet;
    char nombre[MAX_NOMBRE];
    int grado;
    char departamento[MAX_DEPARTAMENTO];
    int edad;
};

void registrarE();
void buscarPC();
void listarPG();
void editarE();
void guardarE(struct Estudiante est);
struct Estudiante leerE(FILE *archivo);

int main() {
    int opcion;
    do {
        printf("\n--- Menu Principal ---\n");
        printf("---------------------\n");
        printf("1. Registrar estudiante\n");
        printf("2. Buscar estudiante por carnet\n");
        printf("3. Lista de estudiantes por grado\n");
        printf("4. Editar un estudiante\n");
        printf("5. Salir\n");
        printf("---------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrarE(); break;
            case 2: buscarPC(); break;
            case 3: listarPG(); break;
            case 4: editarE(); break;
            case 5: printf("Saliendo del programa...\n"); break;
            default: printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}

void registrarE() {
    struct Estudiante est;
    printf("Ingrese el numero de carnet de 5 digitos: ");
    scanf("%d", &est.carnet);
    printf("Ingrese el nombre: ");
    scanf(" %[^\n]", est.nombre);
    printf("Ingrese el grado: ");
    scanf("%d", &est.grado);
    printf("Ingrese el departamento: ");
    scanf(" %[^\n]", est.departamento);
    printf("Ingrese la edad: ");
    scanf("%d", &est.edad);
    
    guardarE(est);
    printf("Estudiante registrado con exito.\n");
}

void buscarPC() {
    int carnet;
    printf("Ingrese el numero de carnet a buscar: ");
    scanf("%d", &carnet);

    FILE *archivo = fopen("estudiantes.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    struct Estudiante est;
    int encontrado = 0;
    while (!feof(archivo)) {
        est = leerE(archivo);
        if (est.carnet == carnet) {
            printf("Estudiante encontrado:\n");
            printf("Carnet: %d\n", est.carnet);
            printf("Nombre: %s\n", est.nombre);
            printf("Grado: %d\n", est.grado);
            printf("Departamento: %s\n", est.departamento);
            printf("Edad: %d\n", est.edad);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Estudiante no encontrado.\n");
    }

    fclose(archivo);
}

void listarPG() {
    int grado;
    printf("Ingrese el grado a listar: ");
    scanf("%d", &grado);

    FILE *archivo = fopen("estudiantes.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    struct Estudiante est;
    int encontrados = 0;
    while (!feof(archivo)) {
        est = leerE(archivo);
        if (est.grado == grado) {
            printf("Carnet: %d, Nombre: %s\n", est.carnet, est.nombre);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron estudiantes en el grado %d.\n", grado);
    } else {
        printf("Total de estudiantes en el grado %d: %d\n", grado, encontrados);
    }

    fclose(archivo);
}

void editarE() {
    int carnet;
    printf("Ingrese el numero de carnet del estudiante a editar: ");
    scanf("%d", &carnet);

    FILE *archivo = fopen("estudiantes.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (archivo == NULL || temp == NULL) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    struct Estudiante est;
    int encontrado = 0;
    while (!feof(archivo)) {
        est = leerE(archivo);
        if (est.carnet == carnet) {
            printf("Ingrese el nuevo nombre: ");
            scanf(" %[^\n]", est.nombre);
            printf("Ingrese el nuevo grado: ");
            scanf("%d", &est.grado);
            printf("Ingrese el nuevo departamento: ");
            scanf(" %[^\n]", est.departamento);
            printf("Ingrese la nueva edad: ");
            scanf("%d", &est.edad);
            encontrado = 1;
        }
        fprintf(temp, "%d,%s,%d,%s,%d\n", est.carnet, est.nombre, est.grado, est.departamento, est.edad);
    }

    fclose(archivo);
    fclose(temp);

    if (encontrado) {
        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");
        printf("Estudiante actualizado con exito.\n");
    } else {
        remove("temp.txt");
        printf("Estudiante no encontrado.\n");
    }
}

void guardarE(struct Estudiante est) {
    FILE *archivo = fopen("estudiantes.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "%d,%s,%d,%s,%d\n", est.carnet, est.nombre, est.grado, est.departamento, est.edad);
    fclose(archivo);
}

struct Estudiante leerE(FILE *archivo) {
    struct Estudiante est;
    fscanf(archivo, "%d,%[^,],%d,%[^,],%d\n", &est.carnet, est.nombre, &est.grado, est.departamento, &est.edad);
    return est;
}