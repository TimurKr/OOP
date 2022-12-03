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

void Customer::add_product(Product* product, unsigned int amount)
{
    for (int i = 0; i < amount; i++)
    {
        products.append(product);
        budget -= product->getPrice();
    }
}

void Customer::remove_product(Product* product)
{
    for (int i = 0; i < products.length(); i++)
    {
        if (products[i]->getId() == product->getId())
        {
            products.remove(i);
            return;
        }
    }
}

bool Customer::canAfford(Product *product, unsigned int amount)
{
    if (product->getPrice() * amount <= budget)
    {
        return true;
    }
    return false;
}

void Customer::finish(QString fileName)
{

    if (fileName.isEmpty()) return;


    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);

    out << name << "\n";

    float suma = 0;
    for (unsigned int prod = 0; prod < products.length(); prod++)
    {
        suma += products[prod]->getPrice();

        out << "Položka: " << products[prod]->getName() << "\nVýrobca: " << products[prod]->getManufacturer() << "\nCena: " << products[prod]->getPrice() << "\n\n";
    }

    out << "\n";
    out << "Cena spolu: " << suma << " €\n";
    out << "Zostatok: " << budget << " €\n";

    return;
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

        products[i].setAll(line.toInt(),
                            data.readLine(),
                            data.readLine(),
                            data.readLine().toInt(),
                            data.readLine().toDouble());
    }

    file.close();

    load_product_tree(products);
}

QVector<Product*> Eshop::find_by_name(QString search)
{

    QVector<Product*> result;

    if (search.isEmpty())
    {
        return result;
    }

    Product *p = nullptr;
    for (unsigned int i = 0; i < products.length(); i++)
    {
        if (products[i].getName().contains(search))
        {
            result.append(&(products[i]));
        }
    }
    return result;
}

QVector<Product*> Eshop::find_by_manufacturer(QString search){

    QVector<Product*> result;

    if (search.isEmpty())
    {
        return result;
    }

    Product *p = nullptr;
    for (unsigned int i = 0; i < products.length(); i++)
    {
        if (products[i].getManufacturer().contains(search))
        {
            result.append(&(products[i]));
        }
    }
    return result;
}

