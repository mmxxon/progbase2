#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>

#include "organisation.hpp"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT
signals:
    void addOrg(Organisation*);
    void disableToggle();
public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();
protected:
    void closeEvent(QCloseEvent *);
private slots:

    void on_okay_button_clicked();

    void on_cancer_button_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
