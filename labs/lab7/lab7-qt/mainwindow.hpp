#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_mainwindow.h"
#include "adddialog.hpp"
#include "editdialog.hpp"
#include "csvstorage.hpp"

#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QPushButton>
#include <QListWidget>
#include <QMainWindow>
#include <QString>
#include <QtGui>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

signals:
  void org_to_update(QListWidgetItem*);
protected:
  void resizeEvent(QResizeEvent*);

private slots:
  void dialogDisabling();

  void add_orgs(const vector<Organisation> & orgs);

  void org_push(Organisation *);

  void org_update(Organisation*);

  // Status bar
  void on_new_action_triggered();

  void on_back_action_triggered();

  void on_open_action_triggered();

  void on_exit_action_triggered();

  // Widget 1
  void on_new_button_clicked();

  void on_open_button_clicked();

  // Widget 2
  void on_add_button_clicked();

  void on_edit_button_clicked();

  void on_delete_button_clicked();

  void on_list_widget_itemClicked(QListWidgetItem *);

  void on_list_widget_itemActivated(QListWidgetItem *);

private:
  Ui::MainWindow* ui;
  AddDialog * adddialog;
  EditDialog * editdialog;

  FileStorage* storage_ = nullptr;
  QString file_name;
};
#endif    // MAINWINDOW_HPP
