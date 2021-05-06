#ifndef PROMOTIONS_H
#define PROMOTIONS_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class PROMOTIONS
{
public:
    PROMOTIONS();
    PROMOTIONS(int,QString,QString,QString,QString);
    QString get_dated();
    QString get_type();
    QString get_datef();
    QString get_pourcentage();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2();
    QSqlQueryModel * afficher3();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString);
    QSqlQueryModel * rechercher(const QString);
    QStringList listepromo();
    int calcultype(QString);

private:
    QString dated,type,datef,pourcentage;
    int id;


};
#endif // PROMOTIONS_H
