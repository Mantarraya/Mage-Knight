#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Grafo.h"
#include "Pila.h"
#include "Cola.h"
#include <time.h>
#include <windows.h>
#include <conio.h>

#define MAXCARTAS 50
int cont = 0;
int indice_Enemigo = 11;
TPila ActionCard;
TCard DiscardDeck[MAXCARTAS];
int nDiscardDeck = 0;
TCard CartasMano[5];
int x=21;
TCola Enemigos; /* COLA DE ENEMIGOS */
TEnemigo EnemigoEnc_1; 
TEnemigo EnemigoEnc_2;
TEnemigo EnemigoEnc_3;
TEnemigo EnemigoEnc_4;
TEnemigo EnemigoEnc_5;
int ganar=0;
int posEAmiga=25;


int posEnemigo1=1;
int posEnemigo2=16;
int posEnemigo3=50;
int posEnemigo4=40;
int posEnemigo5=10;

typedef struct heroe{
    char nombre[30];
    int defensa;
    int nivel;
    int experiencia;
}THeroe;

int posActual = 4;
THeroe heroe;

TCard cartaEspecial;
TCard cartaWound;
TCard CartaMaxAtaque;
TCard CartaMaxDefensa;
TCard CartaMaxHeal;
TCard CartaMaxMove;

int posBigBoss=50;
TEnemigo BigBoss;


void gotoxy(int x,int y){  //x es la can de " " y y es "intro"
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
 }

void imprimir_Tienda(){
    FILE *db_Amiga;
    db_Amiga=fopen("amigo.txt","r");
    char linea[100];
    int indice =17;
    while((fgets(linea,200,db_Amiga))!= NULL && strlen(linea)!=0){
        gotoxy(140,indice++);
        printf("%s",linea);
    }
    fclose(db_Amiga);
}

void crear_Enemigos(){

	inicializar_Cola_Enemigos(&Enemigos);

	/* Insertaremos 5 enemigos */


	TEnemigo EnemigoActual; /* ENEMIGO A CREAR */

	/* ENEMIGO 1 - ANTIMAGE */

	strcpy(EnemigoActual.nombre,"SPIR");
	EnemigoActual.pAttack = 2;
	EnemigoActual.pDefend = 2;
	EnemigoActual.pExperience = 10;

	insertar_Enemigo(&Enemigos, EnemigoActual);

	/* ENEMIGO 2 - RAZOR */

	strcpy(EnemigoActual.nombre,"MORF");
	EnemigoActual.pAttack = 6;
	EnemigoActual.pDefend = 5;
	EnemigoActual.pExperience = 20;

	insertar_Enemigo(&Enemigos, EnemigoActual);

	/* ENEMIGO 3 - BLOOD */

	strcpy(EnemigoActual.nombre,"CLOC");
	EnemigoActual.pAttack = 5;
	EnemigoActual.pDefend = 10;
	EnemigoActual.pExperience = 10;

	insertar_Enemigo(&Enemigos, EnemigoActual);

	/* ENEMIGO 4 - SANDKING */

	strcpy(EnemigoActual.nombre,"IRON");
	EnemigoActual.pAttack = 10;
	EnemigoActual.pDefend = 5;
	EnemigoActual.pExperience = 20;

	insertar_Enemigo(&Enemigos, EnemigoActual);

	/* ENEMIGO 5 - TINKER */

	strcpy(EnemigoActual.nombre,"BAAL");
	EnemigoActual.pAttack = 1;
	EnemigoActual.pDefend = 3;
	EnemigoActual.pExperience = 20;

	insertar_Enemigo(&Enemigos, EnemigoActual);


}



void imprimirLineasHori(int n){
    int i;
    for (i=0;i<n;i++)
        printf("%c", 196);
}

void imprimirHoriDoble(int pos){
    int i;
    for (i=0; i<pos;i++)
        printf("%c",205);
 }
void imprimirVDoble(int posx){
    int i;
    for(i=0;i<50;i++){
        gotoxy(posx,3+i);
        printf("%c\n",186);
    }
}

void imprimir_Letra_Enemigo(){
    gotoxy(6, 43); printf("E\n");
    gotoxy(6, 44); printf("N\n");
    gotoxy(6, 45); printf("E\n");
    gotoxy(6, 46); printf("M\n");
    gotoxy(6, 47); printf("I\n");
    gotoxy(6, 48); printf("G\n");
    gotoxy(6, 49); printf("O\n");
    gotoxy(6, 50); printf("S\n");
}

void imprimir_marco_1(){

    printf(" %c",201); imprimirHoriDoble(180);printf("%c\n",187);
    int i;
    for (i = 0; i < 67; i++){
        printf(" %c%179c %c\n", 186, ' ', 186);
    }

    printf(" %c",200); imprimirHoriDoble(180);printf("%c",188);

}

void imprimir_marco_2(){

    int i;

    printf(" %c",201); imprimirHoriDoble(137); printf("%c",203); imprimirHoriDoble(42);printf("%c\n",187);

//51
    for (i = 0; i < 13; i++){
        printf(" %c %135c %c %41c%c\n", 186, ' ', 186, ' ', 186);
    }

    printf(" %c",186); printf(" %135c", ' '); printf(" %c",204); imprimirHoriDoble(42);printf("%c\n",185);

    for (i = 0; i < 25; i++){
        printf(" %c %135c %c %41c%c\n", 186, ' ', 186, ' ', 186);
    }

    printf(" %c",204); imprimirHoriDoble(137);printf("%c",206); imprimirHoriDoble(42); printf("%c\n", 185);  //185

     for (i = 0; i < 12; i++){
        printf(" %c %135c %c %41c%c\n", 186, ' ', 186, ' ', 186);
    }

     printf(" %c",204); imprimirHoriDoble(137);printf("%c",202); imprimirHoriDoble(42); printf("%c\n", 185);

    for (i = 0; i < 15; i++){
        printf(" %c%179c %c\n", 186, ' ', 186);
    }

    printf(" %c",200); imprimirHoriDoble(180);printf("%c\n",188);

    


}

void imprimir_Dragon(){

    FILE *db_Dragon;
    db_Dragon = fopen("dragon.txt", "r");

    char linea[100];
    int indice = 0;
    while (fgets(linea, 200, db_Dragon) != NULL && strlen(linea) != 0){
        gotoxy(15, indice++);
        printf("%s", linea);
    }

    fclose(db_Dragon);

}

void imprimir_Torre(int n){

    FILE *db_torre;
    db_torre = fopen("torre.txt", "r");

    char linea[100];
    int indice = 42;
    while (fgets(linea, 200, db_torre) != NULL && strlen(linea) != 0){
        gotoxy(n, indice++);
        printf("%s", linea);
    }

    fclose(db_torre);

}
void imprimir_Escudo(int n){

    FILE *db_escudo;
    db_escudo = fopen("escudo.txt", "r");

    char linea[100];
    int indice = 52;
    while (fgets(linea, 200, db_escudo) != NULL && strlen(linea) != 0){
        gotoxy(n, indice++);
        printf("%s", linea);
    }

    fclose(db_escudo);

}

