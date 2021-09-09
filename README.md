# QT-parallel-thread-message-call
It's simple project to help anyone call create ui in Qt from parralel thread. 
Use of class inheriring QEvent library is the cornerstone of the project.
```C++
class MessageEvent: public QEvent
{
public: 
  enum {MessageType = User +1};
  QString _title, _text;
  int _type, answer;
  std::thread::id _threadId;
 
  MessageEvent():QEvent((Type)MessageType){ } 
  // parametrs for show message  
  void gui_launcher(QString title,QString text,int type){
           _title = title; 
           _text = text;
           _type = type;
           answer = 0;
           _threadId = std::this_thread::get_id();
  }
  // any functions for transfer values
  void setAnswer(int _answer){
           answer = _answer; 
  }
};
```
This code allows to catch a signal on display from function:
```C++
void MainWindow::customEvent(QEvent *ev)
{
  //call event
  if((int)ev->type() == MessageEvent::MessageType){ 
    MessageDialog *dlg = new MessageDialog( reinterpret_cast<MessageEvent*>(ev)->_title, reinterpret_cast<MessageEvent*>(ev)->_text, nullptr);
    dlg->exec();
    reinterpret_cast<MessageEvent*>(ev)->setAnswer(dlg->answer);
    //check thread id    
    if(main_thread_id != reinterpret_cast<MessageEvent*>(ev)->_threadId)
      { 
        //continue thread work 
        if(process != nullptr)
           process->Continue();
      } 
   }
}
```
For a call of gui static function is used
```C++
static MessageEvent* MessageBox(QString _text,QString _title, int _type){
 MainWindow* pApp = MainWindow::getApp();
 MessageEvent* _messageEvent = new MessageEvent();
 _messageEvent->gui_launcher(_title,_text,_type);
 std::thread::id this_thread_id = std::this_thread::get_id();
 if(pApp->main_thread_id != this_thread_id){
    QCoreApplication::postEvent(pApp,_messageEvent);
    if(pApp->process != nullptr){ 
       //puase thread for show gui message 
       pApp->process->stopedThread = true;
       pApp->process->Pause();
    }
 } 
 else{
    //call event if main thread
    pApp->customEvent(_messageEvent); 
 } 
 return _messageEvent;
}
```
