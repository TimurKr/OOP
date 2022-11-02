#include <iostream>
#include <string>

//Trieda BankClient
class BankClient {
private:
	int accountBalance = 0;
	std::string accountNumber = "";
protected: //dáta by mali byť síce súkromné aby spĺňala trieda data hiding, ale odvodené triedy by k nim mali mať prístup.
	std::string name = "", address = "";	
public:
	BankClient() {}
	BankClient(std::string m, std::string a, std::string cu, int su) : name(m), address(a), accountNumber(cu), accountBalance(su) {
		std::cout << "konstruktor triedy BankClient" << std::endl;
	}
	std::string Name() { return name; }
	std::string Address() { return address; }
	std::string AccountNumber() { return accountNumber; }
	int AccountBalance() { return accountBalance; }
};

//Príklad: Prístupnosť dát podľa rôzneho typu dedičnosti - Private dedenie
class CompanyClient :private BankClient { //všetko, čo CompanyClient zdedí od triedy BankClient, bude súkromné
private:
	std::string ico, vatNumber;
public:
	CompanyClient(std::string m, std::string a, std::string i, std::string vn);
	std::string Ico() { return ico; }
	std::string VatNumber() { return vatNumber; }
	void printInfo();
};

CompanyClient::CompanyClient(std::string m, std::string a, std::string i, std::string vn) {
	//k tymto premmennym triedy BankClient mam pristup vo funkciach triedy CompanyClient
	name = m;	
	address = a;
	//premenne triedy CompanyClient
	ico = i;
	vatNumber = vn;
	//nemám prístup k premennej accountBalance a accountNumber triedy BankClient, lebo su private
}

void CompanyClient::printInfo() {
	std::cout << "Klient: " << name << " "<< std::endl;
	std::cout << "Adresa: " << address << std::endl;
}

//Príklad: Prístupnosť dát podľa rôzneho typu dedičnosti - Public dedenie
class CompanyClient2 :public BankClient { 
//všetko, čo CompanyClient2 zdedí od triedy BankClient, bude mat rovnaku pristupnost v triede CompanyClient
private:
	std::string ico, vatNumber;
public:
	CompanyClient2(std::string m, std::string a, std::string i, std::string vn);
	std::string Ico() { return ico; }
	std::string VatNumber() { return vatNumber; }	
};

CompanyClient2::CompanyClient2(std::string m, std::string a, std::string i, std::string vn) {
	//k tymto premmennym triedy BankClient mam pristup vo funkciach triedy CompanyClient
	name = m;
	address = a;
	//premenne triedy CompanyClient
	ico = i;
	vatNumber = vn;
	//stale nemám prístup k premennej accountBalance a accountNumber triedy BankClient, lebo su private
}

//Príklad: Trieda BankClient2 doplnena o set metody pre private premenne
class BankClient2 {
private:
	int accountBalance = 0;
	std::string accountNumber = "";
protected: //dáta by mali byť síce súkromné aby spĺňala trieda data hiding, ale odvodené triedy by k nim mali mať prístup.
	std::string name = "", address = "";
	void setAccountBalance(int ab) { accountBalance = ab; }
	void setAccountNumber(std::string an) { accountNumber = an; }
public:
	BankClient2() {}
	BankClient2(std::string m, std::string a, std::string cu, int su) : name(m), address(a), accountNumber(cu), accountBalance(su) {
		std::cout << "konstruktor triedy BankClient" << std::endl;
	}
	~BankClient2() { std::cout << "destruktor triedy BankClient" << std::endl; }
	std::string Name() { return name; }
	std::string Address() { return address; }
	std::string AccountNumber() { return accountNumber; }
	int AccountBalance() { return accountBalance; }
};

class CompanyClient3 :public BankClient2 {
	//všetko, čo CompanyClient3 zdedí od triedy BankClient2, bude mat rovnaku pristupnost v triede CompanyClient
private:
	std::string ico, vatNumber;
public:
	CompanyClient3(std::string m, std::string a, std::string i, std::string vn, std::string an, int ab);
	~CompanyClient3() { std::cout << "destruktor triedy CompanyClient" << std::endl; }
	std::string Ico() { return ico; }
	std::string VatNumber() { return vatNumber; }
};