void inicio_Juego(){

    system("cls");

    imprimir_marco_1();
    imprimir_Dragon();
    imprimir_Torre(3);
    imprimir_Torre(20);
    imprimir_Torre(37);
    imprimir_Torre(54);
    imprimir_Torre(166);
    imprimir_Torre(149);
    imprimir_Torre(132);
    imprimir_Torre(115);
    imprimir_Escudo(77);
                                                                                           gotoxy(93,11);
    printf("          ___           ___           ___           ___                 \n");  gotoxy(93,12);
    printf("         /\\  \\         /\\  \\         /\\__\\         /\\__\\        \n");  gotoxy(93,13);
    printf("        |::\\  \\       /::\\  \\       /:/ _/_       /:/ _/_           \n");  gotoxy(93,14);
    printf("        |:|:\\  \\     /:/\\:\\  \\     /:/ /\\  \\     /:/ /\\__\\     \n");  gotoxy(93,15);
    printf("      __|:|\\:\\  \\   /:/ /::\\  \\   /:/ /::\\  \\   /:/ /:/ _/_      \n");  gotoxy(93,16);
    printf("     /::::|_\\:\\__\\ /:/_/:/\\:\\__\\ /:/__\\/\\:\\__\\ /:/_/:/ /\\__\\\n");  gotoxy(93,17);
    printf("     \\:\\~~\\  \\/__/ \\:\\/:/  \\/__/ \\:\\  \\ /:/  / \\:\\/:/ /:/  /\n");  gotoxy(93,18);
    printf("      \\:\\  \\        \\::/__/       \\:\\  /:/  /   \\::/_/:/  /      \n");  gotoxy(93,19);
    printf("       \\:\\  \\        \\:\\  \\        \\:\\/:/  /     \\:\\/:/  /    \n");  gotoxy(93,20);
    printf("        \\:\\__\\        \\:\\__\\        \\::/  /       \\::/  /       \n");  gotoxy(93,21);
    printf("         \\/__/         \\/__/         \\/__/         \\/__/            \n");

    gotoxy(88,25);
    printf("       ___           ___                       ___           ___                   \n"); gotoxy(88,26);
    printf("      /|  |         /\\  \\                     /\\__\\         /\\  \\                 \n");    gotoxy(88,27);
    printf("     |:|  |         \\:\\  \\       ___         /:/ _/_        \\:\\  \\         ___    \n");    gotoxy(88,28);
    printf("     |:|  |          \\:\\  \\     /\\__\\       /:/ /\\  \\        \\:\\  \\       /\\__\\   \n");    gotoxy(88,29);
    printf("   __|:|  |      _____\\:\\  \\   /:/__/      /:/ /::\\  \\   ___ /::\\  \\     /:/  /   \n");    gotoxy(88,30);
    printf("  /\\ |:|__|____ /::::::::\\__\\ /::\\  \\     /:/__\\/\\:\\__\\ /\\  /:/\\:\\__\\   /:/__/    \n");   gotoxy(88,31);
    printf("  \\:\\/:::::/__/ \\:\\~~\\~~\\/__/ \\/\\:\\  \\__  \\:\\  \\ /:/  / \\:\\/:/  \\/__/  /::\\  \\    \n"); gotoxy(88,32);
    printf("   \\::/~~/~      \\:\\  \\        ~~\\:\\/\\__\\  \\:\\  /:/  /   \\::/__/      /:/\\:\\  \\   \n");  gotoxy(88,33);
    printf("    \\:\\~~\\        \\:\\  \\          \\::/  /   \\:\\/:/  /     \\:\\  \\      \\/__\\:\\  \\  \n");gotoxy(88,34);
    printf("     \\:\\__\\        \\:\\__\\         /:/  /     \\::/  /       \\:\\__\\          \\:\\__\\ \n");  gotoxy(88,35);
    printf("      \\/__/         \\/__/         \\/__/       \\/__/         \\/__/           \\/__/ \n\n\n");
}

void imprimir_Contornos_Mapa(){

    FILE *db_Dragon;
    db_Dragon = fopen("contorno.txt", "r");

    char linea[100];
    int indice = 5;
    while (fgets(linea, 200, db_Dragon) != NULL && strlen(linea) != 0){
        gotoxy(66, indice++);
        printf("%s", linea);
    }

    fclose(db_Dragon);

}


void imprimir_Tile_1(){

    gotoxy(48+30,23);
    printf("      /   \\   /   \\\n");
    gotoxy(48+30,24);
    printf("    :  06F  :  07P  :\n");
    gotoxy(48+30,25);
    printf("  /   \\   /   \\   /   \\\n");
    gotoxy(48+30,26);
    printf(":  03P  :  04H  :  05F  :\n");
    gotoxy(48+30,27);
    printf("  \\   /   \\   /   \\   /\n");
    gotoxy(48+30,28);
    printf("    :  01F  :  02F  :\n");
    gotoxy(48+30,29);
    printf("      \\   /   \\   /\n");  

}

void imprimir_Tile_2(){
    gotoxy(44+30,17);
    printf("      /   \\   /   \\\n");
    gotoxy(44+30,18);
    printf("    :  20U  :  21F  :\n");
    gotoxy(44+30,19);
    printf("  /   \\   /   \\   /   \\\n");
    gotoxy(44+30,20);
    printf(":  15S  :  16P  :  17H  :\n");
    gotoxy(44+30,21);
    printf("  \\   /   \\   /   \\   /\n");
    gotoxy(44+30,22);
    printf("    :  10F  :  11P  :\n");
    gotoxy(44+30,23);
    printf("      \\   /   \\   /\n");

}

void imprimir_Tile_4(){

    gotoxy(40+30,11);
    printf("      /   \\   /   \\\n");
    gotoxy(40+30,12);
    printf("    :  36S  :  37H  :\n");
    gotoxy(40+30,13);
    printf("  /   \\   /   \\   /   \\\n");
    gotoxy(40+30,14);
    printf(":  29S  :  30P  :  31F  :\n");
    gotoxy(40+30,15);
    printf("  \\   /   \\   /   \\   /\n");
    gotoxy(40+30,16);
    printf("    :  24F  :  25H  :\n");
    gotoxy(40+30,17);
    printf("      \\   /   \\   /\n");



}

void imprimir_Tile_3(){

    gotoxy(34+36+30,19);
    printf("/   \\   /   \\\n");
    gotoxy(32+36+30,20);
    printf(":  18S  :  19P  :\n");
    gotoxy(30+36+30,21);
    printf("/   \\   /   \\   /   \\\n");
    gotoxy(28+36+30,22);
    printf(":  12P  :  13P  :  14F  :\n");
    gotoxy(30+36+30,23);
    printf("\\   /   \\   /   \\   /\n");
    gotoxy(32+36+30,24);
    printf(":  08S  :  09F  :\n");
    gotoxy(34+36+30,25);
    printf("\\   /   \\   /\n");


    /*
    gotoxy(64,19);
    printf("      /   \\   /   \\\n");
    gotoxy(64,20);
    printf("    :  18S  :  19P  :\n");
    gotoxy(64,21);
    printf("  /   \\   /   \\   /   \\\n");
    gotoxy(64,22);
    printf(":  12P  :  13P  :  14F  :\n");
    gotoxy(64,23);
    printf("  \\   /   \\   /   \\   /\n");
    gotoxy(64,24);
    printf("    :  08S  :  09F  :\n");
    gotoxy(64,25);
    printf("      \\   /   \\   /\n");

    */
}

void imprimir_Tile_5(){
    gotoxy(30+36+30,13);
    printf("/   \\   /   \\\n");
    gotoxy(28+36+30,14);
    printf(":  32F  :  33F  :\n");
    gotoxy(26+36+30,15);
    printf("/   \\   /   \\   /   \\\n");
    gotoxy(24+36+30,16);
    printf(":  26F  :  27U  :  28S  :\n");
    gotoxy(26+36+30,17);
    printf("\\   /   \\   /   \\   /\n");
    gotoxy(28+36+30,18);
    printf(":  22H  :  23P  :\n");
    gotoxy(30+36+30,19);
    printf("\\   /   \\   /\n");
}

void imprimir_Tile_6(){

    gotoxy(36+30,5);
    printf("      /   \\   /   \\\n");
    gotoxy(36+30,6);
    printf("    :  55F  :  56S  :\n");
    gotoxy(36+30,7);
    printf("  /   \\   /   \\   /   \\\n");
    gotoxy(36+30,8);
    printf(":  50S  :  51H  :  52H  :\n");
    gotoxy(36+30,9);
    printf("  \\   /   \\   /   \\   /\n");
    gotoxy(36+30,10);
    printf("    :  43P  :  44U  :\n");
    gotoxy(36+30,11);
    printf("      \\   /   \\   /\n");

}

