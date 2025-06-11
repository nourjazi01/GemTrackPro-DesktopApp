#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlQuery>
#include <QRegExpValidator>
#include <QtCharts>
#include "suppwindow.h"
#include "modifier.h"
#include <qsharedpointer.h>
#include <QSharedPointer>
#include "oublie.h"
#include <QSystemTrayIcon>
#include<QString>
#include <QSerialPort>
#include <QDebug>
#include <QCoreApplication>
#include <QPrinter>
#include "smtp.h"
#include "client.h"
#include "fournisseur.h"
#include <QDate>
#include <QMediaPlayer>
#include <QSound>
#include <QUrl>
#include <QUrlQuery>
 #include <QtNetwork>


enum class State {
    WaitingForBoxCode,
    WaitingForQuantite,
    WaitingForClosing,
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QIcon icon("C:/Users/USER/Desktop/Atelier_Connexion/logo app.png");
          this->setWindowIcon(icon);
        this->setWindowTitle("GemTrack Pro");

    ui->logout->hide();
    ui->home->hide();
    ui->frame_gestion->hide();
    ui->stackedWidget->hide();
    ui->login_id->setPlaceholderText("ID");
    ui->frame_inside_gestion->hide();
    ui->login_pass->setPlaceholderText("MOT DE PASSE");
    QRegExp regex("[a-zA-Z]+");
    ui->emp_id->setValidator( new QIntValidator(0, 1000, this) );
    ui->emp_age->setValidator( new QIntValidator(18, 60, this) );
    ui->emp_salaire->setValidator( new QIntValidator(1000, 3000, this) );
    //ui->num_tl->setValidator( new QIntValidator(10000000, 99999999, this) );
    ui->emp_nom->setValidator(new QRegExpValidator(regex));
    ui->id->setValidator( new QIntValidator(0, 1000, this) );
    ui->age->setValidator( new QIntValidator(18, 60, this) );
    ui->salaire->setValidator( new QIntValidator(1000, 3000, this) );
    //ui->numero_tl->setValidator( new QIntValidator(10000000, 99999999, this) );
    ui->nom->setValidator(new QRegExpValidator(regex));
    ui->prenom->setValidator(new QRegExpValidator(regex));
    ui->emp_prenom->setValidator(new QRegExpValidator(regex));
    ui->emp_tableView->setModel(e.afficher(ui->emp_Tri_comboBox->currentText(),true));

//-------------------------------------------------BIJOUX----------------------------------------------------------

    ui->tab_bijoux->setModel(B.afficher());

    QRegExp rxCodebox("^[0-9]{1,3}$");
        QRegExpValidator *validatorCodebox = new QRegExpValidator(rxCodebox, this);
        ui->GBle_code->setValidator(validatorCodebox);
        ui->GBle_code_modif->setValidator(validatorCodebox);

    QRegExp rx("^[A-Za-z0-9]{1,10}$");
    QRegExpValidator *validatore = new QRegExpValidator(rx, this);
    ui->GBle_id->setValidator(validatore);

    //tri
    /*GBproxyModel = new QSortFilterProxyModel(this);
    GBproxyModel->setSourceModel(B.afficher());
    ui->tab_bijoux->setModel(GBproxyModel);*/

    connect(ui->tab_bijoux->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(afficherInfoBijou(QModelIndex)));
    connect(ui->GBselect_image , SIGNAL(clicked()), this, SLOT(on_GBselect_image_clicked()));
    connect(ui->GBselect_image_modif , SIGNAL(clicked()), this, SLOT(on_GBselect_image_modif_clicked()));
    connect(ui->GBpb_tri, SIGNAL(clicked()), this, SLOT(on_GBpb_tri_clicked()));
    connect(ui->GBpb_rechercher, SIGNAL(clicked()), this, SLOT(on_GBpb_rechercher_clicked()));
    connect(ui->GBpb_generer, SIGNAL(clicked()), this, SLOT(on_GBpb_generer_clicked()));


//-------------------------------------------------CLIENTS----------------------------------------------------------



    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
        connect(ui->browse, SIGNAL(clicked()), this, SLOT(browse()));
        ui->tab_client->setModel(C.afficher());
        generatesexestatistics();


        connect(ui->tab_client, &QTableView::clicked, this, &MainWindow::afficherinfoclient);
        QRegExp rxe("^[A-Za-z0-9]{1,10}$");
        QRegExpValidator *validator = new QRegExpValidator(rxe, this);
        ui->gc_id->setValidator(validator);
        ui->gc_id_modif->setValidator(validator);

            ui->gc_nom->setValidator(new QRegExpValidator(regex));
            ui->gc_prenom->setValidator(new QRegExpValidator(regex));
            ui->gc_nom_modif->setValidator(new QRegExpValidator(regex));
            ui->gc_prenom_modif->setValidator(new QRegExpValidator(regex));
            QRegExp rgex("^\\+216\\d{8}$");

            QValidator *valid = new QRegExpValidator(rgex, this);
             ui->gc_num->setValidator(valid);
            ui->gc_num->setPlaceholderText("+216");

            ui->gc_num_modif->setValidator(valid);
           ui->gc_num_modif->setPlaceholderText("+216");
           ui->gc_rechercher->setPlaceholderText("Donner l'ID");



//-------------------------------------------------FOURNISSEURS----------------------------------------------------------


           triAscendant = true;
                ui->tab_fournisseur->setModel(F.afficher());
           //**********controle saisie de id***************
               // Créez un QRegExpValidator avec l'expression régulière appropriée
               QRegExp GFrx("^[A-Za-z0-9]{1,10}$");
               QRegExpValidator *GFvalidator = new QRegExpValidator(GFrx, this);
               ui->GFle_id->setValidator(GFvalidator);




               //*************controle saisie de mail******************


                   connect(ui->GFl_email, &QLineEdit::editingFinished, [this]() {
                       QString email = ui->GFl_email->text();
                       QRegExp rxEmail("[A-Za-z0-9.]{1,30}@[A-Za-z.]{1,30}$");

                       if (email.isEmpty()) {
                           // Adresse e-mail est vide
                           QMessageBox::critical(this, "Validation échouée", "Veuillez entrer une adresse e-mail.");
                       } else if (email.length() > 30) {
                           // Adresse e-mail dépasse la taille maximale
                           QMessageBox::critical(this, "Validation échouée", "Adresse e-mail dépasse la taille maximale de 30 caractères. Veuillez entrer une adresse e-mail valide de 30 caractères ou moins.");
                       } else if (!email.contains('@')) {
                           // Adresse e-mail ne contient pas le symbole "@"
                           QMessageBox::critical(this, "Validation échouée", "Veuillez inclure le symbole '@' dans l'adresse e-mail.");
                       } else if (!rxEmail.exactMatch(email)) {
                           // Adresse e-mail contient des caractères non autorisés
                           QMessageBox::critical(this, "Validation échouée", "Adresse e-mail non valide. Veuillez entrer une adresse e-mail valide.");
                       } else {
                           // Adresse e-mail valide
                           QMessageBox::information(this, "Validation réussie", "Adresse e-mail valide.");
                       }
                   });


               //*************controle saisie de mail_modifer******************
                   connect(ui->GFl_email_m, &QLineEdit::editingFinished, [this]() {
                       QString email_m = ui->GFl_email_m->text();
                       QRegExp rxEmail("[A-Za-z0-9.]{1,30}@[A-Za-z.]{1,30}$");

                       if (email_m.isEmpty()) {
                           // Adresse e-mail_m est vide
                           QMessageBox::critical(this, "Validation échouée", "Veuillez entrer une adresse e-mail.");
                       } else if (email_m.length() > 30) {
                           // Adresse e-mail_m dépasse la taille maximale
                           QMessageBox::critical(this, "Validation échouée", "Adresse e-mail dépasse la taille maximale de 30 caractères. Veuillez entrer une adresse e-mail valide de 30 caractères ou moins.");
                       } else if (!email_m.contains('@')) {
                           // Adresse e-mail_m ne contient pas le symbole "@"
                           QMessageBox::critical(this, "Validation échouée", "Veuillez inclure le symbole '@' dans l'adresse e-mail.");
                       } else if (!rxEmail.exactMatch(email_m)) {
                           // Adresse e-mail_m contient des caractères non autorisés
                           QMessageBox::critical(this, "Validation échouée", "Adresse e-mail non valide. Veuillez entrer une adresse e-mail valide.");
                       } else {
                           // Adresse e-mail_m valide
                           QMessageBox::information(this, "Validation réussie", "Adresse e-mail valide.");
                       }
                   });

           //******************controle saise de code postale*********/
               QRegExp rxCodePostal("^[0-9]{1,4}$");
               QRegExpValidator *validatorCodePostal = new QRegExpValidator(rxCodePostal, this);
               ui->GFle_code_postale->setValidator(validatorCodePostal);
           //******************controle saise de code postale_modifier*********/
               ui->GFle_code_postale_m->setValidator(validatorCodePostal);

              /*****tri par codepostale**********/
               proxyModel = new QSortFilterProxyModel(this);
                   proxyModel->setSourceModel(F.afficher());
                   ui->tab_fournisseur->setModel(proxyModel);
           connect(ui->GFpb_trier, SIGNAL(clicked()), this, SLOT(on_GFpb_trier_clicked()));


           //*******************controle saise de nom entreprise **********/
               // Créez un QRegExpValidator avec le motif pour le nom
               QRegExp rxNom("^[A-Za-z]{1,10}$");  // Le nom doit comporter de 1 à 10 lettres minuscules ou majuscules
               QRegExpValidator *validatorNom = new QRegExpValidator(rxNom, this);
               ui->GFle_nom->setValidator(validatorNom);
           //*******************controle saise de nom entreprise_modifier **********/
               ui->GFle_nom_m->setValidator(validatorNom);



           //*************controle saise de num telephone************/

                        QRegExp rxTelephone("^[2-5|7|9]\\d{0,7}$");
                        QRegExpValidator *validatorTelephone = new QRegExpValidator(rxTelephone, this);
                          ui->GFle_num->setValidator(validatorTelephone);
           //*************controle saise de num telephone_m************/
                          ui->GFle_num_m->setValidator(validatorTelephone);




