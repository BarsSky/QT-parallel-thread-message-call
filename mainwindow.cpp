#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MessageDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , process(nullptr)
{
    ui->setupUi(this);
    //take pointer on mainwindow
    getApp(this);
    main_thread_id = std::this_thread::get_id();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::getApp(MainWindow *ptr)
{
    static MainWindow * mwPtr = nullptr;
    if (ptr)
        mwPtr = ptr;

    return mwPtr;
}

void MainWindow::customEvent(QEvent *ev)
{
    //call event
    if((int)ev->type() == MessageEvent::MessageType){
        //check thread id
        MessageDialog *dlg = new MessageDialog(
                    reinterpret_cast<MessageEvent*>(ev)->_title,
                    reinterpret_cast<MessageEvent*>(ev)->_text,
                    nullptr);
        dlg->exec();
        reinterpret_cast<MessageEvent*>(ev)->setAnswer(dlg->answer);
        if(main_thread_id != reinterpret_cast<MessageEvent*>(ev)->_threadId)
        {
            //continue thread work
            if(process != nullptr)
                process->Continue();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    //function for example
    process = new SomeParallelprocess();
}

