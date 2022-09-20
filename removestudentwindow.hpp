#ifndef REMOVESTUDENTWINDOW_H
#define REMOVESTUDENTWINDOW_H

#include <QWidget>

namespace Ui {
class RemoveStudentWindow;
}

class RemoveStudentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RemoveStudentWindow(QWidget *parent = nullptr);
    ~RemoveStudentWindow();

private slots:
    void on_ClassSelector_currentIndexChanged(int index);

    void on_RemoveButton_clicked();

    void on_ConfirmButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::RemoveStudentWindow *ui;
    QStringList fileContents;
};

inline bool rswIsOpen = false;

#endif // REMOVESTUDENTWINDOW_H
