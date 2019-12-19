#include "sandbox.h"
#include "ui_sandbox.h"

#include <QFile>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QTextStream>

#include "sandbox/src/dummygroup/dummyclass.h"

Sandbox::Sandbox(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Sandbox),
  ui_timer_(new QTimer(this)),
  timer_(new QTimer(this)),
  dummy_class_instance_(new sandbox::dummygroup::DummyClass())  {
  ui->setupUi(this);
}

Sandbox::~Sandbox() {
  delete ui;
  delete ui_timer_;
}

void Sandbox::on_quitButton_clicked() {
  QCoreApplication::quit();
}

void Sandbox::on_actionOpen_triggered() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                  tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
      return;
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();
  }
}

void Sandbox::on_actionSave_triggered() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                  tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      // error message
    } else {
      QTextStream stream(&file);
      stream << ui->textEdit->toPlainText();
      stream.flush();
      file.close();
    }
  }
}

void Sandbox::update() {
}

void Sandbox::processing_end() {
}