imprimir_Tile_7(){

    gotoxy(26+36+30,3+4);
    printf("/   \\   /   \\\n");
    gotoxy(24+36+30,4+4);
    printf(":  53P  :  54P  :\n");
    gotoxy(22+36+30,5+4);
    printf("/   \\   /   \\   /   \\\n");
    gotoxy(20+36+30,6+4);
    printf(":  45F  :  46S  :  47S  :\n");
    gotoxy(22+36+30,7+4);
    printf("\\   /   \\   /   \\   /\n");
    gotoxy(24+36+30,8+4);
    printf(":  38F  :  39P  :\n");
    gotoxy(26+36+30,9+4);
    printf("\\   /   \\   /\n");

}

imprimir_Tile_8(){

    gotoxy(46+36+30,5+4);
    printf("/   \\   /   \\\n");
    gotoxy(44+36+30,6+4);
    printf(":  48F  :  49S  :\n");
    gotoxy(42+36+30,7+4);
    printf("/   \\   /   \\   /   \\\n");
    gotoxy(40+36+30,8+4);
    printf(":  40F  :  41F  :  42P  :\n");
    gotoxy(42+36+30,9+4);
    printf("\\   /   \\   /   \\   /\n");
    gotoxy(44+36+30,10+4);
    printf(":  34P  :  35S  :\n");
    gotoxy(46+36+30,11+4);
    printf("\\   /   \\   /\n");
}

void imprimir_Enemigo(TEnemigo EnemigoEncontrado, int posActual){
    x = 43;
    gotoxy(indice_Enemigo,x++);	printf("POSICION DEL ENEMIGO: %d\n\n\n", posActual);
	gotoxy(indice_Enemigo,x++);	printf("%c",218); imprimirLineasHori(20); printf("%c \n",191);
    gotoxy(indice_Enemigo,x++);	printf("%c      ENEMIGO       %c\n",179,179);
    gotoxy(indice_Enemigo,x++);	printf("%c", 195);imprimirLineasHori(20) ;printf("%c\n",180);
    gotoxy(indice_Enemigo,x++);	printf("%c",179); printf(" Enemigo    : %5s", EnemigoEncontrado.nombre);  printf(" %c\n",179);
    gotoxy(indice_Enemigo,x++);	printf("%c",179); printf(" Atacke     : %5d", EnemigoEncontrado.pAttack); printf(" %c\n",179);
    gotoxy(indice_Enemigo,x++);	printf("%c",179); printf(" Defensa    : %5d", EnemigoEncontrado.pDefend); printf(" %c\n",179);
    gotoxy(indice_Enemigo,x++);	printf("%c",179); printf(" Experiencia: %5d", EnemigoEncontrado.pExperience); printf(" %c\n",179);
    gotoxy(indice_Enemigo,x++);	printf("%c",192); imprimirLineasHori(20); printf("%c",217);
    printf("\n\n\n");
    indice_Enemigo += 25;
}

void imprimir_Enemigo_En_Batalla(TEnemigo EnemigoEncontrado){

    x = 29;

    gotoxy(150,x++); printf("%c",218); imprimirLineasHori(20); printf("%c \n",191);
    gotoxy(150,x++); printf("%c      ENEMIGO       %c\n",179,179);
    gotoxy(150,x++); printf("%c", 195);imprimirLineasHori(20) ;printf("%c\n",180);
    gotoxy(150,x++); printf("%c",179); printf(" Enemigo    : %5s", EnemigoEncontrado.nombre);  printf(" %c\n",179);
    gotoxy(150,x++); printf("%c",179); printf(" Atacke     : %5d", EnemigoEncontrado.pAttack); printf(" %c\n",179);
    gotoxy(150,x++); printf("%c",179); printf(" Defensa    : %5d", EnemigoEncontrado.pDefend); printf(" %c\n",179);
    gotoxy(150,x++); printf("%c",179); printf(" Experiencia: %5d", EnemigoEncontrado.pExperience); printf(" %c\n",179);
    gotoxy(150,x++); printf("%c",192); imprimirLineasHori(20); printf("%c",217);
    printf("\n\n\n");
}


void imprimirLineasHori2(int n){
    int i;
    printf("%c",218);
    for (i=0;i<n;i++)
        printf("%c", 196);
    printf("%c", 191);
}

void imprimirLineasHori4(int n){
    int i;
    printf("%c",195);
    for (i=0;i<n;i++)
        printf("%c", 196);
    printf("%c", 180);
}

void imprimirLineasHori3(int n){
    int i;
    printf("%c",192);
    for (i=0;i<n;i++)
        printf("%c", 196);
    printf("%c", 217);
}

void imprimir_Estadisticas(THeroe heroe, int posActual){
        gotoxy(147,3);         printf("POSICION ACTUAL DEL HEROE: %d\n\n\n", posActual);
		gotoxy(143,4);         printf("%c",218); imprimirLineasHori(34); printf("%c \n",191);
        gotoxy(143,5);         printf("%c          ESTADISTICAS            %c\n", 179, 179);
        gotoxy(143,6);         printf("%c", 195);imprimirLineasHori(34) ;printf("%c\n",180);
        gotoxy(143,7);         printf("%c",179); printf("  ____   Heroe      : %11s",heroe.nombre); printf(" %c\n",179);
        gotoxy(143,8);         printf("%c",179); printf(" /    \\  Defensa    : %11d", heroe.defensa);printf(" %c\n",179);
        gotoxy(143,9);         printf("%c",179); printf(" \\ MK /  Nivel      : %11d", heroe.nivel);printf(" %c\n",179);
        gotoxy(143,10);         printf("%c",179); printf("  \\__/   Experiencia: %11d", heroe.experiencia);printf(" %c\n",179);
        gotoxy(143,11);         printf("%c",192); imprimirLineasHori(34); printf("%c",217);
        gotoxy(143,12);         printf("\n\n\n");
 }

void imprimir_Espacio(int n){
    int i;
    for (i = 0; i < n; i++)
        printf(" ");
}

 void imprimir_Cartas_Mano(int numCarta,int posCarta){
 	int i;
    gotoxy(posCarta, 58); imprimirLineasHori2(18) ; printf("\n");
	gotoxy(posCarta, 59); printf("%c    %s",179,CartasMano[numCarta].nombre); imprimir_Espacio(14-strlen(CartasMano[numCarta].nombre));printf("%c\n", 179);
	gotoxy(posCarta, 60); imprimirLineasHori4(18); printf("\n");

	/* Move */

	gotoxy(posCarta, 61); 
    printf("%c",179);
	for (i = 0; i < CartasMano[numCarta].pMove; i++)
		printf("*");
	for (i = CartasMano[numCarta].pMove; i < 5; i++)
		printf(" ");
	printf("  Move   : %1d %c\n", CartasMano[numCarta].pMove,179);

	/* Attack */

    gotoxy(posCarta, 62);
	printf("%c",179);
	for (i = 0; i < CartasMano[numCarta].pAttack; i++)
		printf("*");
	for (i = CartasMano[numCarta].pAttack; i < 5; i++)
		printf(" ");
	printf("  Attack : %1d %c\n", CartasMano[numCarta].pAttack,179);

	/* Defend */

    gotoxy(posCarta, 63);
	printf("%c",179);
	for (i = 0; i < CartasMano[numCarta].pDefend; i++)
		printf("*");
	for (i = CartasMano[numCarta].pDefend; i < 5; i++)
		printf(" ");
	printf("  Defend : %1d %c\n", CartasMano[numCarta].pDefend,179);

	/* Heal */

    gotoxy(posCarta, 64); 
	printf("%c",179);
	for (i = 0; i < CartasMano[numCarta].pHeal; i++)
		printf("*");
	for (i = CartasMano[numCarta].pHeal; i < 5; i++)
		printf(" ");
	printf("  Heal   : %1d %c\n", CartasMano[numCarta].pHeal,179);
	/* Buy */

    gotoxy(posCarta, 65);
	printf("%c",179);
	for (i = 0; i < CartasMano[numCarta].pBuy; i++)
		printf("*");
	for (i = CartasMano[numCarta].pBuy; i < 5; i++)
		printf(" ");
	printf("  Buy    : %1d %c\n", CartasMano[numCarta].pBuy,179);

    gotoxy(posCarta, 66);
	imprimirLineasHori3(18);



 }