/*CompanyClient3::CompanyClient3(std::string m, std::string a, std::string i, std::string vn, std::string an, int ab) {
	//k tymto premmennym triedy BankClient mam pristup vo funkciach triedy CompanyClient
	name = m;
	address = a;
	//premenne triedy CompanyClient
	ico = i;
	vatNumber = vn;
	//protected metody triedy BankClient pomocou ktorých nastavim private premenné
	setAccountBalance(ab);
	setAccountNumber(an);
}*/

//Priklad: Konštruktor triedy CompanyClient s využitím konštruktora triedy BankClient
CompanyClient3::CompanyClient3(std::string m, std::string a, std::string i,
	std::string vn, std::string an, int ab) : BankClient2(m,a,an,ab) {

	std::cout << "konstruktor triedy CompanyClient" << std::endl;
	//nastavujeme iba premenne triedy CompanyClient
	ico = i;
	vatNumber = vn;	
}

//Príklad: Viacnásobná dedičnosť
class Goods {
protected:
	int code;
	std::string name;
	float price;
public:
	Goods(int k, std::string n, float c) :code(k), name(n), price(c){
		std::cout << "Vytvara sa objekt triedy Goods" << std::endl;
	}
	//~Goods() { std::cout << "Zanika objekt triedy Goods" << std::endl; }
	virtual ~Goods() { std::cout << "Zanika objekt triedy Goods" << std::endl; }
	int Code() { return code; }
	std::string Name() { return name; }
	float Price() { return price; }
	virtual void info();
};

class Food :public Goods{
protected:
	std::string expirationDate;	
public:
	Food(int k, std::string n, float c, std::string ds) : Goods(k, n, c), expirationDate(ds){
		std::cout << "Vytvara sa objekt triedy Food" << std::endl;
	}
	//~Food() { std::cout << "Zanika objekt triedy Food" << std::endl; }
	virtual ~Food() { std::cout << "Zanika objekt triedy Food" << std::endl; }
	std::string ExpirationDate() { return expirationDate; }	
	virtual void info();
};

class Vegetable :public Food{
private:
	int quality;
public:
	Vegetable(int k, std::string n, float c, std::string ds, int t) :Food(k, n, c, ds), quality(t)
	{
		std::cout << "Vytvara sa objekt triedy Vegetable" << std::endl;
	}
	~Vegetable() { std::cout << "Zanika objekt triedy Vegetable" << std::endl; }
	int Quality() { return quality; }
	void info();
};

//Definicie funckii info 
/*
void Goods::info()
{
	std::cout << "Tovar s kodom " << code << std::endl;
	std::cout << name << std::endl;
	std::cout << price << " Eur" << std::endl;
}
void Food::info()
{
	std::cout << "Tovar s kodom " << code << std::endl;
	std::cout << name << std::endl;
	std::cout << price << " Eur" << std::endl;
	std::cout << "Datum spotreby: " << expirationDate << std::endl;
}
void Vegetable::info()
{
	std::cout << "Tovar s kodom " << code << std::endl;
	std::cout << name << std::endl;
	std::cout << price << " Eur/kg" << std::endl;
	std::cout << "Datum spotreby: " << expirationDate << std::endl;
	std::cout << "Trieda: " << quality << std::endl;
}*/

//Definicie funckii info 
void Goods::info()
{
	std::cout << "Tovar s kodom " << code << std::endl;
	std::cout << name << std::endl;
	std::cout << price << " Eur" << std::endl;
}
void Food::info()
{
	Goods::info();
	std::cout << "Datum spotreby: " << expirationDate << std::endl;
}
void Vegetable::info()
{
	Food::info();
	std::cout << "Trieda: " << quality << std::endl;
}

//Príklad: Dedičnosť od viacerých rodičov
class Mammal {
protected:
	double feedingPeriod = 0;;
public:
	Mammal(double fP) : feedingPeriod(fP) {};
};

class WingedAnimal  {
protected:
	//double feedingPeriod = 0;
	double wingspan = 0;
public:
	WingedAnimal(double w) : wingspan(w) {};
};

class Bat : public Mammal, public WingedAnimal {
protected:
	int caveDepth = 0;
public:
	Bat(double fP, double w, int cD) : Mammal(fP), WingedAnimal(w), caveDepth(cD) {};
	void printInfo() {
		std::cout << "Feeding period: " << feedingPeriod << " months" << std::endl;
		std::cout << "Wingspan: " << wingspan << " cm" << std::endl;
		std::cout << "Living in cave with depth: " << caveDepth << " m" << std::endl;
	}
};

