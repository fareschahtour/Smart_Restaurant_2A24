#ifndef TABLES_H
#define TABLES_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtGui>
#include <QtSql>
#include <QtCore>

class tables
{
public:
    tables();
    tables(int,int,int,QString);
    tables(int,int,QString);

    bool ajouter();
    bool supprimer(int);

    QSqlQueryModel * afficherecherche(QString);
    QSqlQueryModel * triafficher(QString);
    QSqlQueryModel * afficher();
    QSqlQueryModel * remplircomboreser();
    QSqlQuery request(QString);
    bool modifier(QString,QString,QString,QString);
    QStringList listetables();
    int calcultype(QString);


private:
    int id;
    int num;
    int nbplacedispo;
    QString type;
};

#endif // TABLES_H
