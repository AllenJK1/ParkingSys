#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class Window_
{

private:
    QWidget MenuWindow;
   public:
    Window_(std::string WinTitle, uint64_t x = 300, uint y = 300)
    {
        auto *layout = new QVBoxLayout(&this->MenuWindow);
        auto *label = new QLabel("Register New Client");
        label->setAlignment(Qt::AlignCenter);
        auto *save = new QPushButton("Save", &MenuWindow);
        auto *quit = new QPushButton("Exit", &MenuWindow);
        layout->addWidget(label);
        layout->addWidget(save);
        layout->addWidget(quit);
        QObject::connect(quit, &QPushButton::clicked, &QCoreApplication::quit);
        MenuWindow.show();
    

    }
   
};
