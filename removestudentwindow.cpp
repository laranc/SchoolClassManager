#include "removestudentwindow.hpp"
#include "ui_removestudentwindow.h"
#include <QFile>

RemoveStudentWindow::RemoveStudentWindow(QWidget *parent) : QWidget(parent), ui(new Ui::RemoveStudentWindow)
{
    ui->setupUi(this); // Display GUI

    qDebug() << "Remove student window opened";

    QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
    QFile studentsFile(studentFilePath);
    // Open the file in read only and add the subject name into the combobox
    if (!studentsFile.exists())
        qDebug() << "Error file not found at path: " << studentFilePath;
    else if (!studentsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error reading file";
    else if (studentsFile.size() == 0)
        qDebug() << "Error file size is null. Error message: " << studentsFile.error();
    else
    {
        qDebug() << "File found and opened for reading. File size: " << studentsFile.size();
        while (!studentsFile.atEnd())
        {
            QString line = studentsFile.readLine();
            fileContents.append(line);
            if (line.isUpper())
            {
                line = line.toLower();
                line[0] = line[0].toUpper();
                ui->ClassSelector->addItem(line);
            }
        }
        ui->ClassSelector->setCurrentText("Choose a class"); // Set the default option
        qDebug() << "Classes added to combo box";
        studentsFile.close();
    }
}

RemoveStudentWindow::~RemoveStudentWindow()
{
    delete ui;
}

void RemoveStudentWindow::on_ClassSelector_currentIndexChanged(int index)
{
    qDebug() << "Class slector current index changed";
    // Add the students from the selected class into the list widget
    if (ui->ClassSelector->currentText() != "Choose a class")
    {
        ui->StudentList->clear();

        QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
        QFile classesFile(studentFilePath);
        // Open file in read only mode
        if (!classesFile.exists())
            qDebug() << "Error file not found at path: " << studentFilePath;
        else if (!classesFile.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Error reading file";
        else if (classesFile.size() == 0)
            qDebug() << "Error file size is null. Error message: " << classesFile.error();
        else
        {
            qDebug() << "File found and opened for reading. File size: " << classesFile.size();
            QStringList classList;
            while (!classesFile.atEnd())
            {
                QString line = classesFile.readLine();
                if (line == ui->ClassSelector->currentText().toUpper())
                    while (!classesFile.atEnd())
                    {
                        QString subLine = classesFile.readLine();
                        if (subLine.isUpper()) // Break when another subject name is reached
                            break;
                        else
                            classList.append(subLine); // Add student name into the list
                    }
            }
            classesFile.close();
            ui->StudentList->addItems(classList); // Add the list to the widget
            qDebug() << "Students added to lists";
        }
    }
    else
    {
        ui->StudentList->clear();
        ui->StudentRemoveList->clear();
    }
}

void RemoveStudentWindow::on_RemoveButton_clicked()
{
    qDebug() << "Remove student button clicked";
    // Add the selected item to the remove list
    QListWidgetItem *removedStudent = ui->StudentList->currentItem()->clone(); // Clone the selected item
    ui->StudentRemoveList->addItem(removedStudent); // Add the cloned item
    delete ui->StudentList->takeItem(ui->StudentList->currentRow()); // Remove the original item
}

void RemoveStudentWindow::on_ConfirmButton_clicked()
{
    qDebug() << "Confirm button clicked";

    QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
    QFile classesFile(studentFilePath);
    // Open file for reading and writing in truncate mode
    if (!classesFile.exists())
        qDebug() << "Error file not found at path: " << studentFilePath;
    else if (!classesFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        qDebug() << "Error opening file to read and write";
    else
    {
        qDebug() << "File found and opened for reading and writing. File size: " << classesFile.size();

        while (!classesFile.atEnd())
            fileContents.append(classesFile.readLine()); // Read the contents of the file and put it in a list

        foreach (QString line, fileContents)
        {
            bool toBeRemoved = false;
            for (int i = 0; i < ui->StudentRemoveList->count(); i++) // Check if the student is in the list to be removed
                if (line == ui->StudentRemoveList->item(i)->text())
                    toBeRemoved = true;

            if (!toBeRemoved)
                classesFile.write(line.toUtf8()); // If the student is not to be removed then write the student to the list
        }

        classesFile.close(); // Close the file
        qDebug() << "Student removed from class";
        this->close(); // Close the window
        rswIsOpen = false;
    }
}


void RemoveStudentWindow::on_CancelButton_clicked()
{
    qDebug() << "Cancel button clicked";
    // Close the window
    this->close();
    rswIsOpen = false;
}
