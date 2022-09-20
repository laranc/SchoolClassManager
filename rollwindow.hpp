#ifndef ROLLWINDOW_H
#define ROLLWINDOW_H

#include <QWidget>
#include <QListWidget>
#include "addstudentwindow.hpp"
#include "removestudentwindow.hpp"

namespace Ui {
class RollWindow;
}

class RollWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RollWindow(QWidget *parent = nullptr);
    ~RollWindow();

private slots:
    void on_AddStudent_clicked();

    void on_RemoveStudent_clicked();

    void on_Present_clicked();

    void on_Absent_clicked();

    void on_StudentList_itemClicked(QListWidgetItem *item);

    void on_SaveNotes_clicked();

    void on_DeleteNotes_clicked();

    void on_StudentList_itemSelectionChanged();

    void on_ClassSelector_currentIndexChanged(int index);

    void on_SubmitAll_clicked();

    void on_SubmitStudent_clicked();

private:
    Ui::RollWindow *ui;
    AddStudentWindow *asw;
    RemoveStudentWindow *rsw;
};

inline bool rwIsOpen = false;

#endif // ROLLWINDOW_H