            //*************controle saise du adresse************/
               // Créez un QRegExpValidator avec le motif pour l'adresse
               QRegExp rxAdresse("^[A-Za-z0-9]{1,30}$");  // L'adresse doit comporter de 1 à 30 caractères alphanumériques
               QRegExpValidator *validatorAdresse = new QRegExpValidator(rxAdresse, this);
               ui->GFl_adresse->setValidator(validatorAdresse);
             //*************controle saise du adresse_modifier************/
               ui->GFl_adresse_m->setValidator(validatorAdresse);





               connect(ui->tab_fournisseur->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
                       this, SLOT(afficherInfoFournisseur(QModelIndex)));

//-------------------------------------------------RECLAMATIONS----------------------------------------------------------

                                          ui->lineEdit_IDrec->setValidator(new QIntValidator(0,999999,this));
                                          ui->lineEdit_supprec->setValidator(new QIntValidator (0, 99999999, this));
                                          ui->tab_reclammations->setModel(rec.afficher());
                                          proxyModelrec = new QSortFilterProxyModel(this);
                                              proxyModelrec->setSourceModel(rec.afficher());
                                              ui->tab_reclammations->setModel(proxyModelrec);
                                              QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");
                                                    if (!file.open(QIODevice::ReadOnly))
                                                    {
                                                        QMessageBox::information(0,"info",file.errorString());
                                                    }
                                                    QTextStream in (&file);
                                                   ui->hist->setText(in.readAll());



//----------------------------------------------------------ARDUINO-----------------------------------------------------------------

               int ret=A.connect_arduino(); // lancer la connexion à arduino
                       switch(ret){
                       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                       break;
                       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                       break;
                       case(-1):qDebug() << "arduino is not available";
                       }
                       if(A.getarduino_port_name()=="COM6"){
                           // SARRA
                           qDebug()<<"SARRA";
                       }
                       else if(A.getarduino_port_name()=="COM4"){
                           // NOUR
                           qDebug()<<"NOUR";
                           QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer

                       }
                       else if(A.getarduino_port_name()=="COM5") {
                           //NAJD
                            qDebug()<<"NAJD";
                            A.close_arduino();

                       }

}

MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------------------------EMPLOYES------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_emp_ajouter_clicked()
{

        QString fonction=ui->emp_comboBox->currentText();
        int id=ui->emp_id->text().toInt();
        QString nom=ui->emp_nom->text();
        QString prenom=ui->emp_prenom->text();
        QString mail=ui->emp_mail->text();
        int age=ui->emp_age->text().toInt();
        QString date_embauche="";
        QString status="inactif";
        float salaire=ui->emp_salaire->text().toInt();
        QString code_securite="";
        QString num_tl=ui->emp_num_tl->text();
        QString password=ui->emp_pass->text();
        QString mp_rec=ui->emp_mp_rec->text();
        QString question=ui->emp_comboBox_2->currentText();
        if(age<18 or age>60) {
            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                        QObject::tr(" 17<Age<61 .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            return ;
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
            return ;
        }
        employes e(nom,prenom ,fonction,date_embauche,mail,id,age,salaire,num_tl,password,mp_rec,question,status);

        if(e.is_email_valid(mail)==false){
            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                        QObject::tr(" Mail Invalid .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            return ;
        }



    bool test=e.ajouter();
    if(test)
        {
        bool test1=false;
        if(ui->emp_ascendent->isChecked()){
            test1=true;
        }

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->emp_tableView->setModel(e.afficher(ui->emp_Tri_comboBox->currentText(),test1));//mise a jour

    }
        else{
            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                        QObject::tr("ajout failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}


}

void MainWindow::on_emp_supprimer_clicked()
{
    employes e ;
    e.setid(ui->id_supp->text().toInt());
    bool test=e.supprimer(e.getid());
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Suppression successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


    }
        else
            QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                        QObject::tr("Suppression failed.\n"
                                    "ID is not found!!\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    ui->emp_tableView->setModel(e.afficher(ui->emp_Tri_comboBox->currentText(),test));//mise a jour
}


void MainWindow::on_emp_modifier_clicked()
{
    bool test=false;
    if(ui->emp_ascendent->isChecked()){
        test=true;
    }
    int id=ui->id->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString mail=ui->mail->text();
    int age=ui->age->text().toInt();
    QString date_embauche=ui->date->text();
    float salaire=ui->salaire->text().toInt();
    QString num_tl=ui->numero_tl->text();
    QString password=ui->pass->text();
    QString mp_rec=e.getreponse();
    QString question=e.getquestion();
    QString status=e.getstatus();
    QString fonction=ui->comboBox->currentText();


    employes e(nom,prenom ,fonction,date_embauche,mail,id,age,salaire,num_tl,password,mp_rec,question,status);

    bool test1=e.modifier();
    if(test1){
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr(" mofication successfull!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                    QObject::tr(" modification not complete!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->emp_tableView->setModel(e.afficher(ui->emp_Tri_comboBox->currentText(),test));//mise a jour

}

void MainWindow::on_emp_clear_clicked()
{
    ui->emp_id->clear();
    ui->emp_nom->clear();
    ui->emp_prenom->clear();
    ui->emp_salaire->clear();
    //ui->date->clear();
    ui->emp_age->clear();
    ui->emp_mail->clear();
    ui->emp_pass->clear();
    ui->emp_num_tl->clear();
    ui->emp_mp_rec->clear();
    ui->emp_comboBox->setCurrentIndex(0);
    ui->emp_comboBox_2->setCurrentIndex(0);
}


void MainWindow::on_emp_statistique_clicked()
{
    QSqlQuery query;
            query.prepare("SELECT AGE, COUNT(*) FROM employes GROUP BY AGE");

            if (!query.exec()) {
                qDebug() << "Erreur lors de l'exécution de la requête.";
                //db.close();
                return;
            }

            // Define your two colors
            QColor startColor(251, 189, 251); // #FBBDAF
            QColor endColor(252, 241, 252);   // #FCF1FC

            // Création de la série de données pour le graphique en secteurs
            QPieSeries *series = new QPieSeries();

            int colorIndex = 0;

        while (query.next()) {
            QString type = query.value(0).toString();
            int count = query.value(1).toInt();
            // Interpolate color between startColor and endColor
                    QColor interpolatedColor = startColor.lighter(100 - colorIndex * 20);

                    // Append slice with interpolated color
                    QPieSlice *slice = series->append(type, count);
                    slice->setBrush(interpolatedColor);

                    // Increment colorIndex, but not more than 5 times to avoid going too dark
                    colorIndex = qMin(colorIndex + 1, 5);
        }

        foreach(QPieSlice *slice, series->slices()) {
            QString label = QString("%1 (%2%)")
                .arg(slice->label())
                .arg(100 * slice->percentage(), 0, 'f', 1);
            slice->setLabel(label);
        }

        // Création du graphique et ajout de la série de données
        QChart *chart = new QChart();
        chart->addSeries(series);
            // Set title font size and weight
            QFont titleFont = chart->titleFont();
            titleFont.setPointSize(16); // Adjust the font size as needed
            titleFont.setBold(true);
            chart->setTitleFont(titleFont);

        chart->setTitle("Les statistiques des employés selon l'age: ");

        // Configuration du graphique
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->setAnimationOptions(QChart::AllAnimations);

        // Affichage du graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(640, 480);
        chartView->show();


}


void MainWindow::on_emp_Tri_comboBox_activated(const QString &arg1)
{
    bool test=false;
    if(ui->emp_ascendent->isChecked()){
        test=true;
    }
    ui->emp_tableView->setModel(e.afficher(arg1,test));
}

void MainWindow::on_emp_ascendent_clicked()
{
    QString tri=ui->emp_Tri_comboBox->currentText();
    ui->emp_tableView->setModel(e.afficher(tri,true));
}
void MainWindow::on_emp_descendent_clicked()
{
    QString tri=ui->emp_Tri_comboBox->currentText();
    ui->emp_tableView->setModel(e.afficher(tri,false));
}


void MainWindow::on_login_clicked()
{
    employes e ;
    QString pass=ui->login_pass->text();
    int id=ui->login_id->text().toInt();
    bool test=e.check_login(pass,id);
    if(test){
        ui->logout->show();
        ui->home->show();
        ui->frame_login->hide();
        ui->frame_gestion->show();
    }
}

void MainWindow::on_home_clicked()
{
    ui->frame_inside_gestion->hide();
    ui->frame_gestion->show();
    ui->stackedWidget->hide();
}

void MainWindow::on_gs_employes_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur"){
            ui->frame_inside_gestion->show();
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->employes);
            ui->stackedWidget->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_gs_bijoux_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS bijoux"){
            ui->frame_inside_gestion->show();
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->bijoux);
            ui->stackedWidget->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_gs_client_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS clients"){
            ui->frame_inside_gestion->show();
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->client);
            ui->stackedWidget->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_gs_fournisseur_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS fournisseur"){
            ui->frame_inside_gestion->show();
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->founisseur);
            ui->stackedWidget->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_gs_reclamation_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS reclamations"){
            ui->frame_inside_gestion->show();
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->reclamation);
            ui->stackedWidget->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}



void MainWindow::on_logout_clicked()
{
    on_emp_clear_clicked();
    ui->frame_inside_gestion->hide();
    ui->login_id->clear();
    ui->login_pass->clear();
    ui->frame_login->show();
    ui->logout->hide();
    ui->home->hide();
    ui->frame_gestion->hide();
    ui->stackedWidget->hide();
}



void MainWindow::on_inside_employe_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur"){
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->employes);
            ui->stackedWidget->show();
            ui->logout->show();
            ui->frame_inside_gestion->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_inside_bijou_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS bijoux"){
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->bijoux);
            ui->stackedWidget->show();
            ui->frame_inside_gestion->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_inside_client_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS clients"){
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->client);
            ui->stackedWidget->show();
            ui->frame_inside_gestion->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_inside_fournisseur_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS fournisseur"){
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->founisseur);
            ui->stackedWidget->show();
            ui->logout->show();
            ui->frame_inside_gestion->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}

