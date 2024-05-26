#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Set the main window properties
    setWindowTitle("My Qt App");
    resize(600, 400);

    // Create the central widget and layout
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);

    // Create a button and connect its signal to the slot
    button = new QPushButton("Click Me", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // Add the button to the layout
    layout->addWidget(button);

    // Set the central widget
    setCentralWidget(centralWidget);
}

void MainWindow::onButtonClicked() {
    QMessageBox::information(this, "Information", "Button Clicked");
}
