#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QList>
#include "../include/structures.hpp"
#include "./ui_mainwindow.h"
#include "./ui_CustomerInfo.h"
#include "./ui_ReserveParking.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_reserveButton_clicked();
    void on_exitButton_clicked();

    void onSpotSelected(int spotId);
    void onOccupiedSpotClicked(int spotId, const QString &vehicleReg);
    void onSpotReservationConfirmed(int spotId, const QString &vehicleReg);

private:
    Ui::MainWindow *ui;
    Structures structures;
    QString currentVehicleReg;
    QString currentCustomerName;
    unsigned long currentCustomerId = 0;

    bool promptCustomerInfo();
};
#endif
