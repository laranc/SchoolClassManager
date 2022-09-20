#include "addstudentwindow.hpp"
#include "ui_addstudentwindow.h"
#include <QFile>

AddStudentWindow::AddStudentWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AddStudentWindow)
{
    ui->setupUi(this); // Display GUI

    qDebug() << "Add student window opened";

    QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
    QFile studentsFile(studentFilePath);
    // Read from file and display the subject names in the combobox
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

AddStudentWindow::~AddStudentWindow()
{
    delete ui;
}

void AddStudentWindow::on_ClassSelector_currentIndexChanged(int index)
{
    qDebug() << "Class slector current index changed";
    // Add the students from the selected class into the list widget and display the list of people not in that class into the adjacent student list widget
    if (ui->ClassSelector->currentText() != "Choose a class")
    {
        ui->StudentList->clear();
        ui->StudentAddList->clear();

        QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
        QFile classesFile(studentFilePath);
        // Open the file for read only
        if (!classesFile.exists())
            qDebug() << "Error file not found at path: " << studentFilePath;
        else if (!classesFile.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Error reading file";
        else if (classesFile.size() == 0)
            qDebug() << "Error file size is null. Error message: " << classesFile.error();
        else
        {
            qDebug() << "File found and opened for reading. File size: " << classesFile.size();
            QStringList classList; // List of students from the class
            QStringList studentList; // List of students not in the class
            while (!classesFile.atEnd())
            {
                QString line = classesFile.readLine();
                if (line == ui->ClassSelector->currentText().toUpper()) // Check if the line is a subject name
                {
                    while (!classesFile.atEnd()) // Loop until another subject name is reached
                    {
                        QString subLine = classesFile.readLine();
                        if (subLine.isUpper()) // Break if the line is a subject name
                            break;
                        else
                            classList.append(subLine); // Add to the class list
                    }
                }
                else if (!line.isUpper()) // If the line is not a subject name
                {
                    bool inList = false;
                    for (int i = 0; i < ui->StudentList->count(); i++) // Check if the line (student name) is in th list of students
                        if (line == ui->StudentList->item(i)->text())
                            inList = true;
                    if (!inList)
                        studentList.append(line); // If the line is not in the list of the students then add it to the list of students
                }
            }
            classesFile.close();
            ui->StudentList->addItems(classList); // Add the list to the class list widget
            ui->StudentAddList->addItems(studentList); // Add the list to the student list widget
            qDebug() << "Students added to lists";
        }
    }
    else
    {
        ui->StudentList->clear(); // Clear the list
        ui->StudentAddList->clear(); // Clear the list
    }

}

void AddStudentWindow::on_StudentAddList_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "List item doubled clicked";

    delete ui->StudentAddList->takeItem(ui->StudentAddList->row(item)); // Remove item from the student list
}

void AddStudentWindow::on_AddStudentsButton_clicked()
{
    qDebug() << "Add students button clicked";
    // Move the selected item from one list widget to another
    QListWidgetItem *newStudent = ui->StudentAddList->currentItem()->clone(); // Clone the selected item
    ui->StudentList->addItem(newStudent); // Add the item to the widget
    addedStudents.append(newStudent->text()); // Add the student name to the list of newly added students
    delete ui->StudentAddList->takeItem(ui->StudentAddList->currentRow()); // Remove the original item from the list
}

void AddStudentWindow::on_ConfirmButton_clicked()
{
   qDebug() << "Confirm button clicked";

   QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
   QFile classesFile(studentFilePath);
   // Open the file for reading and writing in truncate mode
   if (!classesFile.exists())
       qDebug() << "Error file not found at path: " << studentFilePath;
   else if (!classesFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
       qDebug() << "Error opening file to read and write";
   else
   {
       qDebug() << "File found and opened for reading. File size: " << classesFile.size();

       while (!classesFile.atEnd())
           fileContents.append(classesFile.readLine()); // Reads the whole file and adds it to a list

       foreach (QString line, fileContents)
       {
           if (line == ui->ClassSelector->currentText().toUpper()) // Checks if the line is a subject name
           {
               classesFile.write(line.toUtf8()); // Writes the subject name to the file with UTF-8 encoding
               for (int i = 0; i < addedStudents.count(); i++)
               {
                   // Writes the new students to the file
                   classesFile.write(addedStudents[i].toUtf8());
                   qDebug() << "From list: "+ addedStudents[i].toUtf8();
               }
           }
           else
           {
               // Writes the line from the list back into the file
               classesFile.write(line.toUtf8());
               qDebug() << "From file: "+ line.toUtf8();
           }
       }
       classesFile.close(); // Closes the file
       qDebug() << "Student added to class";
       // Closes the window
       this->close();
       aswIsOpen = false;
   }
}


void AddStudentWindow::on_CancelButton_clicked()
{
    qDebug() << "Cancel button clicked";
    // Closes the window
    this->close();
    aswIsOpen = false;
}
