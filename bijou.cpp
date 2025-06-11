#include "bijou.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

#include "QZXing.h"
#include <QJsonObject>
#include <QJsonDocument>

Bijou::Bijou()
{
id=""; stock=0; matiere=" "; type=" "; garantie=" "; prix=""; codebox=0;
}
Bijou::Bijou(QString id,int stock,QString type,QString matiere,QString garantie,QString prix,QByteArray imageData, int codebox)
{
    this->id=id;
    this->stock=stock;
     this->codebox=codebox;
    this->type=type;
    this->matiere=matiere;
    this->prix=prix;
    this->garantie=garantie;
    this->imageData = imageData;
}
QString Bijou::getid(){return id;}
int Bijou::getstock(){return stock;}
int Bijou::getcodebox(){return codebox;}
QString Bijou::getmatiere(){return matiere;}
QString Bijou::gettype(){return type;}
QString Bijou::getgarantie(){return garantie;}
QString Bijou::getprix(){return prix;}
QByteArray Bijou::getImageData() const{return imageData;}

void Bijou::setid(QString id){this->id=id;}
void Bijou::setstock(int stock){this->stock=stock;}
void Bijou::setcodebox(int codebox){this->codebox=codebox;}
void Bijou::setmatiere(QString matiere){this->matiere=matiere;}
void Bijou::settype(QString type){this->type=type;}
void Bijou::setgarantie(QString garantie){this->garantie=garantie;}
void Bijou::setprix(QString prix){this->prix=prix;}
void Bijou::setImageData(const QByteArray &data){imageData = data;}

bool Bijou::ajouter()
{
    QSqlQuery query;
    QString stock_string=QString::number(stock);
     QString codebox_string=QString::number(codebox);

          query.prepare("INSERT INTO BIJOUX (ID_BIJOU, STOCK, TYPE, MATIERE, PRIX, GARANTIE, IMAGE_DATA, CODEBOX) "
                        "VALUES (:ID_BIJOU,:STOCK,:TYPE,:MATIERE,:PRIX,:GARANTIE, :IMAGE_DATA, :CODEBOX)");
          query.bindValue(":ID_BIJOU", id);
          query.bindValue(":STOCK", stock_string);
          query.bindValue(":TYPE", type);
          query.bindValue(":MATIERE", matiere);
          query.bindValue(":PRIX", prix);
          query.bindValue(":GARANTIE", garantie);
          query.bindValue(":IMAGE_DATA", imageData);  // Bind the image data QByteArray
          query.bindValue(":CODEBOX", codebox_string);

          return query.exec();
}
QSqlQueryModel* Bijou::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM BIJOUX");
    return model;
}
bool Bijou::supprimer(QString id)
{
    QSqlQuery query;

    query.prepare("Delete from BIJOUX where ID_BIJOU=:id");
    query.bindValue(0, id);

    return query.exec();
}
bool Bijou:: modifier()
{
    QSqlQuery query;
    QString stock_string=QString::number(stock);
    QString codebox_string=QString::number(codebox);

          query.prepare("UPDATE BIJOUX SET STOCK = :STOCK, TYPE = :TYPE, MATIERE = :MATIERE, PRIX = :PRIX, GARANTIE = :GARANTIE, IMAGE_DATA = :IMAGE_DATA, CODEBOX = :CODEBOX WHERE ID_BIJOU = :ID_BIJOU");
          query.bindValue(":ID_BIJOU", id);
          query.bindValue(":STOCK", stock_string);
          query.bindValue(":TYPE", type);
          query.bindValue(":MATIERE", matiere);
          query.bindValue(":PRIX", prix);
          query.bindValue(":GARANTIE", garantie);
          query.bindValue(":IMAGE_DATA", imageData);
          query.bindValue(":CODEBOX", codebox_string);
     return query.exec();

}
bool Bijou::idExists(const QString &id)
{
    QSqlQuery query;
    query.prepare("SELECT ID_BIJOU FROM BIJOUX WHERE ID_BIJOU=:id");
    query.bindValue(":id", id);

    if (query.exec() && query.next())
    {
        // If a row is fetched, the ID exists in the database.
        return true;
    }

    // If no rows were fetched, the ID does not exist.
    return false;
}

QSqlQueryModel* Bijou::afficherBijouParId(const QString &id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM BIJOUX WHERE ID_BIJOU=:id");
    query.bindValue(":id", id);

    if (query.exec()) {
        model->setQuery(query);
    }

    return model;
}
QImage Bijou::generateQRCode(const QString &id,const int stock, const QString &type, const QString &matiere, const QString &garantie, const QString &prix)
{
    // Create a JSON object with bijou details
    QJsonObject bijouDetails;
    bijouDetails["id"] = id;
    bijouDetails["stock"] = stock;
    bijouDetails["type"] = type;
    bijouDetails["matiere"] = matiere;
    bijouDetails["garantie"] = garantie;
    bijouDetails["prix"] = prix;

    // Convert JSON object to string
    QJsonDocument doc(bijouDetails);
    QString data = QString::fromUtf8(doc.toJson());

    // Generate QR code using QZXing
    QImage img = QZXing::encodeData(data);

    if (img.isNull()) {
        qDebug() << "Error: Failed to generate QR code for bijou with ID: " << id;
    }

    return img;
}

QImage Bijou::getImageBijouById(const QString &id)
{
    QSqlQuery query;
    query.prepare("SELECT IMAGE_DATA FROM BIJOUX WHERE ID_BIJOU = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QByteArray imageData = query.value(0).toByteArray();
        QImage image;
        image.loadFromData(imageData);
        return image;
    }

    return QImage();
}

QStringList Bijou::getListeIdBijoux()
{
    QStringList listeIdBijoux;

    QSqlQuery query("SELECT ID_BIJOU FROM BIJOUX");
    while (query.next()) {
        QString id = query.value(0).toString();
        listeIdBijoux.append(id);
    }

    return listeIdBijoux;
}


bool Bijou::boxExists(int code)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM BIJOUX WHERE codebox=:codebox");
    query.bindValue(":codebox", code);

    if (query.exec() && query.next())
    {
        stock=query.value(1).toInt();
        qDebug()<<"stock    :"<<stock;
            QString strage=QString::number(stock);
            QString strcode=QString::number(code);
            query.prepare("UPDATE BIJOUX SET STOCK = '"+strage+"' WHERE codebox = '"+strcode+"'");

            query.bindValue(":STOCK", strage);

            query.exec();

        // If a row is fetched, the ID exists in the database.
        return true;
    }

    // If no rows were fetched, the ID does not exist.
    return false;
}

bool Bijou::quantite(int q,int b){
    QSqlQuery query;
    query.prepare("SELECT * FROM BIJOUX WHERE codebox=:codebox");
    query.bindValue(":codebox", b);

    if (query.exec() && query.next())
    {
        if(getstock()>=q&&getstock()!=0){

            stock=query.value(1).toInt()-q;
            qDebug()<<"stock    :"<<stock;
                QString strage=QString::number(stock);
                QString strcode=QString::number(b);
                query.prepare("UPDATE BIJOUX SET STOCK = '"+strage+"' WHERE codebox = '"+strcode+"'");

                query.bindValue(":STOCK", strage);

                query.exec();
            return true;
        }

     }

    return false;
}

