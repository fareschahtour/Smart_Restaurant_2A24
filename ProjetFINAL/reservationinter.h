#ifndef RESERVATIONINTER_H
#define RESERVATIONINTER_H

#include <QDialog>
#include "reservation.h"
#include "smtp.h"
#include "tables.h"
namespace Ui {
class reservationinter;
}

class reservationinter : public QDialog
{
    Q_OBJECT

public:
    explicit reservationinter(QWidget *parent = nullptr);
    ~reservationinter();

private slots:
    void on_AjouterBouton_clicked();

    void on_ModifierBouton_clicked();

    void on_SupprimerBouton_clicked();

    void on_recherche_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_currentIndexChanged(const QString &arg1);


    void refresh();
    void refreshtable();

    void on_comboBox_modif_currentIndexChanged(const QString &arg1);

    void on_comboBox_Tri_currentIndexChanged(const QString &arg1);

    void sendMail();
    void mailSent(QString);

    void on_AjouterBouton_2_clicked();

    void on_comboBox_modif_2_currentIndexChanged(const QString &arg1);

    void on_ModifierBouton_2_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_SupprimerBouton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void statrefresh();

private:
    tables tmptables;

    reservation tmpreser;
    Ui::reservationinter *ui;
};

#endif // RESERVATIONINTER_H
