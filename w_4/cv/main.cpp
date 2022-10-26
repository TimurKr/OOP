#include <iostream> 
#include <iomanip>
#include <string>
#include <fstream>

using namespace std; 

#define max_products_per_user 10

#define FOUND 0
#define NOT_FOUND 1
#define FOUND_ERROR 2


class Product {
    private: 
        unsigned int id;
        string name;
        string manufacturer;
        unsigned int in_store;
        float price;
    public: 
        // Constructors
        Product () 
            : id(0) {}
        Product (unsigned int id, string name, string manufacturer, unsigned int in_store, float price) 
            : id(id), name(name), manufacturer(manufacturer), in_store(in_store), price(price) {};

        // Interface
        void setAll(unsigned int id, string name, string manufacturer, unsigned int in_store, float price);
        void setId(unsigned int id) { this->id = id; };
        void setName(unsigned int name) { this->name = name; };
        void setManufacturer(unsigned int manufacturer) { this->manufacturer = manufacturer; };
        void setInStore(unsigned int in_store) { this->in_store = in_store; };
        void setPrice(float price) { this->price = price; };

        void printAll();

        unsigned int getId() { return id; };
        string getName() { return name; };
        string getManufacturer() { return manufacturer; };
        unsigned int getInStore() { return in_store; };
        float getPrice() { return price; };
};

void Product::setAll(unsigned int id, string name, string manufacturer, unsigned int in_store, float price){
    this->id = id;
    this->name = name;
    this->manufacturer = manufacturer;
    this->in_store = in_store;
    this->price = price;
}

void Product::printAll(){
    std::cout << 
        id << " " <<
        name << " " << 
        manufacturer << " " << 
        in_store << " " << 
        price << endl;
}

class Customer {
    private: 
        string name, surname;
        float budget;
        unsigned int num_prod;
        Product* products[max_products_per_user];
    public:
        // Constructors
        Customer();

        Customer(string name, string surname, float budget)
        : name(name), surname(surname), budget(budget) {}

        bool add_product(Product* product);

        void printAllProducts();

        bool canAfford(Product* product);

        bool finish(string path_to_bill);
        
};

Customer::Customer() { 
    std::cout << "Vytajte u nás v obchode" << endl << endl;
    std::cout << "Prosím zadajte svoje meno: ";
    std::cin >> name;
    std::cout << "Prosím zadajte svoje priezvisko: ";
    std::cin >> surname;
    std::cout << "Aký máte na dnes rozpočet?: ";
    std::cin >> budget;
    num_prod = 0;
}

bool Customer::add_product(Product* product) {
    if (num_prod == max_products_per_user) { return false; }
    if (product == nullptr) { return false; }

    products[num_prod++] = product;
    budget -= product->getPrice();
    return true;
}

void Customer::printAllProducts() {
    std::cout << "Num of Prod: " << num_prod << endl;
    for (int i=0; i<num_prod; i++) {
        products[i]->printAll();
    }
}

bool Customer::canAfford(Product* product) {
    if (product->getPrice() <= budget) {
        return true;
    }
    return false;
}

bool Customer::finish(string path_to_bill) {
    fstream f;
    f.open(path_to_bill, ios::out);
    if (!f.is_open()) {
        return false;
    }
    f << name << " " << surname << endl;

    float suma = 0;
    for (unsigned int prod=0; prod<num_prod; prod++){
        suma += products[prod]->getPrice(); 

        f << 
            "Položka: " <<  products[prod]->getName() << 
            "\tVýrobca: " << products[prod]-> getManufacturer() << 
            "\t\tCena: " << products[prod]->getPrice()<< endl;
    }

    f << endl; 
    f << "Cena spolu: " << suma << endl;
    f << "Zostatok: " << budget << endl;

    std::cout << "Blok si nájdete v dokumente " << path_to_bill << endl;
    return true;
}



class Eshop {
    private:
        Product *products = nullptr;
        unsigned int num_prod = 0;
    public:
        // Constructors
        Eshop (string path_to_input);
        ~Eshop ();
        bool read_database(string path_to_database);

        // Interface 
        void printSaleInfo(unsigned int ID);
        void setInStore(unsigned int ID, unsigned int new_in_store);
        void printAllProducts();

        // Search
        Product* find_by_id(unsigned int id);
        Product* find_by_name(string name);
        Product* find_by_manufacturer(string manufacturer);
        
        // Shopping
        bool end();
        Product* pick_product();
        void shop(Customer& customer);
};

Eshop::Eshop(string path_to_input) {
    if (!read_database(path_to_input)) {
        std::cout << "Databázu sa nepodarilo otvorit!" << endl;
    }
    std::cout << "Dnešná ponuka:" << std::endl;
    printAllProducts();
}

