#ifndef NOTIFICATION_H
#define NOTIFICATION_H


#include <QSystemTrayIcon>
#include<QString>
class Notification
{
public:
    Notification();
    void notification_ajoutclient();
    void notification_supprimerclient();
    void notification_modifierclient();
    void notification_mail();
    void notification_pdf();


};

#endif // NOTIFICATION_H
