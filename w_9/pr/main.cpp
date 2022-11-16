#include <iostream>
#include <iomanip>

#include <chrono>
#include <utility>
#include <algorithm>

#include <vector>
#include <list>
#include <map>
#include <string>

class Timer { //meranie vypoctoveho casu pomocou STL <chrono>
public:
	static std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
	static std::chrono::time_point<std::chrono::high_resolution_clock> t_end;

	static void start() { t_start = std::chrono::high_resolution_clock::now(); }
	static void end(std::string s) { t_end = std::chrono::high_resolution_clock::now(); print(s); }
	static void print(std::string s) {
		std::cout << std::fixed << std::setprecision(2) << s
			<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
			<< " ms\n";
	}
};

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_start = std::chrono::high_resolution_clock::now();
std::chrono::time_point<std::chrono::high_resolution_clock> Timer::t_end = std::chrono::high_resolution_clock::now();

template<class T>
void printVectorData(T* data, int size) {
	for (int i = 0; i < size; i++)
	{
		std::cout << data[i] << std::endl;
	}
}

class Point {
private:
	int x = 0, y = 0;
public:
	Point() {};
	Point(int xx, int yy) :x(xx), y(yy) {};
	int X() { return x; }
	int Y() { return y; }
	void print() { std::cout << "X=" << x << " " << "Y=" << y << std::endl; }
};

