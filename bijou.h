#ifndef BIJOU_H
#define BIJOU_H

#include <QString>
#include <QSqlQueryModel>

class Bijou
{
private:
    int stock,codebox;
    QString id,matiere,type,garantie,prix;
    QByteArray imageData;

public:
    Bijou();
    Bijou(QString,int,QString,QString,QString,QString,QByteArray,int);

    QString getid();
    int getstock();
    int getcodebox();
    QString getmatiere();
    QString gettype();
    QString getgarantie();
    QString getprix();
    QByteArray getImageData() const;

    void setid(QString);
    void setstock(int);
    void setcodebox(int);
    void setmatiere(QString);
    void settype(QString);
    void setgarantie(QString);
    void setprix(QString);
    void setImageData(const QByteArray &data);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier();
    bool idExists(const QString &id);
    bool boxExists(int code);
    bool quantite(int q,int b);
    //recherche
    QSqlQueryModel* afficherBijouParId(const QString &);

    QImage generateQRCode(const QString &,const int , const QString &, const QString &, const QString &, const QString &);

    QImage getImageBijouById(const QString &id);

    QStringList getListeIdBijoux();

};

#endif // BIJOU_H
