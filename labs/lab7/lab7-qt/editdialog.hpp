#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>

#include "organisation.hpp"

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT
signals:
    void upd_org(Organisation*);
    void disableToggle();
public:
    explicit EditDialog(QWidget *parent = 0);
    ~EditDialog();
protected:
    void closeEvent(QCloseEvent *);
private slots:

    void on_okay_button_clicked();

    void on_cancer_button_clicked();

    void edit_org(QListWidgetItem*);
private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
