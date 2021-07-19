#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define NUM_DIGITOS 3
#define NUM_LETRAS 3
#define MAX_TRIPULANTES 9

typedef struct ClaveStruct{
    unsigned short parteDigitos[NUM_DIGITOS];
    char parteLetras[NUM_LETRAS];
}Clave;

typedef struct nodoStruct{
    Clave clave;
    struct nodoStruct *siguiente;
}Nodo;

typedef struct listaClaves{
    int ocupacion;
    Nodo cabeza;
}ListaClaves;



void introducirClaveManual(Clave *nueva);
void imprimirClave(const Clave clave);
unsigned short checkIgualdadClaves(const Clave claveSecreta, const Clave intento);
int defenestrarTripulante(unsigned short numTripulantes);
Clave generarClaveSecreta();
Clave generarClaveDistorsionada(const Clave claveSecreta);
void insertarEnLista(Clave valor, ListaClaves *listaClaves);
void imprimirLista (ListaClaves listaClaves, int tabulaciones);
/* Funciones adicionales */
    //Listas
    void inicializarLista(Clave valor, ListaClaves *listaClaves);
    //Funciones estéticas
    void printTitulo(char a[]);
    void printCajita(char a[], unsigned int tabulaciones);
    void printTripulantes(int numTripulantes);
    //Funciones de jugar
    void explicarFuncionamiento();
    void crearPartida(int *numTripulantes);

int main(){
    Clave claveSecreta;
    Clave intento;
    ListaClaves listaClaves;
    unsigned int numTripulantes = 1;
    int ganar = 1, acabar = 0;
    char opcion;

    /** Pantalla de bienvenida **/
    printTitulo("- TOTALLY NOT AMONG US -");
    printCajita("Pulsa cualquier tecla.", 1);
    printf("\t>");
    opcion = getch();
    system("@cls||clear");
    /** Menú principal **/
    do{
        system("@cls||clear");
        printTitulo("- TOTALLY NOT AMONG US -");
        printCajita("E - Funcionamiento del juego",1);
        printCajita("J - Jugar",1);
        printCajita("Cualquier otra tecla - Salir",1);
        printf("\t>");
        opcion = getch();
        opcion = toupper(opcion);
        system("@cls||clear");
            switch(opcion){
                case 'E':
                    explicarFuncionamiento();
                    break;
                case 'J':
                    crearPartida(&numTripulantes);
                    claveSecreta = generarClaveSecreta();
                    inicializarLista(generarClaveDistorsionada(claveSecreta), &listaClaves);
                    do{
                        if(numTripulantes != 1){
                            /* Info sobre los tripulantes */
                            printCajita("- ESTADO DE LA NAVE -", 0);
                            printTripulantes(numTripulantes);
                            printCajita("Claves que tienes:", 0);
                            imprimirLista(listaClaves, 1);
                            printf("\n\tPulsa cualquier tecla para continuar.\n", 1);
                            printf("\t>");
                            opcion = getch();
                            system("@cls||clear");
                            /* Pantalla de matar */
                            printCajita("MATANDO...",0);
                            printf("\n\t%cQu%c es eso?%cUn desventurado camarada?\n", 168, 130, 168);
                            printf("\n\tPulsa cualquier tecla para matarlo.\n");
                            printf("\t>");
                            opcion = getch();
                            insertarEnLista(generarClaveDistorsionada(claveSecreta), &listaClaves);
                            numTripulantes--;
                            system("@cls||clear");
                            printCajita("KILLED",0);
                            printf("\n\t%cVaya! Pobre del alma que ha partido al cielo... gracias a ti.", 173);
                            printf("\n\n\tPulsa cualquier tecla para continuar.\n");
                            printf("\t>");
                            opcion = getch();
                            system("@cls||clear");
                            /* Defenestrar */
                            if(numTripulantes != 1){
                                printCajita("LOS CAMARADAS DECIDEN SI ECHAN A ALGUIEN", 0);
                                printf("\n\t...\n\t");
                                clock_t start_time = clock();
                                while (clock() < start_time + 1600);
                                if(defenestrarTripulante(numTripulantes) == 1){//Probabilidad de 1/numTripulantes
                                    /* Te expulsan */
                                    printf("\n\tTe han expulsado de la nave :(");
                                    printf("\n\n\tPulsa cualquier tecla para continuar.\n");
                                    printf("\t>");
                                    opcion = getch();
                                    acabar = 1;
                                    ganar = 0;
                                }
                                else{
                                    printf("\n\tPerfecto, sigues dentro de la nave >:)");
                                    printf("\n\n\tPulsa cualquier tecla para continuar.\n");
                                    printf("\t>");
                                    opcion = getch();
                                    system("@cls||clear");
                                    /*Adivinar la clave*/
                                    printCajita("- ADIVINAR LA CLAVE -", 0);
                                    printf("\n\tEstas son las claves que has ido recogiendo:\n");
                                    imprimirLista(listaClaves, 1);
                                    printf("\n\t%cQuieres probar a introducir la clave del reactor?\n", 168);
                                    printf("\tPulsa la tecla S para indicar que s%c.\n", 161);
                                    printf("\t>");
                                    opcion = getch();
                                    system("@cls||clear");
                                    if(toupper(opcion) == 'S'){
                                        introducirClaveManual(&intento);
                                        if(checkIgualdadClaves(claveSecreta, intento)){
                                            printCajita("** CLAVE CORRECTA. LA NAVE SE VA A AUTODESTRUIR. **", 0);
                                            acabar = 1;
                                            ganar = 1;
                                        }
                                        else
                                            printCajita("** CLAVE INCORRECTA. **", 0);
                                        printf("\n\tPulsa cualquier tecla para continuar.\n");
                                        printf("\t>");
                                        opcion = getch();
                                    }
                                    else{
                                        printCajita("Ok, buena suerte en la siguiente ronda ;)", 0);
                                        printf("\n\tPulsa cualquier tecla para continuar.\n");
                                        printf("\t>");
                                        opcion = getch();
                                    }

                                }
                            }
                        }
                        else{
                            printCajita("** HAS MATADO A TODOS, VAYA INSTINTO ASESINO **", 0);
                            printf("\n\tPulsa cualquier tecla para continuar.\n");
                            printf("\t>");
                            opcion = getch();
                            acabar = 1;
                            ganar = 1;
                        }
                        system("@cls||clear");
                    }while(!acabar);
                    system("@cls||clear");
                    if(ganar)
                        printCajita("GANASTE, GG", 0);
                    else{
                        printCajita("PERDISTE :(", 0);
                        printf("\tLa clave era ");
                        imprimirClave(claveSecreta);
                    }
                    printf("\n\tPulsa cualquier tecla para continuar.\n", 1);
                    printf("\t>");
                    opcion = getch();
                    opcion = 'E';//Para que no se salga del bucle
                    break;
                default:
                    printCajita("----------------- HASTA LUEGO, GRACIAS POR JUGAR UWU -----------------",0);
                    printf("\n\n");
                    break;
            }
    }while(opcion == 'E' || opcion == 'J');

    return 0;
}

