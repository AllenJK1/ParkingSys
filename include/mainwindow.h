#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "structures.hpp"

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
