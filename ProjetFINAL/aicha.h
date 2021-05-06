#ifndef AICHA_H
#define AICHA_H

#include <QtMultimedia/qsound.h>
#include "produits.h"
#include "promotions.h"
#include <QMainWindow>
#include <QFileDialog>
namespace Ui {
class aicha;
}

class aicha : public QWidget
{
    Q_OBJECT
    PRODUITS f , *fs;
    PROMOTIONS g , *gs;
    QString ch;
      QSound *sound= new QSound(":/click.wav");

public:
    explicit aicha(QWidget *parent = nullptr);
    ~aicha();
private slots:
    void on_AJOUTER_clicked();
    void on_pushButton_VALIDERMOD_clicked();
    void on_pushButton_SUPPRIMERFRMTS_clicked();
    void on_pushButton_add_teurs_clicked();
    void on_pushButton_mod_teurs_clicked();
    void on_pushButton_supp_teur_clicked();
    void on_rechercher_3_textChanged(const QString &ch);
    void on_rechercher_2_textChanged(const QString &ch);
    void on_radioButton_nom_clicked();
    void on_radioButton_cin_clicked();
    void on_radioButton_pre_clicked();
    void on_radioButton_CODE_clicked();
    void on_radioButton_NOM_clicked();
    void on_radioButton_DOMAINE_clicked();
    void on_radioButton_DEP_clicked();
    void on_pdf_tions_clicked();
    void on_pdf_teurs_clicked();
    void statrefresh();

private:
    Ui::aicha *ui;
    PRODUITS tmpPRODUITS;
    PROMOTIONS tmpPROMOTIONS;
};

#endif // AICHA_H
