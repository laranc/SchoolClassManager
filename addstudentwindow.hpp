#ifndef ADDSTUDENTWINDOW_H
#define ADDSTUDENTWINDOW_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class AddStudentWindow;
}

class AddStudentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddStudentWindow(QWidget *parent = nullptr);
    ~AddStudentWindow();

private slots:
    void on_ClassSelector_currentIndexChanged(int index);

    void on_StudentAddList_itemDoubleClicked(QListWidgetItem *item);

    void on_AddStudentsButton_clicked();

    void on_ConfirmButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddStudentWindow *ui;
    QStringList fileContents;
    QStringList addedStudents;
};

inline bool aswIsOpen = false;

#endif // ADDSTUDENTWINDOW_H
