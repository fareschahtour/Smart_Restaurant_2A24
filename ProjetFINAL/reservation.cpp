#include "reservation.h"

reservation::reservation()
{

}

reservation::reservation(int id,int nbtable,QDate datereser,int heure)
{
    this->id=id;
    this->nbtable=nbtable;
    this->datereser=datereser;
    this->heure=heure;
}

reservation::reservation(int nbtable,QDate datereser,int heure)
{
    this->nbtable=nbtable;
    this->datereser=datereser;
    this->heure=heure;
}

//*******AJOUTER

bool reservation::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO RESERVATION (NBTABLE, DATERESERVATION, HEURE) "
                    "VALUES (:nbtable, :datereser, :heure)");


query.bindValue(":nbtable", nbtable);
query.bindValue(":datereser", datereser);
query.bindValue(":heure", heure);


return    query.exec();
}

//******AFFICHER

QSqlQueryModel * reservation::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from RESERVATION");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre de table"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date reservation"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));


    return model;
}

//*******SUPPRIMPER

bool reservation::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from RESERVATION where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool reservation::modifier(QString nbtable, QDate datereser,QString heure,QString id)
{
QSqlQuery query;

query.prepare("UPDATE RESERVATION SET NBTABLE= :nbtable, DATERESERVATION= :datereser, HEURE= :heure "
                    " WHERE  ID = :id ");


query.bindValue(":id", id);
query.bindValue(":nbtable", nbtable);
query.bindValue(":datereser", datereser);
query.bindValue(":heure", heure);


return    query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * reservation::remplircomboreser()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from RESERVATION");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery reservation::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from RESERVATION where ID= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}

//******RECHERCHE AVANCEE

QSqlQueryModel * reservation::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from RESERVATION  where (NBTABLE LIKE '%"+res+"%' OR ID LIKE '%"+res+"%' OR HEURE LIKE '%"+res+"%' )");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre de table"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date reservation"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));


    return model;
}

//******AFFICHER TRI

QSqlQueryModel * reservation::triafficher(QString col)
{QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from RESERVATION order by "+col);
    query.exec();


model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre de table"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date reservation"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));

return model;
}


