#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//THis header defines the mainwindow class and all its slots and helper finctions
// includes all QT libary headers so that cpp does not need to include tehm

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
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include "structures.hpp"
#include "ui_mainwindow.h"
#include "ui_CustomerInfo.h"
#include "ui_ReserveParking.h"

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
    // main action buttons
    void on_reserveButton_clicked();
    void on_exitButton_clicked();
    void on_manageParkingButton_clicked(); // for editing parkng lots and addign floors
    void on_ratesButton_clicked(); // for changing rates and addign tiers

    // menubar actions
    void on_actionManageFloorsLots_triggered();
    void on_actionRates_triggered();
    void on_actionExit_triggered();

    // spot selection callbacks with floor parameter
    void onSpotSelected(unsigned long floorId, int spotId);
    void onOccupiedSpotClicked(unsigned long floorId, int spotId, const QString &vehicleReg);
    void onSpotReservationConfirmed(unsigned long floorId, int spotId, const QString &vehicleReg);

    // updates status on starting menu
    void updateDashboardStatus();

private:
    Ui::MainWindow *ui;
    Structures structures;
    QString currentVehicleReg;
    QString currentCustomerName;
    QString currentCustomerPhone; // store phone number from promt
    unsigned long currentCustomerId = 0;

    bool promptCustomerInfo();
};
#endif
