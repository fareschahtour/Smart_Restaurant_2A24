#include "produits.h"

#include <QDebug>

PRODUITS::PRODUITS()
{
    id=0;
    nom="";
    type="";
    prix="";
    description="";
}

PRODUITS::PRODUITS(int id,QString nom,QString type,QString prix,QString description)
{
  this->id=id;
  this->nom=nom;
  this->type=type;
  this->prix=prix;
  this->description=description;

}
    QString PRODUITS::get_nom(){return  nom;}
    QString PRODUITS::get_type() {return type;}
     QString PRODUITS::get_prix() {return prix;}
     QString PRODUITS::get_description() {return description;}
    int PRODUITS ::get_id(){return  id;}


bool PRODUITS::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO produits (ID,NOM,TYPE,PRIX,DESCRIPTION) "
                    "VALUES (:id,:nom,:type,:prix,:description)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":type", type);
query.bindValue(":prix", prix);
query.bindValue(":description", description);

return    query.exec();
}

QSqlQueryModel * PRODUITS::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from produits ORDER BY id");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Description"));


    return model;

}

QSqlQueryModel * PRODUITS::afficher2()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from produits ORDER BY Nom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Description"));



    return model;
}
QSqlQueryModel *  PRODUITS::afficher3()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from produits ORDER BY Type");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Description"));


    return model;

}
QSqlQueryModel *  PRODUITS::afficher4()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from produits ORDER BY Description");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Description"));


    return model;

}
bool  PRODUITS::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from produits where id= :id");
query.bindValue(":id", res);
return    query.exec();
}

bool PRODUITS::modifier(int id,QString nom,QString type,QString prix,QString description)
{


     QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("UPDATE produits SET NOM=:nom ,Type=:type,Prix=:prix,Description=:description, where id=:id");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":prix", prix);
    query.bindValue(":description", description);
     return    query.exec();
}
QSqlQueryModel * PRODUITS :: rechercher(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="select * from produits where id like '"+ch+"%' or Nom like '"+ch+"%' or Type like '"+ch+"%'    ";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prix "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Description"));
    return model;
}
