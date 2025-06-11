#ifndef MODIFIER_H
#define MODIFIER_H
#include "employes.h"
#include <QDialog>

namespace Ui {
class Modifier;
}

class Modifier : public QDialog
{
    Q_OBJECT

public:
    explicit Modifier(QWidget *parent = nullptr);
    ~Modifier();

    bool id_exist(int id);
    void update(int id, const QString &nom, const QString &prenom, int age, const QString &mail, const QString &fonction, const QString &date_embauche, double salaire, const QString &code_securite, int num_tl);

private slots:
    void on_chercher_clicked();

    void on_modifie_clicked();

    void on_Annuler_clicked();

private:
    Ui::Modifier *ui;
    employes e;
};

#endif // MODIFIER_H
