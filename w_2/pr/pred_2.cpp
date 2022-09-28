#include <iostream> //vlozenie hlavickového súboru
#include <iomanip>
#include <string>
#include <fstream>

using namespace std; //miesto pre direktívy;

int increase(int y) { //vytvorí sa lokálna kópia premennej
	return y += 1;
}

void increasePtr(int* y) { //nevytvára sa kópia, pristupuje sa priamo k premennej
	*y += 1;
}

int increaseConstPtr(const int* y) { //nevytvára sa kópia, ale mám zabránené meniť premennú na adrese
	return *y + 1;
}

void increaseRef(int& y) { //nevytvorí sa kópia, upravuje sa priamo premenná
	y += 1;
}

int increaseConstRef(const int& y) {//nevytvára sa kópia, ale mám zabránené meniť premmenú
	return y + 1;
}

int main() { //funkcia main, musí mat aj návratový typ

	// cout << "Hello World!\n"; // kód funkcie main


// V c++ je mozny nasledujuci zapis
	
    // int sum = 0;
	// for (int i = 0; i <= 10; i++) {
	// 	for (int j = 0; j < 10; j++) {
	// 		sum += 1;
	// 	}
	// }
	// printf("Suma je %d\n", sum);

	// if (int flag = 200 > sum) {
	// 	printf("Flag > sum \n");
	// }
	
	// int a = 10;
	// bool state = a == 10;
	// if (state == true) {
	// 	printf("a=10\n");
	// }



//Príklad: Chceme vypísať hodnotu císla a znakový retazec

	// float cislo = 2.5;
	// char s[] = "Toto bol moj prvy vypis v C++";
	// cout << "Hodnota cisla je : " << cislo;
	// cout << "Hodnota cisla je : " << cislo << "\n";
	// cout << "Hodnota cisla je : " << cislo << endl << s << endl;
	// std::cout << "Hodnota cisla je : " << cislo << std::endl << s << std::endl;



//Príklad: Výpis desatinného čísla na rôzny počet miest

	// double cislo = 12.3456;
	// cout << fixed << setprecision(2) << cislo << endl;
	// cout << scientific << setprecision(2) << cislo << endl;
	


//Príklad: Chceme načítať vek používateľa z klávesnice

	// float age;
	// cout << "Zadaje Vas vek : " << "\n";
	// cin >> age;
	// cout << "Vas vek je " << age << endl;
	
	// float age;
	// float height;
	// cout << "Zadaje Vas vek a vysku : " << endl;
	// cin >> age >> height;
	// cout << "Vas vek je " << age << " a Vasa vyska je " << height << endl;
    
	// int age;
	// cout << "Zadaje Vas vek : " << endl;
	// cin >> age;
	// cout << "Vas vek je " << age << endl;
	


//Načítajme do premennej typu string reťazec zo vstupu z klávesnice:

	// string name;
	// cout << "Zadaje Vase meno : " << endl;
	// cin >> name;
	// cout << "Vase meno je " << name << endl;
	
	// string name, surname;
	// cout << "Zadaje Vase cele meno : " << endl;
	// cin >> name >> surname;
	// cout << "Vase meno je " << name << " " << surname << endl;
	
	// string name;
	// cout << "Zadaje Vase meno a priezvisko: " << endl;
	// getline(cin, name);
	// cout << "Vase meno a priezvisko je " << name << endl;



//Príklad: otvorte subor file.dat na zápis na koniec súboru:

	// fstream afile;
	// afile.open("file.txt", ios::out);
	// afile.close();
	


//Príklad: Otvorenie súboru s testovaním

	// fstream textfile("file.txt", ios::out | ios::app);
	// if (textfile.is_open() == false) {
	//   cout << "Subor sa nepodarilo otvorit!" << endl;
	// }
	// textfile.close();



//Príklad: Zapísanie čísel do textového súboru

	// fstream textfile;
	// textfile.open("cisla.txt", ios::out);
	// if (textfile.is_open()) {
	// 	for (int i = 0; i < 10; i++) {
	// 		textfile << i << endl;
	// 	}
	// 	textfile.close();
	// }
	// else {
	// 	cout << "Subor sa nepodarilo otvorit!" << endl;
	// }
	


//Príklad: Načítanie čísel z textového súboru

	// int numbers[10];
	// fstream textfileInput;
	// textfileInput.open("cisla.txt", ios::in);
	// if (textfileInput.is_open()) {
	// 	for (int i = 0; i < 10; i++) {
	// 		textfileInput >> numbers[i];
	// 	}
	// 	textfileInput.close();
	// }
	// else {
	// 	cout << "Subor sa nepodarilo otvorit!" << endl;
	// }

	// for (int i = 0; i < 10; i++)
	// {
	// 	cout << numbers[i] << " ";
	// }
	


//Príklad:  Vytvorenie obrázku vo formáte .raw (binárneho súboru)
	
	// fstream image;
	// image.open("image.raw", fstream::out | fstream::binary);
	// for (int i = 0; i < 100; i++) {
	// 	for (int j = 0; j < 100; j++) {
	// 		if ((i - 50) * (i - 50) + (j - 50) * (j - 50) <= 400) {
	// 			image.put(255);
	// 		}
	// 		else {
	// 			image.put(0);
	// 		}
	// 	}
	// }
	// image.close();
	


//Príklad:  Načítanie dát z .raw súboru do poľa
	
	// fstream image;
	// unsigned char intensity[100][100];
	// image.open("image.raw", ios::in | ios::binary);
	// for (int i = 0; i < 100; i++) {
	// 	for (int j = 0; j < 100; j++) {
	// 		intensity[i][j] = (unsigned char)image.get();
	// 	}
	// }
	// image.close();

	// for (int i = 0; i < 100; i++) {
	// 	for (int j = 0; j < 100; j++) {
	// 		cout << (int)intensity[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	


//nemusím definovať ios::out mode ok pouzijem ofstream

	// ofstream file("example.txt");
	// if (file.is_open()) {
	// 	file << "Lorem ipsum dolor sit amet, consectetur adipiscing elit" << endl;
	// 	file << "sed do eiusmod tempor incididunt ut labore" << endl;
	// 	file << "Suspendisse interdum consectetur libero id faucibus" << endl;
	// 	file.close();
	// }
	// else {
	// 	cout << "Subor sa nepodarilo otvorit!" << endl;
	// }



//Príklad:  Načítanie reťazcov znakov zo súbora

	// string line;
	// ifstream file("example.txt");
	// if (file.is_open()) {
	// 	while (getline(file, line)) {
	// 		cout << line << endl;
	// 	}
	// 	file.close();
	// }
	// else {
	// 	cout << "Subor sa nepodarilo otvorit!" << endl;
	// }



//Príklad:  Načítanie reťazcov znakov zo súbora s kontrolou konca suboru

	// string line;
	// ifstream file("example.txt");
	// if (file.is_open()) {
	// 	while (!file.eof()) {
	// 		getline(file, line);
	// 		cout << line << endl;
	// 	}
	// 	file.close();
	// }



//Príklad: Alokácia celočíselnej premennej

	// int* cislo;
	// cislo = new int;
	// *cislo = 10;
	// cout << "Na adrese " << cislo << " je ulozena hodnota " << *cislo << endl;
	// delete cislo;



//Príklad: Alokácia reálneho čísla:

	// float a = 2.5;
	// float* b = new float(3.2);
	// float* c = new float;
	// cout << "a = " << a << " b = " << *b << " c = " << *c << endl;
	// *c = a + *b;
	// cout << "a = " << a << " b = " << *b << " c = " << *c << endl;
	// delete b;
	// delete c;



//Príklad: Alokácia štruktúry

	// struct bod {
	// 	int x, y;
	// };

	// bod A = { 100,150 };
	// //A.x = 100;
	// //A.y = 150;
	// cout << "Bod A ma suradnice: " << A.x << " " << A.y << endl;
	// //bod* B = new bod;
	// bod* B = new bod(A);
	// B->x += 20;  // to iste ako (*B).x += 20;
	// B->y -= 40; // to iste ako (*B).y -= 40;
	// cout << "Bod B ma suradnice: " << B->x << " " << B->y << endl;
	// delete B;



//Príklad: Výpočet hodnôt funkcie f(x)=x2 na intervale <0,1>

	// int n;
	// cout << "V kolkych bodoch sa ma funkcia vypocitat?" << endl;
	// cin >> n;

	// float* x = new float[n];
	// float* fx = new float[n];

	// for (int i = 0; i < n; i++) {
	// 	x[i] = i * (1. / (n - 1));
	// 	fx[i] = x[i] * x[i];
	// 	cout << "f(" << x[i] << ")=" << fx[i] << endl;
	// }

	// delete[] x;
	// delete[] fx;



// 2D pole

	// int m = 3, n = 3;
	// int** pole = new int* [m];
	// for (int i = 0; i < m; i++) {
	// 	pole[i] = new int[n];
	// }
	// for (int i = 0; i < m; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		pole[i][j] = i * n + j;
	// 		cout << pole[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// for (int i = 0; i < m; i++) {
	// 	delete[] pole[i];
	// }
	// delete[] pole;



//2D pole ako 1D pole

	// int m = 3, n = 3;
	// int* pole = new int[m * n];
	// for (int i = 0; i < m; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		pole[i * n + j] = i * n + j;
	// 		cout << pole[i * n + j] << " ";
	// 	}
	// 	cout << endl;
	// }



//Argumenty funkcii

	// int a = 1;
	// a = increase(a); //vytvorí sa lokálna kópia premennej
	// cout << a << endl;

	// increasePtr(&a); //nevytvára sa kópia, pristupuje sa priamo k premennej
	// cout << a << endl;

	// a = increaseConstPtr(&a); //nevytvára sa kópia, ale mám zabránené meniť premennú na adrese
	// cout << a << endl;

	// increaseRef(a); //nevytvorí sa kópia, upravuje sa priamo premenná
	// cout << a << endl;

	// a = increaseConstRef(a); //nevytvára sa kópia, ale mám zabránené meniť premmenú
	cout << a << endl;

	return 0; //návratová hodnota funkcie main
}