#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include "organisation.hpp"

#include <QDebug>
#include <QDialog>
#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class EditDialog;
}

class EditDialog: public QDialog {
  Q_OBJECT
signals:
  void upd_org(Organisation*);
  void disableToggle();

public:
  explicit EditDialog(QWidget* parent = 0);
  ~EditDialog();

protected:
  void closeEvent(QCloseEvent*);
private slots:

  void on_okay_button_clicked();

  void on_cancer_button_clicked();

  void edit_org(QListWidgetItem*);

private:
  Ui::EditDialog* ui;
};

#endif    // EDITDIALOG_H