void barajear_DiscardDeck(TCard DiscardDeck[],int n){

    int i;
    for (i = n-1; i >= 1; i--){
        int pos = rand() % i;
        TCard aux = DiscardDeck[i];
        DiscardDeck[i] = DiscardDeck[pos];
        DiscardDeck[pos] = aux;
    }

}

void imprimir_DiscardDeck(TCard DiscardDeck[],int n){

    int i;
    for (i = 0; i < n; i++){
        printf("%d.- %s\n",i+1, DiscardDeck[i].nombre);
        printf("%8s: %d\n", "Attack", DiscardDeck[i].pAttack);
        printf("%8s: %d\n", "Buy", DiscardDeck[i].pBuy);
        printf("%8s: %d\n", "Defend", DiscardDeck[i].pDefend);
        printf("%8s: %d\n", "Heal", DiscardDeck[i].pHeal);
        printf("%8s: %d\n\n", "Move", DiscardDeck[i].pMove);
    }
}

void agregar_Carta_DiscardDeck(TCard DiscardDeck[], TCard carta ,int *nDiscardDeck){

    DiscardDeck[*nDiscardDeck] = carta;

    (*nDiscardDeck)++;

}
TCard quitar_Carta_DiscarDeck(TCard DiscardDeck[] ,int *nDiscardDeck){

    (*nDiscardDeck)--;

    return DiscardDeck[(*nDiscardDeck)];

}

int aleatorio(int a, int b){

   int value = rand() % (b-a+1) + a;
   return value;

}

//llenar las cartas
void Baraja_Inicial(){

    int i;
    inicializar_Baraja(&ActionCard);

    TCard carta;

    for(i=0; i<10000; i++){


        int tipoCard=aleatorio(1,5);


        //printf("value si %d\n", value);

        if(tipoCard==1){
    		carta.nombre="BONUS ATACK";
    		carta.pAttack=aleatorio(2,5);
    		carta.pBuy=1;
    		carta.pDefend=1;
    		carta.pHeal=1;
    		carta.pMove=1;
        }else if(tipoCard==2){
    		carta.nombre="BONUS BUY";
    		carta.pBuy=aleatorio(2,5);
    		carta.pAttack=1;
    		carta.pDefend=1;
    		carta.pHeal=1;
    		carta.pMove=1;
        }else if(tipoCard==3){
    		carta.nombre="BONUS DEFEND";
    		carta.pDefend=aleatorio(2,5);
    		carta.pBuy=1;
    		carta.pAttack=1;
    		carta.pHeal=1;
    		carta.pMove=1;
        }else if(tipoCard==4){
        	carta.nombre="BONUS HEAL";
        	carta.pHeal=aleatorio(2,5);
        	carta.pDefend=1;
        	carta.pBuy=1;
        	carta.pAttack=1;
        	carta.pMove=1;
        }else if(tipoCard==5){
    		carta.nombre="BONUS MOVE";
    		carta.pMove=aleatorio(2,5);
    		carta.pAttack=1;
    		carta.pBuy=1;
    		carta.pDefend=1;
    		carta.pHeal=1;
         }

        insertar_Carta_Baraja(&ActionCard, carta);
    }

    cartaEspecial.nombre="  ESPECIAL";
    cartaEspecial.pAttack=5;
    cartaEspecial.pBuy=1;
    cartaEspecial.pDefend=1;
    cartaEspecial.pHeal=1;
    cartaEspecial.pMove=1;

    cartaWound.nombre="  WOUND";
    cartaWound.pAttack=0;
    cartaWound.pBuy=0;
    cartaWound.pDefend=0;
    cartaWound.pHeal=0;
    cartaWound.pMove=0;

    CartaMaxAtaque.nombre="  ATAQUE MAX";
    CartaMaxAtaque.pAttack=5;
    CartaMaxAtaque.pBuy=1;
    CartaMaxAtaque.pDefend=1;
    CartaMaxAtaque.pHeal=1;
    CartaMaxAtaque.pMove=1;

    CartaMaxDefensa.nombre="  DEFENSA MAX";
    CartaMaxDefensa.pAttack=1;
    CartaMaxDefensa.pBuy=1;
    CartaMaxDefensa.pDefend=5;
    CartaMaxDefensa.pHeal=1;
    CartaMaxDefensa.pMove=1;

    CartaMaxHeal.nombre="  HEAL MAX";
    CartaMaxHeal.pAttack=1;
    CartaMaxHeal.pBuy=1;
    CartaMaxHeal.pDefend=1;
    CartaMaxHeal.pHeal=5;
    CartaMaxHeal.pMove=1;

    CartaMaxMove.nombre="  MOVE MAX";
    CartaMaxMove.pAttack=1;
    CartaMaxMove.pBuy=1;
    CartaMaxMove.pDefend=1;
    CartaMaxMove.pHeal=1;
    CartaMaxMove.pMove=5;


}

void llenar_Conexiones(int Conexiones[60][60]){
    FILE *db_conexion;
    db_conexion = fopen("mConexion.txt", "r");

    int i, j;

    for (i = 1; i <= 56; i++){
        for (j = 1; j <= 56; j++){
            fscanf(db_conexion, "%d ", &Conexiones[i][j]);
        }
    }

    fclose(db_conexion);
}

void llenar_Pesos(int Pesos[60][60]){
    FILE *db_pesos;
    db_pesos = fopen("mPeso.txt", "r");

    int i, j;

    for (i = 1; i <= 56; i++){
        for (j = 1; j <= 56; j++){
            fscanf(db_pesos, "%d ", &Pesos[i][j]);
        }
    }

    fclose(db_pesos);
}

void llenar_SpaceXTileVisual(int SpaceXTile[60][10]){
    FILE *db_spaceXTile;
    db_spaceXTile = fopen("visualizarSpaceXTile.txt", "r");

    int i, j;

    for (i = 1; i <= 56; i++){
        for (j = 1; j <= 8; j++){
            fscanf(db_spaceXTile, "%d ", &SpaceXTile[i][j]);
        }
    }
    fclose(db_spaceXTile);
}

void imprimir_Hill(){

    FILE *db_hill;
    db_hill = fopen("hill.txt", "r");

    char linea[100];
    int indice = 16;
    while (fgets(linea, 200, db_hill) != NULL && strlen(linea) != 0){
        gotoxy(10, indice++);
        printf("%s", linea);
    }

    fclose(db_hill);

}

void imprimir_Forest(){

    FILE *db_Forest;
    db_Forest = fopen("forest.txt", "r");

    char linea[100];
    int indice = 16;
    while (fgets(linea, 200, db_Forest) != NULL && strlen(linea) != 0){
        gotoxy(10, indice++);
        printf("%s", linea);
    }

    fclose(db_Forest);

}

void imprimir_Swamp(){

    FILE *db_Swamp;
    db_Swamp = fopen("swamp.txt", "r");

    char linea[100];
    int indice = 16;
    while (fgets(linea, 200, db_Swamp) != NULL && strlen(linea) != 0){
        gotoxy(10, indice++);
        printf("%s", linea);
    }

    fclose(db_Swamp);

}

void imprimir_Plain(){
    FILE *db_Plain;
    db_Plain = fopen("plain.txt", "r");

    char linea[100];
    int indice = 16;
    while (fgets(linea, 200, db_Plain) != NULL && strlen(linea) != 0){
        gotoxy(10, indice++);
        printf("%s", linea);
    }
    fclose(db_Plain);
}

