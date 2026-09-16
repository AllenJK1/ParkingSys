#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_CustomerInfo.h"
#include "./ui_ReserveParking.h"
#include <QDialog>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // All parking spots are free by default!
}

MainWindow::~MainWindow()
{
    delete ui;
}

// -------------------------------------------------------------
// HELPER: PROMPT CUSTOMER / VEHICLE INPUT DIALOG
// -------------------------------------------------------------
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

        // Save into backend Customer struct:
        currentCustomerId = structures.AddCustomer(FirstName.toStdString(), SecondName.toStdString(), IdNumber.toStdString());
        currentVehicleReg = VehicleReg;
        currentCustomerName = (FirstName.isEmpty() && SecondName.isEmpty()) ? "Customer" : (FirstName + " " + SecondName);

        qDebug() << "Customer registered:" << currentCustomerName << "Vehicle:" << currentVehicleReg;
        return true;
    }
    return false;
}

// -------------------------------------------------------------
// 1. CUSTOMER REGISTRATION (Button 1)
// -------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    if (promptCustomerInfo()) {
        QMessageBox::information(
            this,
            "Customer Registered",
            QString("Customer %1 (%2) has been registered successfully!\nEntry ID: %3\n\nYou can now proceed to reserve a parking spot.")
                .arg(currentCustomerName)
                .arg(currentVehicleReg)
                .arg(currentCustomerId)
        );
    } else {
        qDebug() << "User Cancelled Customer Registration";
    }
}

// -------------------------------------------------------------
// 2. PARKING LOT SELECTION (Button 2)
// -------------------------------------------------------------
void MainWindow::on_pushButton_2_clicked()
{
    QDialog dialog(this);
    Ui::ReserveParkingDialog ParkingUi;
    ParkingUi.setupUi(&dialog);

    int selectedSpot = -1;
    QPushButton *lastSelectedBtn = nullptr;

    // Query actual ground floor (Floor 0) status from backend Structures:
    Floor currentFloor = structures.GetFloors(0);

    // Populate 6 rows x 2 columns (12 parking spots)
    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 2; ++col)
        {
            int spotId = row * 2 + col; // 0 to 11

            QPushButton *spotBtn = new QPushButton(&dialog);
            spotBtn->setMinimumSize(85, 38);

            // Read live status from the struct:
            bool isOccupied = currentFloor.parkinglots[spotId].occupied;
            QString regNumber = QString::fromStdString(currentFloor.parkinglots[spotId].OVehicleReg);

            if (isOccupied)
            {
                spotBtn->setText(QString("Spot %1\n%2").arg(spotId + 1).arg(regNumber));
                spotBtn->setStyleSheet(
                    "background-color: #c62828; color: white; font-weight: bold; "
                    "border-radius: 5px; font-size: 10px;"
                );

                // On-click action for OCCUPIED spot: display occupant details
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

                // On-click action for AVAILABLE spot: select and highlight
                QObject::connect(spotBtn, &QPushButton::clicked, [this, &selectedSpot, &lastSelectedBtn, spotBtn, spotId]() {
                    // Reset previously selected button style back to green
                    if (lastSelectedBtn && lastSelectedBtn != spotBtn) {
                        lastSelectedBtn->setStyleSheet(
                            "background-color: #2e7d32; color: white; font-weight: bold; "
                            "border-radius: 5px; font-size: 10px;"
                        );
                    }

                    // Highlight selected button in blue with yellow border
                    selectedSpot = spotId;
                    lastSelectedBtn = spotBtn;
                    spotBtn->setStyleSheet(
                        "background-color: #1565c0; color: white; font-weight: bold; "
                        "border-radius: 5px; font-size: 10px; border: 2px solid yellow;"
                    );

                    // Trigger on-click slot
                    this->onSpotSelected(spotId);
                });
            }

            ParkingUi.gridLayout->addWidget(spotBtn, row, col);
        }
    }

    if (dialog.exec() == QDialog::Accepted)
    {
        if (selectedSpot != -1) {
            // If user hasn't registered vehicle details yet, prompt them now:
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

            // Confirm reservation and commit to structures:
            this->onSpotReservationConfirmed(selectedSpot, currentVehicleReg);

            // Clear active vehicle so next reservation prompts for the next car:
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

// -------------------------------------------------------------
// 3. ACTION HANDLERS
// -------------------------------------------------------------

// Triggered immediately when user clicks on an available spot:
void MainWindow::onSpotSelected(int spotId)
{
    qDebug() << "[ACTION] User picked Spot:" << (spotId + 1);
}

// Triggered when user clicks on an occupied spot:
void MainWindow::onOccupiedSpotClicked(int spotId, const QString &vehicleReg)
{
    qDebug() << "[ACTION] Clicked occupied Spot:" << (spotId + 1) << "Occupant:" << vehicleReg;
    QMessageBox::information(
        this,
        "Spot Already Occupied",
        QString("Spot %1 is currently occupied.\n\nVehicle Registration: %2").arg(spotId + 1).arg(vehicleReg)
    );
}

// Triggered when user clicks OK to commit the reservation into the structs:
void MainWindow::onSpotReservationConfirmed(int spotId, const QString &vehicleReg)
{
    QString reg = vehicleReg.isEmpty() ? "UNREGISTERED" : vehicleReg;

    // Commit to the backend Structures (Floor 0):
    int result = structures.SelectSpace(reg.toStdString(), 0, spotId);

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

