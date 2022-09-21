#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    char nazov[64];
    char vyrobca[64];
    int na_sklade;
    float cena;
} PRODUKT;

//typedef struct {
//    char* meno, priezvisko;
//    float rozpocet;
//    PRODUKT* kosik[64];
//} ZAKAZNIK;

int main(){
    FILE* f = fopen("../src/produkty.txt","r");
    unsigned int len;
    fscanf(f, "%u\n", &len);
    PRODUKT* produkty;
    produkty = malloc(sizeof(PRODUKT)*len);
    int row;

    for (row=0; row<len; row+=1){
        produkty[row].id = scanf(f, "%u", &produkty[row].id);

    }
    for (row=0; row<len; row+=1){
        printf("%d,%s\n",produkty[row].id, produkty[row].nazov);
    }
}