void llenar_ArrTipoSpace(char arrTipoSpace[]){
    FILE *db_tipoSpace;
    db_tipoSpace = fopen("tipoSpace.txt", "r");
    int i;
    for (i = 0; i <= 60; i++)
        arrTipoSpace[i] = ' ';
    for (i = 1; i <= 56; i++)
        fscanf(db_tipoSpace,"%c ", &arrTipoSpace[i]);
    fclose(db_tipoSpace);
}


void agregarSpacesVisibles(int arrVisualSpace[60], int numTile){
    if(numTile==2){
        arrVisualSpace[10]=1;
        arrVisualSpace[11]=1;
        arrVisualSpace[15]=1;
        arrVisualSpace[16]=1;
        arrVisualSpace[17]=1;
        arrVisualSpace[20]=1;
        arrVisualSpace[21]=1;    
    }
    if(numTile==3){
        arrVisualSpace[8]=1;
        arrVisualSpace[9]=1;
        arrVisualSpace[12]=1;
        arrVisualSpace[13]=1;
        arrVisualSpace[14]=1;
        arrVisualSpace[18]=1;
        arrVisualSpace[19]=1;    
    }
    if(numTile==4){
        arrVisualSpace[24]=1;
        arrVisualSpace[25]=1;
        arrVisualSpace[29]=1;
        arrVisualSpace[30]=1;
        arrVisualSpace[31]=1;
        arrVisualSpace[36]=1;
        arrVisualSpace[37]=1;    
    }
    if(numTile==5){
        arrVisualSpace[22]=1;
        arrVisualSpace[23]=1;
        arrVisualSpace[25]=1;
        arrVisualSpace[26]=1;
        arrVisualSpace[28]=1;
        arrVisualSpace[32]=1;
        arrVisualSpace[33]=1;    
    }
    if(numTile==6){
        arrVisualSpace[43]=1;
        arrVisualSpace[44]=1;
        arrVisualSpace[50]=1;
        arrVisualSpace[51]=1;
        arrVisualSpace[52]=1;
        arrVisualSpace[55]=1;
        arrVisualSpace[56]=1;    
    }
    if(numTile==7){
        arrVisualSpace[38]=1;
        arrVisualSpace[39]=1;
        arrVisualSpace[45]=1;
        arrVisualSpace[46]=1;
        arrVisualSpace[47]=1;
        arrVisualSpace[53]=1;
        arrVisualSpace[54]=1;    
    }
    if(numTile==8){
        arrVisualSpace[34]=1;
        arrVisualSpace[35]=1;
        arrVisualSpace[40]=1;
        arrVisualSpace[41]=1;
        arrVisualSpace[42]=1;
        arrVisualSpace[48]=1;
        arrVisualSpace[49]=1;    
    }
}

void imprimir_bienvenido(){
    FILE *db_bienvenido;
    db_bienvenido = fopen("bienvenido.txt", "r");

    char linea[200];
    int i = 58;
    while (fgets(linea, 200, db_bienvenido) != NULL && strlen(linea) != 0){
            gotoxy(25, i);printf("%s", linea);
            i++;
    }
    fclose(db_bienvenido);
}

void imprimir_victoria(){
    FILE *db_victoria;
    db_victoria = fopen("VICTORIA.txt", "r");
    char linea[200];
    int i = 25;
    while (fgets(linea, 200, db_victoria) != NULL && strlen(linea) != 0){
            gotoxy(50, i);printf("%s", linea);
            i++;
    }
    fclose(db_victoria);
}



/*Muestras los Tiles visualisados durante el juego */
void imprimir_Tiles_Visualizados_Actual(int arrVisualTile[]){
    if (arrVisualTile[1])
        imprimir_Tile_1();
    if (arrVisualTile[2]) 
        imprimir_Tile_2();
    if (arrVisualTile[3]) 
        imprimir_Tile_3();
    if (arrVisualTile[4]) 
        imprimir_Tile_4();
    if (arrVisualTile[5]) 
        imprimir_Tile_5();
    if (arrVisualTile[6]) 
        imprimir_Tile_6();
    if (arrVisualTile[7]) 
        imprimir_Tile_7();
    if (arrVisualTile[8]) 
        imprimir_Tile_8();
}

void imprimir_Leyenda_Space(){
    gotoxy(22, 5); printf("  LEYENDA MOVE X SPACE:\n");
    gotoxy(22, 7); printf("P  ->  PLAIN           2\n");
    gotoxy(22, 8); printf("F  ->  FOREST          3\n");
    gotoxy(22, 9); printf("H  ->  HILL            4\n");
    gotoxy(22, 10); printf("S  ->  SWAMP           5\n");
    gotoxy(22, 11); printf("U  ->  UNREACHABLE     X\n");
    gotoxy(20, 13); printf("PRECIO PARA VISUALIZAR TILE: 2");
}


void imprimir_Enemigos_Visibles(int arrEnemigosVis[]){

    imprimir_Letra_Enemigo();

    indice_Enemigo = 11;
    
    if(arrEnemigosVis[0]==1) imprimir_Enemigo(EnemigoEnc_1,posEnemigo1);
    if(arrEnemigosVis[1]==1) imprimir_Enemigo(EnemigoEnc_2,posEnemigo2);
    if(arrEnemigosVis[2]==1) imprimir_Enemigo(EnemigoEnc_3,posEnemigo3);
    if(arrEnemigosVis[3]==1) imprimir_Enemigo(EnemigoEnc_4,posEnemigo4);
    if(arrEnemigosVis[4]==1) imprimir_Enemigo(EnemigoEnc_5,posEnemigo5);
}   


int buscarEnemigo(int arrVisualSpace[], int posEnemigo){
    int i;
    if(arrVisualSpace[posEnemigo]==1) return 1;
    return 0;    
}

void agregarEnemigoVisibles(int arrEnemigosVis[], int arrVisualSpace[]){
    int encontrado;
    encontrado=buscarEnemigo(arrVisualSpace, posEnemigo1);
    if(encontrado) {
        arrEnemigosVis[0]=1;
    }
    encontrado=buscarEnemigo(arrVisualSpace, posEnemigo2);
    if(encontrado) {
        arrEnemigosVis[1]=1;
    }
    encontrado=buscarEnemigo(arrVisualSpace, posEnemigo3);
    if(encontrado) {
        arrEnemigosVis[2]=1;
    }
    encontrado=buscarEnemigo(arrVisualSpace, posEnemigo4);
    if(encontrado) {
        arrEnemigosVis[3]=1;
    }
    encontrado=buscarEnemigo(arrVisualSpace, posEnemigo5);
    if(encontrado) {
        arrEnemigosVis[4]=1;
    }
}

imprimir_TipoSpace(char arrTipoSpace[], int posActual){
    if (arrTipoSpace[posActual] == 'F') imprimir_Forest();
    if (arrTipoSpace[posActual] == 'S') imprimir_Swamp();
    if (arrTipoSpace[posActual] == 'P') imprimir_Plain();
    if (arrTipoSpace[posActual] == 'H') imprimir_Hill();
}

void imprimir_marco_3(){
    int i;

    printf(" %c",201); imprimirHoriDoble(137); printf("%c",203); imprimirHoriDoble(42);printf("%c\n",187);

//51
    for (i = 0; i < 13; i++){
        printf(" %c %135c %c %41c%c\n", 186, ' ', 186, ' ', 186);
    }

    printf(" %c",186); printf(" %135c", ' '); printf(" %c",204); imprimirHoriDoble(42);printf("%c\n",185);

    for (i = 0; i < 25; i++){
        printf(" %c %135c %c %41c%c\n", 186, ' ', 186, ' ', 186);
    }

    printf(" %c",204); imprimirHoriDoble(137);printf("%c",185); for(i=0;i<42;i++)printf(" "); printf("%c\n", 186);  //185

     for (i = 0; i < 12; i++){
        printf(" %c %135c %c %41c%c\n", 186, ' ', 186, ' ', 186);
    }

     printf(" %c",204); imprimirHoriDoble(137);printf("%c",202); imprimirHoriDoble(42); printf("%c\n", 185);

    for (i = 0; i < 15; i++){
        printf(" %c%179c %c\n", 186, ' ', 186);
    }

    printf(" %c",200); imprimirHoriDoble(180);printf("%c\n",188);



}

