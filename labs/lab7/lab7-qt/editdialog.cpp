#include "editdialog.hpp"

#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget* parent):
    QDialog(parent), ui(new Ui::EditDialog) {
  ui->setupUi(this);
}

EditDialog::~EditDialog() { delete ui; }

void EditDialog::on_okay_button_clicked() {
  Organisation* org = new Organisation();

  org->label = (ui->edit_label->text().length() != 0) ?
                 ui->edit_label->text().toStdString() :
                 ui->edit_label->placeholderText().toStdString();
  org->country = (ui->edit_country->text().length() != 0) ?
                   ui->edit_country->text().toStdString() :
                   ui->edit_country->placeholderText().toStdString();
  org->founders = (ui->edit_founders->text().length() != 0) ?
                    ui->edit_founders->text().toStdString() :
                    ui->edit_founders->placeholderText().toStdString();

  emit upd_org(org);
  EditDialog::close();
}

void EditDialog::on_cancer_button_clicked() { EditDialog::close(); }

void EditDialog::closeEvent(QCloseEvent* event) {
  QWidget::closeEvent(event);
  emit disableToggle();
}

void EditDialog::edit_org(QListWidgetItem* item) {
  Organisation org = item->data(Qt::UserRole).value<Organisation>();

  ui->edit_label->setPlaceholderText(QString::fromStdString(org.label));
  ui->edit_country->setPlaceholderText(QString::fromStdString(org.country));
  ui->edit_founders->setPlaceholderText(QString::fromStdString(org.founders));
}
