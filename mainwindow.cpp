
#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new QDeclarativeView();
    ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(ui);
    ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    sova = new CSovaMain(ui, 1920,1080);
}

MainWindow::~MainWindow()
{
    delete ui;
}

