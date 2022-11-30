#include "ItemWidgets2.h"

ItemWidgets2::ItemWidgets2(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void ItemWidgets2::on_actionOpen_triggered(bool checked) {
	QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "Txt Files (*.txt)");

	if (fileName.isEmpty()) {
		return;
	}

	//qDebug() << fileName;

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QTextStream in(&file);

	QString line = in.readLine();
	int count = line.toInt();
	//qDebug() << count;

	//std::vector<product> products;
	QVector<product> products;
	products.resize(count);

	int i = 0;
	while (!in.atEnd()) {
		QString line = in.readLine();
		if (line.isEmpty()) {
			continue;
		}

		products[i].id = line.toInt();
		products[i].productName = in.readLine();
		products[i].company = in.readLine();
		products[i].quantity = in.readLine().toInt();
		products[i].price = in.readLine().toDouble();

		//qDebug() << products[i].id << products[i].productName << products[i].company
		//	<< products[i].quantity << products[i].price;

		i++;
	}

	file.close();

	fillList(products);
	fillTree(products);
	fillTable(products);
}

void ItemWidgets2::fillList(QVector<product>& products)
{
	ui.listWidget->blockSignals(true);

	for (size_t i = 0; i < products.size(); i++)
	{
		QString productLine = QString("Id: %1, Name: %2, Company: %3, Quantity: %4, Price %5")
			.arg(products[i].id).arg(products[i].productName)
			.arg(products[i].company).arg(products[i].quantity).arg(products[i].price);

		QListWidgetItem* item = new QListWidgetItem(productLine);
		ui.listWidget->addItem(item);
	}

	ui.listWidget->blockSignals(false);
	ui.listWidget->setCurrentRow(0);

	//QListWidgetItem* item5 = ui.listWidget->item(5);
	//qDebug() << item5->text();
}

void ItemWidgets2::fillTree(QVector<product>& products)
{
	QTreeWidgetItem* parent = new QTreeWidgetItem(ui.treeWidget);
	parent->setText(0, "Products");

	for (size_t i = 0; i < products.size(); i++)
	{
		QTreeWidgetItem* child = new QTreeWidgetItem();
		child->setText(0, QString("%1").arg(products[i].id));
		child->setText(1, QString("%1").arg(products[i].productName));
		child->setText(2, QString("%1").arg(products[i].company));
		child->setText(3, QString("%1ks").arg(products[i].quantity));
		child->setText(4, QStringLiteral("%1€").arg(products[i].price));

		parent->addChild(child);
	}

	ui.treeWidget->expandItem(parent);

	//QTreeWidgetItem* i = ui.treeWidget->topLevelItem(0)->child(5);
	//qDebug() << i->text(1);
}

void ItemWidgets2::fillTable(QVector<product>& products)
{
	for (size_t i = 0; i < products.size(); i++)
	{
		ui.tableWidget->insertRow(i);

		QTableWidgetItem* tableItemId = new QTableWidgetItem(QString("%1").arg(products[i].id));
		QTableWidgetItem* tableItemName = new QTableWidgetItem(products[i].productName);
		QTableWidgetItem* tableItemCompany = new QTableWidgetItem(products[i].company);
		QTableWidgetItem* tableItemQ = new QTableWidgetItem(QString("%1ks").arg(products[i].quantity));
		QTableWidgetItem* tableItemPrice = new QTableWidgetItem(QStringLiteral("%1€").arg(products[i].price));

		ui.tableWidget->setItem(i, 0, tableItemId);
		ui.tableWidget->setItem(i, 1, tableItemName);
		ui.tableWidget->setItem(i, 2, tableItemCompany);
		ui.tableWidget->setItem(i, 3, tableItemQ);
		ui.tableWidget->setItem(i, 4, tableItemPrice);
	}
}

void ItemWidgets2::on_actionSave_triggered(bool chacked)
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "Txt Files (*.txt)");

	if (fileName.isEmpty()) {
		return;
	}

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}

	QTextStream out(&file);

	out << ui.listWidget->currentItem()->text() << "\n";

	file.close();
}

void ItemWidgets2::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
	qDebug() << "on_listWidget_currentItemChanged";
	qDebug() << current->text(); //text v aktualnom riadku
	qDebug() << ui.listWidget->currentIndex().row();
	qDebug() << ui.listWidget->currentRow();
}

void ItemWidgets2::on_treeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
	int index = ui.treeWidget->indexOfTopLevelItem(current);

	if (index == -1) {
		qDebug() << "on_treeWidget_currentItemChanged";
		qDebug() << current->text(1); //text v aktualnom riadku
		qDebug() << ui.treeWidget->currentIndex().row();
		qDebug() << ui.treeWidget->currentIndex().column();
	}
}

void ItemWidgets2::on_tableWidget_currentItemChanged(QTableWidgetItem* current, QTableWidgetItem* previous)
{
	qDebug() << "on_tableWidget_currentItemChanged";
	qDebug() << current->text(); //text v aktualnej bunke tabulky
	qDebug() << ui.tableWidget->currentIndex().row();
	qDebug() << ui.tableWidget->currentIndex().column();
}