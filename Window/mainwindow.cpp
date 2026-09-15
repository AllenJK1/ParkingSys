#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_CustomerInfo.h"
#include <QDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QDialog dialog(this);
    Ui::Dialog customerUi;
    customerUi.setupUi(&dialog);

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "OK clicked!";
        QString FirstName = customerUi.textEdit->toPlainText();
        QString SecondName = customerUi.textEdit_2->toPlainText();
        QString VehicleReg = customerUi.textEdit_3->toPlainText();
        QString IdNumber = customerUi.textEdit_4->toPlainText();
        qDebug() << "First Name: "  << FirstName;
        qDebug() << "Second Name: " << SecondName;
        qDebug() << "Vehicle Reg: " << VehicleReg;
        qDebug() << "ID Number: "   << IdNumber;

    }
    else {
        qDebug() << "User Clicked Cancel";
    }
}