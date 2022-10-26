#include <iostream>
#include <string>
#include <chrono>

// ComplexNumber
class ComplexNumber
{
private:
    float a = 0, b = 0;

public:
    ComplexNumber(float real, float imag)
    {
        a = real;
        b = imag;
    }                  // pretazeny
    ComplexNumber() {} // pretazeny
    ComplexNumber Plus(const ComplexNumber &x);
    float A() { return a; }
    float B() { return b; }
    void setA(float newA) { a = newA; }
    void setB(float newB) { b = newB; }
    void print() { std::cout << a << "+" << b << "i"; }

    ComplexNumber operator+(const ComplexNumber &x);
    ComplexNumber operator*(const ComplexNumber &x);
    ComplexNumber operator*(float t);
};

ComplexNumber ComplexNumber::Plus(const ComplexNumber &x)
{
    ComplexNumber z(0, 0);
    z.setA(x.a + a);
    z.setB(x.b + b);
    return z;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber &x)
{
    ComplexNumber z;
    z.setA(a + x.a);
    z.setB(b + x.b);
    return z;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &x)
{
    ComplexNumber z;
    z.setA(a * x.a - b * x.b);
    z.setB(a * x.b + b * x.a);
    return z;
}

ComplexNumber ComplexNumber::operator*(float t)
{
    ComplexNumber z;
    z.setA(a * t);
    z.setB(b * t);
    return z;
}

// Date
class Date
{
private:
    int day, month, year;

public:
    Date() : day(0), month(0), year(0) {}
    Date(std::string s, std::string delimiter);
    Date(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }

    void print() { std::cout << day << ". " << month << ". " << year << std::endl; }
    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    bool operator>(const Date &dat);
    bool operator<(const Date &dat);
    bool operator==(const Date &dat);

    Date &operator++();
    Date operator++(int);

    friend std::istream &operator>>(std::istream &input, Date &D);
};

Date::Date(std::string s, std::string delimiter)
{ // rozdelim datum day delimiter month delimiter year
    int pos = 0;
    std::string token;
    int date[3] = {0, 0, 0};
    int counter = 0;

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        date[counter] = std::stoi(token);
        s.erase(0, pos + delimiter.length());
        counter++;
    }
    day = date[0];
    month = date[1];
    year = std::stoi(s);
}

