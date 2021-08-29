#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MessageEvent.h"
#include "QCoreApplication"
#include "SomeParallelprocess.h"
#include "thread"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *getApp(MainWindow *ptr = nullptr);
    virtual void customEvent(QEvent *ev);
    //work class in parallel thread
    SomeParallelprocess* process;
    //id main thread
    std::thread::id main_thread_id;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

static MessageEvent* MessageBox(QString _text,QString _title, int _type){
    MainWindow* pApp = MainWindow::getApp();
    MessageEvent* gl = new MessageEvent();
    gl->gui_launcher(_title,_text,_type);
    std::thread::id this_thread_id = std::this_thread::get_id();
    if(pApp->main_thread_id != this_thread_id){
        QCoreApplication::postEvent(pApp,gl);
        if(pApp->process != nullptr){ //puase thread for show gui message
            pApp->process->stopedThread = true;
            pApp->process->Pause();
        }
    }
    else{
        //call event if main thread
        pApp->customEvent(gl);
    }
    return gl;
}

static MessageEvent* MessageBox(QString _text, int _type = -1)
{
    return MessageBox(_text, "", _type);
}

#endif // MAINWINDOW_H