void introducirClaveManual(Clave *nueva){
    int digitos;
    char letras[NUM_LETRAS];
    int i;

    printf("\tIntroduce la parte num%crica:\n\t>", 130);
    scanf("%d", &digitos);
    for(i = 0; i < NUM_DIGITOS; i++){
        nueva->parteDigitos[(NUM_DIGITOS-1)-i] = digitos - (digitos/10)*10;
        digitos /= 10;
    }
    printf("\tIntroduce la parte alfab%ctica:\n\t>", 130);
    scanf("%s",letras);
    for(i = 0; i < NUM_LETRAS; i++)
        nueva->parteLetras[i] = toupper(nueva->parteLetras[i]);
    for(i = 0; i < NUM_LETRAS; i++)
        nueva->parteLetras[i] = letras[i];
}

void imprimirClave(const Clave clave){
    int i;

    printf("(");
    for (i = 0; i < NUM_DIGITOS; ++i)
        printf("%d",clave.parteDigitos[i]);
    printf(", ");
    for (i = 0; i < NUM_LETRAS; ++i)
        printf("%c",clave.parteLetras[i]);
    printf(")\n");
}

unsigned short checkIgualdadClaves(const Clave claveSecreta, const Clave intento){
    int i;
    int result = 1;

    for(i = 0; i < NUM_DIGITOS; i++)
        if (claveSecreta.parteDigitos[i] != intento.parteDigitos[i])
            result = 0;

    for(i = 0; i < NUM_LETRAS; i++)
        if (claveSecreta.parteLetras[i] != toupper(intento.parteLetras[i]))
            result = 0;

    return result;
}

int defenestrarTripulante(unsigned short numTripulantes){
    srand(time(NULL));
    return rand() % numTripulantes;
}