Product* Eshop::find_by_id(unsigned int ID)
{
    for (unsigned int i = 0; i < products.length(); i++)
    {
        if (products[i].getId() == ID)
        {
            return &(products[i]);
        }
    }
    return nullptr;
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


void Eshop::load_cart_tree(QVector<Product*> items)
{
    ui->cart_tree->setCurrentItem(nullptr);
    ui->cart_tree->clear();
    QTreeWidgetItem* parent = new QTreeWidgetItem(ui->cart_tree);
    parent->setText(0, "Products");

    for (size_t i = 0; i < items.size(); i++)
    {
        QTreeWidgetItem* child = new QTreeWidgetItem();
        child->setText(0, QString("%1").arg(items[i]->getId()));
        child->setText(1, QString("%1").arg(items[i]->getName()));
        child->setText(2, QString("%1").arg(items[i]->getManufacturer()));
        child->setText(3, QString("%1ks").arg(items[i]->getInStore()));
        child->setText(4, QStringLiteral("%1 €").arg(items[i]->getPrice()));

        parent->addChild(child);
    }

    ui->cart_tree->expandItem(parent);
}

void Eshop::load_product_tree(QVector<Product*> items)
{
    ui->product_tree->setCurrentItem(nullptr);
    ui->product_tree->clear();
    QTreeWidgetItem* parent = new QTreeWidgetItem(ui->product_tree);
    parent->setText(0, "Products");

    for (size_t i = 0; i < items.size(); i++)
    {
        QTreeWidgetItem* child = new QTreeWidgetItem();
        child->setText(0, QString("%1").arg(items[i]->getId()));
        child->setText(1, QString("%1").arg(items[i]->getName()));
        child->setText(2, QString("%1").arg(items[i]->getManufacturer()));
        child->setText(3, QString("%1ks").arg(items[i]->getInStore()));
        child->setText(4, QStringLiteral("%1 €").arg(items[i]->getPrice()));

        parent->addChild(child);
    }

    ui->product_tree->expandItem(parent);
}

void Eshop::load_product_tree(QVector<Product> items)
{
    ui->product_tree->setCurrentItem(nullptr);
    ui->product_tree->clear();
    QTreeWidgetItem* parent = new QTreeWidgetItem(ui->product_tree);
    parent->setText(0, "Products");

    for (size_t i = 0; i < items.size(); i++)
    {
        QTreeWidgetItem* child = new QTreeWidgetItem();
        child->setText(0, QString("%1").arg(items[i].getId()));
        child->setText(1, QString("%1").arg(items[i].getName()));
        child->setText(2, QString("%1").arg(items[i].getManufacturer()));
        child->setText(3, QString("%1 ks").arg(items[i].getInStore()));
        child->setText(4, QStringLiteral("%1 €").arg(items[i].getPrice()));

        parent->addChild(child);
    }

    ui->product_tree->expandItem(parent);
}

void Eshop::load_product_detail(Product* product)
{
    if (product != nullptr)
    {
        ui->product_name_show->setText(product->getName());
        ui->product_price_show->setValue(product->getPrice());
        ui->product_in_stock_show->setValue(product->getInStore());

        ui->amount_spin->setValue(1);
        ui->amount_spin->setEnabled(true);
        ui->add_to_cart->setEnabled(true);
    }
    else
    {
        ui->product_name_show->setText(QString(""));
        ui->product_price_show->setValue(0.0);
        ui->product_in_stock_show->setValue(0);

        ui->amount_spin->setValue(0);
        ui->amount_spin->setEnabled(false);
        ui->add_to_cart->setEnabled(false);
    }
}

void Eshop::on_shop_clicked()
{
    if (ui->name_input->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Zadajte meno"));
        msgBox.exec();
        return;
    }

    customer = new Customer(ui->name_input->text(), ui->budget_input->value());

    ui->name_input->setEnabled(false);
    ui->budget_input->setEnabled(false);
    ui->product_tree->setEnabled(true);
    ui->search->setEnabled(true);
    ui->search_by->setEnabled(true);
    ui->cart_tree->setEnabled(true);
    ui->checkout->setEnabled(true);
    ui->shop->setEnabled(false);

    load_product_tree(products);
}

void Eshop::on_search_clicked()
{
    if (ui->search_text->text().isEmpty())
    {
        load_product_tree(products);
    }
    else if (ui->search_by->currentText() == QString("Name"))
    {
        load_product_tree(find_by_name(ui->search_text->text()));
    }
    else if (ui->search_by->currentText() == QString("Manufacturer"))
    {
        load_product_tree(find_by_manufacturer(ui->search_text->text()));
    }
    else
    {
        throw 1;
    }
}

void Eshop::on_product_tree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    if (current == nullptr) return;
    load_product_detail(find_by_id(current->text(0).toInt()));
    ui->add_to_cart->setEnabled(true);
    ui->amount_spin->setEnabled(true);
}

void Eshop::on_add_to_cart_clicked()
{
    if (ui->product_tree->currentItem() == nullptr) return;
    Product* product = find_by_id(ui->product_tree->currentItem()->text(0).toInt());
    if (product == nullptr) return;

    unsigned int amount = ui->amount_spin->value();

    if (amount > product->getInStore())
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Nedostatok na sklade."));
        msgBox.exec();
        return;
    }
    if (!customer->canAfford(product, amount))
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Produkt je príliš drahý."));
        msgBox.exec();
        return;
    }
    customer->add_product(product, amount);
    product->setInStore(product->getInStore() - amount);
    ui->budget_input->setValue(ui->budget_input->value() - amount * product->getPrice());
    ui->price->setValue(ui->price->value() + amount * product->getPrice());

    load_cart_tree(customer->cart());
    load_product_tree(products);

    if (!customer->cart().isEmpty())
    {
        ui->checkout->setEnabled(true);
    }
    return;
}

void Eshop::on_cart_tree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    if (current != nullptr)
    {
        ui->remove_from_cart->setEnabled(true);
    }
}

void Eshop::on_remove_from_cart_clicked()
{
    QTreeWidgetItem* item = ui->cart_tree->currentItem();
    if(item == nullptr) return;


    Product* product = find_by_id(item->text(0).toInt());

    ui->budget_input->setValue(ui->budget_input->value() + product->getPrice());
    ui->price->setValue(ui->price->value() - product->getPrice());

    customer->remove_product(product);
    product->setInStore(product->getInStore() + 1);

    load_cart_tree(customer->cart());
    load_product_tree(products);
}

void Eshop::on_checkout_clicked()
{

    QMessageBox msgBox;
    msgBox.setText(QString("Zvolte si miesto uloženia bloku."));
    msgBox.exec();

    customer->finish(QFileDialog::getSaveFileName(this, "Save file", "", "Txt Files (*.txt)"));

    msgBox.setText(QString("Ďakujeme za nákup."));
    msgBox.exec();
    return;
}