Eshop::~Eshop () {
    delete [] products;
}

bool Eshop::read_database(string path_to_database) {

    fstream file;
    file.open(path_to_database, ios::in);

    if (!file.is_open()) {
        return false;
    }
    
    file >> num_prod;
    products = new Product[num_prod];

    unsigned int id;
    string name;
    string manufacturer;
    unsigned int in_store;
    float price;
    for (int prod=0; prod<num_prod; prod+=1){
        file >> id >> name >> manufacturer >> in_store >> price;
        products[prod].setAll(id, name, manufacturer, in_store, price);
    }
    file.close();
    return true;
}

void Eshop::printAllProducts() {
    for (int i=0; i<num_prod; i++) {
        products[i].printAll();
    }
}

Product* Eshop::find_by_name(string search = ""){
    if (search.empty()) { return nullptr; }

    Product * p = nullptr;
    for (unsigned int row=0; row<num_prod; row++){
        if (products[row].getName().find(search) != string::npos)
        {
            return &(products[row]);
        }
    }
    return nullptr;
}

Product* Eshop::find_by_manufacturer(string search){
    if (search.empty()) { return nullptr; }

    Product * p = nullptr;
    for (unsigned int row=0; row<num_prod; row++){
        if (products[row].getManufacturer().find(search) != string::npos)
        {
            return &(products[row]);
        }
    }
    return nullptr;
}

Product* Eshop::find_by_id(unsigned int ID) {
    if (ID == 0) { return nullptr; }
    for (unsigned int row=0; row<num_prod; row++) {
        if (products[row].getId() == ID) { 
            return &(products[row]);
        }
    }
    return nullptr;
}

void Eshop::printSaleInfo(unsigned int ID) {
    Product* p;
    if (nullptr == (p = find_by_id(ID))) {
        std::cout << "Hladaniu nezodpovedajú žiadne produkty." << endl;
        return;
    }
    std::cout << 
        p->getName() <<
        "\tID: " << p->getId() <<
        "\tNa sklade: " << p->getInStore() << 
        "\t\tCena: " << p->getPrice() << endl;
    return;
}

void Eshop::setInStore(unsigned int ID, unsigned int new_in_store) {
    find_by_id(ID)->setInStore(new_in_store);
}

bool Eshop::end() {
    char volba;
    std::cout << "Prajete si pokračovať v nákupe? [y for yes]";
    std::cin >> volba;
    if (volba == 'y'){
        return false;
    }
    std::cout << "Potvrďte ukončenie nákupu: [q]";
    std::cin >> volba;
    if (volba == 'q'){
        return true;
    }
    return end();
}

Product* Eshop::pick_product(){ 
    char volba;
    string search;
    Product* product;

    std::cout << 
        "Výber produktu: - podľa názvu [1] - podľa výrobcu [2]" << endl << 
        "Zvolte hodnotu: ";
    std::cin >> volba;
    if (volba == '1') {
        std::cout << "Zadajte názov hladaného produktu: ";
        std::cin >> search;
        if ((product = find_by_name(search)) == nullptr){
            std::cout << "Nenašli sa žiadne výsledky. Prajete si hladať znova? [y for yes]";
            std::cin >> volba;
            if (volba == 'y') {
                return pick_product();
            }
        } 
        else {
            return product;
        }
    } 
    else if (volba == '2') {
        std::cout << "Zadajte výrobcu hladaného produktu: ";
        std::cin >> search;
        if ((product = find_by_manufacturer(search)) == nullptr){
            std::cout << "Nenašli sa žiadne výsledky. Prajete si hladať znova? [y for yes]";
            std::cin >> volba;
            if (volba == 'y') {
                return pick_product();
            } 
        } 
        else {
            return product;
        }
    }
    else {
        std::cout << "Nesprávna volba. Prajete si pokračovať vo výbere produktu? [y for yes]";
        std::cin >> volba;
        if (volba == 'y') {
            return pick_product();
        }
    }

    return nullptr;
}

void Eshop::shop(Customer& customer){
    Product* product;
    char volba;
    while (true){
        product = pick_product();
        if (product != nullptr) { 
            printSaleInfo(product->getId());
            std::cout << "Prajete si zakúpiť daný produkt? [y for yes]";
            std::cin >> volba;
            if (volba == 'y') {
                if (customer.canAfford(product)) {
                    customer.add_product(product);
                    setInStore(product->getId(), product->getInStore() - 1);
                }
                else {
                    std::cout << "Nedostatok prostriedkov" << endl;
                }
            }
        }
        if (end()) {
            return;
        }
    }
}



int main(){ 
    Eshop eshop = Eshop("./produkty.txt");
    Customer customer = Customer();
    eshop.shop(customer);    
    customer.finish("./blok.txt");
}