void MainWindow::on_inside_reclamation_clicked()
{
    employes e;
    int id=ui->login_id->text().toInt();
    if(e.idExists(id)){
        if(e.getfonction()=="administrateur" or e.getfonction()=="GS reclamations"){
            ui->frame_gestion->hide();
            ui->stackedWidget->setCurrentWidget(ui->reclamation);
            ui->stackedWidget->show();
            ui->frame_inside_gestion->show();
            ui->logout->show();
            ui->home->show();
        }
        else
            {QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                                   QObject::tr(" vous n'avez pas le droit \n"
                                               "d'accéder à cette gestion"), QMessageBox::Cancel);}
    }
}



void MainWindow::on_oublie_clicked()
{
    oublie oubwindow;
    oubwindow.setModal(true);
    oubwindow.exec();
}

void MainWindow::on_emp_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF File", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        return; // User canceled the operation
    }

    // Create a PDF file
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300); // Set the resolution as needed

    // Create a QPainter to draw on the PDF
    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Open a new page for the PDF
    painter.begin(&pdfWriter);

    // Define fonts and styles as needed for your PDF
    QFont headerFont;
    headerFont.setPointSize(10);
    headerFont.setBold(true);

    QFont regularFont;
    regularFont.setPointSize(10);

    // Fetch the data from your database (replace this with your actual query)
    QSqlQueryModel model;
    model.setQuery("SELECT * FROM employes"); // Modify the SQL query accordingly


    // Define the initial vertical offset and spacing between rows
    int yOffset = 50; // Initial vertical offset
    int rowHeight = 70; // Vertical spacing between rows

    // Define column widths and titles
    QVector<int> columnWidths = {100, 150, 200, 300, 150, 300, 100, 350, 220, 220}; // Adjust widths as needed
    QStringList columnTitles = {"id", "nom", "prenom", "fonction", "salaire", "embauche", "age", "e-mail", "numero", "password"};

    // Draw table header
    painter.setFont(headerFont);
    painter.setBrush(QBrush(QColor(200, 200, 200))); // Set header background color
    painter.drawRect(100, yOffset, std::accumulate(columnWidths.begin(), columnWidths.end(), 0), rowHeight);

    for (int col = 0; col < columnTitles.size(); ++col) {
        painter.drawText(100 + std::accumulate(columnWidths.begin(), columnWidths.begin() + col, 0), yOffset, columnWidths[col], rowHeight, Qt::AlignCenter, columnTitles[col]);
    }
    yOffset += rowHeight; // Move to the next row

    // Iterate through the data and write it to the PDF table
    for (int row = 0; row < model.rowCount(); ++row) {
        painter.setFont(regularFont);
        painter.setBrush(QBrush((row % 2 == 0) ? QColor(240, 240, 240) : Qt::white)); // Alternate row colors

        for (int col = 0; col < columnWidths.size(); ++col) {
            QString cellData = model.record(row).value(col).toString();
            painter.drawRect(100 + std::accumulate(columnWidths.begin(), columnWidths.begin() + col, 0), yOffset, columnWidths[col], rowHeight);
            painter.drawText(100 + std::accumulate(columnWidths.begin(), columnWidths.begin() + col, 0), yOffset, columnWidths[col], rowHeight, Qt::AlignCenter, cellData);
        }
        yOffset += rowHeight; // Move to the next row
    }

    // Finish drawing to the PDF
    painter.end();

    // Show a success message
    QMessageBox::information(this, "Export Successful", "Data exported to PDF successfully.");
}

void MainWindow::searchemployes(){
    int searchid=ui->emp_id_chercher->text().toInt();
    QSqlQueryModel* searchreslt=e.afficherEmployeParId(searchid);
    ui->emp_tableView->setModel(searchreslt);
}


void MainWindow::on_emp_chercher_clicked()
{

    connect(ui->emp_chercher , &QPushButton::clicked,this,&MainWindow::searchemployes);

    /*int id = ui->id_chercher->text().toInt();

    if (!id) {
        // Affichez un message d'erreur si l'ID est vide.
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour effectuer la recherche.");
        return;
    }

    // Vérifiez si l'ID existe dans la base de données.
    if (e.idExists(id)) {
       // QSqlQueryModel* model = e.afficherEmployeParId(id);
        ui->tableView->setModel(e.afficherEmployeParId(id));
    } else {
        // Si l'ID n'existe pas, affichez un message d'erreur.
        QMessageBox::warning(this, "Erreur", "L'ID spécifié n'existe pas dans la base de données.");
    }*/
}



void MainWindow::box_id(){
    //bool found=false;

}

void MainWindow::on_emp_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        int row = index.row();

        QString id = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 0)).toString();
        ui->id->setText(id);

        QString fonction = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 3)).toString();
        int fonctionIN = ui->comboBox->findText(fonction); // Find the index of the type in the combo box
                if (fonctionIN != -1){
                ui->comboBox->setCurrentIndex(fonctionIN);} // Set the current index in the combo box

        QString prenom = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 2)).toString();
        ui->prenom->setText(prenom);

        QString nom = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 1)).toString();
        ui->nom->setText(nom);

        QString salaire = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 4)).toString();
        ui->salaire->setText(salaire);


        QString date = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 5)).toString();
        ui->date->setText(date);


        QString age = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 6)).toString();
        ui->age->setText(age);

        QString passe = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 9)).toString();
        ui->pass->setText(passe);


        QString num = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 8)).toString();
        ui->numero_tl->setText(num);


        QString mail = ui->emp_tableView->model()->data(ui->emp_tableView->model()->index(row, 7)).toString();
        ui->mail->setText(mail);





     }
}




//---------------------------------------------------------------------BIJOUX----------------------------------------------------------------------------------




