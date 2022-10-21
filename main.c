#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* En una Cooperativa de Transporte trabajan 6 choferes
Chofer 01, chofer 02……. Chofer 06.
El ingreso de datos de la siguiente manera
•	Nº de Chofer [1-6]
•	Nombre del chofer.
•	Cant. De Kms

Opción 1: Permite el ingrese de los viajes registrados de acuerdo al orden de info que se indicó anteriormente.

Opción 2: Muestra el informe de los viajes realizados y Kms recorridos por chofer hasta ese instante. Cuando se ejecuta esta opción se deshabilita la opción 1.


Opción 3: Muestra la lista de choferes sin ordenar en cualquier momento

Opción 4: suponiendo el gasto de viaje es de 200$ por cada 100 kilómetros recorridos, mostrar el gasto de viaje realizado por cada chofer ordenados en forma descendente por gasto en pesos.
Opción 5: Pasar a un archivo binario los resultados del punto 2 (NO HACER)
Opción 6: Salir
*/

typedef struct Conductor{
    int cod_chof;
    char nom_chof[20];
    int cv;
    int ckms;
    float gastoviaje;
    struct elemento *sig;
}nodo;

nodo* crearNodo(int codChof, int recorridoKms, char* nombre){

    nodo* nodoNuevo = (nodo*)malloc(sizeof(nodo));

    nodoNuevo->cod_chof = codChof;
    nodoNuevo->ckms = recorridoKms;
    strcpy(nodoNuevo->nom_chof, nombre);
    nodoNuevo->cv = 1;
    nodoNuevo->gastoviaje = recorridoKms * 2;
    nodoNuevo->sig = NULL;

    return nodoNuevo;

}

void insertarNodo(nodo **c, int codChof, int recorridoKms, char* nombre){

    nodo* nodoNuevo;

    if(*c == NULL){
        nodoNuevo = crearNodo(codChof, recorridoKms, nombre);
        *c = nodoNuevo;
    }else if((*c)->cod_chof == codChof){
        (*c)->ckms += recorridoKms;
        (*c)->cv++;
        (*c)->gastoviaje += recorridoKms*2;
    }else{
        insertarNodo(&(*c)->sig, codChof, recorridoKms, nombre);
    }

}

void mostrarListaCompleta(nodo* nodo){

    printf("|| Cod. Chofer || Nombre || Viajes || Kms || Gastos\n\n");
    while(nodo != NULL){
        printf("||   %d   ||   %s   ||   %d   ||   %d   ||   %.2f   ||\n", nodo->cod_chof, nodo->nom_chof, nodo->cv, nodo->ckms, nodo->gastoviaje);
        nodo = nodo->sig;
    }
}

void mostrarListaRecorridos(nodo* nodo){

    printf("|| Cod. Chofer || Nombre || Viajes || Kms\n\n");
    while(nodo != NULL){
        printf("||   %d   ||   %s   ||   %d   ||   %d   ||\n", nodo->cod_chof, nodo->nom_chof, nodo->cv, nodo->ckms);
        nodo = nodo->sig;
    }
}

nodo* ordenarLista(nodo* c){

    nodo* auxUno;
    nodo* auxDos;
    float aux = 0;

    auxUno = c;
    while(auxUno != NULL){

        auxDos = auxUno->sig;

        while(auxDos != NULL){
            if(auxUno->gastoviaje < auxDos->gastoviaje){
                aux = auxUno->gastoviaje;
                auxUno->gastoviaje = auxDos->gastoviaje;
                auxDos->gastoviaje = aux;
            }
            auxDos = auxDos->sig;
        }
        auxUno = auxUno->sig;
    }
    auxUno = c;

    return auxUno;
}

int menu(){

    int opcion;

    do{
        printf("\t\t\t\t\tMenu\n");
        printf("\t1. Ingresar viaje\n");
        printf("\t2. Mostrar informe de cantidad de viajes y Kms recorridos por cada chofer (Bloquea la opcion 1)\n");
        printf("\t3. Mostrar lista de choferes sin ordenar\n");
        printf("\t4. Mostrar la lista ordenada por gastos de recorrido: $200 por cada 100 Kms\n");
        printf("\t5. Salir\n");

        printf("\n\t\tSeleccione una opcion: ");
        scanf("%d", &opcion);
        printf("\n");

    }while(opcion < 1 || opcion > 5);

    return opcion;
}

int main(){

    nodo* cabeza = NULL;
    nodo* ordenado = NULL;
    int m, codChof = 0, cantKms = 0, bandera = 0;
    char nombreChof[20] = {0};
    char listaChoferes[][20] = {"Chofer 1", "Chofer 2", "Chofer 3", "Chofer 4", "Chofer 5", "Chofer 6"};

    do{

        m = menu();

        switch(m){
            case 1:

                if(bandera == 1){
                    break;
                }

                printf("Ingrese el codigo del chofer: ");
                scanf("%d", &codChof);

                while(codChof < 1 || codChof > 6){
                    printf("\nCodigo inexistente...\n");
                    printf("Reingrese el codigo: ");
                    scanf("%d", &codChof);
                }

                strcpy(nombreChof, listaChoferes[codChof-1]);

                printf("Ingrese la cantidad de kilometros recorridos: ");
                scanf("%d", &cantKms);

                insertarNodo(&cabeza, codChof, cantKms, nombreChof);

                system("cls");
                break;
            case 2:
                mostrarListaRecorridos(cabeza);
                bandera = 1;
                system("pause");
                system("cls");
                break;
            case 3:
                mostrarListaCompleta(cabeza);
                system("pause");
                system("cls");
                break;
            case 4:
                ordenado = ordenarLista(cabeza);
                mostrarListaCompleta(ordenado);
                system("pause");
                system("cls");
                break;
        }

    }while(m != 5);

    return 0;
}
