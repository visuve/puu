#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "TreeModel.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->treeView->setModel(new TreeModel(this));
}

MainWindow::~MainWindow()
{
	delete ui;
}

