#ifndef GESTION_FOURNISSEUR_H
#define GESTION_FOURNISSEUR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets/QMessageBox>
#include "fournisseur.h"
#include "matiere.h"

namespace Ui {
class Gestion_fournisseur;
}

class Gestion_fournisseur : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gestion_fournisseur(QWidget *parent = nullptr);
    ~Gestion_fournisseur();
private slots:
    void on_AJOUTER_clicked();

    void on_SUPPRIMER_clicked();

    void on_cinTRI_clicked();

    void on_nomTRI_clicked();

    void on_numTRI_clicked();

    void on_RECHERCHER_clicked();

    void on_MODIFIER_clicked();

    void on_rechercheMODIFIER_clicked();

    void on_AJOUTER_M_clicked();

    void on_SUPPRIMER_M_clicked();

    void on_rechercheMODIFIER_M_clicked();

    void on_MODIFIER_M_clicked();

    void on_RECHERCHER_M_clicked();

    void on_idTRI_clicked();

    void on_NOM_M_TRI_clicked();

    void on_qteTRI_clicked();

    void on_PDF_clicked();

    void on_imprimer_clicked();

    void on_browseBtn_clicked();

    void on_sendBtn_clicked();

    void on_Excel_clicked();

    void on_listematiere_clicked();

    void on_listefournisseur_clicked();

    void statrefresh();


private:
    void on_AJOUTER_2_clicked();
    Fournisseur F;
    Matiere M;
    QStringList files;

    Ui::Gestion_fournisseur *ui;
};

#endif // GESTION_FOURNISSEUR_H
