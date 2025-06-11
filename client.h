#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <regex>
#include <QRegularExpression>
#include<QSslSocket>
class Client
{
public:
    Client();
    Client(QString,QString,QString,QString,QString,QString,QString);
    QString getid();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getnum_tel();
    QString getmail();
    QString getsexe();

    void setid(QString);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setnum_tel(QString);
    void setmail(QString);
    void setsexe(QString);

    bool ajouter();
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* searchByid(const QString& id);
    bool supprimer(QString);
    bool idExists(const QString &id);
    bool is_email_valid(const QString& email);
    QSqlQuery getsexestatistics();


private:

    QString nom,prenom,adresse,mail,sexe,id,num_tel;

};

#endif // CLIENT_H
