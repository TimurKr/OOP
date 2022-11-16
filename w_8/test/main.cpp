#include <iostream>
#include <string>


//Zadanie začína pod definíciou konštruktora triedy Date
class Date {
private:
	int d = 0, m = 0, y = 0;
public:
	Date() {};
	Date(int D, int M, int Y) :d(D), m(M), y(Y) {};
	Date& fromString(std::string dtext);
	std::string toString() {
		return std::string(std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y));
	};
};

Date& Date::fromString(std::string dtext)
{
	size_t pos = 0;
	std::string token;
	int date[3] = { 0,0,0 };
	int counter = 0;
	std::string delimiter = ".";

	while ((pos = dtext.find(".")) != std::string::npos) {

		token = dtext.substr(0, pos);
		date[counter] = std::stoi(token);
		dtext.erase(0, pos + delimiter.length());
		counter++;
	}
	d = date[0];
	m = date[1];
	y = std::stoi(dtext);
	return *this;
}

//1. Vytvorte triedy ZooAnimal a ZooBird podľa nasledovného objektového návrhu (obe musia spĺňať data hiding):


/*
Trieda ZooAnimal bude mať premenné:
-	názov 
-	dátum narodenia (premenná bude triedy Date)
-	neceločíselná výška v metroch
a metódy:
-	prázdny konštruktor, ktorý nastaví defaultne „nulové“ hodnoty
-	konštruktor s parametrami
-	metódy na pristúp a nastavenie premenných
*/


/*
Trieda ZooBird bude dediť triedu ZooAnimal a bude mať premenné:
-	celočíselne rozpätie krídiel v cm
a metódy:
-	prázdny konštruktor, ktorý nastaví defaultne „nulové“ hodnoty
-	konštruktor s parametrami schopný nastaviť aj premenné rodičovskej triedy
-	metódy na pristúp a nastavenie premenných
-	metódu print, ktorá vypíše všetky dostupné údaje
*/

class ZooAnimal { 
    protected:
        std::string name="";
        Date birth_date=Date(0,0,0);
        double height=0;
    public:
        ZooAnimal() : name(""), birth_date(Date()), height(0) {}
        ZooAnimal(std::string n, int birth_day, int birth_month, int birth_year, double h) : 
            name(n), birth_date(Date(birth_day, birth_month, birth_year)), height(h) {}

        std::string getName() { return name; }
        Date getBirthDate() { return birth_date; }
        double getHeight() { return height; }

        void setName(std::string n) { name = n; }
        void setBirthDate(Date date) { birth_date = date; }
        void setHeight(double h) { height = h; }
};

class ZooBird : ZooAnimal {
    private:
        int wing_span=0;
    public:
        ZooBird() {}
        ZooBird(std::string n, int birth_day, int birth_month, int birth_year, double h, int w_s) :
            ZooAnimal(n, birth_day, birth_month, birth_year, h), wing_span(w_s) {}

        int getWingSpan() { return wing_span; }
        void setWingSpan(int w_s) { wing_span = w_s; }

        void printAll() {
            std::cout << "Zviera: " << name << std::endl;
            std::cout << "Narodené dňa: " << birth_date.toString() << std::endl;
            std::cout << "Výška: " << height << std::endl;
            std::cout << "Rotpätie krídel: " << wing_span << std::endl;
        }
};




void changeWingspan(ZooBird b, int newWingSpan) {
	//2. zavolajte funkciu ktorá zmení hodnota rozpätia krídiel objektu b
	b.setWingSpan(newWingSpan);
}

int main()
{
	std::cout << "Kolko zaznamov sa ma nacitat? (max 3)" << std::endl;
	int n = 0;

	//3. do premennej n načítajte hodnotu z konzoly
	std::cin >> n;

	//4. dynamicky alokujte pole pre n objektov triedy ZooBird do premennej birds
	ZooBird* birds = new ZooBird[n];

	//5. zabezpecte aby nasledujúci riadok nevypisoval chybu
	std::fstream textfile;

	//6. do premennej textfile otvorte súbor dataBirds.txt na čítanie

	if (textfile.is_open() == false) {
		std::cout << "Subor sa nepodarilo otvorit!" << std::endl;
	}

	//7. vo vnútri v cykle naplňte do tmp premennych hodnoty zo subora
	// a tie následne nastavte do objektov v poli birds
	for (int i = 0; i < n; i++) {
		std::string tmpName;
		std::string tmpBirthDate;
		std::string tmpHeight;
		std::string tmpWingspan;

		
	}

	for (int i = 0; i < n; i++)
	{
		birds[i].print();
	}

	//8. upravte funkciu changeWingspan aby nepracovala s kópiou posledného objektu v poli birds, 
	//ale aby priamo pristupovala k objektu
	changeWingspan(birds[n - 1], 100);

	for (int i = 0; i < n; i++)
	{
		birds[i].print();
	}

	textfile.close();
	return 0;
}