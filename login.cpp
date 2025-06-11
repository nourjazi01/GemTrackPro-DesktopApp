#include "login.h"
#include "ui_login.h"
#include "employes.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QMainWindow>
#include<QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "employes.h"
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
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_Login_clicked()
{
    /*employes e ;
    int id=ui->ID_login->text().toInt();
    QString mdp=ui->Pass_login->text();
    set_login(e.check_login(mdp,id));*/
    this->hide();
    MainWindow mainwin;
    mainwin.setmodal()

}