void imprimir_Batalla(){

    FILE *db_batalla;
    db_batalla = fopen("lucha.txt", "r");

    char linea[200];
    int i = 3;
    while (fgets(linea, 200, db_batalla) != NULL && strlen(linea) != 0){
            gotoxy(16, i);
            printf("%s", linea);
            i++;
    }
    fclose(db_batalla);
}

void imprimir_Heroe(){

    FILE *db_heroe;
    db_heroe = fopen("heroe.txt", "r");

    char linea[200];
    int i = 17;
    while (fgets(linea, 200, db_heroe) != NULL && strlen(linea) != 0){
            gotoxy(145, i);
            printf("%s", linea);
            i++;
    }
    fclose(db_heroe);
}


void batalla(TEnemigo Enemigo,int pos,int posActual){
    char answer[20];
    int accAtaque=0;
    int accDefensa=0;
    int i=1;
    answer[0]='S';
    int nCantBound;
    system("cls");
    imprimir_marco_3();
    imprimir_Batalla();
    imprimir_Estadisticas(heroe, posActual);
    gotoxy(63, 55);
    printf("MANO DE CARTAS\n");
    gotoxy(23, 57);
    printf("1                        2                       3                          4                       5");
    imprimir_Cartas_Mano(0,13);
    imprimir_Cartas_Mano(1,38);
    imprimir_Cartas_Mano(2,63);
    imprimir_Cartas_Mano(3,88);
    imprimir_Cartas_Mano(4,113);

    gotoxy(149, 19);
    printf("ATAQUE Y DEFENSA DEL HEROE: \n");

    gotoxy(152, 21);
    printf("ATAQUE ACUMULADO: %d\n", accAtaque);

    gotoxy(152, 23);
    printf("DEFENSA ACUMULADO: %d\n", accDefensa);

    imprimir_Enemigo_En_Batalla(Enemigo);

    int indice =45;
    while(i<6 || strcmp(answer,"S")==0){

        gotoxy(20,indice++);
        printf("QUE NUMERO DE CARTA DESEA USAR PARA EL INICIO DE LA PELEA?: ");
        scanf("%s", answer);
        i++;
        accAtaque+=CartasMano[atoi(answer)-1].pAttack;
        accDefensa+=CartasMano[atoi(answer)-1].pDefend;
        gotoxy(149, 19);
        printf("ATAQUE Y DEFENSA DEL HEROE: \n");

        gotoxy(152, 21);
        printf("ATAQUE ACUMULADO: %d\n", accAtaque);

        gotoxy(152, 23);
        printf("DEFENSA ACUMULADO: %d\n", accDefensa);

        imprimir_Enemigo_En_Batalla(Enemigo);
        CartasMano[atoi(answer)-1].nombre="------";
        CartasMano[atoi(answer)-1].pMove=0;
        CartasMano[atoi(answer)-1].pAttack=0;
        CartasMano[atoi(answer)-1].pDefend=0;
        CartasMano[atoi(answer)-1].pHeal=0;
        CartasMano[atoi(answer)-1].pBuy=0;
        imprimir_Cartas_Mano(0,13);
        imprimir_Cartas_Mano(1,38);
        imprimir_Cartas_Mano(2,63);
        imprimir_Cartas_Mano(3,88);
        imprimir_Cartas_Mano(4,113);
        int j;
        if(accDefensa> Enemigo.pAttack && accAtaque > Enemigo.pDefend){
            gotoxy(20,indice+2);   
            printf("GANASTE LA BATALLA!!!!!!!");
            heroe.experiencia+=Enemigo.pExperience;
            insertar_Carta_Baraja(&ActionCard, cartaEspecial);
            //falta colocar que el enemigo le brinda una carta y los puntos de experiencia
            if (pos == posEnemigo1) {EnemigoEnc_1.pAttack+=2; EnemigoEnc_1.pDefend+=2; EnemigoEnc_1.pExperience+=10;}
            if (pos == posEnemigo2) {EnemigoEnc_2.pAttack+=2; EnemigoEnc_2.pDefend+=2; EnemigoEnc_2.pExperience+=10;}
            if (pos == posEnemigo3) {EnemigoEnc_3.pAttack+=2; EnemigoEnc_3.pDefend+=2; EnemigoEnc_3.pExperience+=10;}
            if (pos == posEnemigo4) {EnemigoEnc_4.pAttack+=2; EnemigoEnc_4.pDefend+=2; EnemigoEnc_4.pExperience+=10;}
            if (pos == posEnemigo5) {EnemigoEnc_5.pAttack+=2; EnemigoEnc_5.pDefend+=2; EnemigoEnc_5.pExperience+=10;}
            
            if(strcmp(Enemigo.nombre,"BOSS")==0) ganar=1;
            break;
        }
    }
    if(i==6){
        int k;
        if(accAtaque>Enemigo.pDefend && accDefensa<Enemigo.pAttack){
            gotoxy(20,indice+2); 
            printf("GANASTE LA BATALLA....");
            printf("PERO OBTUVISTE %d WOUND",nCantBound);
            heroe.experiencia+=Enemigo.pExperience;
            insertar_Carta_Baraja(&ActionCard, cartaEspecial);
            nCantBound=(abs(Enemigo.pAttack-Enemigo.pAttack))/heroe.defensa+1;
            if (pos == posEnemigo1) {EnemigoEnc_1.pAttack+=2; EnemigoEnc_1.pDefend+=2; EnemigoEnc_1.pExperience+=10;}
            if (pos == posEnemigo2) {EnemigoEnc_2.pAttack+=2; EnemigoEnc_2.pDefend+=2; EnemigoEnc_2.pExperience+=10;}
            if (pos == posEnemigo3) {EnemigoEnc_3.pAttack+=2; EnemigoEnc_3.pDefend+=2; EnemigoEnc_3.pExperience+=10;}
            if (pos == posEnemigo4) {EnemigoEnc_4.pAttack+=2; EnemigoEnc_4.pDefend+=2; EnemigoEnc_4.pExperience+=10;}
            if (pos == posEnemigo5) {EnemigoEnc_5.pAttack+=2; EnemigoEnc_5.pDefend+=2; EnemigoEnc_5.pExperience+=10;}
            for(k = 0; k < nCantBound; k++){
                insertar_Carta_Baraja(&ActionCard, cartaWound);
            }
            if(strcmp(Enemigo.nombre,"BOSS")==0) ganar=1;

        }else if(accDefensa>Enemigo.pAttack && accAtaque<Enemigo.pDefend){
            gotoxy(20,indice+2);
            printf("NO DERROTASTE AL ENEMIGO Y NO OBTUVISTE CARTAS WOUND");
            for(k = 0; k < 5; k++){
                CartasMano[k] = sacar_Carta_Baraja(&ActionCard);
            }
        }else if(accDefensa<Enemigo.pAttack && accAtaque<Enemigo.pDefend){
            nCantBound=ceil((abs(Enemigo.pAttack-Enemigo.pAttack))/heroe.defensa)+1;
            gotoxy(20,indice+2);
            printf("NO DERROTASTE AL ENEMIGO PERO OBTUVISTE %d CARTAS WOUND",nCantBound);
            //como tengo cartas bound entonces solo imprimire una cierta cantidad de cartas
            for(k = 0; k < nCantBound; k++){
                insertar_Carta_Baraja(&ActionCard, cartaWound);
            } 
        }
            //CartasMano[k] = sacar_Carta_Baraja(&ActionCard);

    }
        /*char numCarta[20];
        answer[0]='S';
        while(nCantBound>0  && ganar==0 && answer[0]=='S'){
            gotoxy(140,50);
            printf("DESEA ELIMINAR SUS CARTAS WOUND(S/N)?");
            printf("RESPUESTA: ");
            scanf("%s",answer);
            if(strcmp(answer,"S")==0){
                int accHeal=0;              
                    printf("QUE CARTA WOUND DESEA LIBERAR: ");
                    scanf("%s", numCarta);
                    indice++;
                    while(accHeal<2){
                        if(numCarta[0]>='1' && numCarta[0]<='5'){     
                            accHeal+= CartasMano[atoi(numCarta)-1].pHeal;
                            CartasMano[atoi(numCarta)-1]=sacar_Carta_Baraja(&ActionCard); //SACAR CARTA DE LA PILA
                            agregar_Carta_DiscardDeck(DiscardDeck,CartasMano[atoi(numCarta)-1],&nDiscardDeck);  //COLOCAR EN EL CEMENTERIO  
                            imprimir_Cartas_Mano(0,13);
                            imprimir_Cartas_Mano(1,38);
                            imprimir_Cartas_Mano(2,63);
                            imprimir_Cartas_Mano(3,88);
                            imprimir_Cartas_Mano(4,113);
                        } 
                    }                
            }
        }*/

    
    int j;
    for(j=0; j<5;j++){
        CartasMano[j]=sacar_Carta_Baraja(&ActionCard);
    }
    imprimir_Cartas_Mano(0,13);
    imprimir_Cartas_Mano(1,38);
    imprimir_Cartas_Mano(2,63);
    imprimir_Cartas_Mano(3,88);
    imprimir_Cartas_Mano(4,113); 
    sleep(3);

}

