#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Travelling Salesman Project");
#centralWidget = new
}

MainWindow::~MainWindow()
{
    delete ui;
}
