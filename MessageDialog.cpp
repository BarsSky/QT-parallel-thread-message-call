#include "MessageDialog.h"
#include "ui_MessageDialog.h"

MessageDialog::MessageDialog(QString title, QString text, QWidget *parent) :
    QDialog(parent),
    answer(0),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    ui->label->setText(text);
    ui->label_2->setText(title);
}

MessageDialog::~MessageDialog()
{
    delete ui;
}