bool Date::operator>(const Date &dat)
{
    if (year > dat.year)
    {
        return true;
    }
    else if (year < dat.year)
    {
        return false;
    }
    else
    {
        if (month > dat.month)
        {
            return true;
        }
        else if (month < dat.month)
        {
            return false;
        }
        else
        {
            if (day > dat.day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

bool Date::operator<(const Date &dat)
{
    if (year < dat.year)
    {
        return true;
    }
    else if (year > dat.year)
    {
        return false;
    }
    else
    {
        if (month < dat.month)
        {
            return true;
        }
        else if (month > dat.month)
        {
            return false;
        }
        else
        {
            if (day < dat.day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

bool Date::operator==(const Date &dat)
{
    if (year == dat.year && month == dat.month && day == dat.day)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Date &Date::operator++()
{
    std::cout << "funkcia Date& Date::operator++()" << std::endl;
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day == 31 && month == 12)
    {
        year++;
        month = 1;
        day = 1;
    }
    else if (day == daysInMonth[month - 1])
    {
        month++;
        day = 1;
    }
    else
    {
        day++;
    }
    return *this;
}

Date Date::operator++(int)
{
    std::cout << "Date Date::operator++(int)" << std::endl;
    int d = day, m = month, y = year;

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day == 31 && month == 12)
    {
        year++;
        month = 1;
        day = 1;
    }
    else if (day == daysInMonth[month - 1])
    {
        month++;
        day = 1;
    }
    else
    {
        day++;
    }
    return Date(d, m, y);
}

std::istream &operator>>(std::istream &input, Date &D)
{
    input >> D.day >> D.month >> D.year;
    return input;
}

// myString
class myString
{
private:
    char *s;
    int lenght;

public:
    myString(int d, const char *sInput);
    myString(const myString &str); // kopirovaci konstrutor
    ~myString()
    {
        delete[] s;
        s = nullptr;
    };
    char *getString() { return s; };
    int getLength() { return lenght; };
    void changeString(int d, const char *sInput);

    myString &operator=(const myString &str);
};

myString::myString(int d, const char *sInput) : lenght(d)
{
    s = new char[lenght]; // dynamicka alokacia
    std::cout << "Alokujem pamat v konstruktore na adrese: " << (void *)s << std::endl;
    for (int i = 0; i < lenght; i++)
    {
        s[i] = sInput[i];
    }
}

myString::myString(const myString &str)
{                        // pristupujem k s1 , nemozem ju menit
    lenght = str.lenght; // mozem pristupit k private premennej str.length
    s = new char[lenght];
    std::cout << "Alokujem pamat v kopirovacom konstruktore na adrese: " << (void *)s << std::endl;
    for (int i = 0; i < lenght; i++)
    {
        s[i] = str.s[i];
    }
}

void myString::changeString(int d, const char *sInput)
{
    delete[] s;
    lenght = d;
    s = new char[lenght];
    for (int i = 0; i < lenght; i++)
    {
        s[i] = sInput[i];
    }
}

myString &myString::operator=(const myString &str)
{
    if (lenght < str.lenght) // ak je nový retazec dlhší, realokujeme pamäť
    {
        delete[] s;
        s = new char[str.lenght];
    }
    lenght = str.lenght;
    for (int i = 0; i < lenght; i++)
    {
        s[i] = str.s[i];
    }
    return *this;
}

// Point, Polygon, Calculator
class Point
{
private:
    int x, y;

public:
    Point()
    {
        x = 0;
        y = 0;
    }
    int X() { return x; }
    int Y() { return y; }
    void setPoint(int x1, int y1)
    {
        x = x1;
        y = y1;
    }
};

class Polygon
{
private:
    Point *B;
    int n;

public:
    Polygon(int n2, Point *P) : n(n2) { setPoints(P); };
    Polygon(int n2) : n(n2){};
    Polygon(const Polygon &U); // Kopirovaci konstruktor
    ~Polygon();
    void printPoints(std::string name);
    void setPoints(Point *P);
    int N() { return n; }
    int BX(int index) { return B[index].X(); } // vráti x-súradnicu bodu
    int BY(int index) { return B[index].Y(); } // vráti y-súradnicu bodu

    Point &operator[](int index) { return B[index]; }
    friend std::ostream &operator<<(std::ostream &output, const Polygon &P);
};

Polygon::Polygon(const Polygon &U)
{
    std::cout << "kopirovaci konstruktor" << std::endl;
    n = U.n;
    setPoints(U.B);
}

void Polygon::setPoints(Point *P)
{
    B = new Point[n];
    for (int i = 0; i < n; i++)
    {
        B[i] = P[i];
    }
}

Polygon::~Polygon()
{
    std::cout << "Dealokujem pole..." << std::endl;
    delete[] B;
}

void Polygon::printPoints(std::string name)
{
    std::cout << "n-uholnik " << name << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << i << ". vrchol: " << B[i].X() << "  " << B[i].Y() << std::endl;
    }
}

std::ostream &operator<<(std::ostream &output, const Polygon &P)
{
    for (int i = 0; i < P.n; i++)
    {
        output << i << ". vrchol: " << P.B[i].X() << "  " << P.B[i].Y() << std::endl;
    }
    return output;
}

class Calculator
{
public:
    double perimeter(Polygon U);
    double perimeterAlt(Polygon U);
    Polygon displacement(Polygon &U, int dx, int dy);
};

double Calculator::perimeter(Polygon U)
{
    double o = 0.;
    for (int i = 0; i < U.N() - 1; i++)
    {
        o += sqrt(pow(U.BX(i + 1) - U.BX(i), 2) + pow(U.BY(i + 1) - U.BY(i), 2));
    }

    o += sqrt(pow(U.BX(U.N() - 1) - U.BX(0), 2) + pow(U.BY(U.N() - 1) - U.BY(0), 2));
    return o;
}

double Calculator::perimeterAlt(Polygon U)
{
    double o = 0.;
    for (int i = 0; i < U.N() - 1; i++)
    {
        o += sqrt(pow(U[i + 1].X() - U[i].X(), 2) + pow(U[i + 1].Y() - U[i].Y(), 2));
    }

    o += sqrt(pow(U[U.N() - 1].X() - U[0].X(), 2) + pow(U[U.N() - 1].Y() - U[0].Y(), 2));
    return o;
}

Polygon Calculator::displacement(Polygon &U, int dx, int dy)
{
    Point *B = new Point[U.N()];
    for (int i = 0; i < U.N(); i++)
    {
        B[i].setPoint(U.BX(i) + dx, U.BY(i) + dy);
    }
    Polygon U1(U.N(), B); // dynamicky alokované pole pre body
    delete[] B;
    return U1;
}

int main()
{
    // Príklad: Sčítanie komplexných čísel
    /*
    ComplexNumber x(1, 2), y(3, -1);
    ComplexNumber z(0, 0);
    //ComplexNumber z; //Príklad: Súčet komplexných čísel s preťažením konštruktora
    z = x.Plus(y);
    std::cout << "Sucet cisel ";
    x.print();
    std::cout << " a ";
    y.print();
    std::cout << " je ";
    z.print();
    */

    // Príklad: Počítanie násobkov komplexného čísla
    /*
    ComplexNumber x(1, 2), zz[4];
    for (int i = 0; i < 4; i++)
    {
        zz[i].setA(x.A() * i);
        zz[i].setB(x.B() * i);
        zz[i].print();
        std::cout << std::endl;
    }
    */

    // Príklad: Počítanie vopred neznámeho počtu násobkov komplexného čísla
    /*
    ComplexNumber x(1, 2), *z;
    int n;
    std::cout << "Kolko nasobkov sa ma vypocitat? ";
    std::cin >> n;
    z = new ComplexNumber[n];

    for (int i = 0; i < n; i++)	{
        z[i].setA(x.A() * i);
        z[i].setB(x.B() * i);
        z[i].print();
        std::cout << std::endl;
    }
    */

    // Príklad: Program, ktorý vypočíta, koľko dní ostáva do najbližšej výplaty.
    /*
    int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int d, m, y;
    std::string sdat;
    std::cout << "Aky je dnesny datum? ";
    std::getline(std::cin, sdat);

    Date dat(sdat, "."); //volam Date(std::string s,std::string delimiter);
    std::cout << "Ktory den v mesiaci chodi vyplata? ";
    std::cin >> d;

    y = dat.getYear();
    if (dat.getDay() <= d) {
        m = dat.getMonth(); //vyplata tento mesiac
    }
    else {
        if (dat.getMonth() == 12) {
            m = 1;
            y++; //vyplata az v dalsom roku
        }
        else {
            m = dat.getMonth() + 1; //vyplata buduci mesiac
        }
    }

    Date payout(d, m, y); //Date(int d, int m, int y)

    std::cout << "Najblizsia vyplata bude dna ";
    payout.print();

    if (payout.getMonth() == 1 && dat.getMonth() == 12) {
        d = d + 31;
    }
    else {
        d = d + daysInMonth[dat.getMonth() - 1] * (payout.getMonth() - dat.getMonth());
    }
    std::cout << "Do vyplaty zostava " << d - dat.getDay() << " dni" << std::endl;
    */

    // Príklad: Priraďovanie znakových reťazcov pomocou kopírovacieho konštruktora
    /*
    myString s1(35, "Toto je test novej triedy myString");
    myString s2 = s1;  //Zavola kopirovaci konstruktor s s1 ako argumentom
    std::cout.write(s1.getString(), s1.getLength());
    std::cout << std::endl;
    std::cout.write(s2.getString(), s2.getLength());
    std::cout << std::endl;

    s1.changeString(20, "Podarilo sa nam to?");
    std::cout.write(s1.getString(), s1.getLength());
    std::cout << std::endl;
    std::cout.write(s2.getString(), s2.getLength());
    */

    // Príklad: Počítanie obvodu n - uholníka
    /*
    Point B[4];
    B[0].setPoint(0, 0);
    B[1].setPoint(1, 0);
    B[2].setPoint(1, 1);
    B[3].setPoint(0, 1);

    Polygon square(4, B);
    Calculator K;

    square.printPoints("Stvorec");
    std::cout << "Obvod stvorca je: " << K.perimeter(square) << std::endl;
    */

    // Príklad: Posúvanie n - uholníka
    /*
    Polygon newSquare = K.displacement(square, 1, 1);
    newSquare.printPoints("Posunuty stvorec");
    */

    // Príklad: Počítanie s komplexnými číslami
    /*
    ComplexNumber x(1, 2), y(3, -1), z(1,1), z1, z2, z3;
    z1 = x + y; //y je vstup do ComplexNumber operator+(const ComplexNumber& x);
    z2 = x * y;
    z3 = x * 3.;
    std::cout << "Komplexne cisla: ";
    x.print();
    std::cout << ", ";
    y.print();
    std::cout << std::endl << "x+y: ";
    z1.print();
    std::cout << std::endl << "x*y: ";
    z2.print();
    std::cout << std::endl << "x*3: ";
    z3.print();
    */

    // Príklad: Porovnávanie veku dvoch osôb
    /*
    std::string meno1, meno2, sdat1, sdat2;
    std::cout << "Meno a datum narodenia prvej osoby: " << std::endl;
    std::getline(std::cin, meno1);
    std::getline(std::cin, sdat1);
    std::cout << "Meno a datum narodenia druhej osoby: " << std::endl;
    std::getline(std::cin, meno2);
    std::getline(std::cin, sdat2);

    Date dat1(sdat1, "."), dat2(sdat2, ".");

    if (dat1 < dat2) {
        std::cout << meno1 << " je starsi ako " << meno2 << std::endl;
    }
    else if (dat1 > dat2) {
        std::cout << meno2 << " je starsi ako " << meno1 << std::endl;
    }
    else if(dat1 == dat2 ){
        std::cout << "Tito dvaja su rovnako stari" << std::endl;
    }
    */

    /*
    int i=0;
    int j = i++; // v j je 0
    int l = i; // v l je 1
    int k = ++i; //v k je 2
    */

    // Príklad: Určenie nasledujúceho dňa
    /*
    std::string sdat;
    std::cout << "Aky je dnesny datum? ";
    std::getline(std::cin, sdat);
    Date dat(sdat, ".");

    Date tommorow = ++dat; //++dat zvysi datum o jeden den a vrati uz zvyseny datum.
    std::cout << "Zajtrajsi datum je: ";
    dat.print();
    Date stillTommorow = dat++; //dat++ zvysi datum o jeden den, ale vrati originalny datum pred zvysenim.
    std::cout << "Pozajtrajsi datum je: ";
    dat.print();

    tommorow.print();
    stillTommorow.print();
    dat.print();
    */

    // Príklad: Priraďovanie objektov triedy myString:
    /*
    myString s1(35, "Toto je test novej triedy myString");
    myString s2(0, "");
    std::cout.write(s1.getString(), s1.getLength());
    std::cout << std::endl;
    std::cout.write(s2.getString(), s2.getLength());
    std::cout << std::endl;
    s2 = s1; //na tomto mieste sa nevola kopirovaci konstruktor! treba pretazit operator =
    std::cout.write(s1.getString(), s1.getLength());
    std::cout << std::endl;
    std::cout.write(s2.getString(), s2.getLength());
    std::cout << std::endl;
    */

    // Príklad: Výpis súradníc bodov n-uholnika do konzoly pomocou operátoru << :
    /*
    Point B[4];
    B[0].setPoint(0, 0);
    B[1].setPoint(1, 0);
    B[2].setPoint(1, 1);
    B[3].setPoint(0, 1);

    Polygon square(4, B);
    Calculator K;
    square.printPoints("Stvorec");
    std::cout << "Obvod stvorca je: " << K.perimeterAlt(square) << std::endl;

    std::cout << square;
    */

    // Príklad: Priradenie dátumu zo vstupu z konzoly pomocou vstupného operátoru >> :

    /*
    Date d;
    std::cout << "Zadaj postupne den, mesiac a rok:" << std::endl;
    std::cin >> d;
    d.print();
    */

    return 0;
}