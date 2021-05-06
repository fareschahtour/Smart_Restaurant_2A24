#ifndef NOUR_H
#define NOUR_H

#include <QMainWindow>
#include "employe.h"
#include "poste.h"
#include <QtWidgets/QMessageBox>
#include <QFileDialog>

namespace Ui {
class Nour;
}

class Nour : public QMainWindow
{
    Q_OBJECT

public:
    explicit Nour(QWidget *parent = nullptr);
    ~Nour();
private slots:
    void on_ajouter_clicked();

    void on_rechercher_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_recherchemodif_clicked();

    void on_tricin_clicked();

    void on_trinom_clicked();

    void on_trinum_clicked();

    void on_pdf_clicked();

    void on_imprimer_clicked();

    void on_trisalaire_clicked();

    void on_trinbheures_clicked();

    void on_trimatricule_clicked();

    void on_recherchermatricule_clicked();

    void on_modifier2_clicked();

    void on_supprimer2_clicked();

    void on_ajouter2_clicked();



    void on_sendBtn_clicked();

    void on_browseBtn_clicked();

    void on_Excel_clicked();

    void statrefresh();


private:
    Ui::Nour *ui;
    employe E;
    poste P;
    QStringList files;
};

#endif // NOUR_H
