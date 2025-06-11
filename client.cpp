#include "client.h"
#include <QString>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QSslSocket>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
Client::Client()
{
    id="";
    nom="";
    prenom="";
    adresse="";
    num_tel="";
    mail="";
    sexe="";

}
Client::Client(QString id,QString nom,QString prenom,QString adresse,QString num_tel,QString mail,QString sexe)
{
 this->id=id;this->nom=nom;this->prenom=prenom;this->adresse=adresse;this->num_tel=num_tel;this->mail=mail;this->sexe=sexe;
}
QString Client:: getid(){return id;}
QString Client:: getnom(){return nom;}
QString Client:: getprenom(){return prenom;}
QString Client:: getadresse(){return adresse;}
QString Client:: getnum_tel(){return num_tel;}
QString Client:: getmail(){return mail;}
QString Client:: getsexe(){return sexe;}

void Client:: setid(QString id){this->id=id;}
void Client:: setnom(QString nom){this->nom=nom;}
void Client:: setprenom(QString prenom){this->prenom=prenom;}
void Client:: setadresse(QString adresse){this->adresse=adresse;}
void Client:: setnum_tel(QString num_tel){this->num_tel=num_tel;}
void Client:: setmail(QString mail){this->mail=mail;}
void Client:: setsexe(QString sexe){this->sexe=sexe;}


bool Client:: ajouter ()
{
    Client C;
        if(C.is_email_valid(mail)==false){
            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                        QObject::tr(" Mail Invalid .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }



    QSqlQuery query;

          query.prepare("INSERT INTO client (id, nom, prenom,adresse,num_tel,mail,sexe) "
                        "VALUES (:id, :nom, :prenom,:adresse,:num_tel,:mail,:sexe)");
          query.bindValue(":id", id);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":num_tel", num_tel);
          query.bindValue(":mail", mail);
          query.bindValue(":sexe", sexe);


          return query.exec();

}
bool Client:: modifier ()
{
    Client C;
        if(C.is_email_valid(mail)==false){
            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                        QObject::tr(" Mail Invalid .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }
    QSqlQuery query;

          query.prepare("update client set id='"+id+"', nom='"+nom+"',prenom='"+prenom+"',adresse='"+adresse+"',num_tel='"+num_tel+"',mail='"+mail+"',sexe='"+sexe+"' where id='"+id+"'");

          query.bindValue(":id", id);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":num_tel", num_tel);
          query.bindValue(":mail", mail);
          query.bindValue(":sexe", sexe);


          return query.exec();



}

bool Client::supprimer(QString id)
{
    QSqlQuery query;

          query.prepare("Delete from client where id=:id");
          query.bindValue(0, id);


          return query.exec();

}



QSqlQueryModel* Client::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("select * from client"); 
       model->setQuery("SELECT * FROM client ORDER BY nom");



    return model;
}
QSqlQueryModel* Client::searchByid(const QString& id) {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM client WHERE id LIKE '%" + id + "%' ORDER BY nom");
    return model;
}
bool Client::idExists(const QString &id) {
    QSqlQuery query;
    query.prepare("SELECT id FROM client WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {

        return true;
    }


    return false;
}
bool Client::is_email_valid(const QString& email)
{
    // Define a regular expression pattern for email validation
    QRegularExpression regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

    // Use the regular expression to check if the email is valid
    return regex.match(email).hasMatch();
}
QSqlQuery Client::getsexestatistics() {
    QSqlQuery query;
    query.prepare("SELECT sexe, COUNT(*) FROM client GROUP BY sexe");
    query.exec();
    return query;
}
