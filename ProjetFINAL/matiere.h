#ifndef MATIERE_H
#define MATIERE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

namespace Ui {
class matiere;
}


class Matiere
{
    QString nom,  type;
    int id, qte;
public:
    Matiere();
    Matiere(int,QString,int,QString);


    int getid();
    QString getnom();
    int getqte();
    QString gettype();

    void setid(int id);
    void setnom(QString nom);
    void setqte(int qte);
    void settype(QString type);


    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id(int);
    QSqlQueryModel* afficher_nom(QString);
    QSqlQueryModel* afficher_type(QString);
    QSqlQueryModel* afficher_qte(int);
    bool modifier(int);
    bool recherche_nom(QString);
    bool recherche_type(QString);
    bool recherche_id(int);
    bool recherche_qte(int);
    bool supprimer(int);
    QStringList listemat();
    int calcultype(QString);

};

#endif // MATIERE_H
