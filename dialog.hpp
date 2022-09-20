#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "rollwindow.hpp"
#include "detailswindow.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_RollButton_clicked();

    void on_EditDetailsButton_clicked();

private:
    Ui::Dialog *ui;
    RollWindow *rw;
    DetailsWindow *dw;
};

#endif // DIALOG_H
