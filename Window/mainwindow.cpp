#include "mainwindow.h"

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

bool MainWindow::promptCustomerInfo()
{
    QDialog dialog(this);
    Ui::CustomerUiDialog customerUi;
    customerUi.setupUi(&dialog);

    if (dialog.exec() == QDialog::Accepted) {
        QString FirstName = customerUi.textEdit->toPlainText().trimmed();
        QString SecondName = customerUi.textEdit_2->toPlainText().trimmed();
        QString VehicleReg = customerUi.textEdit_3->toPlainText().trimmed();
        QString IdNumber = customerUi.textEdit_4->toPlainText().trimmed();

        if (VehicleReg.isEmpty()) {
            QMessageBox::warning(this, "Missing Information", "Please enter at least the Vehicle Registration number.");
            return false;
        }

        currentCustomerId = structures.AddCustomer(FirstName.toStdString(), SecondName.toStdString(), IdNumber.toStdString());
        currentVehicleReg = VehicleReg;
        currentCustomerName = (FirstName.isEmpty() && SecondName.isEmpty()) ? "Customer" : (FirstName + " " + SecondName);

        qDebug() << "Customer registered:" << currentCustomerName << "Vehicle:" << currentVehicleReg;
        return true;
    }
    return false;
}

void MainWindow::on_reserveButton_clicked()
{
    QDialog dialog(this);
    Ui::ReserveParkingDialog ParkingUi;
    ParkingUi.setupUi(&dialog);

    int selectedSpot = -1;
    QPushButton *lastSelectedBtn = nullptr;

    Floor currentFloor = structures.GetFloors(0);

    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 2; ++col)
        {
            int spotId = row * 2 + col;

            QPushButton *spotBtn = new QPushButton(&dialog);
            spotBtn->setMinimumSize(85, 38);

            bool isOccupied = currentFloor.parkinglots[spotId].occupied;
            QString regNumber = QString::fromStdString(currentFloor.parkinglots[spotId].OVehicleReg);

            if (isOccupied)
            {
                spotBtn->setText(QString("Spot %1\n%2").arg(spotId + 1).arg(regNumber));
                spotBtn->setStyleSheet(
                    "background-color: #c62828; color: white; font-weight: bold; "
                    "border-radius: 5px; font-size: 10px;"
                );

                QObject::connect(spotBtn, &QPushButton::clicked, [this, spotId, regNumber]() {
                    this->onOccupiedSpotClicked(spotId, regNumber);
                });
            }
            else
            {
                spotBtn->setText(QString("Spot %1\n[ FREE ]").arg(spotId + 1));
                spotBtn->setStyleSheet(
                    "background-color: #2e7d32; color: white; font-weight: bold; "
                    "border-radius: 5px; font-size: 10px;"
                );

                QObject::connect(spotBtn, &QPushButton::clicked, [this, &selectedSpot, &lastSelectedBtn, spotBtn, spotId]() {
                    if (lastSelectedBtn && lastSelectedBtn != spotBtn) {
                        lastSelectedBtn->setStyleSheet(
                            "background-color: #2e7d32; color: white; font-weight: bold; "
                            "border-radius: 5px; font-size: 10px;"
                        );
                    }

                    selectedSpot = spotId;
                    lastSelectedBtn = spotBtn;
                    spotBtn->setStyleSheet(
                        "background-color: #1565c0; color: white; font-weight: bold; "
                        "border-radius: 5px; font-size: 10px; border: 2px solid yellow;"
                    );

                    this->onSpotSelected(spotId);
                });
            }

            ParkingUi.gridLayout->addWidget(spotBtn, row, col);
        }
    }

    if (dialog.exec() == QDialog::Accepted)
    {
        if (selectedSpot != -1) {
            if (currentVehicleReg.isEmpty()) {
                QMessageBox::information(
                    this,
                    "Customer Details Required",
                    QString("You selected Spot %1.\n\nPlease enter the customer and vehicle registration details to complete this reservation.").arg(selectedSpot + 1)
                );

                if (!promptCustomerInfo()) {
                    qDebug() << "Reservation aborted: User cancelled customer details dialog.";
                    return;
                }
            }

            this->onSpotReservationConfirmed(selectedSpot, currentVehicleReg);

            currentVehicleReg.clear();
            currentCustomerName.clear();
        } else {
            QMessageBox::warning(this, "No Spot Selected", "Please select an available parking spot before clicking OK.");
        }
    }
    else
    {
        qDebug() << "Reservation Dialog Cancelled";
    }
}

void MainWindow::on_exitButton_clicked()
{
    qDebug() << "Exit / Checkout clicked";
}

void MainWindow::onSpotSelected(int spotId)
{
    qDebug() << "[ACTION] User picked Spot:" << (spotId + 1);
}

void MainWindow::onOccupiedSpotClicked(int spotId, const QString &vehicleReg)
{
    qDebug() << "[ACTION] Clicked occupied Spot:" << (spotId + 1) << "Occupant:" << vehicleReg;
    QMessageBox::information(
        this,
        "Spot Already Occupied",
        QString("Spot %1 is currently occupied.\n\nVehicle Registration: %2").arg(spotId + 1).arg(vehicleReg)
    );
}

void MainWindow::onSpotReservationConfirmed(int spotId, const QString &vehicleReg)
{
    QString reg = vehicleReg.isEmpty() ? "UNREGISTERED" : vehicleReg;

    int result = structures.SelectSpace(reg.toStdString(), 0, spotId, currentCustomerId);

    if (result == 0) {
        qDebug() << "[SUCCESS] Spot" << (spotId + 1) << "assigned to vehicle:" << reg;
        QMessageBox::information(
            this,
            "Reservation Confirmed",
            QString("Spot %1 has been successfully reserved for vehicle:\n%2").arg(spotId + 1).arg(reg)
        );
    } else {
        qDebug() << "[ERROR] Could not reserve Spot" << (spotId + 1);
        QMessageBox::critical(
            this,
            "Error",
            QString("Could not reserve Spot %1. It may already be occupied.").arg(spotId + 1)
        );
    }
}
