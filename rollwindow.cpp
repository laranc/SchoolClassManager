#include "rollwindow.hpp"
#include "ui_rollwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

RollWindow::RollWindow(QWidget *parent) : QWidget(parent), ui(new Ui::RollWindow)
{
    ui->setupUi(this); // Initialises the graphical user interface for this window
    qDebug() << "Roll window opened";

    QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes"; // Sets the path to the file
    QFile studentsFile(studentFilePath);                                                            // Initialises the file

    // Open file for reading
    if (!studentsFile.exists())
        qDebug() << "Error file not found at path: " << studentFilePath; // Handle if the file does not exist
    else if (!studentsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error reading file"; // Handle if the file is unable to be opened
    else if (studentsFile.size() == 0)
        qDebug() << "Error file size is null. Error message: " << studentsFile.error(); // Handle if the file is empty
    else
    {
        qDebug() << "File found and opened for reading. File size: " << studentsFile.size();
        while (!studentsFile.atEnd())
        {
            QString line = studentsFile.readLine();
            if (line.isUpper()) // The structure of the file contains subject names in uppercase and student names in capitalised (e.g. "ENGLISH" "John Doe") therefore if it is capitalised then it must be a subject
            {
                line = line.toLower();            // Converts the subject name into lowercase
                line[0] = line[0].toUpper();      // Capitalises the first letter
                ui->ClassSelector->addItem(line); // Adds to dropdown selector (combobox)
            }
        }
        ui->ClassSelector->setCurrentText("Choose class"); // Sets the default text to "Choose class"
        qDebug() << "Classes added to combo box";
        studentsFile.close(); // Closes the file to prevent a memory leak
    }
}

RollWindow::~RollWindow()
{
    delete ui;
}

void RollWindow::on_AddStudent_clicked()
{
    qDebug() << "Add student button clicked";
    // Opens the window to add a student to a class
    if (!aswIsOpen)
    {
        asw = new AddStudentWindow;
        asw->show();
        aswIsOpen = true;
    }
}

void RollWindow::on_RemoveStudent_clicked()
{
    qDebug() << "Remove student button clicked";
    // Opens the window to remove a student from the class
    if (!rswIsOpen)
    {
        rsw = new RemoveStudentWindow;
        rsw->show();
        rswIsOpen = true;
    }
}

void RollWindow::on_Present_clicked()
{
    qDebug() << "Present radio button clicked";

    ui->AbsentReasonSelector->setEnabled(false); // Disables the combobox to select a reason for absence
}

void RollWindow::on_Absent_clicked()
{
    qDebug() << "Absent radio button clicked";

    ui->AbsentReasonSelector->setEnabled(true); // Enables the combobox to select a reason for absence
}

void RollWindow::on_StudentList_itemClicked(QListWidgetItem *item)
{
    qDebug() << "Student list item clicked";

    ui->StudentName->setText(item->text()); // Displays the name of the student at the top of the window
}

void RollWindow::on_SaveNotes_clicked()
{
    qDebug() << "Save notes button clicked";

    QString studentNote = ui->StudentNotesArea->toPlainText(); // Saves the text to a string

    QString notesFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/student_notes";
    QFile notesFile(notesFilePath);

    QTextStream out(&notesFile); // Open a textstream in the file
    // Opens file for writing in append mode
    if (!notesFile.exists())
        qDebug() << "Error file not found at path: " << notesFilePath;
    else if (!notesFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        qDebug() << "Error opening file to writing";
    else
    {
        out << ui->StudentName->text() << " - " << studentNote << "\n"
            << "end"
            << "\n"; // Prints Student name, and the note to the file
        out.flush(); // Flushes the buffer of the textstream
        qDebug() << "Student note: " << studentNote;
        notesFile.close(); // Closes file to prevent a memory leak
    }
}

void RollWindow::on_DeleteNotes_clicked()
{
    qDebug() << "Delete notes button clicked";

    QString notesFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/student_notes";
    QFile notesFile(notesFilePath);
    // Opens a file for writing only
    if (!notesFile.exists())
        qDebug() << "Error file not found at path: " << notesFilePath;
    else if (!notesFile.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "Error opening file to writing";
    else
    {
        notesFile.write("\n");         // Clears the file
        ui->StudentNotesArea->clear(); // Clears the notes widget
    }
    notesFile.close(); // Closes file
}

void RollWindow::on_StudentList_itemSelectionChanged()
{
    qDebug() << "Studen list item selection changed";

    ui->StudentNotesArea->clear(); // Clears notes widget
}

void RollWindow::on_ClassSelector_currentIndexChanged(int index)
{
    qDebug() << "Class selector selected class changed";
    // Display the students in the class in the student list widget
    if (ui->ClassSelector->currentText() != "Choose a class") // Only read the file if a class is selected
    {
        ui->StudentList->clear(); // Clears the list

        QString studentFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/classes";
        QFile studentsFile(studentFilePath);
        // Opens the file in read only mode
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
            while (!studentsFile.atEnd())
            {
                QString line = studentsFile.readLine();
                if (line == ui->ClassSelector->currentText().toUpper()) // Subject names in the file are in capitals, therefore checking if it is a class name or a student name
                    while (!studentsFile.atEnd())                       // Loop again after the class name is found=
                    {
                        QString subLine = studentsFile.readLine();
                        if (subLine.isUpper()) // Break once the loop gets to another class name
                            break;
                        studentList.append(subLine); // Append the student names to the list
                    }
            }
            ui->StudentList->addItems(studentList); // Add the list to the widget
            qDebug() << "Classes added to combo box";
            studentsFile.close();
        }
    }
    else
        ui->StudentList->clear(); // Clears the list in case the combobox returns to "Choose a class" rather than a valid subject name
}

void RollWindow::on_SubmitStudent_clicked()
{
    qDebug() << "Submit student button clicked";

    QString rollFilePath = QCoreApplication::applicationDirPath() + "/../task3_program/class_roll";
    QFile rollFile(rollFilePath);
    // Opens file for reading and writing in append mode
    if (!rollFile.exists())
        qDebug() << "Error file not found at path: " << rollFilePath;
    else if (!rollFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        qDebug() << "Error writing to file";
    else
    {
        qDebug() << "Opened file for writing, current file size: " << rollFile.size();

        QTextStream stream(&rollFile); // Opens a text stream attached to the file

        if (ui->Present->isChecked()) // Checks if the radiobutton is set to "Present"
        {
            stream << ui->ClassSelector->currentText() << ": " << ui->StudentList->currentItem()->text() << " - PRESENT \n"; // Prints the name of the class, the student and the present status (ie. ENGLISH: John Doe - PRESENT)
            stream.flush();                                                                                                  // Flushes the buffer of the stream
            ui->StudentList->currentItem()->setForeground(Qt::green);                                                        // Sets the colour of the student name in the list widget to green
        }
        else if (ui->Absent->isChecked() && ui->AbsentReasonSelector->currentIndex() != 0) // Check if the radiobutton is set to "Absent" and that the reason for absence as selected in the combobox is not set to "Absent reason" and is set to a valid reason
        {
            stream << ui->ClassSelector->currentText() << ": " << ui->StudentList->currentItem()->text() << " - ABSENT | " << ui->AbsentReasonSelector->currentText() << "\n"; // ENGLISH: John Doe - ABSENT | SICK
            stream.flush();
            ui->StudentList->currentItem()->setForeground(Qt::red); // Sets colour of the student name in the list widget to red
        }
        else if (ui->Absent->isChecked() && ui->AbsentReasonSelector->currentIndex() == 0) // If the radiobutton is set to "Absent" but an absent reason is not selected
        {
            // Opens an error message
            QMessageBox errmsg;
            errmsg.setText("Please select a valid reason from the dropdown");
            errmsg.setWindowTitle("Error");
            errmsg.exec();
        }
    }
}

void RollWindow::on_SubmitAll_clicked()
{
    qDebug() << "Submit all button clicked";
    // Closes the window
    this->close();
    rwIsOpen = false;
}