//Príklad: Dedičnosť od viacerých rodičov a virtualne funckie
class Animal {
protected:
	std::string name = "";
	std::string order = "";
public:
	Animal() { std::cout << "Prazdny konstruktor triedy Animal" << std::endl; };
	Animal(std::string n, std::string o) :name(n), order(o) { 
		std::cout << "Konstruktor triedy Animal" << std::endl; 
	};
};

//class Mammal2 : public Animal {
class Mammal2 : virtual public Animal {
protected:
	double feedingPeriod = 0;
public:	
	Mammal2(std::string n, std::string o, double fP) : Animal(n,o), feedingPeriod(fP) { 
		std::cout << "Konstruktor triedy Mammal" << std::endl; 
	};
};

//class WingedAnimal2 : public Animal {
class WingedAnimal2 : virtual public Animal {
protected:
	double wingspan = 0;
public:
	WingedAnimal2(std::string n, std::string o, double w) : Animal(n, o), wingspan(w) { 
		std::cout << "Konstruktor triedy WingedAnimal" << std::endl; 
	};
};

class Bat2 : public Mammal2,  public WingedAnimal2 {
protected:
	int caveDepth = 0;
public:
	Bat2(std::string n, std::string o, double fP, double w, int cD) : Mammal2(n, o, fP), WingedAnimal2(n, o, cD), caveDepth(cD) {};
	//Bat2(std::string n, std::string o, double fP, double w, int cD) : Mammal2(n, o, fP), WingedAnimal2(n, o, cD), Animal(n,o), caveDepth(cD) {};
	void printInfo() {
		std::cout << "Name: " << name << std::endl;
		std::cout << "Order: " << order << std::endl;
		std::cout << "Feeding period: " << feedingPeriod << " months" << std::endl;
		std::cout << "Wingspan: " << wingspan << " cm" << std::endl;
		std::cout << "Living in cave with depth: " << caveDepth << " m" << std::endl;
	}
};