void imprimirPantalla(int arrEnemigosVis[], int arrVisualSpace[] ,int arrVisualTile[],char arrTipoSpace[]){

        imprimir_marco_2();        

        imprimir_Estadisticas(heroe, posActual);
        gotoxy(63, 55);
        printf("MANO DE CARTAS\n");
        gotoxy(23, 57);
        printf("1                        2                       3                          4                       5");
        imprimir_Cartas_Mano(0,13);
        imprimir_Cartas_Mano(1,38);
        imprimir_Cartas_Mano(2,63);
        imprimir_Cartas_Mano(3,88);
        imprimir_Cartas_Mano(4,113);        

        imprimir_Contornos_Mapa();
        agregarEnemigoVisibles(arrEnemigosVis, arrVisualSpace); 
        imprimir_Enemigos_Visibles(arrEnemigosVis);

        imprimir_Tiles_Visualizados_Actual(arrVisualTile);   

        imprimir_Leyenda_Space(); 

        imprimir_TipoSpace(arrTipoSpace, posActual);   

        imprimir_Heroe(); 

}



void empezarBatalla(TEnemigo EnemigoEnc,int posEnemigo,int arrEnemigosVis[], int arrVisualSpace[] ,int arrVisualTile[], char arrTipoSpace[]){
    gotoxy(145,42);
    printf("ESTAS CERCA DE UN ENEMIGO\n");
    gotoxy(145,44);
    printf("DESEA ENTRAR EN BATALLA (S/N)?");
    gotoxy(145,46);
    printf("RESPUESTA:");
    char answer[20];
    scanf("%s", answer);
    if(strcmp(answer,"S")==0) batalla(EnemigoEnc, posEnemigo, posActual);
    else{
        gotoxy(145,42);
        printf("                                   ");
        gotoxy(145,44);
        printf("                                   ");
        gotoxy(145,46);
        printf("                                   ");
    }
    system("cls");
    imprimirPantalla(arrEnemigosVis,  arrVisualSpace , arrVisualTile, arrTipoSpace);

}

