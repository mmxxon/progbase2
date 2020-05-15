#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include "organisation.hpp"

#include <QDebug>
#include <QDialog>
#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class AddDialog;
}

class AddDialog: public QDialog {
  Q_OBJECT
signals:
  void addOrg(Organisation*);
  void disableToggle();

public:
  explicit AddDialog(QWidget* parent = 0);
  ~AddDialog();

protected:
  void closeEvent(QCloseEvent*);
private slots:

  void on_okay_button_clicked();

  void on_cancer_button_clicked();

private:
  Ui::AddDialog* ui;
};

#endif    // ADDDIALOG_H
