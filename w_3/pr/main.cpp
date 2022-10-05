#include <iostream>
#include <string>

//Príklad: Vytvoríme triedu Human
class Human {
private:
	std::string name, profession;
	int age;
public:
	Human(); //konštruktor musí byť public
	Human(std::string n, std::string p, int a); //konštruktor s parametrami.
	//Human(std::string n, std::string p, int a) :name(n), profession(p), age(a) {};
	//Human(std::string n, std::string p = "stazista", int a = 18);
	void setData(std::string n, std::string p, int a);
	void printData();
	int getAge();
	void setProfession(std::string newP);
};

Human::Human() {
	name = "";
	profession = "";
	//name = "Mr. Nobody";
	//profession = "unknown";
	age = 0;
}

Human::Human(std::string n, std::string p, int a) {
	name = n;
	profession = p;
	age = a;
}

void Human::setData(std::string n, std::string p, int a) {
	name = n;
	profession = p;
	age = a;
}

void Human::printData() {
	std::cout << "Ahoj, volam sa " << name << std::endl;
	std::cout << "Mam " << age << " rokov" << std::endl;
	std::cout << "Moje zamestnanie je " << profession << std::endl;
}

int Human::getAge() {
	return age;
}

void Human::setProfession(std::string newP) {
	profession = newP;
}

//Príklad: Trieda na uchovávanie znakových reťazcov (imitácia typu string), s definovaným deštruktorom
class myString {
private:
	char* s;
	int lenght;
public:
	myString(int d, const char* sInput);
	~myString();
	char* getString();
	int getLength();
	void changeString(int d, const char* sInput);
};

myString::myString(int d, const char* sInput) :lenght(d) {
	s = new char[lenght]; //dynamicka alokacia
	for (int i = 0; i < lenght; i++) {
		s[i] = sInput[i];
	}
}

myString::~myString() {
	delete[] s; //dealokacia pamate alokovanej v konstruktore
	//s = nullptr; //nastavenie pointera ako prazdny pointer
	std::cout << "zavolany destruktor\n";
}

char* myString::getString() {
	return s;
}

int myString::getLength() {
	return lenght;
}

void myString::changeString(int d, const char* sInput) {
	delete[] s;
	lenght = d;
	s = new char[lenght];
	for (int i = 0; i < lenght; i++) {
		s[i] = sInput[i];
	}
}

//Príklad: Trieda Human s inline funkciou setProfession a getAge
class Human2 {
private:
	std::string name, profession;
	int age;
public:
	Human2() :name(""), profession(""), age(0) {};
	Human2(std::string n, std::string p, int a) :name(n), profession(p), age(a) {};
	void setData(std::string n, std::string p, int a);
	void printData();
	inline void setProfession(std::string newP) { profession = newP; };
	int getAge() { return age; }; //numusim ani napisat inline a bude inline
};

void Human2::setData(std::string n, std::string p, int a) {
	name = n;
	profession = p;
	age = a;
}

void Human2::printData() {
	std::cout << "Ahoj, volam sa " << name << std::endl;
	std::cout << "Mam " << age << " rokov" << std::endl;
	std::cout << "Moje zamestnanie je " << profession << std::endl;
}



//Príklad: Priraďovanie trojuholníkov
class Point {
private:
	int x, y;
public:
	Point(int x1, int y1) :x(x1), y(y1) {}
	int X() { return x; }
	int Y() { return y; }
};

class Triangle {
private:
	Point A, B, C;
public:
	Triangle(Point b1, Point b2, Point b3) :A(b1), B(b2), C(b3) {}
	void printPoints(std::string pointName);
	void changePoints(Point b1, Point b2, Point b3) { A = b1; B = b2; C = b3; }
};

void Triangle::printPoints(std::string pointName) {
	std::cout << "Triangle: " << pointName << std::endl;
	std::cout << "A[" << A.X() << ", " << A.Y() << "]" << std::endl;
	std::cout << "B[" << B.X() << ", " << B.Y() << "]" << std::endl;
	std::cout << "C[" << C.X() << ", " << C.Y() << "]" << std::endl;
}

class Point2 {
private:
	int x, y;
public:
	Point2() :x(0), y(0) {}
	int X() { return x; }
	int Y() { return y; }
	void setPoint(int x1, int y1) { x = x1; y = y1; }
};

class Triangle2 {
private:
	Point2 B[3];
public:
	Triangle2(Point2 b1, Point2 b2, Point2 b3) { B[0] = b1; B[1] = b2; B[2] = b3; }
	void printPoints(std::string name);
	void changePoints(Point2 b1, Point2 b2, Point2 b3) { B[0] = b1; B[1] = b2; B[2] = b3; }
};

void Triangle2::printPoints(std::string printName) {
	std::cout << "Triangle " << printName << std::endl;
	std::cout << "A[" << B[0].X() << ", " << B[0].Y() << "]" << std::endl;
	std::cout << "B[" << B[1].X() << ", " << B[1].Y() << "]" << std::endl;
	std::cout << "C[" << B[2].X() << ", " << B[2].Y() << "]" << std::endl;
}