void MainWindow::on_GBpb_ajouter_clicked()
{
    QString id=ui->GBle_id->text();
    int stock=ui->GBle_stock->text().toInt();
    int codebox=ui->GBle_code->text().toInt();
    QString matiere = ui->GBcombo_matiere->currentText(); // Get selected matiere from combo box
    QString type = ui->GBcombo_type->currentText();       // Get selected type from combo box
    QString garantie=ui->GBle_garantie->text();
    QString prix=ui->GBle_prix->text();
    QByteArray imageData = selectedImageData;

    Bijou B(id,stock,type,matiere,garantie,prix,imageData,codebox);
    bool test=B.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("ajout avec succès.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_bijoux->setModel(B.afficher());//mise a jour

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("l'ajout a échoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_GBpb_supprimer_clicked()
{
    QString id = ui->GBle_id_supp->text();

    if (id.isEmpty()) {
        // Show an error message if the ID input is empty.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Veuillez entrer un identifiant avant de tenter de supprimer."), QMessageBox::Ok);
        return;
    }

    // Check if the ID exists in the database.
    Bijou B1;
    B1.setid(id);

    if (B1.idExists(id)) {
        // The ID exists, so proceed with the deletion.
        bool test = B1.supprimer(B1.getid());

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Suppression avec succès.\nClick Cancel to exit."), QMessageBox::Cancel);
            ui->tab_bijoux->setModel(B.afficher()); // Mise à jour
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("La suppression a échoué.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else {
        // Show an error message if the ID does not exist in the database and return from the function.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("L'identifiant n'existe pas."), QMessageBox::Ok);
        return;
    }
}


void MainWindow::on_GBpb_modifier_clicked()
{
    QString id = ui->GBle_id_modif->text();
    Bijou B;
    B.setid(id);
    int newStock = ui->GBle_stock_modif->text().toInt();
    int newCodebox = ui->GBle_code_modif->text().toInt();
    QString newType = ui->GBcombo_type_modif->currentText();    // Get selected type from combo box
    QString newMatiere = ui->GBcombo_matiere_modif->currentText(); // Get selected matiere from combo box
    QString newGarantie = ui->GBle_garantie_modif->text();
    QString newPrix = ui->GBle_prix_modif->text();

    if (id.isEmpty()) {
        // Affichez un message d'erreur si l'ID est vide.
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour effectuer la modification.");
        return;
    }

    // Check if the newId already exists in the database.
    if (!B.idExists(id)) {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("L'identifiant n'existe pas dans la base de données. Veuillez choisir un identifiant unique."), QMessageBox::Ok);
        return; // ID doesn't exist, so don't proceed with modification.
    }

    // If the ID is unique and changes are made, update the bijou's information.
    B.setid(id);
    B.setstock(newStock);
    B.settype(newType);
    B.setmatiere(newMatiere);
    B.setgarantie(newGarantie);
    B.setprix(newPrix);
    B.setImageData(selectedImageData); // Set the image data
    B.setcodebox(newCodebox);

    bool test = B.modifier();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification avec succès.\nClick Cancel to exit."), QMessageBox::Cancel);
        ui->tab_bijoux->setModel(B.afficher()); // Mise à jour
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("La Modification a échoué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_GBpb_annuler_ajout_clicked()
{
    // Effacez les champs d'entrée ou effectuez toute autre action que vous souhaitez
    ui->GBle_id->clear();
    ui->GBle_stock->clear();
    //ui->combo_type->clear();
    //ui->combo_matiere->clear();
    ui->GBle_garantie->clear();
    ui->GBle_prix->clear();
    ui->GBle_path->clear();
    ui->GBle_code->clear();
}

void MainWindow::afficherInfoBijou(const QModelIndex &index)
{
    if (index.isValid())
    {
        int row = index.row();

        QString id = ui->tab_bijoux->model()->data(ui->tab_bijoux->model()->index(row, 0)).toString();
        ui->GBle_id_modif->setText(id);

        int stock = ui->tab_bijoux->model()->data(ui->tab_bijoux->model()->index(row, 1)).toInt();
        ui->GBle_stock_modif->setText(QString::number(stock));

        QString type = ui->tab_bijoux->model()->data(ui->tab_bijoux->model()->index(row, 2)).toString();
        int typeIndex = ui->GBcombo_type_modif->findText(type); // Find the index of the type in the combo box
        if (typeIndex != -1){
        ui->GBcombo_type_modif->setCurrentIndex(typeIndex);} // Set the current index in the combo box

        QString prix = ui->tab_bijoux->model()->data(ui->tab_bijoux->model()->index(row, 3)).toString();
        ui->GBle_prix_modif->setText(prix);

        QString matiere = ui->tab_bijoux->model()->data(ui->tab_bijoux->model()->index(row, 4)).toString();
        int matiereIndex = ui->GBcombo_matiere_modif->findText(matiere); // Find the index of the matiere in the combo box
        if (matiereIndex != -1) {
        ui->GBcombo_matiere_modif->setCurrentIndex(matiereIndex);}// Set the current index in the combo box

        QString garantie = ui->tab_bijoux->model()->data(ui->tab_bijoux->model()->index(row, 5)).toString();
        ui->GBle_garantie_modif->setText(garantie);

        int codebox = ui->tab_bijoux->model()->data(ui->tab_bijoux->model()->index(row, 7)).toInt();
        ui->GBle_code_modif->setText(QString::number(codebox));
     }
}

void MainWindow::on_GBpb_annuler_modif_clicked()
{
    // Effacez les champs d'entrée ou effectuez toute autre action que vous souhaitez
    ui->GBle_id_modif->clear();
    ui->GBle_stock_modif->clear();
    //ui->combo_type_modif->clear();
    //ui->combo_matiere_modif->clear();
    ui->GBle_garantie_modif->clear();
    ui->GBle_prix_modif->clear();
    ui->GBle_path_modif->clear();
    ui->GBle_code_modif->clear();
}

void MainWindow::on_GBselect_image_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg *.bmp)");
        if (!filePath.isEmpty()) {
            QFile imageFile(filePath);
            if (imageFile.open(QIODevice::ReadOnly)) {
                selectedImageData = imageFile.readAll();
                ui->GBle_path->setText(filePath);
                // Now, the selected image data is stored in the selectedImageData QByteArray.
                // You can use this data to store in the database or perform other operations.
                imageFile.close();
            } else {
                // Handle error opening the image file.
                QMessageBox::critical(this, "Error", "Failed to open the image file.");
            }
        }
}

void MainWindow::on_GBselect_image_modif_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg *.bmp)");
        if (!filePath.isEmpty()) {
            QFile imageFile(filePath);
            if (imageFile.open(QIODevice::ReadOnly)) {
                selectedImageData = imageFile.readAll();
                ui->GBle_path_modif->setText(filePath);
                // Now, the selected image data is stored in the selectedImageData QByteArray.
                // You can use this data to store in the database or perform other operations.
                imageFile.close();
            } else {
                // Handle error opening the image file.
                QMessageBox::critical(this, "Error", "Failed to open the image file.");
            }
        }
}

void MainWindow::on_GBpb_tri_clicked()
{
    GBproxyModel = new QSortFilterProxyModel(this);
    GBproxyModel->setSourceModel(B.afficher());
    ui->tab_bijoux->setModel(GBproxyModel);
    // Sort the data in the second column (assuming column index is 1) in ascending order
    ui->tab_bijoux->sortByColumn(1, Qt::AscendingOrder);
}

void MainWindow::on_GBpb_rechercher_clicked()
{
    ui->GBle_recherche_id->setPlaceholderText("Tapez l'ID à rechercher");
    QString id = ui->GBle_recherche_id->text();

    if (id.isEmpty()) {
        // Affichez un message d'erreur si l'ID est vide.
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour effectuer la recherche.");
        return;
    }

    // Vérifiez si l'ID existe dans la base de données.
    if (B.idExists(id)) {
        // Si l'ID existe, affichez ses données dans le tableau tab_bijoux.
        QSqlQueryModel* model = B.afficherBijouParId(id);
        ui->tab_bijoux->setModel(model);
    } else {
        // Si l'ID n'existe pas, affichez un message d'erreur.
        QMessageBox::warning(this, "Erreur", "L'ID spécifié n'existe pas dans la base de données.");
    }
}

void MainWindow::on_GBpb_stat_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT TYPE, COUNT(*) FROM BIJOUX GROUP BY TYPE");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête.";
        //db.close();
        return;
    }

        // Define your two colors
        QColor startColor(251, 189, 251); // #FBBDAF
        QColor endColor(252, 241, 252);   // #FCF1FC

        // Création de la série de données pour le graphique en secteurs
        QPieSeries *series = new QPieSeries();

        int colorIndex = 0;

    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        // Interpolate color between startColor and endColor
                QColor interpolatedColor = startColor.lighter(100 - colorIndex * 20);

                // Append slice with interpolated color
                QPieSlice *slice = series->append(type, count);
                slice->setBrush(interpolatedColor);

                // Increment colorIndex, but not more than 5 times to avoid going too dark
                colorIndex = qMin(colorIndex + 1, 5);
    }

    foreach(QPieSlice *slice, series->slices()) {
        QString label = QString("%1 (%2%)")
            .arg(slice->label())
            .arg(100 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(label);
    }

    // Création du graphique et ajout de la série de données
    QChart *chart = new QChart();
    chart->addSeries(series);
        // Set title font size and weight
        QFont titleFont = chart->titleFont();
        titleFont.setPointSize(16); // Adjust the font size as needed
        titleFont.setBold(true);
        chart->setTitleFont(titleFont);

    chart->setTitle("Les statistiques des bijoux selon le type: ");

    // Configuration du graphique
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);

    // Affichage du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    chartView->show();
}


void MainWindow::on_GBpb_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        return;  // L'utilisateur a annulé la boîte de dialogue
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    // En-tête du document
    QTextCharFormat headerFormat;
    headerFormat.setFontPointSize(12);
    headerFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(headerFormat);
    cursor.insertText("Liste des Bijoux\n\n");

    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setCellPadding(10);  // Add cell padding for better presentation
    QTextTable *table = cursor.insertTable(1, 8, tableFormat);
    QTextCursor cellCursor;

    // Remplir les en-têtes de colonne
    cellCursor = table->cellAt(0, 0).firstCursorPosition();
    cellCursor.insertText("Identifiant");

    cellCursor = table->cellAt(0, 1).firstCursorPosition();
    cellCursor.insertText("Stock");

    cellCursor = table->cellAt(0, 2).firstCursorPosition();
    cellCursor.insertText("Type");

    cellCursor = table->cellAt(0, 3).firstCursorPosition();
    cellCursor.insertText("Prix");

    cellCursor = table->cellAt(0, 4).firstCursorPosition();
    cellCursor.insertText("Matière");

    cellCursor = table->cellAt(0, 5).firstCursorPosition();
    cellCursor.insertText("Garantie");

    cellCursor = table->cellAt(0, 6).firstCursorPosition();
    cellCursor.insertText("Image");

    cellCursor = table->cellAt(0, 7).firstCursorPosition();
    cellCursor.insertText("Code box");


    QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tab_bijoux->model());

    for (int row = 0; row < model->rowCount(); ++row) {
        table->appendRows(1);

        for (int col = 0; col < 8; ++col) {
            cellCursor = table->cellAt(row + 1, col).firstCursorPosition();


            if (col == 6) {
                QByteArray imageData = model->data(model->index(row, col)).toByteArray();
                QImage image;
                image.loadFromData(imageData);

                QSize imageSize(70, 70);
                cellCursor.insertImage(image.scaled(imageSize));
            } else {
                cellCursor.insertText(model->data(model->index(row, col)).toString());
            }
        }
    }

    doc.print(&printer);

    QMessageBox::information(this, "Succès", "Liste des bijoux exportée sous forme de PDF.");
}

//catalogue+codeQR
void MainWindow::on_GBpb_generer_clicked()
{
    QString bijouId = ui->GBle_id_codeqr->text();

    ui->GBlabel_qrcode->setScaledContents(true);
    ui->GBlabel_qrcode->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    if (!bijouId.isEmpty()) {
        // Fetch other bijou details from the database
        QSqlQuery query;
        query.prepare("SELECT STOCK, TYPE, MATIERE, GARANTIE, PRIX FROM BIJOUX WHERE ID_BIJOU = :id");
        query.bindValue(":id", bijouId);

        if (query.exec() && query.next()) {
            int stock = query.value(0).toInt();
            QString type = query.value(1).toString();
            QString matiere = query.value(2).toString();
            QString garantie = query.value(3).toString();
            QString prix = query.value(4).toString();

            // Generate QR code using bijou details
            QImage img = B.generateQRCode(bijouId, stock, type, matiere, garantie, prix);

            if (!img.isNull()) {
                ui->GBlabel_qrcode->setPixmap(QPixmap::fromImage(img));
                //img.save("path/to/save/qrcode.png");
            } else {
                qDebug() << "Error: Failed to generate QR code for Bijou ID: " << bijouId;
            }
        } else {
            qDebug() << "Error: Failed to fetch bijou details from the database for ID: " << bijouId;
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr("L'identifiant n'existe pas dans la base de données."), QMessageBox::Ok);
        }
    } else {
        qDebug() << "Bijou identifier is empty!";
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Veuillez saisir un identifiant."), QMessageBox::Ok);
    }
}

void MainWindow::afficherBijouActuel()
{
    QString currentBijouId = bijouIds[currentBijouIndex];
    QImage bijouImage = B.getImageBijouById(currentBijouId);
    QImage qrImage;

    ui->GBcat_codeqr->setScaledContents(true);
    ui->GBcat_codeqr->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    ui->GBcat_image->setScaledContents(true);
    ui->GBcat_image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QSqlQuery query;
    query.prepare("SELECT STOCK, TYPE, MATIERE, GARANTIE, PRIX FROM BIJOUX WHERE ID_BIJOU = :id");
    query.bindValue(":id", currentBijouId);

    if (query.exec() && query.next()) {
        int stock = query.value(0).toInt();
        QString type = query.value(1).toString();
        QString matiere = query.value(2).toString();
        QString garantie = query.value(3).toString();
        QString prix = query.value(4).toString();

        // Generate QR code using bijou details
        qrImage = B.generateQRCode(currentBijouId, stock, type, matiere, garantie, prix);

        if (!qrImage.isNull()) {
            ui->GBlabel_qrcode->setPixmap(QPixmap::fromImage(qrImage));
            //img.save("path/to/save/qrcode.png");
        } else {
            qDebug() << "Error: Failed to generate QR code for Bijou ID: " << currentBijouId;
        }
    }

    // Affichez l'image dans le QLabel.
    if (!bijouImage.isNull()) {
            ui->GBcat_image->setPixmap(QPixmap::fromImage(bijouImage));
        } else {
            // Si l'image n'est pas trouvée, vous pouvez afficher une image par défaut ou un message.
            ui->GBcat_image->clear(); // Effacez l'image précédente au cas où.
            ui->GBcat_image->setText("Image non disponible");
        }
    // Affichez le code QR dans le QLabel.
    ui->GBcat_codeqr->setPixmap(QPixmap::fromImage(qrImage));
}

