#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QObject>
#include "reclammations.h"
#include <QString>
#include <QPainter>
#include <string>
#include <iostream>
reclammations::reclammations()
{
    ID_reclammations=0;
    date_achat=QDate();
    date_rec=QDate();
    date_rep=QDate();
    mail_client="";
    etat="";
    description="";

}

reclammations::reclammations(int ID_reclammations,QDate date_achat,QDate date_rec,QDate date_rep,QString mail_client,QString etat,QString description)
{
    this->ID_reclammations=ID_reclammations;
   this->date_achat=date_achat;
    this->date_rec=date_rec;
    this->date_rep=date_rep;
    this->mail_client=mail_client;
    this->etat=etat;
    this->description=description;


}
//getters:
QString reclammations::getMail(){return mail_client;}
QString reclammations::getEtat(){return etat;}
QString reclammations::getDescription(){return description;}
QDate reclammations::getDate_achat(){return date_achat;}
QDate reclammations::getDate_rec(){return date_rec;}
QDate reclammations::getDate_rep(){return date_rep;}
int reclammations::getID_reclammations(){return ID_reclammations;}

//setters
void reclammations::setMail(QString m){mail_client=m;}
void reclammations::setEtat(QString e){etat=e;}
void reclammations::setDescription(QString d){description=d;}
void reclammations::setDate_achat(QDate da){ date_achat=da;}
void reclammations::setDate_rec(QDate drec){date_rec=drec;}
void reclammations::setDate_rep(QDate dr){date_rep=dr;}
void reclammations::setID_reclammations(int id){ ID_reclammations=id;}


bool reclammations::ajouter()
{

 QSqlQuery query ;
 QString res=QString::number(ID_reclammations);
 QString res1=date_achat.toString(Qt::ISODate);
 QString res2=date_rec.toString(Qt::ISODate);
 QString res3=date_rep.toString(Qt::ISODate);




 //prepare() prend la requete en parametre pour la preparer a l execusion:
 query.prepare("INSERT INTO GS_RECLAMMATIONS (ID_RECLAMMATIONS,DATE_ACHAT,DATE_REC,DATE_REP,MAIL_CLIENT,ETAT,DESCRIPTION)  "
               "VALUES (:ID_RECLAMMATIONS,:DATE_ACHAT,:DATE_REC,:DATE_REP,:MAIL_CLIENT,:ETAT,:DESCRIPTION)");

 // creation des variables liees :
  query.bindValue(0,res);
  query.bindValue(1,date_achat);
  query.bindValue(2,date_rec);
  query.bindValue(3,date_rep);
  query.bindValue(4,mail_client);
  query.bindValue(5,etat);
  query.bindValue(6,description);

  return query.exec();

}


QSqlQueryModel* reclammations::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM GS_RECLAMMATIONS ");
        return model;
}

bool reclammations::supprimer(int ID_reclammations)
{
    QString res=QString::number(ID_reclammations);

        QSqlQuery query;
        query.prepare("delete from GS_RECLAMMATIONS where ID_RECLAMMATIONS= :ID_reclammations");
        query.bindValue(0,res );
        return query.exec();
}

bool reclammations::modifier()
{
    QString res=QString::number(ID_reclammations);
    QString res1=date_achat.toString(Qt::ISODate);
    QString res2=date_rec.toString(Qt::ISODate);
    QString res3=date_rep.toString(Qt::ISODate);
    /*checkQuery.prepare("SELECT ID_RECLAMMATIONS FROM GS_RECLAMMATIONS WHERE ID_RECLAMMATIONS= :ID_RECLAMMATIONS");
   checkQuery.bindValue(0,ID_reclammations);*/
   QSqlQuery query ;

   query.prepare("UPDATE GS_RECLAMMATIONS SET DATE_ACHAT= '"+res1+"', DATE_REC='"+res2+"', DATE_REP='"+res3+"', MAIL_CLIENT= '"+mail_client+"', ETAT= '"+etat+"', DESCRIPTION= '"+description+"' WHERE ID_RECLAMMATIONS= '"+res+"'");
   query.bindValue(0,res);
   query.bindValue(1,date_achat);
   query.bindValue(2,date_rec);
   query.bindValue(3,date_rep);
   query.bindValue(4,mail_client);
   query.bindValue(5,etat);
   query.bindValue(6,description);
    return query.exec();


}

QSqlQueryModel* reclammations::afficherrecETAT(const QString &etat)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM GS_RECLAMMATIONS  WHERE ETAT=:ETAT");
    query.bindValue(":ETAT", etat);

    if (query.exec()) {
        model->setQuery(query);
    }

    return model;
}

bool reclammations::etatExiste(QString &etat)
{
    QSqlQuery query;
    query.prepare("SELECT ETAT FROM GS_RECLAMMATIONS WHERE ETAT=ETAT");
    query.bindValue(":ETAT", etat);

    if (query.exec() && query.next())
    {
        // If a row is fetched, the ID exists in the database.
        return true;
    }

    // If no rows were fetched, the ID does not exist.
    return false;
}
