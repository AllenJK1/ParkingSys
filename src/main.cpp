#include "../include/main.hpp"
#include "../include/window_mgmt.hpp"
#include "../include/structures.hpp"
Structures structures;
int PromptUserInfo();
int RequestUserInfo(unsigned long ID);
int main(int argc, char *argv[])
{
    unsigned long clients;
    clients = PromptUserInfo();
    std::cout << "\nYour Entry ID is: " << clients ;
    clients = PromptUserInfo();
    std::cout << "\nYour Entry ID is: " << clients ;
    std::cout << "\n";
    RequestUserInfo(0);
    RequestUserInfo(1);
    return 0;
}
int RequestUserInfo(unsigned long ID)
{
    Customer querry = structures.GetCustomer(ID);
    std::cout << "\nFirstname: " << querry.FirstName ;
    return 0;
}
int PromptUserInfo()
{
    std::string Fname, Lname, ID;
    std::cout << "\nEnter Firstname: ";
    std::cin >> Fname;
    std::cout << "\nEnter Second name: ";
    std::cin >> Lname;
    std::cout << "\nEnter Id: ";
    std::cin >> ID;
    
    return structures.AddCustomer(Fname, Lname, ID);
    
; 

}
/*

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
 
 *
 */