int main()
{
	//Priklad pouzitia std::vector
	/*
	std::vector<int> v;
	v.push_back(1); //pridavam int na koniec std::vectoru
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	std::cout << v[1] << std::endl; //mozem pouzit nahodny pristup k prvku z vectora
	std::cout << "velkost: " << v.size() << std::endl; //viem zistit aktualnu velkost

	for (int i = 0; i < v.size(); i++)  //loop pomocou pristupu cez []
	{
		v[i] += 1;
		std::cout << v[i] << std::endl;
	}
	std::cout << std::endl;

	for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i) //loop pomocou iterátora
	{
		*i = *i + 1; //*i ukazuje priamo na prvok pola -> mozem ho menit
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;

	//vyuzitie funckii std::begin a std::end
	for (std::vector<int>::iterator i = std::begin(v); i != std::end(v); ++i)
	{
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;

	//loop pomocou konstatneho iterátora
	for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << *i << std::endl;
		//*i = *i + 1; //nemozem menit hodnotu *i, lebo iterator je konstatny
	}
	std::cout << std::endl;

	//loop pomocou reverzneho iterátora
	for (std::vector<int>::reverse_iterator i = v.rbegin(); i != v.rend(); ++i)
	{
		*i = *i + 1;
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;

	//Co sa stane ak chcem pristupit k prvku ktory neexisuje?
	//std::cout << v[5] << std::endl; // pozor! -> [] nekontroluje hranice

	try {
		std::cout << v.at(5) << std::endl; //fukcia at() kontroluje hranice a hadze out_of_range exception
	}
	catch (const std::out_of_range& oor) {
		std::cout << "Out of Range error: " << oor.what() << '\n';
	}
	*/

	//std::vector a casova narocnost:
	/*
	size_t n = 20000000;

	std::vector<double> bigV;

	Timer::start();
	for (size_t i = 0; i < n; i++)
	{
		bigV.push_back(i + i / 2. + sqrt(i));
	}
	Timer::end("Vector with pushBack: Wall clock time passed: ");

	double* bigA = new double[n]; //dynamicky alokovane pole

	Timer::start();
	for (size_t i = 0; i < n; i++)
	{
		bigA[i] = (i + i / 2. + sqrt(i));
	}
	Timer::end("Dynamically allocated array: Wall clock time passed: ");
	delete[] bigA;

	//ako zvysit efektivitu std::vectora? Pouzijem funkciu .resize().

	std::vector<double> bigV2;

	Timer::start();
	bigV2.resize(n); //pole sa naplni nulami  - ak by som chcel z nejakeho dovodu aby tam boli ine cisla tak mozem pouzit druhy argument bigV2.resize(n,...);

	for (size_t i = 0; i < n; i++)
	{
		bigV2[i] = (i + i / 2. + sqrt(i));
	}
	Timer::end("Vector with resize and access with [] : Wall clock time passed : ");

	//ako co by sa stalo keby namiesto [] pristupu na zapis pouzijem .at ?

	std::vector<double> bigV3;

	Timer::start();
	bigV3.resize(n); //pole sa naplni nulami  - ak by som chcel z nejakeho dovodu aby tam boli ine cisla tak mozem pouzit druhy argument bigV2.resize(n,...);

	for (size_t i = 0; i < n; i++)
	{
		//bigV3.at(i) = (i + i / 2. + sqrt(i));
		try {
			bigV3.at(i) = (i + i / 2. + sqrt(i));
		}
		catch (const std::out_of_range& oor) {
			std::cout << "Out of Range error: " << oor.what() << '\n';
		}
	}
	Timer::end("Vector with resize and access with .at() : Wall clock time passed : ");

	//Co ked neviem kolko dat chcem ulozit do vectora? napr citam zo suboru v ktorom neviem kolko je hodnot?

	std::vector<double> bigV4;
	size_t m = 20000000;

	bigV4.reserve(m * 2); //odhadnem velkost nacitanych dat - najde sa v pamati dostatocne velky blok na ulozenie takychto dat
	std::cout << "Capacity before loading data: " << bigV4.capacity() << std::endl; //capacity je velkost bloku ktoru som si odhadol -> nemylit si z .size()

	Timer::start();
	for (size_t i = 0; i < m; i++)
	{
		bigV4.push_back(i + i / 2. + sqrt(i));
	}
	Timer::end("Vector with pushBack but with reserve: Wall clock time passed: ");

	bigV4.shrink_to_fit(); //zredukujem capacity na size -> uvolnim pamat, ktoru som nezaplnil
	std::cout << "Capacity after loading data and after shrink_to_fit: " << bigV4.capacity() << std::endl;

	bigV4.clear(); //zmenit size na 0, ale capacity stale ostane na povodnej hodnote - miesto ostane alokovane

	std::cout << bigV4.size() << " " << bigV4.capacity() << std::endl;
	bigV4.shrink_to_fit(); //zmensim aj capacity na 0 - vsetko miesto, ktore vektor alokoval sa uvolnilo
	std::cout << bigV4.size() << " " << bigV4.capacity() << std::endl;
	*/

	//Konstruktor std::vectora
	/*
	std::vector<double> vNew(10, 5); //resize a nastavenie povodenej hodnoty moze byt priamo v konstruktore
	for (size_t i = 0; i < vNew.size(); i++)
	{
		std::cout << vNew.at(i) << std::endl;
	}
	std::cout << std::endl;

	std::vector<double> vNewCopy(vNew); //konstruktor prekopiruje data z vNew do vNewCopy;
	for (size_t i = 0; i < vNewCopy.size(); i++)
	{
		vNewCopy.at(i) += 1;
		std::cout << vNewCopy.at(i) << std::endl;
	}

	std::vector<double> vNewCopyPart(vNew.begin(), vNew.begin() + 5);  //konstruktor prekopiruje iba prvych 5 prvkov z vNew do vNewCopy;
	std::cout << std::endl;
	for (size_t i = 0; i < vNewCopyPart.size(); i++)
	{
		vNewCopyPart.at(i) += 2;
		std::cout << vNewCopyPart.at(i) << std::endl;
	}
	std::cout << std::endl;

	std::vector<double> vNew2(2); //vektor o velkosti 2
	vNew2 = vNew; //vektor vNew sa prekopiruje do vNew2
	std::cout << vNew2.size() << " " << vNew.size() << std::endl; //obe maju uz rovnaku velkost

	for (size_t i = 0; i < vNew.size(); i++)
	{
		vNew.at(i) = 10; //zmena vo vNew neovlivni data vo vNew2 - lebo tam su kopie dat
	}

	for (size_t i = 0; i < vNew.size(); i++)
	{
		std::cout << vNew.at(i) << std::endl;
		std::cout << vNew2.at(i) << std::endl;
	}

	//Co ked chcem data iba presunut?
	std::cout << std::endl;
	vNew2 = std::move(vNew); //funkcia STL kniznice <utility>
	std::cout << vNew2.size() << " " << vNew.size() << std::endl; //vNew je po presunuti prazdne
	std::cout << vNew.capacity() << std::endl; //uvolnila sa aj pamat, ktoru vNew zaberal
	*/

	//ostatne funkcie std::vectora
	/*
	std::vector<int> d(10);
	for (int i = 0; i < d.size(); i++)
	{
		d[i] = i;
	}

	std::cout << "First: " << d.front() << " Last: " << d.back() << std::endl; //referencia na prvy a posledny prvok
	d.back() = 99;

	for (int i = 0; i < d.size(); i++)
	{
		std::cout << d.at(i) << " ";
	}

	if (!d.empty()) { // .empty() vrati true ak .size() == 0
		std::cout << "There is data in vector" << std::endl;
	}

	if (d.size() == 0) { // .empty() vrati true ak .size() == 0
		std::cout << "There is data in vector" << std::endl;
	}

	printVectorData<int>(d.data(), static_cast<int>(d.size())); //.data() vrati smernik na data vo vektore

	d.assign(5, 1); //resiznem vector na velkost 5 a priradim do neho jednotky
	printVectorData<int>(d.data(), static_cast<int>(d.size()));

	std::cout << "d po assign(5, 1): " << d.size() << " " << d.capacity() << std::endl; //po assigne sa nezmeni capacity

	std::vector<int> d2;
	d2.assign(d.begin() + 1, d.end() - 1); //alebo viem priradit cast ineho vektora

	std::cout << "d2 po assign(d.begin() + 1, d.end() - 1): " << d2.size() << " " << d2.capacity() << std::endl;

	while (!d.empty())
	{
		d.pop_back(); //odstranim posledny prvok - po kazdom pop_back sa zmensni velkost o 1 = moze sa zavolat resize()
	}

	std::cout << "d po pop_back(): " << d.size() << " " << d.capacity() << std::endl; //pop_back nezmensuje capacity

	std::vector<int>::iterator it = d2.begin() + 1;
	d2.insert(it, 3); //vlozim hodnotu 3 na 2 poziciu vo vectore - zvacsi sa aj velkost vektora o 1
	printVectorData<int>(d2.data(), static_cast<int>(d2.size()));

	d2.erase(d2.begin() + 1); // vymazem prvok ktory som vysie vlozil.
	//Nemohol som pouzit premennu it, lebo po resize ktory sposobil insert sa iterator "pokazi".

	printVectorData<int>(d2.data(), static_cast<int>(d2.size()));

	std::vector<int> dSwap1(5, 1);
	std::vector<int> dSwap2(3, 5);
	dSwap1.swap(dSwap2); //prehodi obsahy vektorov

	printVectorData<int>(dSwap1.data(), static_cast<int>(dSwap1.size()));
	printVectorData<int>(dSwap2.data(), static_cast<int>(dSwap2.size()));

	std::cout << "dSwap1 capacity: " << dSwap1.capacity() << std::endl; //upravi sa aj capacity
	std::cout << "dSwap2 capacity: " << dSwap2.capacity() << std::endl;
	*/

	//std::vector objektov
	/*
	std::vector<Point> p;
	p.push_back(Point(1, 2)); //klasicky push_back potrebuje na vstup objekt Point
	p.emplace_back(3, 4); //pomocou emplace_back mozem pridat Point tak, ze vymenujem iba argumenty konsturktora triedy Point

	for (size_t i = 0; i < p.size(); i++)
	{
		p.at(i).print();
	}
	*/

	//std::vector ako argument funkcie z algorithm
	/*
	std::vector<int> a(10);

	for (int i = 0; i < a.size(); i++)
	{
		a[i] = i;
	}
	std::cout << *std::max_element(a.begin(), a.end());
	*/

	//2D vector
	/*
	std::vector<std::vector<int>> v2d;
	v2d.resize(5);
	for (size_t i = 0; i < v2d.size(); i++)
	{
		v2d[i].resize(5, 1);
	}

	for (size_t i = 0; i < v2d.size(); i++)
	{
		for (size_t j = 0; j < v2d[i].size(); j++)
		{
			std::cout << v2d[i][j] << v2d.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}

	std::vector<std::vector<int>> a2d(5, std::vector<int>(5, 2));
	for (size_t i = 0; i < a2d.size(); i++)
	{
		for (size_t j = 0; j < a2d[i].size(); j++)
		{
			std::cout << a2d[i][j] << " ";
		}
		std::cout << std::endl;
	}
	*/

	//std::vector<std::vector<std::vector<std::vector<int>>>> v4d;

	//std::list ukazka
	/*
	std::list<int> l;
	for (int i = 0; i < 10; i++)
	{
		l.push_back(i + 10);
	}

	std::cout << "velkost: " << l.size() << std::endl; //viem zistit aktualnu velkost

	//pozor! nemozem pouzit nahodny pristup k prvku z listu
	for (std::list<int>::iterator i = l.begin(); i != l.end(); ++i) //loop pomocou iterátora
	{
		*i = *i + 1; //*i ukazuje priamo na prvok pola -> mozem ho menit
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;

	std::list<int>::iterator it = l.begin(); //iterator zaciatku listu
	std::advance(it, 5); // posunieme iterator sa na 5 prvkoch v liste
	std::cout << *it << std::endl;
	*/

	//std::map ukazka
	/*
	std::map<std::string, int > m;

	//do mapy sa uklada premenna typu std::pair
	m.insert(std::make_pair("a", 1));
	m.insert(std::make_pair("b", 2));
	m.insert(std::make_pair("c", 3));
	m.insert(std::make_pair("d", 4));
	m.insert(std::pair<std::string, int>("e", 5));

	std::cout << "velkost: " << m.size() << std::endl; //viem zistit akutualnu velkost
	std::cout << m["a"] << std::endl; //mozem pouzit nahodny pristup k prvku pomocou key z map
	std::cout << m.at("a") << std::endl; //mozem pouzit nahodny pristup k prvku pomocou key z map -  ak nenajde key vrati  out_of_range

	std::cout << std::endl;
	for (std::map<std::string, int>::iterator i = m.begin(); i != m.end(); ++i) //loop pomocou iterátora
	{
		std::cout << (*i).first << " " << (*i).second << std::endl;
	}

	m.insert(std::make_pair("a", 6)); //kluce musia byt unikatne - takyto zaznam sa nevlozi
	m["a"] = 7; //hodnota sa nahradi

	std::cout << std::endl;
	for (std::map<std::string, int>::iterator i = m.begin(); i != m.end(); ++i) //loop pomocou iterátora
	{
		std::cout << (*i).first << " " << (*i).second << std::endl;
	}
	*/
	return 0;
}