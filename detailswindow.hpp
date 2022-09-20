#ifndef DETAILSWINDOW_H
#define DETAILSWINDOW_H

#include <QWidget>
#include <QListWidget>
#include "editdetailswindow.hpp"

namespace Ui {
class DetailsWindow;
}

class DetailsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DetailsWindow(QWidget *parent = nullptr);
    ~DetailsWindow();

private slots:
    void on_ClassSelector_currentIndexChanged(int index);

    void on_StudentList_itemClicked(QListWidgetItem *item);

    void on_ConfirmButton_clicked();

    void on_EditNameButton_clicked();

    void on_EditAddressButton_clicked();

    void on_EditContactNumButton_clicked();

    void on_EditContactNameButton_clicked();

    void on_EditAgeButton_clicked();

    void on_EditGenderButton_clicked();

private:
    Ui::DetailsWindow *ui;
    EditDetailsWindow *edw;
};

inline bool dwIsOpen = false;

#endif // DETAILSWINDOW_H
