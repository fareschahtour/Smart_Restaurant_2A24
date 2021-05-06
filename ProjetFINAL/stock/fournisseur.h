#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
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
/*class Fournisseur
{QString nom, prenom, adresse, email;
    int CIN, num;

public:
    Fournisseur(){}
    Fournisseur(int, QString, QString, QString , QString, int );


    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getAdresse(){return adresse;}
    QString getEmail(){return email;}

    int getCIN(){return CIN;}
    int getNum(){return num;}


    void setNom(QString nom){nom=nom;}
    void setPrenom(QString prenom){prenom=prenom;}
    void setAdresse(QString adresse){adresse=adresse;}
    void setEmail(QString email){email=email;}
    void setCIN(int CIN){CIN=CIN;}
    void setNum(int num){num=num;}

    bool ajouter();
     QSqlQueryModel * afficher();

     QSqlQueryModel* afficher_cin(int);
     QSqlQueryModel* afficher_nom(QString);
     QSqlQueryModel* afficher_num(int);
     bool modifier(int);
     bool recherche_nom(QString);
     bool recherche_num(int);
     bool recherche_cin(int);
     bool supprimer(int);
};*/

#endif // FOURNISSEUR_H
