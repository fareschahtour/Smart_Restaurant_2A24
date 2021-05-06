#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtGui>
#include <QtSql>
#include <QtCore>

class reservation
{
public:
    reservation();
    reservation(int,int,QDate,int);
    reservation(int,QDate,int);

    bool ajouter();
    bool supprimer(int);

    QSqlQueryModel * afficherecherche(QString);
    QSqlQueryModel * triafficher(QString);
    QSqlQueryModel * afficher();
    QSqlQueryModel * remplircomboreser();
    QSqlQuery request(QString);
    bool modifier(QString,QDate,QString,QString);

private:
    int id;
    int nbtable;
    QDate datereser;
    int heure;
};

#endif // RESERVATION_H
