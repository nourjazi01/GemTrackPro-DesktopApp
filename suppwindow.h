#ifndef SUPPWINDOW_H
#define SUPPWINDOW_H

#include <QDialog>

namespace Ui {
class suppwindow;
}

class suppwindow : public QDialog
{
    Q_OBJECT

public:
    explicit suppwindow(QWidget *parent = nullptr);
    ~suppwindow();

private slots:
    void on_supprimer_clicked();

    void on_anuuler_clicked();

private:
    Ui::suppwindow *ui;
};

#endif // SUPPWINDOW_H