int main(){

    strcpy(BigBoss.nombre,"BOSS");
    BigBoss.pAttack = 2;
    BigBoss.pDefend = 2;
    BigBoss.pExperience = 30;

	crear_Enemigos();
    int Conexiones[60][60];
    int Pesos[60][60];
    int SpaceXTile[60][10];
    int experienciaTile[10];
    char arrTipoSpace[60];

    //for(i=0; i<10;i++) experienciaTile[i]=0;

    experienciaTile[2]=30;
    experienciaTile[3]=45;
    experienciaTile[4]=60;
    experienciaTile[5]=75;
    experienciaTile[6]=90;
    experienciaTile[7]=105;   
    experienciaTile[8]=120;

    llenar_Conexiones(Conexiones);
    llenar_Pesos(Pesos);
    llenar_SpaceXTileVisual(SpaceXTile);
    llenar_ArrTipoSpace(arrTipoSpace);

	srand (time(NULL));

	/* Creamos las 16 cartas primeras en el mazo */

    Baraja_Inicial();

    inicio_Juego();
    gotoxy(82,45);
    printf("GAME IN DEVELOPMENT");
    gotoxy(78,46);
    printf("INGRESE EL NOMBRE DEL HEROE: \n");
    gotoxy(87,47);
    gets(heroe.nombre);

    sleep(0);

    heroe.defensa = 2; heroe.nivel = 1; heroe.experiencia = 10;

    /* APLICAR BORRADO DE CONSOLA */
    system("cls");
    /* 5 Cartas Iniciales */
    int i;
  
    int tileActual=1;

    for(i = 0; i < 5; i++){
    	CartasMano[i] = sacar_Carta_Baraja(&ActionCard);
    }

    int numCarta;
    int numSpace;

    EnemigoEnc_1 = sacar_Enemigo(&Enemigos);
    EnemigoEnc_2 = sacar_Enemigo(&Enemigos);
    EnemigoEnc_3 = sacar_Enemigo(&Enemigos);
    EnemigoEnc_4 = sacar_Enemigo(&Enemigos);
    EnemigoEnc_5= sacar_Enemigo(&Enemigos);

    int arrVisualSpace[60];
    for (i = 0; i <= 56; i++) arrVisualSpace[i] = 0;
    arrVisualSpace[1] = 1;
    arrVisualSpace[2] = 1;
    arrVisualSpace[3] = 1;
    arrVisualSpace[4] = 1;
    arrVisualSpace[5] = 1;
    arrVisualSpace[6] = 1;
    arrVisualSpace[7] = 1;


    /* Arreglo de Tiles Visibles */

    int arrVisualTile[10];
    for(i=0;i<=8;i++) 
        arrVisualTile[i] = 0;
    arrVisualTile[1] = 1;

    /* Imprimir Intro al empezar el mapa */

    imprimir_marco_2();
    imprimir_Estadisticas(heroe, posActual);
    imprimir_Contornos_Mapa();
    imprimir_Tile_1();
    imprimir_Leyenda_Space();
    imprimir_Heroe();
    imprimir_bienvenido();
    sleep(3);
    system("cls");

    int arrEnemigosVis[6];
    for(i=0;i<5;i++) arrEnemigosVis[i]=0;
    char answer[20];    

	while (1){		
        imprimirPantalla(arrEnemigosVis,arrVisualSpace,arrVisualTile,arrTipoSpace);
        char numCarta[20];
        if(arrVisualSpace[posBigBoss]==1){
            gotoxy(143, 39);
            printf("LA POSICION DEL ENEMIGO FINAL ES: %d ", posBigBoss);
        }
        if(posBigBoss==posActual){
            //imprimir_BigBoss();
            gotoxy(143, 41);
            printf("           BIG BOSS!!!!");
            empezarBatalla( BigBoss, posBigBoss,arrEnemigosVis,arrVisualSpace,arrVisualTile,arrTipoSpace);
        }

        if(ganar==1){
            system("cls");
            imprimir_marco_1();
            imprimir_victoria();
            
            sleep(1000);
        }


        if(arrVisualSpace[posEAmiga]==1){
            gotoxy(143, 16);
            printf("POSICION DE LA ESTRUCTURA AMIGA: %d ", posEAmiga);
        }
        if(posEAmiga==posActual){
            imprimir_Tienda();
            gotoxy(143, 41);
            printf("DESEA COMPRAR ALGO?(S/N) ");
            gotoxy(143, 43);
            printf("RESPUESTA: ");  
            scanf("%s", answer);
            if(strcmp(answer,"S")==0){
                gotoxy(143, 45);
                printf("QUE TIPO DE CARTAS DESEA COMPRAR? ");
                gotoxy(143, 46);
                printf("1.Attack(5)\n");
                gotoxy(143, 47);
                printf("2.Defend(5)\n");
                gotoxy(143, 48);
                printf("3.Heal(5)\n");
                gotoxy(143, 49);
                printf("4.Move(5)\n");
                gotoxy(143, 50);
                printf("RESPUESTA: ");
                scanf("%s", answer);
                if(strcmp(answer,"1")==0) insertar_Carta_Baraja(&ActionCard,CartaMaxAtaque);
                if(strcmp(answer,"2")==0) insertar_Carta_Baraja(&ActionCard,CartaMaxDefensa);
                if(strcmp(answer,"3")==0) CartasMano[0] = sacar_Carta_Baraja(&ActionCard);
                if(strcmp(answer,"4")==0) insertar_Carta_Baraja(&ActionCard,CartaMaxMove);
            }
            system("cls");
            imprimirPantalla(arrEnemigosVis,  arrVisualSpace , arrVisualTile, arrTipoSpace);
        }

        if(posActual==posEnemigo1) empezarBatalla( EnemigoEnc_1, posEnemigo1,arrEnemigosVis,arrVisualSpace,arrVisualTile,arrTipoSpace);
        if(posActual==posEnemigo2) empezarBatalla( EnemigoEnc_2, posEnemigo1,arrEnemigosVis,arrVisualSpace,arrVisualTile,arrTipoSpace);
        if(posActual==posEnemigo3) empezarBatalla( EnemigoEnc_3, posEnemigo3,arrEnemigosVis,arrVisualSpace,arrVisualTile,arrTipoSpace);
        if(posActual==posEnemigo4) empezarBatalla( EnemigoEnc_4, posEnemigo4,arrEnemigosVis,arrVisualSpace,arrVisualTile,arrTipoSpace);
        if(posActual==posEnemigo5) empezarBatalla( EnemigoEnc_5, posEnemigo5,arrEnemigosVis,arrVisualSpace,arrVisualTile,arrTipoSpace);           
    

        /* Niveles */

        if (heroe.experiencia >= 60)
            heroe.nivel = 4;
        else if (heroe.experiencia >= 40)
            heroe.nivel = 3;
        else if (heroe.experiencia >= 20)
            heroe.nivel = 2;

        //posCarta = 10;
        /* IMPRIMIR OPCIONES */
        gotoxy(140, 42);
        printf(" 1. DESEA MOVERSE?\n");
        gotoxy(140, 43);
        printf(" 2. DESEA VISUALIZAR UN TILE?\n");
        gotoxy(140, 45);
        printf("    RESPUESTA: ");
        char opcion[20];
        scanf("%s", opcion);

        if(strcmp(opcion,"1")==0){
            gotoxy(140,45);
            printf("    A DONDE DESEA MOVERSE? ");
            scanf("%s", answer);

            int indice = 46;

            if (((strlen(answer) == 1 && answer[0] > '0' && answer[0] <= '9') ||
               (strlen(answer) == 2 && answer[0] >='1' && answer[0] <= '4' && answer[1]>='0' && answer[1]<='9' ) ||
               (strlen(answer)==2 && answer[0]=='5' && answer[1]>='0' && answer[1]<='6')) && Conexiones[posActual][atoi(answer)] == 1 && arrVisualSpace[atoi(answer)] == 1){
                char numCarta[20];
                int moveAcc=0;
                int healAcc=0;
                while(moveAcc<Pesos[posActual][atoi(answer)]){
                    gotoxy(140,indice);
                    printf("    SELECCIONE UNA CARTA: ");
                    scanf("%s", numCarta);
                    indice++;
                    if(numCarta[0]>='1' && numCarta[0]<='5'){     
                        moveAcc+= CartasMano[atoi(numCarta)-1].pMove;
                        CartasMano[atoi(numCarta)-1]=sacar_Carta_Baraja(&ActionCard); //SACAR CARTA DE LA PILA
                        agregar_Carta_DiscardDeck(DiscardDeck,CartasMano[atoi(numCarta)-1],&nDiscardDeck);  //COLOCAR EN EL CEMENTERIO
                        if(strcmp(numCarta,"1")==0) imprimir_Cartas_Mano(0,13);
                        if(strcmp(numCarta,"2")==0) imprimir_Cartas_Mano(1,38);
                        if(strcmp(numCarta,"3")==0) imprimir_Cartas_Mano(2,63);
                        if(strcmp(numCarta,"4")==0) imprimir_Cartas_Mano(3,88);
                        if(strcmp(numCarta,"5")==0) imprimir_Cartas_Mano(4,113); 
                    }
                }




                //hasta aqui ya se movio
                printf("%d \n", Conexiones[posActual][atoi(answer)]);
                posActual = atoi(answer);

                gotoxy(53,38);
                printf("!MOVIMIENTO VALIDO!\n");
            }    
            else{
                gotoxy(53,38);
                printf("MOVIMIENTO INVALIDO!\n");
            }


        }else if(strcmp(opcion,"2")==0){
            //inialmente aparece el contorno, luego iran aparenciaendo los tiles
            gotoxy(140,45);
            printf("    NUMERO DE TILE A VISUALIZAR: ");
            scanf("%s", answer);
            if((strlen(answer) == 1 && answer[0] > '0' && answer[0] <= '8')  && SpaceXTile[posActual][atoi(answer)]==1 && arrVisualTile[atoi(answer)] ==0 ){
                char numCarta[20];
                int moveAcc=0;
                int indice = 46;
                while(moveAcc<2){
                    gotoxy(140,indice);
                    printf("    SELECCIONE UNA CARTA: ");
                    scanf("%s", numCarta);
                    if(numCarta[0]>='1' && numCarta[0]<='5'){
                        moveAcc+= CartasMano[atoi(numCarta)-1].pMove;
                        CartasMano[atoi(numCarta)-1]=sacar_Carta_Baraja(&ActionCard); //SACAR CARTA DE LA PILA
                        agregar_Carta_DiscardDeck(DiscardDeck,CartasMano[atoi(numCarta)-1],&nDiscardDeck);  //COLOCAR EN EL CEMENTERIO 

                        if(strcmp(numCarta,"1")==0) imprimir_Cartas_Mano(0,13);
                        if(strcmp(numCarta,"2")==0) imprimir_Cartas_Mano(1,38);
                        if(strcmp(numCarta,"3")==0) imprimir_Cartas_Mano(2,63);
                        if(strcmp(numCarta,"4")==0) imprimir_Cartas_Mano(3,88);
                        if(strcmp(numCarta,"5")==0) imprimir_Cartas_Mano(4,113);
                    }
                    indice++;
                }
                arrVisualTile[atoi(answer)]=1;
                agregarSpacesVisibles(arrVisualSpace, atoi(answer));
                agregarEnemigoVisibles(arrEnemigosVis, arrVisualSpace); 
                imprimir_Tiles_Visualizados_Actual(arrVisualTile);  
                gotoxy(53,38);   
                printf("YA PUEDES VISUALIZAR EL TILE VECINO!");
                printf("OJO AUN NO PUEDES PASAR!!!! JAJAJA");

            }else{
                gotoxy(53,38);
                printf("AUN NO SE ENCUENTRA DEMASIADO CERCA AL TILE" );
            }


        }

        if(arrVisualSpace[posEAmiga]==1){
            gotoxy(143, 16);
            printf("POSICION DE LA ESTRUCTURA AMIGA: %d ", posEAmiga);
        }

        sleep(3);


		 /* APLICAR BORRADO DE CONSOLA */
        system("cls");
        x=21;





	}





	return 0;
}