void MainWindow::on_GBpb_precedent_clicked()
{
    currentBijouIndex--;
    if (currentBijouIndex < 0) {
        currentBijouIndex = bijouIds.size() - 1;
    }
    afficherBijouActuel();
}

void MainWindow::on_GBpb_suivant_clicked()
{
    currentBijouIndex++;
    if (currentBijouIndex >= bijouIds.size()) {
        currentBijouIndex = 0;
    }
    afficherBijouActuel();
}

void MainWindow::on_GBpb_commencer_clicked()
{
    bijouIds = B.getListeIdBijoux();
    afficherBijouActuel();
}



//---------------------------------------------------------------------------------------CLIENTS-------------------------------------------------------------------------------------


void MainWindow::on_gc_ajouter_clicked()
{
    QString sexe;
    QString id=ui->gc_id->text();
    QString nom=ui->gc_nom->text();
    QString prenom=ui->gc_prenom->text();
    QString adresse=ui->gc_adresse->text();
    QString num_tel=ui->gc_num->text();
    QString mail=ui->gc_mail->text();
    if(ui->homme->isChecked()){
        C.setsexe("homme");
    }
    if(ui->femme->isChecked()){
        C.setsexe("femme");
    }
    sexe=C.getsexe();

    Client C(id,nom,prenom,adresse,num_tel,mail,sexe);
    bool test=C.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_client->setModel(C.afficher());
      generatesexestatistics();
      //N.notification_ajoutclient();

}
    else{
        QMessageBox::critical(nullptr, QObject::tr(" not ok"),
                    QObject::tr("ajout failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}






}

void MainWindow::on_gc_supprimer_clicked()
{QString id = ui->gc_id_supp->text();

    if (id.isEmpty()) {

        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Please enter an ID before attempting to delete."), QMessageBox::Ok);
        return;
    }


    Client C1;
    C1.setid(id);
    QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer ce client?", QMessageBox::Yes | QMessageBox::No);

    if (confirmation == QMessageBox::Yes) {
    if (C1.idExists(id)) {

        Client C1;
        C1.setid(id);
        bool test = C1.supprimer(C1.getid());

        if (test) {

            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Suppression successful.\nClick Cancel to exit."), QMessageBox::Cancel);
           ui->tab_client->setModel(C.afficher());
           generatesexestatistics();
          // N.notification_supprimerclient();
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Suppression failed.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else {

        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr(" ID n'existe pas."), QMessageBox::Ok);
    }
}
}

void MainWindow::on_gc_modifier_clicked()
{
    QString id = ui->gc_id_modif->text();
        Client C;
        C.setid(id);
        QString newNom = ui->gc_nom_modif->text();
        QString newPrenom = ui->gc_prenom_modif->text();
        QString newAdresse = ui->gc_adresse_modif->text();
        QString newNumTel = ui->gc_num_modif->text();
        QString newMail = ui->gc_mail_modif->text();

        QString newSexe;
                    if (ui->homme_modif->isChecked()) {
                        newSexe = "homme";
                    } else if (ui->femme_modif->isChecked()) {
                        newSexe = "femme";
                    }


                    if (!C.idExists(id)) {
                        QMessageBox::critical(nullptr, QObject::tr("Error"),
                            QObject::tr("Entrer un unique id."), QMessageBox::Ok);
                        return; // ID already exists, so don't proceed with modification.
                    }




                    C.setid(id);
                    C.setnom(newNom);
                    C.setprenom(newPrenom);
                    C.setadresse(newAdresse);
                    C.setnum_tel(newNumTel);
                    C.setmail(newMail);
                    C.setsexe(newSexe);

                    bool test = C.modifier();

                    if (test) {
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Modification successful.\nClick Cancel to exit."), QMessageBox::Cancel);
                                   ui->tab_client->setModel(C.afficher());
                                   generatesexestatistics();
        //                           N.notification_modifierclient();
                                } else {
                                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                        QObject::tr("Modification failed.\nClick Cancel to exit."), QMessageBox::Cancel);
                                }

}

void MainWindow::afficherinfoclient(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        QString id = ui->tab_client->model()->data(ui->tab_client->model()->index(row, 0)).toString();
        ui->gc_id_modif->setText(id);
        ui->gc_id_supp->setText(id);
        QString nom = ui->tab_client->model()->data(ui->tab_client->model()->index(row, 1)).toString();
        ui->gc_nom_modif->setText(nom);
        QString prenom = ui->tab_client->model()->data(ui->tab_client->model()->index(row, 2)).toString();
        ui->gc_prenom_modif->setText(prenom);
        QString adresse = ui->tab_client->model()->data(ui->tab_client->model()->index(row, 3)).toString();
        ui->gc_adresse_modif->setText(adresse);
        QString num_tel = ui->tab_client->model()->data(ui->tab_client->model()->index(row, 4)).toString();
        ui->gc_num_modif->setText(num_tel);
        QString mail = ui->tab_client->model()->data(ui->tab_client->model()->index(row, 5)).toString();
        ui->gc_mail_modif->setText(mail);
        QString sexe = ui->tab_client->model()->data(ui->tab_client->model()->index(row, 6)).toString();
        if (sexe == "homme") {
                ui->homme_modif->setChecked(true);
                ui->femme_modif->setChecked(false);
            } else if (sexe == "femme") {
                ui->homme_modif->setChecked(false);
                ui->femme_modif->setChecked(true);
            } else {
                ui->homme_modif->setChecked(false);
                ui->femme_modif->setChecked(false);
            }

    }
}

void MainWindow::on_gc_annuler_clicked()
{

    ui->gc_id->clear();
        ui->gc_nom->clear();
        ui->gc_prenom->clear();
        ui->gc_adresse->clear();
        ui->gc_num->clear();
        ui->gc_mail->clear();

        ui->homme->setChecked(false);
        ui->femme->setChecked(false);

}

void MainWindow::on_gc_annuler2_clicked()
{
        ui->gc_id_modif->clear();
        ui->gc_nom_modif->clear();
        ui->gc_prenom_modif->clear();
        ui->gc_adresse_modif->clear();
        ui->gc_num_modif->clear();
        ui->gc_mail_modif->clear();

        ui->homme_modif->setChecked(false);
        ui->femme_modif->setChecked(false);


}


void MainWindow::searchClients() {
    QString searchid = ui->gc_rechercher->text();

    // Perform the search based on the entered name
    // You can modify your Client class to add a searchByName method
    // that fetches clients based on the name.
    QSqlQueryModel* searchResult = C.searchByid(searchid);

    // Set the QTableView model to the search result
    ui->tab_client->setModel(searchResult);
}

void MainWindow::on_gc_rech_clicked()
{
    connect(ui->gc_rech, &QPushButton::clicked, this, &MainWindow::searchClients);


}
void MainWindow::generatesexestatistics() {
    // Effacer le contenu précédent du layout vertical
        QLayoutItem *child;
        while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    QPieSeries *series = new QPieSeries();

    // Query the database to count the number of male and female clients
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM client WHERE sexe = 'homme'");
    int maleCount = query.next() ? query.value(0).toInt() : 0;

    query.exec("SELECT COUNT(*) FROM client WHERE sexe = 'femme'");
    int femaleCount = query.next() ? query.value(0).toInt() : 0;
    int totalCount = maleCount + femaleCount;

    // Add male and female slices to the Pie Chart
    QPieSlice *maleSlice = series->append("Hommes", maleCount);
    QPieSlice *femaleSlice = series->append("Femmes", femaleCount);

    // Highlight the male slice
    maleSlice->setExploded();
    maleSlice->setLabelVisible();
    maleSlice->setPen(QPen(Qt::darkBlue, 2));
    maleSlice->setBrush(Qt::blue);
    // Highlight the male slice
    femaleSlice->setExploded();
    femaleSlice->setLabelVisible();
    femaleSlice->setPen(QPen(Qt::darkRed, 2));
    femaleSlice->setBrush(Qt::red);
    maleSlice->setLabel(QString("Hommes: %1%").arg(static_cast<double>(maleCount) / totalCount * 100, 0, 'f', 1));
    femaleSlice->setLabel(QString("Femmes: %1%").arg(static_cast<double>(femaleCount) / totalCount * 100, 0, 'f', 1));

    // Set the chart title
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des clients selon le genre");

    // Create a QChartView to display the Pie Chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the QChartView to your UI
    ui->verticalLayout->addWidget(chartView);
}

void MainWindow::on_gc_pdf_clicked()
{   QString fileName = QFileDialog::getSaveFileName(this, "Save PDF File", "", "PDF Files (*.pdf)");

             if (fileName.isEmpty()) {

            return; // User canceled the operation
             }

        QPdfWriter pdfWriter(fileName);

        pdfWriter.setPageSize(QPageSize(QPageSize::A4));

        pdfWriter.setResolution(300); // Set the resolution as needed


         // Create a QPainter to draw on the PDF

        QPainter painter(&pdfWriter);

        painter.setRenderHint(QPainter::Antialiasing);

        painter.begin(&pdfWriter);

        QFont headerFont;

        headerFont.setPointSize(10);

        headerFont.setBold(true);


        QFont regularFont;

        regularFont.setPointSize(10);

        QSqlQueryModel model;

        model.setQuery("SELECT * FROM client"); // Modify the SQL query accordingly


        int yOffset = 50; // Initial vertical offset

        int rowHeight = 70; // Vertical spacing between rows

        QVector<int> columnWidths = {200, 300, 200, 300, 300, 500, 200}; // Adjust widths as needed

        QStringList columnTitles = {"id", "nom", "prenom", "adresse", "numero de tel", "e-mail", "sexe"};

        painter.setFont(headerFont);

        painter.setBrush(QBrush(QColor(200, 200, 200))); // Set headerbackground color

        painter.drawRect(100, yOffset,
        std::accumulate(columnWidths.begin(), columnWidths.end(), 0),rowHeight);

        for (int col = 0; col < columnTitles.size(); ++col) {

        painter.drawText(100 + std::accumulate(columnWidths.begin(), columnWidths.begin() + col, 0), yOffset, columnWidths[col], rowHeight,Qt::AlignCenter, columnTitles[col]);}

        yOffset += rowHeight; // Move to the next row

        for (int row = 0; row < model.rowCount(); ++row) {

        painter.setFont(regularFont);

        painter.setBrush(QBrush((row % 2 == 0) ? QColor(240, 240, 240) : Qt::white)); // Alternate row colors


       for (int col = 0; col < columnWidths.size(); ++col) {

              QString cellData = model.record(row).value(col).toString();

              painter.drawRect(100 + std::accumulate(columnWidths.begin(), columnWidths.begin() + col, 0),yOffset, columnWidths[col], rowHeight);

              painter.drawText(100 +std::accumulate(columnWidths.begin(), columnWidths.begin() + col, 0),yOffset, columnWidths[col], rowHeight, Qt::AlignCenter, cellData);

                                                            }
              yOffset += rowHeight; // Move to the next row
                                 }
             painter.end();

       QMessageBox::information(this, "Export Successful", "Data exported to PDF successfully.");
      // N.notification_pdf();

}

void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::information( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
   // N.notification_mail();
}




//-------------------------------------------------------------------------------------------FOURNISSEURS-----------------------------------------------------------------------------------------




void MainWindow::on_GFpb_ajouter_clicked()
{
    QString id_fournisseur=ui->GFle_id->text();
    int code_postale=ui->GFle_code_postale->text().toInt();
    QString num_de_telephone=ui->GFle_num->text();
    QString nom_entreprise=ui->GFle_nom->text();
    QString type=ui->GFcombo_type->currentText();
    QString adresse=ui->GFl_adresse->text();
    QString adresse_email=ui->GFl_email->text();
    Fournisseur F(id_fournisseur,code_postale,num_de_telephone ,nom_entreprise ,adresse , adresse_email, type);


    bool test=F.ajouter();
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("ajout successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_fournisseur->setModel(F.afficher());

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("ajout failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_GFpb_supprimer_clicked()
{
    QString id_fournisseur = ui->GFle_id_supp->text();

    if (id_fournisseur.isEmpty()) {
        // Show an error message if the ID input is empty.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Veuillez entrer un identifiant avant de tenter de supprimer."), QMessageBox::Ok);
        return;
    }

    // Check if the ID exists in the database.
    Fournisseur F1;
    F1.setid_fournisseur(id_fournisseur);

    if (F1.idExists(id_fournisseur)) {
        // The ID exists, so proceed with the deletion.
        bool test = F1.supprimer(F1.getid_fournisseur());

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Suppression avec succès.\nClick Cancel to exit."), QMessageBox::Cancel);
            ui->tab_fournisseur->setModel(F.afficher()); // Mise à jour
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("La suppression a échoué.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else {
        // Show an error message if the ID does not exist in the database and return from the function.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("L'identifiant n'existe pas."), QMessageBox::Ok);
        return;
    }
}


void MainWindow::on_GFpb_modifier_clicked()
{
    QString id_fournisseur = ui->GFle_id_m->text();
    Fournisseur F;
    F.setid_fournisseur(id_fournisseur);
    int newcode_postale= ui->GFle_code_postale_m->text().toInt();
    QString newnum_telephone = ui->GFle_num_m->text();
    QString newnom_entreprise = ui->GFle_nom_m->text();
    QString newadresse = ui->GFl_adresse_m->text();
    QString newadresse_email = ui->GFl_adresse_m->text();
    QString newtype = ui->GFcombo_type_m->currentText();

    // Check if the newId already exists in the database.
    if (!F.idExists(id_fournisseur)) {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("ID not exists in the database. Please choose a unique ID."), QMessageBox::Ok);
        return; // ID already exists, so don't proceed with modification.
    }

    // If the ID is unique and changes are made, update the client's information.
    F.setid_fournisseur(id_fournisseur);
    F.settype(newtype);
    F.setadresse(newadresse);
    F.setcode_postale(newcode_postale);
    F.setadresse_email(newadresse_email);
    F.setnum_telephone(newnum_telephone);
    F.setnom_entreprise(newnom_entreprise);


    bool test = F.modifier();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification successful.\nClick Cancel to exit."), QMessageBox::Cancel);
        ui->tab_fournisseur->setModel(F.afficher()); // Mise à jour
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Modification failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_GFpb_annuler_ajout_clicked()
{
    // Effacez les champs d'entrée ou effectuez toute autre action que vous souhaitez
    ui->GFle_id->clear();
    ui->GFle_nom->clear();
    ui->GFle_num->clear();
    ui->GFcombo_type->clear();
    ui->GFle_code_postale->clear();
    ui->GFl_adresse->clear();
    ui->GFl_email->clear();
}


void MainWindow::afficherInfoFournisseur(const QModelIndex &index)
{
    if (index.isValid())
    {
        int row = index.row();

        QString id_fournisseur = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, 0)).toString();
        ui->GFle_id_m->setText(id_fournisseur);

        QString type = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, 1)).toString();
        int typeIndex = ui->GFcombo_type_m->findText(type); // Find the index of the type in the combo box
                if (typeIndex != -1){
                ui->GFcombo_type_m->setCurrentIndex(typeIndex);} // Set the current index in the combo box

        QString nom_entreprise = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, 2)).toString();
        ui->GFle_nom_m->setText(nom_entreprise);

        QString adresse = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, 3)).toString();
        ui->GFl_adresse_m->setText(adresse);

        int code_postale = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, 4)).toInt();
        ui->GFle_code_postale_m->setText(QString::number(code_postale));


        QString num_de_telephone = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, 5)).toString();
        ui->GFle_num_m->setText(num_de_telephone);


        QString adresse_email = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, 6)).toString();
        ui->GFl_email_m->setText(adresse_email);





     }
}

