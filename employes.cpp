#include "employes.h"
employes::employes(){
    id=0;
    nom="";
    prenom="";
    fonction="";
    date_embauche="";
    mail="";
    age=0;
    salaire=0;
    mp_rec="";
    num_tl="";
    password="";
    question="";
    status="";
}


employes::employes(QString nom,QString prenom ,QString fonction , QString date_embauche , QString mail , int id , int age ,float salaire,QString num_tl,QString password,QString mp_rec,QString question,QString status )
{
    this->password=password;
    this->nom=nom;
    this->prenom=prenom;
    this->fonction=fonction;
    this->date_embauche=date_embauche;
    this->mail=mail;
    this->num_tl=num_tl;
    this->password=password;
    this->id=id;
    this->age=age;
    this->salaire=salaire;
    this->mp_rec=mp_rec;
    this->question=question;
    this->status=status;
}


bool employes::is_email_valid(const QString& email)
{
    // Define a regular expression pattern for email validation
    QRegularExpression regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

    // Use the regular expression to check if the email is valid
    return regex.match(email).hasMatch();
}


bool employes:: ajouter ()
{



    QSqlQuery query;

    QString res=QString::number(id);
    QString ress=QString::number(age);
    //QString resss=QString::number(num_tl);
    QString ressss=QString::number(salaire);
    date_embauche=getdate();
          query.prepare("INSERT INTO EMPLOYES (id, nom, prenom,fonction,mail,salaire,age,num_tl,password,mp_rec,question,status) "
                        "VALUES (:ID, :NOM, :PRENOM,:FONCTION,:MAIL,:SALAIRE,:AGE,:NUM_TL,:PASSWORD,:MP_REC,:QUESTION,:STATUS)");
          query.bindValue(":ID", res);
          query.bindValue(":NOM", nom);
          query.bindValue(":PRENOM", prenom);
          query.bindValue(":AGE",ress);
          query.bindValue(":MAIL", mail);
          query.bindValue(":FONCTION", fonction);
          query.bindValue(":DATE_EMBAUCHE", date_embauche);
          query.bindValue(":SALAIRE",ressss);
          query.bindValue(":PASSWORD",password);
          query.bindValue(":MP_REC",mp_rec);
          query.bindValue(":NUM_TL",num_tl);
          query.bindValue(":QUESTION",question);
          query.bindValue(":STATUS",status);


          return query.exec();

}


bool employes::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM employes WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.numRowsAffected() > 0) {
        return true; // Rows were affected, so deletion was successful
    } else {
        return false; // No rows were affected, so deletion failed
    }
}


QSqlQueryModel* employes::afficher(QString tri,bool test)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    if(test){
        if(tri=="Age") model->setQuery("SELECT * FROM employes ORDER BY age ASC");
        else if(tri=="Nom") model->setQuery("SELECT * FROM employes ORDER BY nom ASC");
        else model->setQuery("select * from employes order by salaire ASC");
    }
    else{
        if(tri=="Age") model->setQuery("SELECT * FROM employes ORDER BY age DESC");
        else if(tri=="Nom") model->setQuery("SELECT * FROM employes ORDER BY nom DESC");
        else model->setQuery("select * from employes order by salaire DESC");
    }

    return model;
}


bool employes::idExists(int id){
    QSqlQuery query;
        query.prepare("SELECT * FROM employes WHERE id = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {

            nom=query.value(1).toString();
            prenom=query.value(2).toString();
            fonction=query.value(3).toString();
            salaire=query.value(4).toString().toFloat();
            date_embauche=query.value(5).toString();
            age=query.value(6).toString().toInt();
            mail=query.value(7).toString();
            num_tl=query.value(8).toString();
            password=query.value(9).toString();
            mp_rec=query.value(10).toString();
            question=query.value(11).toString();

            return true;
        }
        return false;
}


bool employes::modifier(){
    if(age<18 or age>60) {
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                    QObject::tr(" 17<Age<61 .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    /*if(num_tl<10000000 or num_tl>99999999) {
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                    QObject::tr(" Numero incorrect  .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }*/
    if(salaire<1000 or salaire>3000) {
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                    QObject::tr(" 1000<Salaire<3000 .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    //std::string strmail=mail.toStdString();
    employes e ;
    if(e.is_email_valid(mail)==false){
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                    QObject::tr(" Mail Invalid .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }



       QSqlQuery query;
       QString idStr = QString::number(id);
       QString ageStr = QString::number(age);
       QString salaireStr = QString::number(salaire);
       //QString num_tlStr = QString::number(num_tl);

       query.prepare("update employes set id='"+idStr+"', nom='"+nom+"',prenom='"+prenom+"',fonction='"+fonction+"',num_tl='"+num_tl+"',mail='"+mail+"',age='"+ageStr+"',date_embauche='"+date_embauche+"',salaire='"+salaireStr+"',password='"+password+"' where id='"+idStr+"'");
       query.bindValue(":ID",idStr);
       query.bindValue(":NOM", nom);
       query.bindValue(":PRENOM", prenom);
       query.bindValue(":AGE", ageStr);
       query.bindValue(":MAIL", mail);
       query.bindValue(":FONCTION", fonction);
       query.bindValue(":DATE_EMBAUCHE", date_embauche);
       query.bindValue(":SALAIRE", salaireStr);
       query.bindValue(":NUM_TL", num_tl);
       query.bindValue(":PASSWORD",password);


       return query.exec();
}


bool employes::check_login(QString mpd, int id_login){
    if(idExists(id_login)){
        if (mpd==getpass())
            return true;
    }
    return false;
}
QSqlQueryModel* employes::afficherEmployeParId(const int &id)
{

    QString idStr = QString::number(id);
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes WHERE id LIKE '%" + idStr + "%' ORDER BY nom");
        return model;

}
