#ifndef PRODUITS_H
#define PRODUITS_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class PRODUITS
{
public:
    PRODUITS();
    PRODUITS(int,QString,QString,QString,QString);
    QString get_nom();
    QString get_type();
    QString get_prix();
    QString get_description();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2();
    QSqlQueryModel * afficher3();
    QSqlQueryModel * afficher4();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString);
    QSqlQueryModel * rechercher(const QString);
private:
    QString nom,type,prix,description;
    int id;


};

#endif // PRODUITS_H