void MainWindow::on_GFpb_annuler_supp_clicked()
{
    // Effacez les champs d'entrée ou effectuez toute autre action que vous souhaitez
    ui->GFle_id_supp->clear();


}

void MainWindow::on_GFpb_annuler_m_clicked()
{
    // Effacez les champs d'entrée ou effectuez toute autre action que vous souhaitez
    ui->GFle_id_m->clear();
    ui->GFle_nom_m->clear();
    ui->GFle_num_m->clear();
    ui->GFcombo_type_m->clear();
    ui->GFle_code_postale_m->clear();
    ui->GFl_adresse_m->clear();
    ui->GFl_email_m->clear();

}

void MainWindow::on_GFpb_chercher_clicked()
{
    QString nom_entreprise = ui->GFle_nom_c->text();

        if (nom_entreprise.isEmpty()) {
            // Affichez un message d'erreur si le nom est vide.
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un nom d'entreprise pour effectuer la recherche.");
            return;
        }

        // Vérifiez si le nom existe dans la base de données.
        if (F.nom_Exists(nom_entreprise)) {
            // Si le nom existe, affichez ses données dans le tableau tab_bijoux.
            QSqlQueryModel* model = F.afficheFournissuerParnom(nom_entreprise);
            ui->tab_fournisseur->setModel(model);
        } else {
            // Si le nom n'existe pas, affichez un message d'erreur.
            QMessageBox::warning(this, "Erreur", "Le nom spécifié n'existe pas dans la base de données.");
        }
}

void MainWindow::on_GFpb_trier_clicked()
{
    //ui->tab_fournisseur->sortByColumn(4, Qt::AscendingOrder);
    if (triAscendant) {
            ui->tab_fournisseur->sortByColumn(4, Qt::AscendingOrder);
        } else {
            ui->tab_fournisseur->setSortingEnabled(false);  // Désactivez le tri
            ui->tab_fournisseur->setSortingEnabled(true);   // Réactivez le tri pour annuler le tri précédent

        }

        triAscendant = !triAscendant;

}

void MainWindow::on_GFpb_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
            if (fileName.isEmpty()) {
                return;  // L'utilisateur a annulé la boîte de dialogue
            }

            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);

            QTextDocument doc;
            QTextCursor cursor(&doc);

            // En-tête du document
            QTextCharFormat headerFormat;
            headerFormat.setFontPointSize(14);
            headerFormat.setFontWeight(QFont::Bold);
            cursor.setCharFormat(headerFormat);
            cursor.insertText("Liste des Fournisseurs\n\n");

            // Crée un tableau avec des colonnes pour chaque champ de la table
            QTextTableFormat tableFormat;
            tableFormat.setAlignment(Qt::AlignLeft);
            QTextTable *table = cursor.insertTable(1, 9, tableFormat);
            QTextCursor cellCursor;

            // Remplir les en-têtes de colonne
            cellCursor = table->cellAt(0, 0).firstCursorPosition();
            cellCursor.insertText("id_fournisseur");

            cellCursor = table->cellAt(0, 1).firstCursorPosition();
            cellCursor.insertText("type");

            cellCursor = table->cellAt(0, 2).firstCursorPosition();
            cellCursor.insertText("nom_entreprise");

            cellCursor = table->cellAt(0, 3).firstCursorPosition();
            cellCursor.insertText("adresse");

            cellCursor = table->cellAt(0, 4).firstCursorPosition();
            cellCursor.insertText("code_postale");

            cellCursor = table->cellAt(0, 5).firstCursorPosition();
            cellCursor.insertText("num_de_telephone");

            cellCursor = table->cellAt(0, 6).firstCursorPosition();
            cellCursor.insertText("adresse_email");


            // Obtain the fournisseur data from your table model
            QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tab_fournisseur->model());

            // Fill the table data
            for (int row = 0; row < model->rowCount(); ++row) {
                table->appendRows(1);

                for (int col = 0; col < 7; ++col) {
                    cellCursor = table->cellAt(row + 1, col).firstCursorPosition();
                    cellCursor.insertText(model->data(model->index(row, col)).toString());
                }
            }

            doc.print(&printer);

            // Display a success message
            QMessageBox::information(this, "Succès", "Liste des fournisseur exportée sous forme de PDF.");

}

