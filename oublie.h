#ifndef OUBLIE_H
#define OUBLIE_H

#include <QDialog>

namespace Ui {
class oublie;
}

class oublie : public QDialog
{
    Q_OBJECT

public:
    explicit oublie(QWidget *parent = nullptr);
    ~oublie();

private slots:
    void on_rechercher_clicked();

    void on_continuer_clicked();

    void on_enregistrer_clicked();

    void on_annuler_clicked();

private:
    Ui::oublie *ui;
};

#endif // OUBLIE_H