Clave generarClaveSecreta(){
    Clave c;
    int i;

    srand(time(NULL));
    for(i = 0; i < NUM_DIGITOS; i++){
        do{
            c.parteDigitos[i] = rand()%8;
        }while(c.parteDigitos[i] < 1 || c.parteDigitos[i] > 8);
    }
    for(i = 0; i < NUM_LETRAS; i++){
        do{
            c.parteLetras[i] = rand()%23 + 66;//Genera un rand entre 66 y 89, que son los códigos ASCII de las letras B e Y
        }while(c.parteLetras[i] < 66 || c.parteLetras[i] > 89);
    }

    return c;
}
Clave generarClaveDistorsionada(const Clave claveSecreta){
    Clave c;
    int i;

    for(i = 0; i < NUM_DIGITOS; i++){
        c.parteDigitos[i] = claveSecreta.parteDigitos[i];//Copiar de la clave secreta
        c.parteDigitos[i] += (rand()%2 - 1);//Sumarle o restarle 1 al azar
        c.parteDigitos[i] %= 8;//Evitar que se salga de rango
    }//Que no se pase de 8
    for(i = 0; i < NUM_LETRAS; i++){
        c.parteLetras[i] = claveSecreta.parteLetras[i];//Copiar de la clave secreta
        c.parteLetras[i] += (rand()%2 - 1);//Sumarle o restarle 1 al azar
        c.parteLetras[i] -= 66;//La letra más baja es la B, el ASCII 66
        c.parteLetras[i] %= 23;//Evitar que se salga de rango
        c.parteLetras[i] += 66;//Volvemos a ponerlo donde estaba
    }

    return c;
}
void insertarEnLista(Clave valor, ListaClaves *listaClaves){
    Nodo *it;
    int i;

    it = &(*listaClaves).cabeza;
    while((*it).siguiente != NULL)
        it = (*it).siguiente;

    (*it).siguiente = (Nodo *)malloc(sizeof(Nodo));
    for(i = 0; i < NUM_DIGITOS; i++)
        (*it).siguiente->clave.parteDigitos[i] = valor.parteDigitos[i];
    for(i = 0; i < NUM_LETRAS; i++)
        (*it).siguiente->clave.parteLetras[i] = valor.parteLetras[i];
    (*it).siguiente->siguiente = NULL;
    (*listaClaves).ocupacion++;
}
void imprimirLista (ListaClaves listaClaves, int tabulaciones){
    Nodo *it;
    unsigned int cont = 1;

    it = &listaClaves.cabeza;
    while(it != NULL){
        if(cont > 1){
            for(int i = 1; i <= tabulaciones; i++)
                printf("\t");
            imprimirClave((*it).clave);
        }
        cont++;
        it = (*it).siguiente;
    }
    if(cont == 2)
        printf("\n\tNinguna.");
}

void inicializarLista(Clave valor, ListaClaves *listaClaves){
    int i;
    for(i = 0; i < NUM_DIGITOS; i++)
        (*listaClaves).cabeza.clave.parteDigitos[i] = valor.parteDigitos[i];
    for(i = 0; i < NUM_LETRAS; i++)
        (*listaClaves).cabeza.clave.parteLetras[i] = valor.parteLetras[i];

    (*listaClaves).cabeza.siguiente = NULL;
    (*listaClaves).ocupacion = 1;
}
void printTitulo(char a[]){
    int i, j = 0;
    /*Arriba*/
    printf("%c%c",176,177);
    for(i = 0; i <= strlen(a)+7; i++)
        printf("%c",178);
    printf("%c%c\n",177,176);
    /*Medio*/
    printf("%c%c%c%c%c ",176,177,178,177,176);
    while(a[j]!='\0'){
        printf("%c",a[j]);
        j++;
    }
    printf(" %c%c%c%c%c\n",176,177,178,177,176);
    /*Abajo*/
    printf("%c%c",176,177);
    for(i = 0; i <= strlen(a)+7; i++)
        printf("%c",178);
    printf("%c%c\n",177,176);

}
void printCajita(char a[], unsigned int tabulaciones){
    int i,j = 0;
    /*Arriba*/
    if(tabulaciones > 0)
        for(i = 1; i <= tabulaciones; i++)
            printf("\t");
    printf("%c", 201);
    for(i = 0; i < strlen(a)+2; i++)
        printf("%c",205);
    printf("%c\n", 187);
    /*Medio*/
    if(tabulaciones > 0)
        for(i = 1; i <= tabulaciones; i++)
            printf("\t");
    printf("%c ",186);
    while(a[j]!='\0'){
        printf("%c",a[j]);
        j++;
    }
    printf(" %c\n", 186);
    /*Abajo*/
    if(tabulaciones > 0)
        for(i = 1; i <= tabulaciones; i++)
            printf("\t");
    printf("%c", 200);
    for(int i = 0; i < strlen(a)+2; i++)
        printf("%c",205);
    printf("%c\n", 188);

}
void printTripulantes(int numTripulantes){
    char tripulantes[23] = "Quedan ", tripAux[2];
    itoa(numTripulantes, tripAux, 10);
    strcat(tripulantes, tripAux);
    strcat(tripulantes, " triuplantes.");
    printCajita(tripulantes,0);
}
void explicarFuncionamiento(){
    char opcion;
    printCajita("---------------------------------------- FUNCIONAMIENTO ----------------------------------------", 0);
    printf("\t-Est%cs en una nave espacial y debes sabotear el reactor.\n", 160);
    printf("\t-Para ello, deber%cs obtener el c%cdigo del mismo a partir de los camaradas que asesines.\n", 160, 162);
    printf("\t-Ten en cuenta que en cada ronda pueden sospechar de ti y echarte de la nave.\n");
    printf("\n\tPulsa cualquier tecla para continuar.\n", 1);
    printf("\t>");
    opcion = getch();
    system("@cls||clear");
}
void crearPartida(int *numTripulantes){
    char opcion;
    do{
        printCajita("---------------------------------------- CREAR PARTIDA ----------------------------------------", 0);
        printf("\tCont%cndote a ti, %ccu%cntos tripulantes hay en la nave?", 160, 168, 160);
        printf("\n\t>");
        fflush(stdin);
        scanf("%c", &opcion);
        *numTripulantes = (int)opcion - 48;
        system("@cls||clear");
    }while(*numTripulantes < 3 || *numTripulantes > MAX_TRIPULANTES);
}
