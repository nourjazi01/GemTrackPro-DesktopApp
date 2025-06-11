#include "fournisseur.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Fournisseur::Fournisseur()
{
    id_fournisseur="";
    code_postale=0;
    num_de_telephone="";
    nom_entreprise="";
    adresse="";
    adresse_email="";
    type="";
}

Fournisseur::Fournisseur(QString id_fournisseur,int code_postale,QString num_de_telephone ,QString nom_entreprise ,QString adresse ,QString adresse_email,QString type)
{
    this->id_fournisseur=id_fournisseur;
    this->code_postale=code_postale;
    this->num_de_telephone=num_de_telephone;
    this->nom_entreprise=nom_entreprise;
    this->adresse=adresse;
    this->adresse_email=adresse_email;
    this->type=type;
}
QString Fournisseur:: getid_fournisseur(){return id_fournisseur;}
int Fournisseur:: getcode_postale() {return  code_postale;}
QString Fournisseur ::getnum_telephone(){ return num_de_telephone;}
QString Fournisseur:: getnom_entreprise(){return nom_entreprise;}
QString Fournisseur :: getadresse(){return adresse;}
QString Fournisseur ::getadresse_email(){return adresse_email;}
QString Fournisseur::gettype(){return type;}
void Fournisseur::setid_fournisseur(QString id_fournisseur){this->id_fournisseur=id_fournisseur;}
void Fournisseur::setcode_postale(int code_postale){this->code_postale=code_postale;}
void Fournisseur::setnum_telephone(QString num_de_telephone){this->num_de_telephone=num_de_telephone;}
void Fournisseur::setnom_entreprise(QString nom_entreprise){this->nom_entreprise=nom_entreprise;}
void Fournisseur::setadresse(QString adresse){this->adresse=adresse;}
void Fournisseur::setadresse_email(QString adresse_email){this->adresse_email=adresse_email;}
void Fournisseur::settype(QString type){this->type=type;}

/*****************Ajouter*******************/

bool Fournisseur::ajouter()
{
    QSqlQuery query;
    QString codepostale_string= QString::number(code_postale);
          query.prepare("INSERT INTO FOURNISSEUR (ID_FOURNISSEUR,TYPE,NOM_ENTREPRISE,ADRESSE,CODE_POSTALE,NUM_DE_TELEPHONE, ADRESSE_EMAIL ) "
                        "VALUES (:ID_FOURNISSEUR,:TYPE,:NOM_ENTREPRISE,:ADRESSE,:CODE_POSTALE,:NUM_DE_TELEPHONE, :ADRESSE_EMAIL )");
          query.bindValue(":ID_FOURNISSEUR", id_fournisseur);
          query.bindValue(":TYPE",type);
          query.bindValue(":NOM_ENTREPRISE",nom_entreprise);
          query.bindValue(":ADRESSE", adresse);
          query.bindValue(":CODE_POSTALE", codepostale_string);
          query.bindValue(":NUM_DE_TELEPHONE",num_de_telephone);
          query.bindValue(":ADRESSE_EMAIL",adresse_email);


return query.exec();
}




/*******************Supprimer*********************/

bool Fournisseur::supprimer(QString id_fournisseur)
{
    QSqlQuery query;
          query.prepare("Delete from FOURNISSEUR where ID_FOURNISSEUR=:id_fournisseur ");
          query.bindValue(0, id_fournisseur);



return query.exec();


}


/**********************Affichage******************/

QSqlQueryModel* Fournisseur ::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM FOURNISSEUR");
    return model;
}




/***********Modifier**************/


bool Fournisseur:: modifier()
{
    QSqlQuery query;
    QString codepostale_string= QString::number(code_postale);

          query.prepare("UPDATE FOURNISSEUR SET NUM_DE_TELEPHONE= :NUM_DE_TELEPHONE , ADRESSE_EMAIL =:ADRESSE_EMAIL, TYPE = :TYPE, NOM_ENTREPRISE = :NOM_ENTREPRISE, ADRESSE = :ADRESSE,CODE_POSTALE = :CODE_POSTALE  WHERE ID_FOURNISSEUR= :ID_FOURNISSEUR");
          query.bindValue(":NUM_DE_TELEPHONE",num_de_telephone);
          query.bindValue(":ADRESSE_EMAIL",adresse_email);
          query.bindValue(":TYPE", type);
          query.bindValue(":NOM_ENTREPRISE",nom_entreprise);
          query.bindValue(":ADRESSE",adresse);
          query.bindValue(":CODE_POSTALE",codepostale_string);
          query.bindValue(":ID_FOURNISSEUR", id_fournisseur);


     return query.exec();

}



/*******Contorle saisie de l'existance de ID***********/

bool Fournisseur::idExists(const QString &id_fournisseur)
{
    QSqlQuery query;
    query.prepare("SELECT ID_FOURNISSEUR FROM FOURNISSEUR WHERE ID_FOURNISSEUR=:id_fournisseur");
    query.bindValue(":id_fournisseur", id_fournisseur);

    if (query.exec() && query.next())
    {
        // If a row is fetched, the ID exists in the database.
        return true;
    }

    // If no rows were fetched, the ID does not exist.
    return false;
}


bool Fournisseur::nom_Exists(const QString &nom_entreprise)
{
    QSqlQuery query;
    query.prepare("SELECT ID_FOURNISSEUR FROM FOURNISSEUR WHERE NOM_ENTREPRISE=:nom_entreprise");
    query.bindValue(":nom_entreprise", nom_entreprise);

    if (query.exec() && query.next())
    {
        // If a row is fetched, the ID exists in the database.
        return true;
    }

    // If no rows were fetched, the ID does not exist.
    return false;
}


QSqlQueryModel* Fournisseur::afficheFournissuerParnom(const QString &nom_entreprise)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FOURNISSEUR WHERE NOM_ENTREPRISE=:nom_entreprise");
    query.bindValue(":nom_entreprise", nom_entreprise);

    if (query.exec()) {
        model->setQuery(query);
    }

    return model;
}





