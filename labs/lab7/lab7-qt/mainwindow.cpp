#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QPixmap edit_icon("../../items/edit.svg");
  QPixmap add_icon("../../items/add.svg");
  QPixmap delete_icon("../../items/delete.svg");
  QPixmap window_icon("../../items/cool.svg");
  ui->add_button->setIcon(add_icon);
  ui->edit_button->setIcon(edit_icon);
  ui->delete_button->setIcon(delete_icon);
  ui->back_action->setVisible(0);
  setWindowIcon(window_icon);
}

MainWindow::~MainWindow()
{
    if(storage_!=nullptr)
        delete storage_;
    delete ui;
}

void MainWindow::add_orgs(const vector<Organisation> & orgs) {
    for(const Organisation & org : orgs) {
        QVariant var=QVariant::fromValue(org);
        QListWidgetItem * item=new QListWidgetItem();
        item->setTextAlignment(Qt::AlignHCenter);
        item->setText(QString::fromStdString(org.label));
        item->setData(Qt::UserRole,var);
        ui->list_widget->addItem(item);
    }
}

void MainWindow::org_push(Organisation * org) {
  storage_->insertOrg(*org);
  vector<Organisation> orgs = storage_->getAllOrgs();

  QListWidgetItem * item = new QListWidgetItem();

  QVariant var;
  var.setValue(orgs.at(orgs.size()-1));

  QString label = QString::fromStdString(orgs.at(orgs.size() - 1).label);
  item->setText(label);
  item->setData(Qt::UserRole, var);
  item->setTextAlignment(Qt::AlignHCenter);

  ui->list_widget->addItem(item);
}

void MainWindow::org_update(Organisation*org) {
  QListWidgetItem * item = ui->list_widget->selectedItems().at(0);
  Organisation orgn = item->data(Qt::UserRole).value<Organisation>();
  org->id = orgn.id;
  if (!storage_->updateOrg(*org)) {
    qDebug() << "Err on update";
    return;
  }
  QVariant var;
  var.setValue(*org);
  item->setText(QString::fromStdString(org->label));
  item->setData(Qt::UserRole, var);
  item->setTextAlignment(Qt::AlignHCenter);
  on_list_widget_itemClicked(item);
}

// adaptive size
void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);

  int width = MainWindow::size().width();
  int height = MainWindow::size().height();

  // first widget
  if (ui->stackedWidget->currentIndex() == 0) {
    int text_size = (width / 34 < height / 6.7) ? (width / 34) : (height / 6.7);
    text_size = (text_size > 15) ? text_size : 15;
    ui->new_button->setFont(QFont("Arial Black", text_size));
    ui->open_button->setFont(QFont("Arial Black", text_size));
    if (width > 696 && height > 135) {
      ui->new_button->setFixedWidth(width / 4);
      ui->open_button->setFixedWidth(width / 4);
      ui->new_button->setFixedHeight(width / 10);
      ui->open_button->setFixedHeight(width / 10);
    }
  }

  // second widget
  else if (ui->stackedWidget->currentIndex() == 1) {
    int button_size = (width / 18 < height / 10) ? (width / 18) : (height / 10);
    button_size = (button_size > 40) ? button_size : 40;

    ui->label_label->setFont(QFont("Arial Black", button_size / 2.5));
    ui->label_country->setFont(QFont("Arial Black", button_size / 2.5));
    ui->label_founders->setFont(QFont("Arial Black", button_size / 2.5));

    ui->list_widget->item(0)->setFont(QFont("Arial", button_size / 3));
    ui->list_widget->setFont(QFont("Arial", button_size / 4));

    ui->label_field->setFont(QFont("Arial", button_size / 3));
    ui->country_field->setFont(QFont("Arial", button_size / 3));
    ui->founders_field->setFont(QFont("Arial", button_size / 3));

    ui->add_button->setFixedHeight(button_size);
    ui->add_button->setFixedWidth(button_size);
    ui->add_button->setIconSize(QSize(button_size / 2, button_size / 2));

    ui->edit_button->setFixedHeight(button_size);
    ui->edit_button->setFixedWidth(button_size);
    ui->edit_button->setIconSize(QSize(button_size / 2, button_size / 2));

    ui->delete_button->setFixedHeight(button_size);
    ui->delete_button->setFixedWidth(button_size);
    ui->delete_button->setIconSize(QSize(button_size / 2, button_size / 2));

    if (width > 750 && height > 320) {
      ui->label_label->setFixedWidth(width / 5);
      ui->label_label->setFixedHeight(width / 10);

      ui->label_country->setFixedWidth(width / 5);
      ui->label_country->setFixedHeight(width / 10);

      ui->label_founders->setFixedWidth(width / 5);
      ui->label_founders->setFixedHeight(width / 10);

      ui->list_widget->setFixedWidth(width / 2.5);
    }
  }
}

