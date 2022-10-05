#include <iostream> 
#include <iomanip>
#include <string>
#include <fstream>

using namespace std; 

#define FOUND 0
#define NOT_FOUND 1
#define FOUND_ERROR 2


struct PRODUKT{
    unsigned int id;
    string nazov;
    string vyrobca;
    unsigned int na_sklade;
    float cena;
};

struct ZAKAZNIK{
   string meno, priezvisko;
   float rozpocet;
   unsigned int kosik_len;
   PRODUKT kosik[64];
};

void populate_produkty(string file_path, PRODUKT *produkty, int& num_prod){

    fstream file;
    file.open(file_path, ios::in);

    if (!file.is_open()) {
	    cout << "Subor sa nepodarilo otvorit!" << endl;
    }
    
    file >> num_prod;
    cout << num_prod << endl;

    produkty = new PRODUKT[num_prod];

    for (int prod=0; prod<num_prod; prod+=1){
        file 
            >> produkty[prod].id
            >> produkty[prod].nazov
            >> produkty[prod].vyrobca
            >> produkty[prod].na_sklade
            >> produkty[prod].cena;
    }
    file.close();
} 

ZAKAZNIK init_zakaznik(){
    ZAKAZNIK zakaznik;
    cout << endl << endl 
        << "Vitajte v obchode." << endl << endl 
        << "Zadajte svoje meno: ";
    cin >> zakaznik.meno;
    cout << "Zadajte svoje priezvisko: ";
    cin >> zakaznik.priezvisko;
    cout << "Aký máš rozpočet? ";
    cin >> zakaznik.rozpocet;
    zakaznik.kosik_len = 0;
    return zakaznik;
}

void nakup(PRODUKT* produkty, int prod_len, ZAKAZNIK& zakaznik){

    char volba;
    unsigned int found;
    unsigned int row;
    unsigned int id;
    string search;
    while (1) {
        cout << "Prajete si vyhladávať podľa názvu[1], " 
            << "výrobcu[2], alebo chcete ukončiť nákup[3]? ";
        cin >> volba;
        if (volba == '1'){
            cout << "Zadajte názov hladaného produktu: ";
            cin >> search;
            cout << "Výsleky hladania produktov s názvom " << search << endl;

            found = NOT_FOUND;
            for (row=0; row<prod_len; row++){
                cout << row;
                if (produkty[row].nazov.find(search) != string::npos){
                    cout
                        << "id: " << produkty[row].id
                        << "nazov: " << produkty[row].nazov
                        << "vyrobca: " << produkty[row].vyrobca
                        << endl;
                    found = FOUND;
                }
            }

            if (!found){
                cout << "Žiaden produkt nezodpovedá hladaniu." << endl << endl;
                continue;
            }

        } else if (volba == '2') {
            cout << "Zadajte názov hladaného výrobcu: ";
            cin >> search;
            cout << "Výsleky hladania produktov s výrobcom " << search << endl;
            
            found = NOT_FOUND;
            for (row=0; row<prod_len; row++){
                if (produkty[row].vyrobca.find(search) != string::npos){
                    cout
                        << "ID: " << produkty[row].id
                        << "Nazov: " << produkty[row].nazov
                        << "Vyrobca: " << produkty[row].vyrobca
                        << endl;
                    found = FOUND;
                }
            }

            if (!found){
                cout << "Žiaden produkt nezodpovedá hladaniu." << endl << endl;
                continue;
            }

        } else if (volba == '3') {
            return;

        } else {
            cout << "Zadajte valídnu volbu";
            volba = '0';
            continue;
        }
        
        int id;
        cout << "Zadajte id požadovaného produktu: ";
        cin >> id;
        
        found = NOT_FOUND;
        for (row=0; row<prod_len; row++){
            if (produkty[row].id == id){
                cout
                    << "ID: " << produkty[row].id
                    << "Nazov: " << produkty[row].nazov
                    << "Vyrobca: " << produkty[row].vyrobca
                    << "Množstvo na sklade: " << produkty[row].na_sklade
                    << "Cena: " << produkty[row].cena
                    << endl << endl;
                
                if (zakaznik.rozpocet < produkty[row].cena) {
                    cout << "Na daný produkt nemáte dostatočný rozpočet." << endl 
                    << "Zostávajúci rozpočet: " << zakaznik.rozpocet << endl;
                    found = FOUND_ERROR;
                    break;
                }

                if (produkty[row].na_sklade <= 0){
                    cout << "Daný produkt nie je na sklade";
                    found = FOUND_ERROR;
                    break;
                }

                found = FOUND;
                cout << "Prajete si tovar zakúpiť? [y/n] ";
                cin >> volba;

                if (volba == 'y'){
                    zakaznik.kosik[zakaznik.kosik_len] = produkty[row];
                    zakaznik.kosik_len++;
                    zakaznik.rozpocet -= produkty[row].cena;
                    produkty[row].na_sklade -= 1;
                    cout <<"Produkt bol vložený do košíka." << endl;
                } else {
                    cout <<"Produkt nebol vložený do košíka." << endl;
                }
                break;
            }
        }
        if (!found){
            cout << "Nenašiel sa produkt s daným id." << endl;
            continue;
        } else if (found == FOUND_ERROR) {
            cout << "Nastala chyba." << endl;
            continue;
        }

        printf("\nVáš košík:\n");
        for (row=0; row<zakaznik.kosik_len; row++){
            cout 
                << "ID: " << zakaznik.kosik[row].id 
                << "Názov: " << zakaznik.kosik[row].nazov 
                << "Výrobca: " << zakaznik.kosik[row].vyrobca 
                << "Množstvo na sklade: " << zakaznik.kosik[row].na_sklade 
                << "Cena: " << zakaznik.kosik[row].cena
                << endl; 
        }
        printf("Zostávajúci rozpočet: %.2f\n", zakaznik.rozpocet);
    }
}

// void uzavretie(ZAKAZNIK* zakaznik){
//     FILE* f = fopen("./blok.txt","w");
//     if(f == 0) {
//         printf("fopen failed to open bločik.txt");
//         exit(1);
//     }
//     fprintf(f, "%s %s\n\n", zakaznik->meno, zakaznik->priezvisko);
//     float suma = 0;
//     int i;
//     for (i=0; i<zakaznik->kosik_len; i++){
//         suma += zakaznik->kosik[i].cena; 
//         fprintf(f,"Položka:  %s\t\tVyrobca:  %s\t\t\t%.2f\n", 
//             zakaznik->kosik[i].nazov, zakaznik->kosik[i].vyrobca, zakaznik->kosik[i].cena
//         );
//     }
//     fprintf(f, "\nSpolu %.2f €\nZostatok na účte: %.2f €", suma, suma + zakaznik->rozpocet);
//     printf("\n\nPočas nákupu ste minuli %.2f € z %.2f €\n", suma, suma + zakaznik->rozpocet);
//     printf("Blok si nájdete v dokumente blok.txt");
// }


int main(){
    
    PRODUKT* produkty;
    int num_prod; 
    populate_produkty("./produkty.txt", produkty, num_prod);

    ZAKAZNIK zakaznik = init_zakaznik();

    cout << endl 
        << "Vitaj " << zakaznik.meno << " " << zakaznik.priezvisko << endl;

    nakup(produkty, num_prod, zakaznik);

    // uzavretie(&zakaznik);

}
