#include "editdetailswindow.hpp"
#include "ui_editdetailswindow.h"

// Functionality in this window is currently broken
EditDetailsWindow::EditDetailsWindow(QString detailName, /*QLabel &detailEdit,*/ QWidget *parent) : QDialog(parent), ui(new Ui::EditDetailsWindow)
{
    ui->setupUi(this);

    //detailValue = &detailEdit; // Errors encountered when using references, will be touched upon further in the extension task

    ui->DetailName->setText(detailName);
    ui->DetailEdit->setText(detailValue.text());
}

EditDetailsWindow::~EditDetailsWindow()
{
    delete ui;
}

void EditDetailsWindow::on_ButtonBox_accepted()
{
    edwIsOpen = false;
}


void EditDetailsWindow::on_ButtonBox_rejected()
{
    edwIsOpen = false;
}

