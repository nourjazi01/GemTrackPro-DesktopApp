#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "employes.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "bijou.h"
#include "client.h"
#include "fournisseur.h"
#include "reclammations.h"
#include "arduino.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int return_index();
    void setSizePolicyRecursively(QWidget *widget, QSizePolicy::Policy horizontal, QSizePolicy::Policy vertical);
    void centerAndResize();
    void afficherBijouActuel();
    void combobox();



private slots:
    void on_emp_ajouter_clicked();

    void on_emp_supprimer_clicked();

    void on_emp_modifier_clicked();

    void on_emp_clear_clicked();

    void on_emp_Tri_comboBox_activated(const QString &arg1);

    void on_login_clicked();

    void on_gs_employes_clicked();

    void on_emp_statistique_clicked();

    void on_home_clicked();

    void on_gs_bijoux_clicked();

    void on_gs_client_clicked();

    void on_gs_fournisseur_clicked();

    void on_gs_reclamation_clicked();

    void on_logout_clicked();


    
    void on_oublie_clicked();

    void on_emp_pdf_clicked();

    void on_emp_ascendent_clicked();

    void on_emp_descendent_clicked();

    void on_emp_chercher_clicked();

    void searchemployes();

    void box_id();

    //BIJOUX

    void on_GBpb_ajouter_clicked();

        void on_GBpb_supprimer_clicked();

        void on_GBpb_modifier_clicked();

        void on_GBpb_annuler_ajout_clicked();

        void afficherInfoBijou(const QModelIndex &index);

        void on_GBpb_annuler_modif_clicked();

        void on_GBselect_image_clicked();

        void on_GBselect_image_modif_clicked();

        void on_GBpb_tri_clicked();

        void on_GBpb_rechercher_clicked();

        void on_GBpb_stat_clicked();

        void on_GBpb_pdf_clicked();

        void on_GBpb_generer_clicked();

        void on_GBpb_precedent_clicked();

        void on_GBpb_suivant_clicked();

        void on_GBpb_commencer_clicked();



    void on_gc_ajouter_clicked();

        void on_gc_supprimer_clicked();

        void on_gc_modifier_clicked();

        void afficherinfoclient(const QModelIndex &index);

        void on_gc_annuler_clicked();

        void on_gc_annuler2_clicked();



        void on_gc_rech_clicked();
        void searchClients();
        void generatesexestatistics();

        void on_gc_pdf_clicked();

        void sendMail();
        void mailSent(QString);
        void browse();



        void on_GFpb_ajouter_clicked();

            void on_GFpb_supprimer_clicked();

            void on_GFpb_modifier_clicked();

            void on_GFpb_annuler_ajout_clicked();

            void on_GFpb_annuler_supp_clicked();

            void afficherInfoFournisseur(const QModelIndex &index);

            void on_GFpb_annuler_m_clicked();

            void on_GFpb_trier_clicked();

            void on_GFpb_chercher_clicked();

            void on_GFpb_pdf_clicked();

            void on_GFpb_stat_clicked();


            void on_pb_supprimerrec_clicked();

            void on_pb_validerrec_clicked();


                void on_pb_modifierrec_clicked();

                void on_pushButton_statistiquerec_clicked();

                void on_pushButtonrec_clicked();

                void on_pushButton_trierrec_clicked();

                void on_pushButton_rechercherrec_clicked();

             void on_comboBox_activated(const QString &arg1);

                 // void update_label();


             void on_inside_employe_clicked();

             void on_inside_bijou_clicked();

             void on_inside_client_clicked();

             void on_inside_fournisseur_clicked();

             void on_inside_reclamation_clicked();

             void on_emp_tableView_clicked(const QModelIndex &index);

             //---------------arduino--------------
             void update_label();


private:
    Ui::MainWindow *ui;

    //EMPLOYES

    employes e ;

    //BIJOUX

    Bijou B;
    QByteArray selectedImageData;
    QSortFilterProxyModel *GBproxyModel;
    //QImage qrCodeImage;
    int currentBijouIndex = 0;
    QList<QString> bijouIds;

    //CLIENTS

    Client C;
    QStringList files;

    //FOURNISSEURS

    Fournisseur F;
    QSortFilterProxyModel *proxyModel;
    bool triAscendant;

    //RECLAMATIONS

    reclammations rec;
    QByteArray data;
    QSerialPort serial;
    QSortFilterProxyModel *proxyModelrec;

    //arduino nour
    arduino A;
    QByteArray data1;


};

#endif // MAINWINDOW_H