// menu bar
void MainWindow::on_new_action_triggered() {
  on_new_button_clicked();
}
void MainWindow::on_open_action_triggered() {
  on_open_button_clicked();
}

void MainWindow::on_back_action_triggered() {
  ui->stackedWidget->setCurrentIndex(0);
  ui->label_country->setEnabled(0);
  ui->label_founders->setEnabled(0);
  ui->label_field->setEnabled(0);
  ui->add_button->setEnabled(0);
  ui->list_widget->setEnabled(0);
  ui->back_action->setVisible(0);
  ui->back_action->setEnabled(0);
  resize(width()-1,height()-1);
}

void MainWindow::on_exit_action_triggered() {close();}

// widget 1
void MainWindow::on_new_button_clicked() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  QString dir =
    QDir(QDir::currentPath())
      .cleanPath(QDir(QDir::currentPath()).absoluteFilePath("../../data"));
  QString path = dialog.getSaveFileName(this, "Select new path",
                                        dir + "/organisations.csv",
                                        "Storage (*.csv);;All (*.*)");
  if (path.length() == 0) return;
  qDebug() << "Path: " << path;
  ui->label_country->setEnabled(1);
  ui->label_founders->setEnabled(1);
  ui->label_field->setEnabled(1);
  ui->add_button->setEnabled(1);
  ui->list_widget->setEnabled(1);
  ui->back_action->setVisible(1);
  ui->back_action->setEnabled(1);
  if (storage_) {
    delete storage_;
    for (int i = 2; i < ui->list_widget->count(); i++) {
      delete ui->list_widget->item(i);
    }
  }
  file_name = path;
  storage_ = new CsvStorage(path.toStdString());
  add_orgs(storage_->getAllOrgs());
  ui->stackedWidget->setCurrentIndex(1);
  resize(width()-1,height()-1);
}

void MainWindow::on_open_button_clicked() {
  QString dir = QDir(QDir::currentPath()).cleanPath(QDir(QDir::currentPath()).absoluteFilePath("../../data"));
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFile);
  QString path = dialog.getOpenFileName(this,"Select path to file", dir, "Storage (*.csv);;All (*.*)");
  if (path.length()==0) return;
  qDebug() << "Path: " << path;
  ui->label_country->setEnabled(1);
  ui->label_founders->setEnabled(1);
  ui->label_field->setEnabled(1);
  ui->add_button->setEnabled(1);
  ui->list_widget->setEnabled(1);
  ui->back_action->setVisible(1);
  ui->back_action->setEnabled(1);
  if (storage_) {
    delete storage_;
    for (int i = 2; i < ui->list_widget->count(); i++) {
      delete ui->list_widget->item(i);
    }
  }
  file_name = path;
  storage_ = new CsvStorage(path.toStdString());
  add_orgs(storage_->getAllOrgs());
  ui->stackedWidget->setCurrentIndex(1);
  resize(width()-1,height()-1);
}

