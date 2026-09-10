#include "../include/main.hpp"
#include "../include/window_mgmt.hpp"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Parking Sys");
    window.resize(300, 300);
    auto *layout = new QVBoxLayout(&window);
    auto *label = new QLabel("Click count", &window);
    label->setAlignment(Qt::AlignCenter);
    auto *counterButton = new QPushButton("Increment", &window);
    auto *quitButton = new QPushButton("Quit", &window);
    layout->addWidget(label);
    layout->addWidget(counterButton);
    layout->addWidget(quitButton);
    int count = 0;
    QObject::connect(counterButton, &QPushButton::clicked, [&count, label]()
                     {
                        ++count;
                        std::string text = std::format("Click count: {}", count);
                        label->setText(QString::fromStdString(text));

                     });
    QObject::connect(quitButton, &QPushButton::clicked, &app, &QCoreApplication::quit);
    window.show();
    
    
    return app.exec();
}

