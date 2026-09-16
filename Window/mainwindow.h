#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "../include/structures.hpp"

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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    // On-click action handlers for parking spots:
    void onSpotSelected(int spotId);
    void onOccupiedSpotClicked(int spotId, const QString &vehicleReg);
    void onSpotReservationConfirmed(int spotId, const QString &vehicleReg);

private:
    Ui::MainWindow *ui;

    // Backend structures instance:
    Structures structures;

    // Active customer / vehicle info to be assigned to spots:
    QString currentVehicleReg;
    QString currentCustomerName;
    unsigned long currentCustomerId = 0;

    // Helper to prompt customer input window
    bool promptCustomerInfo();
};
#endif // MAINWINDOW_H