int main()
{	
	//Priklad: Príklad: Prístupnosť dát podľa rôzneho typu dedičnosti -	Private dedenie
	/*
	BankClient client("Pavol Horvath", "Bratislava", "012011/0100", 15000);	
	std::cout << "Klient: " << client.Name() << std::endl;
	std::cout << "Adresa: " << client.Address() << std::endl;
	std::cout << "Cislo uctu: "  << client.AccountNumber() << std::endl;
	std::cout << "Stav uctu: " << client.AccountBalance() << " Eur" << std::endl;

	CompanyClient companyCient("Eset", "Bratislava", "123456", "01/123456");
	//V hlavnom programe nemozem pouzit napr funckie companyCient.Name(), companyCient.Surname() ... lebo su uz v triede CompanyClient sukromne
	companyCient.printInfo();
	std::cout << "ICO: " << companyCient.Ico() << std::endl;
	std::cout << "Vat number: " << companyCient.VatNumber() << std::endl;
	*/

	//Priklad: Príklad: Prístupnosť dát podľa rôzneho typu dedičnosti -	Public dedenie
	/*
	BankClient client("Pavol Horvath", "Bratislava", "012011/0100", 15000);
	std::cout << "Klient: " << client.Name() << std::endl;
	std::cout << "Adresa: " << client.Address() << std::endl;
	std::cout << "Cislo uctu: " << client.AccountNumber() << std::endl;
	std::cout << "Stav uctu: " << client.AccountBalance() << " Eur" << std::endl;

	CompanyClient2 companyClient2("Eset", "Bratislava", "123456", "01/123456");
	std::cout << "Klient: " << companyClient2.Name() << std::endl;
	std::cout << "Adresa: " << companyClient2.Address() << std::endl;
	std::cout << "ICO: " << companyClient2.Ico() << std::endl;
	std::cout << "Vat number: " << companyClient2.VatNumber() << std::endl;
	std::cout << "Account number " << companyClient2.AccountNumber() << std::endl;
	*/

	//Trieda BankClient doplnena o set metody pre private premenne
	/*
	BankClient2 client("Pavol Horvath", "Bratislava", "012011/0100", 15000);
	std::cout << "Klient: " << client.Name() << std::endl;
	std::cout << "Adresa: " << client.Address() << std::endl;
	std::cout << "Cislo uctu: " << client.AccountNumber() << std::endl;
	std::cout << "Stav uctu: " << client.AccountBalance() << " Eur" << std::endl;

	CompanyClient3 companyClient("Eset", "Bratislava", "123456", "01/123456", "012011/0100", 150000);
	std::cout << "Klient: " << companyClient.Name() << std::endl;
	std::cout << "Adresa: " << companyClient.Address() << std::endl;
	std::cout << "Cislo uctu: " << companyClient.AccountNumber() << std::endl;
	std::cout << "Stav uctu: " << companyClient.AccountBalance() << std::endl;
	std::cout << "ICO: " << companyClient.Ico() << std::endl;
	std::cout << "Vat number: " << companyClient.VatNumber() << std::endl;	
	*/
	

	//Príklad: Viacnásobná dedičnosť
	/*
	Vegetable z[3] = { 
		Vegetable(123, "Paprika", 2.29, "28.11.2021", 1),
		Vegetable(540, "Uhorka", 1.79, "6.12.2021", 2),
		Vegetable(673, "Kapusta", 0.59, "20.11.2021", 1)
	};
	int code;
	std::cout << "Zadaj kod: " << std::endl;
	std::cin >> code;
	int index = -1;
	for (int i = 0; i < 3; i++) {
		if (z[i].Code() == code) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		std::cout << "Tovar s takymto kodom nemame na sklade" << std::endl;
	}
	else
	{
		std::cout << z[index].Name() << std::endl;
		std::cout << z[index].Price() << " Eur/kg" << std::endl;
		std::cout << "Datum spotreby: " << z[index].ExpirationDate() << std::endl;
		std::cout << "Trieda: " << z[index].Quality() << std::endl;
	}
	*/
		
	//Príklad: Dedičnosť od viacerých rodičov
	/*
	Bat b(5., 20., 15);
	b.printInfo();
	*/

	//Príklad: Smerník na obejekt triedy Goods
	/*
	Vegetable z[3] = {
		Vegetable(123, "Paprika", 2.29, "28.11.2020", 1),
		Vegetable(540, "Uhorka", 1.79, "6.12.2020", 2),
		Vegetable(673, "Kapusta", 0.59, "20.11.2020", 1)
	};
	Goods* pointer = z;
	std::cout << "Smernik ukazuje na tuto zeleninu: " << std::endl;
	std::cout << pointer->Name() << std::endl;
	std::cout << pointer->Price() << " Eur/kg" << std::endl;	
	*/

	//Príklad: Smerník na objekt triedy Goods
	/*
	Goods* g = new Vegetable(540, "Uhorka", 1.79, "6.12.2020", 2);
	std::cout << "Smernik ukazuje na tuto zeleninu: " << std::endl;
	std::cout << g->Name() << std::endl;
	std::cout << g->Price() << " Eur/kg" << std::endl;
	delete g;
	*/
	
	//Príklad: Supermarket s výpisom informácií o tovare
	/*
	Goods t(309, "Chladnicka", 452.31);
	Food p(598, "Chlieb", 1.19, "5.11.2020");
	Vegetable z(439, "Cibula", 20, "10.1.2021", 1);
	t.info();
	p.info();
	z.info();
	*/

	//Príklad: Smerník na objekt triedy Goods - virtualne funckie
	/*
	Goods* g = new Vegetable(540, "Uhorka", 1.79, "6.12.2020", 2);
	g->info();
	delete g;
	*/

	//Príklad: Supermarket s poľom smerníkov
	/*
	Goods* t[3] = { new Goods(309, "Chladnicka", 452.31),
			new Food(598, "Chlieb", 1.19, "5.11.2020"),
			new Vegetable(439, "Cibula", 20, "10.1.2021", 1) 
	};
	for (int i = 0; i < 3; i++) {
		t[i]->info();
	}
	
	//Príklad: Supermarket s virtuálnymi deštruktormi :	
	for (size_t i = 0; i < 3; i++)
	{
		delete t[i];
	} 	
	*/

	//Príklad: Dedičnosť od viacerých rodičov a virtualne funckie
	/*
	Bat2 b("Netopier obycajny", "netopierovite", 5., 20., 15);
	b.printInfo();
	*/	
}