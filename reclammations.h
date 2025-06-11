#ifndef RECLAMMATIONS_H
#define RECLAMMATIONS_H

#include <QSqlQueryModel>
#include <QString>
#include <QDate>

using namespace std;
class reclammations
{
private:
    int ID_reclammations;
    QDate date_achat,date_rec,date_rep;
    QString  mail_client,etat,description;


public:
    //constructeurs:
    reclammations();
    reclammations(int,QDate,QDate,QDate,QString,QString,QString);


    //setters
    void setMail(QString );
    void setEtat(QString );
    void setDescription(QString );
    void setDate_achat(QDate );
    void setDate_rec(QDate );
    void setDate_rep(QDate );
    void setID_reclammations(int );

    //getters:
    QString getMail();
    QString getEtat();
    QString getDescription();
    QDate getDate_achat();
    QDate getDate_rec();
    QDate getDate_rep();
    int getID_reclammations();


    //LES FONCTIONS :
        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(int );
        bool modifier();
        QSqlQueryModel * affichertrie(QString );
        //QSqlQueryModel *  affichertrie(QString ch);
        QSqlQueryModel* afficherrecETAT(const QString &);
        bool etatExiste(QString &);

};

#endif // RECLAMMATIONS_H
