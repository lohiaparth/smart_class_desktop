#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "whiteboard.h"
#include <QVBoxLayout>  // Ensure this is included

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a whiteboard instance and add it to the main window layout
    Whiteboard *whiteboard = new Whiteboard(this);

    // Set layout to drawingArea, ensure drawingArea exists in the .ui file
    QVBoxLayout *layout = new QVBoxLayout();  // Create a new QVBoxLayout
    layout->addWidget(whiteboard);            // Add whiteboard to layout
    ui->centralwidget->setLayout(layout);       // Set layout to drawingArea
}

MainWindow::~MainWindow()
{
    delete ui;
}
