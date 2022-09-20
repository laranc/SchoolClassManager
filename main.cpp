#include "dialog.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Initialises the application
    Dialog w; // Defines a dialog box
    w.show(); // Opens the dialog box
    return a.exec(); // Executes the application
}