int main()
{
	
	Human Jozef;
	Jozef.setData("Jozef", "murar", 35);
	Jozef.printData();

	std::cout << Jozef.getAge() << std::endl;
	Jozef.setProfession("elektrikar");
	Jozef.printData();
	

	/*
	Human Martin;
	Martin.printData();
	*/

	/*
	Human zamestnanec("Katarina", "uctovnicka", 26);
	zamestnanec.printData();
	*/

	/*
	Human zamestnanec("Katarina");
	zamestnanec.printData();
	*/

	/*
	myString s1(36, "Toto je test novej triedy myString\n");
	myString s2(25, "Asi sa nam to podarilo!\n");
	std::cout.write(s1.getString(), s1.getLength());
	std::cout.write(s2.getString(), s2.getLength());
	// aj keď to nie je explicitne povedané, tu sa zavolajú deštruktory

	//s1.~myString();
	*/

	/*
	Human2 zamestnanec("Katarina", "uctovnicka", 29);
	zamestnanec.setProfession("veducia ekonomickeho oddelenia");
	zamestnanec.printData();
	*/

	/*
	Human2 zamestanci[10];
	for (size_t i = 0; i < 10; i++)
	{
		zamestanci[i].setData("abc", "test", i);
		zamestanci[i].printData();
	}
	*/

	/*
	Human2 zamestanci[4] = { Human2("Michal", "uradnik", 18),
		Human2("Maria", "uradnik", 18),
		Human2("Jozef", "uradnik", 18),
		Human2("Julia", "uradnik", 18) };

	for (size_t i = 0; i < 4; i++)
	{
		zamestanci[i].printData();
	}
	*/

	/*
	Human2 a = Human2("Michal", "uradnik", 18);
	Human2 b = Human2("Jozef", "uradnik", 18);
	Human2 c = Human2("Maria", "uradnik", 18);
	Human2 d = Human2("Julia", "uradnik", 18);

	Human2 zamestanci[4] = { a,b,c,d};

	for (size_t i = 0; i < 4; i++)
	{
		zamestanci[i].printData();
	}
	*/

	/*
	Point A(10, 10), B(20, 10), C(15, 15);
	Point D(0, 0), E(10, 0), F(3, 6);
	Triangle T1(A, B, C);
	Triangle T2(D, E, F);
	T1.printPoints("T1");
	T2.printPoints("T2");
	T2 = T1;
	T2.printPoints("T2");
	T1.changePoints(D, E, F); //obsah T2 sa už nezmení, aj keď bol kópiou T1
	T1.printPoints("T1");
	T2.printPoints("T2");
	*/

	/*
	Point2 A, B, C;
	A.setPoint(10, 10);
	B.setPoint(20, 10);
	C.setPoint(15, 15);
	Triangle2 T1(A, B, C);
	Triangle2 T2(C, B, A);
	T1.printPoints("T1");
	T2.printPoints("T2");
	T2 = T1;
	T1.printPoints("T1");
	T2.printPoints("T2");
	*/

	/*
	myString s1(35, "Toto je test novej triedy myString");
	myString s2 = s1;
	std::cout.write(s1.getString(), s1.getLength());	std::cout << std::endl;
	std::cout.write(s2.getString(), s2.getLength());	std::cout << std::endl;

	s1.changeString(20, "Podarilo sa nam to?");
	std::cout.write(s1.getString(), s1.getLength());	std::cout << std::endl;
	std::cout.write(s2.getString(), s2.getLength());
	*/

	//Príklad: Smerník na objekt triedy Human

	/*
	Human* Jozef = new Human;
	Jozef->setData("Jozo", "murar", 35);
	Jozef->printData();
	delete Jozef;
	*/

	//Teraz uvažujeme konštruktor s parametrami

	/*
	Human* Maria = new Human("Maria", "uctovnicka", 30);
	Maria->printData();
	delete Maria;
	*/

	//Príklad: Alokácia poľa objektov triedy Human

	/*
	Human* student = new Human[2];
	student[0].setData("Peter", "Student", 20);
	student[1].setData("Filip", "Student", 22);
	for (int i = 0; i < 2; i++) {
		student[i].printData();
	}
	delete[] student;
	*/

	//Príklad: Alokácia poľa smerníkov na objekty

	/*
	Human** student = new Human* [3];
	student[0] = new Human("Peter", "Student", 20);
	student[1] = new Human("Filip", "Student", 22);
	student[2] = new Human("Maria", "Student", 21);
	for (int i = 0; i < 3; i++) {
		student[i]->printData();
	}
	for (int i = 0; i < 3; i++) {
		delete student[i];
	}

	delete[] student;
	*/

	//Treba si uvedomiť rozdiel pri vytváraní poľa objektov a poľa smerníkov na objekty

	/*
	Human* student = new Human[2];
	for (int i = 0; i < 2; i++) {
		student[i].printData();
	}
	*/

	//Takyto kod spadne

	/*
	Human** studentPtr = new Human*[2];
	for (int i = 0; i < 2; i++) {
		studentPtr[i]->printData();
	}
	*/

	//Takyto kod je spravny

	/*
	Human** studentPtr = new Human * [2];
	for (int i = 0; i < 2; i++) {
		studentPtr[i] = new Human();
		studentPtr[i]->printData();
	}
	for (int i = 0; i < 2; i++) {
		delete studentPtr[i];
	}

	delete[] studentPtr;
	*/

	return 0;
}
