#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

namespace Ui {
class Fournisseur;
}

class Fournisseur
{
    QString nom, prenom, adresse, email;
    int cin, num;

public:
    Fournisseur();
    Fournisseur(int,QString,QString,QString,QString,int);
    int getcin();

    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getemail();
    int getnum();

    void setcin(int cin);

    void setnom(QString nom);
    void setprenom(QString prenom);
    void setadresse(QString adresse);
    void setemail(QString email);
    void setnum(int num);

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_cin(int);
    QSqlQueryModel* afficher_nom(QString);
    QSqlQueryModel* afficher_num(int);
    bool modifier(int);
    bool recherche_nom(QString);
    bool recherche_num(int);
    bool recherche_cin(int);
    bool supprimer(int);
};


#endif // FOURNISSEUR_H