void MainWindow::on_GFpb_stat_clicked()
{
    QSqlQuery query;
           query.prepare("SELECT TYPE, COUNT(*) FROM FOURNISSEUR GROUP BY TYPE");

           if (!query.exec()) {
               qDebug() << "Erreur lors de l'exécution de la requête.";
               //db.close();
               return;
           }

           // Define your two colors
           QColor startColor(251, 189, 251); // #FBBDAF
           QColor endColor(252, 241, 252);   // #FCF1FC

           // Création de la série de données pour le graphique en secteurs
           QPieSeries *series = new QPieSeries();

           int colorIndex = 0;

       while (query.next()) {
           QString type = query.value(0).toString();
           int count = query.value(1).toInt();
           // Interpolate color between startColor and endColor
                   QColor interpolatedColor = startColor.lighter(100 - colorIndex * 20);

                   // Append slice with interpolated color
                   QPieSlice *slice = series->append(type, count);
                   slice->setBrush(interpolatedColor);

                   // Increment colorIndex, but not more than 5 times to avoid going too dark
                   colorIndex = qMin(colorIndex + 1, 5);
       }

       foreach(QPieSlice *slice, series->slices()) {
           QString label = QString("%1 (%2%)")
               .arg(slice->label())
               .arg(100 * slice->percentage(), 0, 'f', 1);
           slice->setLabel(label);
       }

       // Création du graphique et ajout de la série de données
       QChart *chart = new QChart();
       chart->addSeries(series);
           // Set title font size and weight
           QFont titleFont = chart->titleFont();
           titleFont.setPointSize(16); // Adjust the font size as needed
           titleFont.setBold(true);
           chart->setTitleFont(titleFont);

       chart->setTitle("Les statistiques des fourniseurs selon le type: ");

       // Configuration du graphique
       chart->legend()->setAlignment(Qt::AlignRight);
       chart->setAnimationOptions(QChart::AllAnimations);

       // Affichage du graphique
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(640, 480);
       chartView->show();

}



//--------------------------------------------------------------------------------------RECLAMATIONS------------------------------------------------------------------------------------------------


void MainWindow::on_pb_validerrec_clicked()
{
    int ID_reclammations=ui->lineEdit_IDrec->text().toInt();
    QDate date_achat=ui->dateEdit_achat->date();
    QDate date_rec =ui->dateEdit_rec->date();
    QDate date_rep =ui->dateEdit_rep->date();

    QString mail_client=ui->lineEdit_mailrec->text();
    QString etat=ui->radioButton->isChecked() ? "traitee " : "non traitee";
    QString description=ui->lineEdit_descriptionrec->text();

    reclammations rec(ID_reclammations,date_achat,date_rec,date_rep,mail_client,etat,description);
     QMessageBox msgBox;
        if (mail_client.isEmpty() || etat.isEmpty() || description.isEmpty()) {
            QMessageBox::information(nullptr, "Failed", "Please fill in all the required fields.");
            return;
        }

    QRegExp regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    bool isEmailValid = regex.exactMatch(mail_client);

    if( !isEmailValid )
    {
        QMessageBox::information(nullptr, "Failed", "Invalid email format !");
       // return 0;
    }
    if (ID_reclammations==0)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }

    int value6= ui->radioButton_3->isChecked() ;
    int value7= ui->radioButton_4->isChecked() ;
    if (value6==0 and value7==0)
    {
        QMessageBox::information(nullptr, "Failed", "The type is empty please try to select it !");
        return ;
    }
    else{

    bool test=rec.ajouter();

    QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");//declarations d'un fichier
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream cout(&file);

    if (test)
    {   QMessageBox::information(nullptr, QObject::tr("réclamation ajoutée"),
                                 QObject::tr("successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
                     ui->tab_reclammations->setModel(rec.afficher());//rafraishissement
        //QString message2="Vous avez ajouté une reclammations\n";
                     QDateTime currentDateTime = QDateTime::currentDateTime(); // Obtenez la date et l'heure actuelles
                         QString message2 = "Vous avez ajouté une réclamation à " + currentDateTime.toString("dd/MM/yyyy hh:mm:ss") + "\n";

        cout << message2;
        QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");
       /*if (!file.open(QIODevice::ReadOnly))
       {
           QMessageBox::information(0,"info",file.errorString());
       }*/
       QTextStream in (&file);


      ui->hist->setText(in.readAll());

    /*QMessageBox::information(nullptr, QObject::tr("matèriel ajouté"),
                QObject::tr("successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);*/
    ui->tab_reclammations->setModel(rec.afficher());//rafraishissement

    }
    else
        msgBox.setText("Echec d'ajout!!!");
        msgBox.exec();
    }
}


void MainWindow::on_pb_supprimerrec_clicked()
{


    reclammations rec1;
    //QMediaPlayer *player = new QMediaPlayer;
               //player->setMedia(QUrl::fromLocalFile("C:/Users/easytech/Downloads/buttton.wav"));
             //  player->setVolume(50);
              // player->play();
    rec1.setID_reclammations(ui->lineEdit_supprec->text().toInt());
    bool test55=rec1.supprimer(rec1.getID_reclammations());
    qDebug()<<"test    :    "<<test55;
    QMessageBox msgBox;
    QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");//declarations d'un fichier
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream cout(&file);

    if (test55)
    {
        //qDebug()<<"reclammation";
        msgBox.setText("Suppression avec succés ");
        ui->tab_reclammations->setModel(rec.afficher());
        //QString message2="Vous avez supprimer une reclammations\n";
        QDateTime currentDateTime = QDateTime::currentDateTime(); // Obtenez la date et l'heure actuelles
            QString message2 = "Vous avez supprimé une réclamation à " + currentDateTime.toString("dd/MM/yyyy hh:mm:ss") + "\n";

                cout << message2;
                QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");
               if (!file.open(QIODevice::ReadOnly))
               {
                   QMessageBox::information(0,"info",file.errorString());
               }
               QTextStream in (&file);


              ui->hist->setText(in.readAll());
              ui->tab_reclammations->setModel(rec.afficher());//rafraishissement

    }
    else
        msgBox.setText("Echec de suppression!!!");
        msgBox.exec();
}


void MainWindow::on_pb_modifierrec_clicked()
{
    int id = ui->lineEdit_ID_2rec->text().toInt();
    QDate da = ui->lineEdit_achat_2->date(); // Adjust the format based on your input
    QDate drec = ui->lineEdit_rec_2->date();
    QDate dr = ui->lineEdit_rep_2->date();
    //rec.setID_reclammations(id);

    QString m=ui->lineEdit_mail_2rec->text();
    QString e=ui->radioButton->isChecked() ? "traitee" : "non traitee";
    QString d=ui->lineEdit_description_2rec->text();
    int value6= ui->radioButton->isChecked() ;
    int value7= ui->radioButton_2->isChecked() ;
    if (m.isEmpty() || e.isEmpty() || d.isEmpty()) {
        QMessageBox::information(nullptr, "Failed", "Please fill in all the required fields.");
        return;
    }
    QRegExp regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    bool isEmailValid = regex.exactMatch(m);
    if( !isEmailValid )
    {
        QMessageBox::information(nullptr, "Failed", "Error: Invalid email format. ");
        //return 0;
    }
   /* if (e.toLower() != "traitee" && e.toLower() != "non traitee") {
        QMessageBox::information(nullptr, "Failed", "Invalid value for 'etat'. Use 'traitee' or 'non traitee'.");
        return;
    }*/
    if (value6==0 and value7==0)
    {
        QMessageBox::information(nullptr, "Failed", "The type is empty please try to select it !");
        return ;
    }
    else{

    reclammations rec2(id,da,drec,dr,m,e,d);
    bool test=rec2.modifier();
    QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");//declarations d'un fichier
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return;

        QTextStream cout(&file);
    QMessageBox msgbox;
    if(test){
        if(e=="traitee"){
            QString command=QString::number(rec2.getID_reclammations());
            A.write_to_arduino(command.toStdString().c_str());
        }
        ui->tab_reclammations->setModel(rec2.afficher());
        //QString message2="Vous avez modifier une reclammations\n";
        QDateTime currentDateTime = QDateTime::currentDateTime(); // Obtenez la date et l'heure actuelles
            QString message2 = "Vous avez modifié une réclamation à " + currentDateTime.toString("dd/MM/yyyy hh:mm:ss") + "\n";

                cout << message2;
                QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");
               if (!file.open(QIODevice::ReadOnly))
               {
                   QMessageBox::information(0,"info",file.errorString());
               }
               QTextStream in (&file);


              ui->hist->setText(in.readAll());

            QMessageBox::information(nullptr, QObject::tr("réclamation modifiée"),
                        QObject::tr("successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_reclammations->setModel(rec.afficher());//rafraishissement

    }
    else
        msgbox.setText("echec de la modification");
        msgbox.exec();
    }
}


void MainWindow::on_pushButton_statistiquerec_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT ETAT, COUNT(*) FROM GS_RECLAMMATIONS GROUP BY ETAT");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête.";
        //db.close();
        return;
    }

    // Define your two colors
    QColor startColor(251, 189, 251); // #FBBDAF
    QColor endColor(252, 241, 252);   // #FCF1FC

    // Création de la série de données pour le graphique en secteurs
    QPieSeries *series = new QPieSeries();

    int colorIndex = 0;

while (query.next()) {
    QString type = query.value(0).toString();
    int count = query.value(1).toInt();
    // Interpolate color between startColor and endColor
            QColor interpolatedColor = startColor.lighter(100 - colorIndex * 20);

            // Append slice with interpolated color
            QPieSlice *slice = series->append(type, count);
            slice->setBrush(interpolatedColor);

            // Increment colorIndex, but not more than 5 times to avoid going too dark
            colorIndex = qMin(colorIndex + 1, 5);
}

foreach(QPieSlice *slice, series->slices()) {
    QString label = QString("%1 (%2%)")
        .arg(slice->label())
        .arg(100 * slice->percentage(), 0, 'f', 1);
    slice->setLabel(label);
}

// Création du graphique et ajout de la série de données
QChart *chart = new QChart();
chart->addSeries(series);
    // Set title font size and weight
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16); // Adjust the font size as needed
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);

chart->setTitle("Les statistiques des réclamations selon l'état: ");

// Configuration du graphique
chart->legend()->setAlignment(Qt::AlignRight);
chart->setAnimationOptions(QChart::AllAnimations);

