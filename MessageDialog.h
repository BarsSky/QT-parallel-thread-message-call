#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDialog(QString title, QString text,QWidget *parent = nullptr);
    ~MessageDialog();
    int answer;
private:
    Ui::MessageDialog *ui;
};

#endif // MESSAGEDIALOG_H
