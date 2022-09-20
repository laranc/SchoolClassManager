#include "detailswindow.hpp"
#include "ui_detailswindow.h"
#include <QDebug>
#include <QFile>

DetailsWindow::DetailsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::DetailsWindow)
{
    ui->setupUi(this); // Initialises GUI
    qDebug() << "Details window opened";

    QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
    QFile studentsFile(studentFilePath);
    // Opens file in read only mode
    if (!studentsFile.exists())
        qDebug() << "Error file not found at path: " << studentFilePath;
    else if (!studentsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error reading file";
    else if (studentsFile.size() == 0)
        qDebug() << "Error file size is null. Error message: " << studentsFile.error();
    else
    {
        qDebug() << "File found and opened for reading. File size: " << studentsFile.size();
        while(!studentsFile.atEnd())
        {
            QString line = studentsFile.readLine();
            if (line.isUpper()) // Checks if the line is the name of a subject class
            {
                line = line.toLower(); // Sets the name to lowercase
                line[0] = line[0].toUpper(); // Capitalises the first letter
                ui->ClassSelector->addItem(line); // Adds it to the Class Selector combobox
            }
        }
        ui->ClassSelector->setCurrentText("Choose class"); // Sets the default text to "Choose class"
        qDebug() << "Classes added to combo box";
        studentsFile.close(); // Closes file for memory management
    }
}

DetailsWindow::~DetailsWindow()
{
    delete ui;
}

void DetailsWindow::on_ClassSelector_currentIndexChanged(int index)
{
    qDebug() << "Class slector current index changed";
    // Checks if a class has been selected and it is not the default option
    if (ui->ClassSelector->currentText() != "Choose a class")
    {
        ui->StudentList->clear();

        QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
        QFile studentsFile(studentFilePath);
        // Opens file in read only mode
        if (!studentsFile.exists())
            qDebug() << "Error file not found at path: " << studentFilePath;
        else if (!studentsFile.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Error reading file";
        else if (studentsFile.size() == 0)
            qDebug() << "Error file size is null. Error message: " << studentsFile.error();
        else
        {
            qDebug() << "File found and opened for reading. File size: " << studentsFile.size();
            QStringList studentList;
            // Loads the student names from the file to the list widget
            while(!studentsFile.atEnd())
            {
                QString line = studentsFile.readLine();
                if (line == ui->ClassSelector->currentText().toUpper()) // Checks if the line is the name of the subject chosen in the Class Selector combobox
                    while(!studentsFile.atEnd()) // Loop until another subject name is reached
                    {
                        QString subLine = studentsFile.readLine();
                        if (subLine.isUpper()) // Break if it is a subject name
                            break;
                        studentList.append(subLine); // Add student names to the list
                    }
            }
            ui->StudentList->addItems(studentList); // Add list to the widget
            qDebug() << "Students added to list";
            studentsFile.close(); // Close file
        }
    }
    else
        ui->StudentList->clear(); // Clear the widget
}

void DetailsWindow::on_StudentList_itemClicked(QListWidgetItem *item)
{
    // If a student is selected from the list widget then display the details
    qDebug() << "Student list item clicked";
    QString studentDetailsFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/student_details";
    QFile studentDetailsFile(studentDetailsFilePath);
    // Open file in read only mode
    if (!studentDetailsFile.exists())
        qDebug() << "Error file not found at path: " << studentDetailsFilePath;
    else if (!studentDetailsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error reading file";
    else if (studentDetailsFile.size() == 0)
        qDebug() << "Error file size is null. Error message: " << studentDetailsFile.error();
    else
    {
        qDebug() << "File found and opened for reading. File size: " << studentDetailsFile.size();
        QStringList studentList;
        // Read the file through
        while(!studentDetailsFile.atEnd())
        {
            QString line = studentDetailsFile.readLine();
            if (line == ui->StudentList->currentItem()->text().toUpper()) // If the a class name is read
            {
                ui->StudentName->setText(ui->StudentList->currentItem()->text()); // Sets the name of the student to the name selected in the list widget
                for (int i = 0; i <= 4; i++) // 5 pieces of information for each student
                {
                    QString subLine = studentDetailsFile.readLine();
                    switch (i)
                    {
                        case 0:
                            ui->StudentAddress->setText(subLine); // First line is the student's address
                        break;
                        case 1:
                            ui->StudentContactNum->setText(subLine); // Second line is the student's contact number
                        break;
                        case 2:
                            ui->StudentContactName->setText(subLine); // Third line is the student's contact name
                        break;
                        case 3:
                            ui->StudentAge->setText(subLine); // Fourth line is the student's age
                        break;
                        case 4:
                            ui->StudentGender->setText(subLine); // Fifth line is the student's gender
                        break;
                        default:
                            qDebug() << "index out of range"; // Handle an error case
                        break;
                    }
                }
            }
        }
        qDebug() << "Student details added";
        studentDetailsFile.close(); // Close file to release memory
    }
}

void DetailsWindow::on_EditNameButton_clicked()
{
    qDebug() << "Edit name button clicked";
    // Opens the window to edit the details
    if (!edwIsOpen)
    {
        edw = new EditDetailsWindow(ui->NameLabel->text()/*, *ui->StudentName*/);
        edw->show();
        edwIsOpen = true;
    }
}

void DetailsWindow::on_ConfirmButton_clicked()
{
    qDebug() << "Confirm button pressed";
    // Close the window
    this->close();
    dwIsOpen = false;
}

// The following slots do not have any functionality
void DetailsWindow::on_EditAddressButton_clicked()
{
    qDebug() << "Edit address button clicked";
    // Opens the window to edit the details
    if (!edwIsOpen)
    {
        edw = new EditDetailsWindow(ui->AddressLabel->text()/*, *ui->StudentAddress*/);
        edw->show();
        edwIsOpen = true;
    }
}


void DetailsWindow::on_EditContactNumButton_clicked()
{
    qDebug() << "Edit contact number button clicked";
    // Opens the window to edit the details
    if (!edwIsOpen)
    {
        edw = new EditDetailsWindow(ui->ContactNumLabel->text()/*, *ui->StudentContactNum*/);
        edw->show();
        edwIsOpen = true;
    }
}


void DetailsWindow::on_EditContactNameButton_clicked()
{
    qDebug() << "Edit contact name button clicked";
    // Opens the window to edit the details
    if (!edwIsOpen)
    {
        edw = new EditDetailsWindow(ui->ContactNameLabel->text()/*, *ui->StudentContactName*/);
        edw->show();
        edwIsOpen = true;
    }
}


void DetailsWindow::on_EditAgeButton_clicked()
{
    qDebug() << "Edit age button clicked";
    // Opens the window to edit the details
    if (!edwIsOpen)
    {
        edw = new EditDetailsWindow(ui->AgeLabel->text()/*, *ui->StudentAge*/);
        edw->show();
        edwIsOpen = true;
    }
}


void DetailsWindow::on_EditGenderButton_clicked()
{
    qDebug() << "Edit gender button clicked";
    // Opens the window to edit the details
    if (!edwIsOpen)
    {
        edw = new EditDetailsWindow(ui->GenderLabel->text()/*, *ui->StudentGender*/);
        edw->show();
        edwIsOpen = true;
    }
}

