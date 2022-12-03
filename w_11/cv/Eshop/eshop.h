#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>

#include <iostream>
#include <iomanip>

#ifndef ESHOP_H
#define ESHOP_H

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
        QString name;
        float budget;
        QVector<Product*> products;

    public:
        // Constructors
        Customer(QString name, float budget)
        : name(name), budget(budget) {}

        QVector<Product*> cart() { return products; }
        void remove_product(Product* product);
        void add_product(Product* product, unsigned int amount);

        bool canAfford(Product* product, unsigned int amount);

        void finish(QString fileName);

};



class Eshop : public QMainWindow
{
    Q_OBJECT
private:
    Ui::Eshop *ui;
    QVector<Product>products;
    unsigned int num_prod = 0;
    Customer* customer;

private slots:
    void on_actionOpen_triggered(bool checked);

    void on_shop_clicked();

    void on_search_clicked();

    void on_product_tree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);

    void on_add_to_cart_clicked();

    void on_cart_tree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void on_remove_from_cart_clicked();
    void on_checkout_clicked();


public:
    Eshop(QWidget *parent = nullptr);
    ~Eshop();

    // Interface
    void printSaleInfo(unsigned int ID);
    void setInStore(unsigned int ID, unsigned int new_in_store);
    void printAllProducts();

    // Search
    Product* find_by_id(unsigned int id);
    QVector<Product*> find_by_name(QString name);
    QVector<Product*> find_by_manufacturer(QString manufacturer);

    // Shopping
    bool end();
    Product* pick_product();

    // Visuals
    void load_cart_tree(QVector<Product*> items);
    void load_product_tree(QVector<Product> items);
    void load_product_tree(QVector<Product*> items);
    void load_product_detail(Product* product);

};



#endif // ESHOP_H
