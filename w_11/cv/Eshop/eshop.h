#include <QMainWindow>
#include <QFileDialog>

#include <iostream>
#include <iomanip>

#ifndef ESHOP_H
#define ESHOP_H

#define max_products_per_user 10


#define FOUND 0
#define NOT_FOUND 1
#define FOUND_ERROR 2

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Eshop; }
QT_END_NAMESPACE


class Product
{
    private:
        unsigned int id;
        QString name;
        QString manufacturer;
        unsigned int in_store;
        float price;
    public:
        // Constructors
        Product ()
            : id(0) {}
        Product (unsigned int id, QString name, QString manufacturer, unsigned int in_store, float price)
            : id(id), name(name), manufacturer(manufacturer), in_store(in_store), price(price) {};

        // Interface
        void setAll(unsigned int id, QString name, QString manufacturer, unsigned int in_store, float price);
        void setId(unsigned int id) { this->id = id; };
        void setName(QString name) { this->name = name; };
        void setManufacturer(QString manufacturer) { this->manufacturer = manufacturer; };
        void setInStore(unsigned int in_store) { this->in_store = in_store; };
        void setPrice(float price) { this->price = price; };

        void printAll();

        unsigned int getId() { return id; };
        QString getName() { return name; };
        QString getManufacturer() { return manufacturer; };
        unsigned int getInStore() { return in_store; };
        float getPrice() { return price; };
};



class Customer
{
    private:
        QString name, surname;
        float budget;
        unsigned int num_prod;
        Product* products[max_products_per_user];
    public:
        // Constructors
        Customer(QString name, QString surname, float budget)
        : name(name), surname(surname), budget(budget) {}

        bool add_product(Product* product);

        bool canAfford(Product* product);

        bool finish();

};



class Eshop : public QMainWindow
{
    Q_OBJECT
private:
    Ui::Eshop *ui;
    QVector<Product *>products;
    unsigned int num_prod = 0;

private slots:
    void on_actionOpen_triggered(bool checked);

public:
    Eshop(QWidget *parent = nullptr);
    ~Eshop();

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



#endif // ESHOP_H
