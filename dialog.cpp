#include "dialog.hpp"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this); // Initialises GUI
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_RollButton_clicked()
{
    // Check if the Roll Window is open, if not then the window is opened
    if (!rwIsOpen)
    {
        if (ui->HideDialogCheck->isChecked()) // If the "HideDialogCheck" checkbox is checked then the dialog will coose after the button is pressed
            this->hide();

        qDebug() << "Roll button pressed";
        rw = new RollWindow; // Initialises a new window
        rw->show(); // Shows the window
        rwIsOpen = true; // Prevents the window from being opened multiple times
    }
}

void Dialog::on_EditDetailsButton_clicked()
{
    // Check if the Details Window is open
    if (!dwIsOpen)
    {
        if (ui->HideDialogCheck->isChecked())
            this->hide();

        qDebug() << "Edit details button pressed";
        dw = new DetailsWindow; // Initialises window
        dw->show(); // Shows window
        dwIsOpen = true; // Stops the window from being opened twice
    }
}
