#ifndef MESSAGEEVENT_H
#define MESSAGEEVENT_H

#include <QEvent>
#include <QString>
#include <thread>

class MessageEvent: public QEvent
{
public:
    enum {MessageType = User +1};
    QString _title, _text;
    int _type, answer;
    std::thread::id _threadId;

    MessageEvent():QEvent((Type)MessageType){

    }
    // parametrs for show message
    void gui_launcher(QString title,QString text,int type){
       _title = title;
       _text = text;
       _type = type;
       answer = 0;
       _threadId = std::this_thread::get_id();
    }
    void setAnswer(int _answer){
        answer = _answer;
    }
};

#endif // MESSAGEEVENT_H
