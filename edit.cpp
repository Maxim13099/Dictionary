#include "edit.h"
#include "ui_edit.h"

Edit::Edit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Edit)
{
    ui->setupUi(this);
}

Edit::~Edit()
{
    delete ui;
}


QString Edit::getInput() {
    return ui->textEdit->toPlainText();
}

void Edit::on_pushButton_edit_clicked() {
    QString inputText = getInput();
    emit dictionaryUpdated(inputText);
    this->close();
}
