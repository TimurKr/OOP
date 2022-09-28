#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nazov[64];
    char vyrobca[64];
    int na_sklade;
    float cena;
} PRODUKT;

typedef struct {
   char meno[64], priezvisko[64];
   float rozpocet;
   int kosik_len;
   PRODUKT kosik[64];
} ZAKAZNIK;

PRODUKT* populate_produkty(FILE* f, int prod_len){

    PRODUKT* produkty = malloc(sizeof(PRODUKT)*prod_len);

    int row;
    for (row=0; row<prod_len; row+=1){
        fscanf(f,"%u %s %s %d %f", 
            &produkty[row].id,
            produkty[row].nazov,
            produkty[row].vyrobca,
            &produkty[row].na_sklade,
            &produkty[row].cena
        );
    }
    return produkty;
} 

ZAKAZNIK init_zakaznik(){
    ZAKAZNIK zakaznik;
    printf("\n\nVitajte v obchode.\n\nZadajte svoje meno: ");
    scanf("%s", zakaznik.meno);
    printf("Zadajte svoje priezvisko: ");
    scanf("%s", zakaznik.priezvisko);
    printf("Aký máš rozpočet? ");
    scanf("%f", &zakaznik.rozpocet);
    getchar();
    zakaznik.kosik_len = 0;
    return zakaznik;
}


void nakup(PRODUKT* produkty, int prod_len, ZAKAZNIK* zakaznik){

    char volba;
    char found;
    int row;
    while (0==0) {
        printf("\nPrajete si vyhladávať podľa názvu[1], výrobcu[2], alebo chcete ukončiť nákup[3]?");
        volba = getchar();
        if (volba == '1'){
            char search[64];
            printf("Zadajte názov hladaného produktu: ");
            scanf("%s", search);
            printf("Výsledky hladania produktov s názvom %s:\n", search);

            found = 0;
            for (row=0; row<prod_len; row++){
                if (!strcmp(produkty[row].nazov, search)){
                    printf("id: %d\tnazov: %s\tvyrobca: %s\n", 
                        produkty[row].id, produkty[row].nazov, produkty[row].vyrobca
                    );
                    found = 1;
                }
            }
            if (!found){
                printf("Žiaden produkt nezodpovedá hladaniu.\n\n");
                getchar();
                continue;
            }

        } else if (volba == '2') {
            char search[64];
            printf("Zadajte názov hladaného výrobcu: ");
            scanf("%s", search);
            printf("Výsledky hladania produktov s výrobcom %s:\n", search);
            
            found = 0;
            for (row=0; row<prod_len; row++){
                if (!strcmp(produkty[row].vyrobca, search)){
                    printf("id: %d\tnazov: %s\tvyrobca: %s\n", 
                        produkty[row].id, produkty[row].nazov, produkty[row].vyrobca
                    );
                    found = 1;
                }
            }
            if (!found) {
                printf("Žiaden produkt nezodpovedá hladaniu.\n\n");
                getchar();
                continue;
            }

        } else if (volba == '3') {
            return;
        } else {
            printf("Zadajte valídnu volbu");
            volba = '0';
            continue;
        }
        
        int id;
        printf("Zadajte id požadovaného produktu: ");
        scanf("%d", &id);
        getchar();
        found = 0;
        for (row=0; row<prod_len; row++){
            if (produkty[row].id == id){
                printf("id: %d\tnazov: %s\tvyrobca: %s\tMnožstvo na sklade: %d\tCena: %.2f €\n", 
                        produkty[row].id, produkty[row].nazov, produkty[row].vyrobca,
                        produkty[row].na_sklade, produkty[row].cena
                );
                if (zakaznik->rozpocet < produkty[row].cena) {
                    printf("\nNa daný produkt nemáte dostatočný rozpočet.\nZostávajúci rozpočet %.2f\n",
                        zakaznik->rozpocet
                    );
                    found = 2;
                    break;
                }
                if (produkty[row].na_sklade <= 0){
                    printf("\nDaný produkt nie je na sklade.\n");
                    found = 2;
                }
                found = 1;
                printf("Prajete si tovar zakúpiť? [y/n]");
                scanf("%c", &volba);
                getchar();
                if (volba == 'y'){
                    zakaznik->kosik[zakaznik->kosik_len] = produkty[row];
                    zakaznik->kosik_len++;
                    zakaznik->rozpocet -= produkty[row].cena;
                    produkty[row].na_sklade -= 1;
                    printf("Produkt bol vložený do košíka.\n");
                } else {
                    printf("Produkt nebol vložený do košíka.\n");

                }
                break;
            }
        }
        if (found == 0){
            printf("Nenašiel sa produkt s daným id.\n");
            continue;
        } else if (found == 2){
            continue;
        }

        printf("\nVáš košík:\n");
        for (row=0; row<zakaznik->kosik_len; row++){
            printf("id: %d\tnazov: %s\tvyrobca: %s\tMnožstvo na sklade: %d\tCena: %.2f €\n", 
                        zakaznik->kosik[row].id, zakaznik->kosik[row].nazov, zakaznik->kosik[row].vyrobca,
                        zakaznik->kosik[row].na_sklade, zakaznik->kosik[row].cena
                );
        }
        printf("Zostávajúci rozpočet: %.2f\n", zakaznik->rozpocet);
    }
}

void uzavretie(ZAKAZNIK* zakaznik){
    FILE* f = fopen("./blok.txt","w");
    if(f == 0) {
        printf("fopen failed to open bločik.txt");
        exit(1);
    }

    fprintf(f, "%s %s\n\n", zakaznik->meno, zakaznik->priezvisko);
    float suma = 0;
    int i;
    for (i=0; i<zakaznik->kosik_len; i++){
        suma += zakaznik->kosik[i].cena; 
        fprintf(f,"Položka:  %s\t\tVyrobca:  %s\t\t\t%.2f\n", 
            zakaznik->kosik[i].nazov, zakaznik->kosik[i].vyrobca, zakaznik->kosik[i].cena
        );
    }
    fprintf(f, "\nSpolu %.2f €\nZostatok na účte: %.2f €", suma, suma + zakaznik->rozpocet);
    printf("\n\nPočas nákupu ste minuli %.2f € z %.2f €\n", suma, suma + zakaznik->rozpocet);
    printf("Blok si nájdete v dokumente blok.txt");
}


int main(){
    FILE* f = fopen("./produkty.txt","r");
    if(f == 0) {
        printf("fopen failed");
        exit(1);
    }

    // Read numer of products
    unsigned int prod_len;
    fscanf(f, "%u\n", &prod_len);

    PRODUKT* produkty = populate_produkty(f, prod_len);
    ZAKAZNIK zakaznik = init_zakaznik();
    printf("\nAhoj %s %s\n", zakaznik.meno, zakaznik.priezvisko);

    nakup(produkty, prod_len, &zakaznik);

    uzavretie(&zakaznik);

}
