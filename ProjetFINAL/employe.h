#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>


namespace Ui {
class employe;
}

class employe
{
    QString nom, prenom, adresse, email;
    int cin, num;

public:
    employe();
    employe(int,int,QString,QString,QString,QString);
    int getcin();
    int getnum();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getemail();

    void setcin(int cin);
    void setnum(int num);
    void setnom(QString nom);
    void setprenom(QString prenom);
    void setadresse(QString adresse);
    void setemail(QString email);

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

#endif // EMPLOYE_H
