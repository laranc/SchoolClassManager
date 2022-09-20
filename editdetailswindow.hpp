#ifndef EDITDETAILSWINDOW_HPP
#define EDITDETAILSWINDOW_HPP

#include <QDialog>
#include <QLabel>

namespace Ui {
class EditDetailsWindow;
}

class EditDetailsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditDetailsWindow(QString detailName, /*QLabel &detailEdit,*/ QWidget *parent = nullptr);
    ~EditDetailsWindow();

private slots:
    void on_ButtonBox_accepted();

    void on_ButtonBox_rejected();

private:
    Ui::EditDetailsWindow *ui;
    QLabel detailValue;
};

inline bool edwIsOpen = false;

#endif // EDITDETAILSWINDOW_HPP
