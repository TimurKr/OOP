#include "eshop.h"
#include "./ui_eshop.h"

void Product::setAll(unsigned int id, QString name, QString manufacturer, unsigned int in_store, float price)
{
    this->id = id;
    this->name = name;
    this->manufacturer = manufacturer;
    this->in_store = in_store;
    this->price = price;
}

bool Customer::add_product(Product *product)
{
    if (num_prod == max_products_per_user)
    {
        return false;
    }
    if (product == nullptr)
    {
        return false;
    }

    products[num_prod++] = product;
    budget -= product->getPrice();
    return true;
}

bool Customer::canAfford(Product *product)
{
    if (product->getPrice() <= budget)
    {
        return true;
    }
    return false;
}

bool Customer::finish()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "Txt Files (*.txt)");

    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);

    f << name << " " << surname << endl;

    float suma = 0;
    for (unsigned int prod = 0; prod < num_prod; prod++)
    {
        suma += products[prod]->getPrice();

        f << "Položka: " << products[prod]->getName() << "\tVýrobca: " << products[prod]->getManufacturer() << "\t\tCena: " << products[prod]->getPrice() << endl;
    }

    f << endl;
    f << "Cena spolu: " << suma << endl;
    f << "Zostatok: " << budget << endl;

    std::cout << "Blok si nájdete v dokumente " << path_to_bill << endl;
    return true;
}



Eshop::Eshop(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Eshop)
{
    ui->setupUi(this);
}

Eshop::~Eshop()
{
    delete ui;
}



void Eshop::on_actionOpen_triggered(bool checked)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "Txt Files (*.txt)");

    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream data(&file);

    products.resize(data.readLine().toInt());

    int i = 0;
    for (int i = 0; i < products.size(); i++)
    {
        QString line = data.readLine();
        if (line.isEmpty())
        {
            continue;
        }

        products[i]->setAll(line.toInt(),
                            data.readLine(),
                            data.readLine(),
                            data.readLine().toInt(),
                            data.readLine().toDouble());
    }

    file.close();
}



Product *Eshop::find_by_name(string search = "")
{
    if (search.empty())
    {
        return nullptr;
    }

    Product *p = nullptr;
    for (unsigned int row = 0; row < num_prod; row++)
    {
        if (products[row].getName().find(search) != string::npos)
        {
            return &(products[row]);
        }
    }
    return nullptr;
}

Product *Eshop::find_by_manufacturer(string search)
{
    if (search.empty())
    {
        return nullptr;
    }

    Product *p = nullptr;
    for (unsigned int row = 0; row < num_prod; row++)
    {
        if (products[row].getManufacturer().find(search) != string::npos)
        {
            return &(products[row]);
        }
    }
    return nullptr;
}

Product *Eshop::find_by_id(unsigned int ID)
{
    if (ID == 0)
    {
        return nullptr;
    }
    for (unsigned int row = 0; row < num_prod; row++)
    {
        if (products[row].getId() == ID)
        {
            return &(products[row]);
        }
    }
    return nullptr;
}

void Eshop::printSaleInfo(unsigned int ID)
{
    Product *p;
    if (nullptr == (p = find_by_id(ID)))
    {
        std::cout << "Hladaniu nezodpovedajú žiadne produkty." << endl;
        return;
    }
    std::cout << p->getName() << "\tID: " << p->getId() << "\tNa sklade: " << p->getInStore() << "\t\tCena: " << p->getPrice() << endl;
    return;
}

void Eshop::setInStore(unsigned int ID, unsigned int new_in_store)
{
    find_by_id(ID)->setInStore(new_in_store);
}

bool Eshop::end()
{
    char volba;
    std::cout << "Prajete si pokračovať v nákupe? [y for yes]";
    std::cin >> volba;
    if (volba == 'y')
    {
        return false;
    }
    std::cout << "Potvrďte ukončenie nákupu: [q]";
    std::cin >> volba;
    if (volba == 'q')
    {
        return true;
    }
    return end();
}

Product *Eshop::pick_product()
{
    char volba;
    string search;
    Product *product;

    std::cout << "Výber produktu: - podľa názvu [1] - podľa výrobcu [2]" << endl
              << "Zvolte hodnotu: ";
    std::cin >> volba;
    if (volba == '1')
    {
        std::cout << "Zadajte názov hladaného produktu: ";
        std::cin >> search;
        if ((product = find_by_name(search)) == nullptr)
        {
            std::cout << "Nenašli sa žiadne výsledky. Prajete si hladať znova? [y for yes]";
            std::cin >> volba;
            if (volba == 'y')
            {
                return pick_product();
            }
        }
        else
        {
            return product;
        }
    }
    else if (volba == '2')
    {
        std::cout << "Zadajte výrobcu hladaného produktu: ";
        std::cin >> search;
        if ((product = find_by_manufacturer(search)) == nullptr)
        {
            std::cout << "Nenašli sa žiadne výsledky. Prajete si hladať znova? [y for yes]";
            std::cin >> volba;
            if (volba == 'y')
            {
                return pick_product();
            }
        }
        else
        {
            return product;
        }
    }
    else
    {
        std::cout << "Nesprávna volba. Prajete si pokračovať vo výbere produktu? [y for yes]";
        std::cin >> volba;
        if (volba == 'y')
        {
            return pick_product();
        }
    }

    return nullptr;
}

void Eshop::shop(Customer &customer)
{
    Product *product;
    char volba;
    while (true)
    {
        product = pick_product();
        if (product != nullptr)
        {
            printSaleInfo(product->getId());
            std::cout << "Prajete si zakúpiť daný produkt? [y for yes]";
            std::cin >> volba;
            if (volba == 'y')
            {
                if (customer.canAfford(product))
                {
                    customer.add_product(product);
                    setInStore(product->getId(), product->getInStore() - 1);
                }
                else
                {
                    std::cout << "Nedostatok prostriedkov" << endl;
                }
            }
        }
        if (end())
        {
            return;
        }
    }
}
