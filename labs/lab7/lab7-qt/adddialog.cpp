#include "adddialog.hpp"

#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget* parent): QDialog(parent), ui(new Ui::AddDialog) {
  ui->setupUi(this);
}

AddDialog::~AddDialog() { delete ui; }

void AddDialog::on_okay_button_clicked() {
  Organisation* org = new Organisation();
  org->label = ui->edit_label->text().toStdString();
  org->country = ui->edit_country->text().toStdString();
  org->founders = ui->edit_founders->text().toStdString();

  emit addOrg(org);
  AddDialog::close();
}

void AddDialog::on_cancer_button_clicked() { AddDialog::close(); }

void AddDialog::closeEvent(QCloseEvent* event) {
  QWidget::closeEvent(event);
  emit disableToggle();
}
