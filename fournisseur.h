#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>

#include<QSqlQueryModel>

class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(QString,int,QString,QString,QString,QString,QString);

    QString getid_fournisseur();
    int getcode_postale();
    QString getnum_telephone();
    QString getnom_entreprise();
    QString getadresse();
    QString getadresse_email();
    QString gettype();

    void setid_fournisseur(QString);
    void setcode_postale(int);
    void setnum_telephone(QString);
    void setnom_entreprise(QString);
    void setadresse(QString);
    void setadresse_email(QString);
    void settype(QString);
    bool ajouter();
   QSqlQueryModel*afficher();
   bool supprimer(QString);
   bool modifier();
   bool idExists(const QString &);
   bool nom_Exists(const QString &);
   QSqlQueryModel* afficheFournissuerParnom(const QString &);




private:
   int code_postale;
   QString nom_entreprise,adresse,adresse_email,type,id_fournisseur,num_de_telephone;

};

#endif // FOURNISSEUR_H
