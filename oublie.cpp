#include "oublie.h"
#include "ui_oublie.h"
#include "employes.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlQuery>
#include <QRegExpValidator>
#include <QtCharts>
#include "suppwindow.h"
#include "modifier.h"
#include <QSqlQuery>
oublie::oublie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oublie)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

oublie::~oublie()
{
    delete ui;
}

void oublie::on_rechercher_clicked()
{
    employes e ;
    bool test = e.idExists(ui->id_oub->text().toInt());
    if(test){
        ui->stackedWidget->setCurrentIndex(1);
        ui->label_question->setText(e.getquestion());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("Employes Introuvalbe!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void oublie::on_continuer_clicked()
{
    employes e ;
    e.idExists(ui->id_oub->text().toInt());
    QString reponse=ui->reponse->text();
    if(reponse==e.getreponse()){
        ui->stackedWidget->setCurrentIndex(2);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("Reponse Incorrecte!!!\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void oublie::on_enregistrer_clicked()
{
    int id = ui->id_oub->text().toInt() ;
    employes e ;
    e.idExists(id);
    QString idStr = QString::number(id);

    QString pass=ui->pass->text();
    QString pass2=ui->pass_2->text();
    if(pass==pass2){
        e.setpass(pass);
        QSqlQuery query ;
        query.prepare("update employes set password='"+pass+"' where id='"+idStr+"'");
        query.bindValue(":PASSWORD",pass);
        query.exec();
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("enregistrer avec succée\nClick Cancel to exit."), QMessageBox::Cancel);
        this->close();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("les mot de passe ne sont pas compatible\n"
                                 "       Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void oublie::on_annuler_clicked()
{
    this->close();
}
