#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QChar>

#include <qdebug.h>
#include <QMessageBox>
#include <regex>
#include <QRegularExpression>
#include <string>
#include "qsqlerror.h"

class employes
{
private :
    QString  nom , prenom , fonction , date_embauche , mail ,mp_rec,password,num_tl,question,status;
    int id ,age;
    float salaire;
public:
        employes();
        employes(QString, QString, QString, QString,  QString, int, int,  float,QString,QString,QString,QString,QString );
        //Getters
        QString getnom(){return nom;}
        QString getprenom(){return prenom;}
        QString getfonction(){return fonction;}
        QString getdate(){return date_embauche;}
        QString getmail(){return mail;}
        QString getpass(){return password;}
        QString getreponse(){return mp_rec;}
        int getid(){return id;}
        int getage(){return age;}
        QString getnum(){return num_tl;}
        float getsalaire(){return salaire;}
        QString getquestion(){return question;}
        QString getstatus(){return status;}

        //Setters
        void setnom(QString n){ nom=n ;}
        void setprenom(QString p){ prenom=p ;}
        void setfonction(QString f){ fonction=f ;}
        void setdate(QString d){ date_embauche=d ;}
        void setmail(QString m){ mail=m ;}
        void setpass(QString mp){ password=mp ;}
        void setreponse(QString v){mp_rec = v;}
        void setid(int i){ id=i ;}
        void setage(int a){ age=a ;}
        void setnum(QString nu){ num_tl=nu ;}
        void setquestion(QString q){question=q;}
        void setsalaire(float s){salaire=s;}
        void setstatus(float st){salaire=st;}

        //Fonction BD
        bool ajouter();
        bool modifier();
        QSqlQueryModel* afficher(QString tri,bool test);
        bool supprimer(int);
        bool idExists(int id);
        bool is_email_valid(const QString& email);
        bool check_login(QString mpd, int id_login);

        QSqlQueryModel* afficherEmployeParId(const int &);


};

#endif // EMPLOYES_H
