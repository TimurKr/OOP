#pragma once

#include <QtWidgets>
#include "ui_ItemWidgets2.h"

struct product {
	int id;
	QString productName;
	QString company;
	int quantity;
	double price;
};

class ItemWidgets2 : public QMainWindow
{
    Q_OBJECT

public:
    ItemWidgets2(QWidget *parent = Q_NULLPTR);
	void fillList(QVector<product>& products);
	void fillTree(QVector<product>& products);
	void fillTable(QVector<product>& products);

private:
    Ui::ItemWidgets2Class ui;
private slots:
	void on_actionOpen_triggered(bool chacked = false);
	void on_actionSave_triggered(bool chacked = false);
	void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
	void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
	void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
};
