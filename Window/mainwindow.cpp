#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionManageFloorsLots, &QAction::triggered, this, &MainWindow::on_actionManageFloorsLots_triggered);
    connect(ui->actionRates, &QAction::triggered, this, &MainWindow::on_actionRates_triggered);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    updateDashboardStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDashboardStatus()
{
    unsigned long totalSpots = 0;
    unsigned long occupiedSpots = 0;
    unsigned long floorCount = structures.GetFloorCount();

    for (unsigned long f = 0; f < floorCount; ++f)
    {
        Floor fl = structures.GetFloors(f);
        totalSpots += fl.parkinglots.size();
        for (const auto &lot : fl.parkinglots)
        {
            if (lot.occupied) occupiedSpots++;
        }
    }
    unsigned long freeSpots = (totalSpots >= occupiedSpots) ? (totalSpots - occupiedSpots) : 0;
    ui->statusLabel->setText(QString("Floors: %1  |  Total Spots: %2  |  Available: %3  |  Occupied: %4")
        .arg(floorCount)
        .arg(totalSpots)
        .arg(freeSpots)
        .arg(occupiedSpots));
}

bool MainWindow::promptCustomerInfo()
{
    QDialog dialog(this);
    Ui::CustomerUiDialog customerUi;
    customerUi.setupUi(&dialog);

    if (dialog.exec() == QDialog::Accepted) {
        QString FirstName = customerUi.textEdit->toPlainText().trimmed();
        QString SecondName = customerUi.textEdit_3->toPlainText().trimmed();
        QString VehicleReg = customerUi.textEdit_2->toPlainText().trimmed();
        QString IdNumber = customerUi.textEdit_4->toPlainText().trimmed();
        QString PhoneNumber = customerUi.textEdit_5->toPlainText().trimmed();

        if (VehicleReg.isEmpty()) {
            QMessageBox::warning(this, "Missing Information", "Please enter at least the Vehicle Registration number.");
            return false;
        }

        currentCustomerId = structures.AddCustomer(FirstName.toStdString(), SecondName.toStdString(), IdNumber.toStdString(), PhoneNumber.toStdString());
        currentVehicleReg = VehicleReg;
        currentCustomerName = (FirstName.isEmpty() && SecondName.isEmpty()) ? "Customer" : (FirstName + " " + SecondName);
        currentCustomerPhone = PhoneNumber;

        qDebug() << "Customer registered:" << currentCustomerName << "Vehicle:" << currentVehicleReg << "Phone:" << currentCustomerPhone;
        return true;
    }
    return false;
}

void MainWindow::on_reserveButton_clicked()
{
    qDebug() << "Reserve spot clicked";
}

void MainWindow::on_exitButton_clicked()
{
    qDebug() << "Exit clicked";
}

void MainWindow::on_manageParkingButton_clicked()
{
    qDebug() << "Manage parking clicked";
}

void MainWindow::on_ratesButton_clicked()
{
    qDebug() << "Rates clicked";
}

void MainWindow::on_actionManageFloorsLots_triggered()
{
    on_manageParkingButton_clicked();
}

void MainWindow::on_actionRates_triggered()
{
    on_ratesButton_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::onSpotSelected(unsigned long floorId, int spotId)
{
    qDebug() << "User picked Floor:" << (floorId + 1) << "Spot:" << (spotId + 1);
}

void MainWindow::onOccupiedSpotClicked(unsigned long floorId, int spotId, const QString &vehicleReg)
{
    qDebug() << "Clicked occupied Floor:" << (floorId + 1) << "Spot:" << (spotId + 1) << "Occupant:" << vehicleReg;
}

void MainWindow::onSpotReservationConfirmed(unsigned long floorId, int spotId, const QString &vehicleReg)
{
    qDebug() << "Confirmed Floor:" << (floorId + 1) << "Spot:" << (spotId + 1) << "Vehicle:" << vehicleReg;
}