// Affichage du graphique
QChartView *chartView = new QChartView(chart);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(640, 480);
chartView->show();
}


void MainWindow::on_pushButtonrec_clicked()
{ QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        return;  // L'utilisateur a annulé la boîte de dialogue
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    // En-tête du document
    QTextCharFormat headerFormat;
    headerFormat.setFontPointSize(14);
    headerFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(headerFormat);
    cursor.insertText("Liste des reclammations\n\n");

    // Crée un tableau avec des colonnes pour chaque champ de la table
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    QTextTable *table = cursor.insertTable(1, 7, tableFormat);
    QTextCursor cellCursor;

    // Remplir les en-têtes de colonne
    cellCursor = table->cellAt(0, 0).firstCursorPosition();
    cellCursor.insertText("ID_RECLAMMATIONS");

    cellCursor = table->cellAt(0, 1).firstCursorPosition();
    cellCursor.insertText("DATE_ACHAT");

    cellCursor = table->cellAt(0, 2).firstCursorPosition();
    cellCursor.insertText("DATE_REC");

    cellCursor = table->cellAt(0, 3).firstCursorPosition();
    cellCursor.insertText("DATE_REP");

    cellCursor = table->cellAt(0, 4).firstCursorPosition();
    cellCursor.insertText("MAIL_CLIENT");

    cellCursor = table->cellAt(0, 5).firstCursorPosition();
    cellCursor.insertText("ETAT");

    cellCursor = table->cellAt(0, 6).firstCursorPosition();
    cellCursor.insertText("DESCRIPTION");

    // Obtain the client data from your table model
    QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tab_reclammations->model());

    // Fill the table data
    for (int row = 0; row < model->rowCount(); ++row) {
        table->appendRows(1);

        for (int col = 0; col < 7; ++col) {
            cellCursor = table->cellAt(row + 1, col).firstCursorPosition();
            cellCursor.insertText(model->data(model->index(row, col)).toString());
        }
    }

    doc.print(&printer);

    // Display a success message
    QMessageBox::information(this, "Succès", "Liste des clients exportée sous forme de PDF.");
    QSqlQuery qry;
            QDateTime dateTime=QDateTime::currentDateTime();

            QString date=dateTime.toString();

            qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('Generation de PDF',:dateTime)");
            qry.bindValue(":dateTime",dateTime);

            qry.exec();
}

void MainWindow::on_pushButton_trierrec_clicked()
{
    ui->tab_reclammations->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::on_pushButton_rechercherrec_clicked()
{
    QString etat = ui->lineEdit_4->text();

    if (etat.isEmpty()) {
        // Affichez un message d'erreur si l'ID est vide.
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ETAT pour effectuer la recherche.");
        return;
    }
    QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");//declarations d'un fichier
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return;

        QTextStream cout(&file);
    // Vérifiez si l'ID existe dans la base de données.
    if (rec.etatExiste(etat)) {
        // Si l'ID existe, affichez ses données dans le tableau tab_bijoux.
        QSqlQueryModel* model = rec.afficherrecETAT(etat);
        ui->tab_reclammations->setModel(model);
        QString message2="Vous avez rechercher une reclammations\n";
                cout << message2;
                QFile file("C:/Users/USER/Desktop/Projet C++/Integration finale/Atelier_Connexion/historique.txt");
               if (!file.open(QIODevice::ReadOnly))
               {
                   QMessageBox::information(0,"info",file.errorString());
               }
               QTextStream in (&file);


              ui->hist->setText(in.readAll());


    } else {
        // Si l'ID n'existe pas, affichez un message d'erreur.
        QMessageBox::warning(this, "Erreur", "L'ETAT spécifié n'existe pas dans la base de données.");
    }
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{  int nb;
    if(arg1=="January")
        nb=1;
    else if(arg1=="February")
        nb=2;
    else if(arg1=="March")
        nb=3;
    else if(arg1=="April")
        nb=4;
    else if(arg1=="May")
        nb=5;
    else if(arg1=="June")
        nb=6;
    else if(arg1=="July")
        nb=7;
    else if(arg1=="August")
        nb=8;
    else if(arg1=="September")
        nb=9;
    else if(arg1=="October")
        nb=10;
    else if(arg1=="November")
        nb=11;
    //else if(arg1=="Decembre")
        nb=12;

    qDebug () << nb;
    QSqlQuery query;
    query.prepare("SELECT ID_RECLAMMATIONS, DATE_REC FROM GS_RECLAMMATIONS WHERE DATE_REC BETWEEN ? AND ?");
    QString startDateString = QDate(2023, nb, 1).toString("yyyy-MM-dd");
    QString endDateString = QDate(2023, nb, 31).toString("yyyy-MM-dd");
    query.addBindValue(startDateString);
    query.addBindValue(endDateString);
    if (!query.exec()) {
        qDebug() << "Failed to retrieve appointments from database!";
        return;
    }

    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(7); // Set the number of columns to 7
    model->setRowCount(31);

    // Get the start date (Monday) for the current week
    QDate startDate = QDate::currentDate().addDays(-QDate::currentDate().dayOfWeek() + 1);

    // Set the column headers to the dates for the current week
    for (int i = 0; i < 7; i++) {
        QString dateString = startDate.addDays(i).toString("ddd ");
        model->setHeaderData(i, Qt::Horizontal, dateString);
    }
QBrush brush(QColor(173, 216, 230));
    while (query.next()) {
        QString patientName = query.value("ID_reclammations").toString();
        QDate appointmentDate = query.value("DATE_REC").toDate();
        int row = appointmentDate.day() - 1;
        int column = appointmentDate.dayOfWeek() - 1;
        QStandardItem *existingItem = model->item(row, column);
           if (existingItem) {
               // If there is an existing item, append the new patient name to the existing tooltip
               QString existingToolTip = existingItem->toolTip();
               existingToolTip += ", " + patientName;
               existingItem->setToolTip(existingToolTip);

               // Append the new patient name to the existing item text
               QString existingText = existingItem->text();
               existingText += ", " + patientName;
               existingItem->setText(existingText);
           } else {
               // If there is no existing item, create a new item with the patient name
               QStandardItem *item = new QStandardItem(patientName);
               item->setToolTip(appointmentDate.toString());
               item->setBackground(brush);
               model->setItem(row, column, item);
           }
    }

    // Set the model on the table view
    ui->tableView_3->setModel(model);

}

//------------------------------------------------------------------------ARDUINO---------------------------------------------------------------------------------------

void MainWindow::update_label()
{

     data = A.read_from_arduino(); // Supposons que read_from_arduino() renvoie une QString
     QString datastring = QString::fromUtf8(data);
    qDebug() << "Data from Arduino: " << datastring;

    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE CARDKEY = :datastring");
    query.bindValue(":datastring", datastring);

    if (query.exec() && query.next()) {
        // Au moins une ligne a été trouvée

        /*QMessageBox msgBox;
        msgBox.setText("carte accepté, accès autorisé");
        msgBox.exec();*/
        ui->frame_login->hide();
        ui->frame_gestion->show();
        QString nomprenom = query.value(1).toString() + " " + query.value(2).toString();
        QByteArray nomprenomBYTE = nomprenom.toUtf8();
        A.write_to_arduino(nomprenomBYTE);

        query.prepare("UPDATE EMPLOYES SET STATUS = :nouvstatus WHERE CARDKEY = :datastring");
        query.bindValue(":datastring", datastring);
        query.bindValue(":nouvstatus", "actif");
        if (query.exec()) {qDebug() << "cbon employe wala actif";}
        else {qDebug() << "Erreur lors de la mise à jour de l'attribut status";}

    } else {
        // Aucune ligne trouvée ou erreur d'exécution de la requête
        ui->frame_gestion->hide();
        ui->frame_login->show();
        QMessageBox msgBox;
        msgBox.setText("carte refusé, accès non autorisé");
        msgBox.exec();


    }
    }




void MainWindow::combobox(){
    QSerialPort serial;
        serial.setPortName("COM5");
        serial.setBaudRate(QSerialPort::Baud9600);

    if (serial.open(QIODevice::ReadWrite)) {
            qDebug() << "Serial port opened successfully.";

        State currentState = State::WaitingForBoxCode;
        QByteArray boxCode;
        QByteArray quantit;
        QByteArray close;
        Bijou b ;
        QObject::connect(&serial, &QSerialPort::readyRead, [&]() {
            QByteArray data = serial.readAll();

            switch (currentState) {
            case State::WaitingForBoxCode:
                boxCode += data;
                if (boxCode.length() == 3) {
                    qDebug() << "Box code: " << boxCode;
                    if (b.boxExists(boxCode.toInt())) {
                        qDebug() << "TRUE";
                        QString command="b%255";
                        serial.write(command.toStdString().c_str());
                        currentState = State::WaitingForQuantite;
                    } else {
                        qDebug() << "FALSE";
                        QString command="r%255";
                        serial.write(command.toStdString().c_str());
                        boxCode.clear();
                    }
                }
                break;

            case State::WaitingForQuantite:
                quantit += data;
                if (quantit.endsWith("*")) {
                    quantit.chop(1);
                    qDebug() << "Quantite: " << quantit;
                    if (b.quantite(quantit.toInt() , boxCode.toInt())) {
                        qDebug() << "Valid quantite and box code"<<boxCode;
                        QString command="g%255";
                        serial.write(command.toStdString().c_str());
                        currentState = State::WaitingForClosing;
                    } else {
                        currentState = State::WaitingForBoxCode;
                        qDebug() << "Invalid quantite !!!";
                        QString command="r%255";
                        serial.write(command.toStdString().c_str());
                    }


                    boxCode.clear();
                    quantit.clear();
                }
                break;

            case State::WaitingForClosing:
                close+=data;
                if(close.endsWith("*")){
                    close.chop(1);
                    qDebug()<<"close  :  "<<close;
                    if(close=="CAB"){
                        qDebug() << "Closing the Box";
                        QString command="c";
                        serial.write(command.toStdString().c_str());
                        currentState = State::WaitingForBoxCode;
                    }
                    else{
                        qDebug() << "Box still open !!!";
                    }
                    close.clear();
                }
                break;
            default:
                break;
            }
        });
        }

}