// widget 2

// actions
void MainWindow::on_add_button_clicked() {
  adddialog = new AddDialog(this);
  dialogDisabling();
  adddialog->show();
  connect(adddialog, SIGNAL(addOrg(Organisation*)), SLOT(org_push(Organisation *)));
  connect(adddialog, SIGNAL(disableToggle()), SLOT(dialogDisabling()));
}

void MainWindow::dialogDisabling() {
  QGraphicsBlurEffect * effect = new QGraphicsBlurEffect(this);
  if (ui->menuBar->isEnabled()) {
    ui->menuBar->setEnabled(0);
    ui->list_widget->setEnabled(0);
    ui->add_button->setEnabled(0);
    ui->delete_button->setEnabled(0);
    ui->edit_button->setEnabled(0);
    MainWindow::setGraphicsEffect(effect);
  } else {
    ui->menuBar->setEnabled(1);
    ui->list_widget->setEnabled(1);
    ui->add_button->setEnabled(1);
    if (ui->list_widget->selectedItems().count()!=0) {
      ui->delete_button->setEnabled(1);
      ui->edit_button->setEnabled(1);
    }
    MainWindow::setGraphicsEffect(0);
  }
}

void MainWindow::on_edit_button_clicked() {
  editdialog = new EditDialog(this);
  dialogDisabling();
  editdialog->show();
  connect(this, SIGNAL(org_to_update(QListWidgetItem*)), editdialog, SLOT(edit_org(QListWidgetItem*)));
  connect(editdialog, SIGNAL(upd_org(Organisation*)),this, SLOT(org_update(Organisation*)));
  connect(editdialog, SIGNAL(disableToggle()), SLOT(dialogDisabling()));

  emit(org_to_update(ui->list_widget->selectedItems().at(0)));
}

void MainWindow::on_delete_button_clicked() {
  QMessageBox::StandardButton answer;
  answer = QMessageBox::question(
        this,
        "Deletion",
        "Really?",
        QMessageBox::Yes|QMessageBox::No);
  if (answer == QMessageBox::No) return;
  QList<QListWidgetItem*> items = ui->list_widget->selectedItems();
  if (items.at(0) == NULL ) return;
  foreach (QListWidgetItem * item, items) {
        items = ui->list_widget->selectedItems();
        Organisation org = item->data(Qt::UserRole).value<Organisation>();
        qDebug() << "deletion: " << org.id;
        storage_->removeOrg(org.id);
        delete ui->list_widget->takeItem(ui->list_widget->row(item));
  }
  vector<Organisation> orgs = storage_->getAllOrgs();
  if (orgs.empty()) {
    ui->delete_button->setEnabled(false);
    ui->edit_button->setEnabled(false);

    ui->label_field->setText("");
    ui->country_field->setText("");
    ui->founders_field->setText("");
  } else {
    items = ui->list_widget->selectedItems();
    QListWidgetItem * item = items.at(0);
    QVariant var = item->data(Qt::UserRole);
    Organisation org = var.value<Organisation>();

    ui->label_field->setText(QString::fromStdString(org.label));
    ui->country_field->setText(QString::fromStdString(org.country));
    ui->founders_field->setText(QString::fromStdString(org.founders));

  }

}

void MainWindow::on_list_widget_itemClicked(QListWidgetItem *item) {
  ui->delete_button->setEnabled(1);
  ui->add_button->setEnabled(1);
  ui->edit_button->setEnabled(1);
  Organisation org = item->data(Qt::UserRole).value<Organisation>();
  ui->label_field->setText(QString::fromStdString(org.label));
  ui->country_field->setText(QString::fromStdString(org.country));
  ui->founders_field->setText(QString::fromStdString(org.founders));
}

void MainWindow::on_list_widget_itemActivated(QListWidgetItem *item) {
  on_list_widget_itemClicked(item);
}
