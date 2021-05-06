#include "promotions.h"

#include <QDebug>

PROMOTIONS::PROMOTIONS()
{
    id=0;
    type="";
    dated="";
    datef="";
    pourcentage="";
}

PROMOTIONS::PROMOTIONS(int id,QString type,QString dated,QString datef,QString pourcentage)
{
  this->id=id;
  this->type=type;
  this->dated=dated;
  this->datef=datef;
  this->pourcentage=pourcentage;

}
    QString PROMOTIONS ::get_dated(){return  dated;}
    QString PROMOTIONS::get_type() {return type;}
     QString  PROMOTIONS::get_datef() {return datef;}
     QString  PROMOTIONS::get_pourcentage() {return pourcentage;}
    int  PROMOTIONS ::get_id(){return  id;}


bool PROMOTIONS::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO promotions (ID,TYPE,DATED,DATEF,POURCENTAGE) "
                    "VALUES (:id,:type,:dated,:datef,:pourcentage)");
query.bindValue(":id", id);
query.bindValue(":type", type);
query.bindValue(":dated", dated);
query.bindValue(":datef", datef);
query.bindValue(":pourcentage", pourcentage);

return    query.exec();
}

QSqlQueryModel * PROMOTIONS::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from promotions ORDER BY id");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("dated"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("datef "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("pourcentage"));


    return model;

}

QSqlQueryModel * PROMOTIONS::afficher2()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from promotions ORDER BY id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("dated"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datef "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("pourcentage"));



    return model;
}
QSqlQueryModel *  PROMOTIONS::afficher3()
{QSqlQueryModel * model= new QSqlQueryModel();


    model->setQuery("select * from promotions ORDER BY id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("dated"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datef "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("pourcentage"));


    return model;

}
bool  PROMOTIONS::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from promotions where id= :id");
query.bindValue(":id", res);
return    query.exec();
}

bool PROMOTIONS::modifier(int id,QString type,QString dated,QString datef,QString pourcentage)
{


     QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("UPDATE promotions SET Type=:type,dated=:dated ,datef=:datef,pourcentage=:pourcentage, where id=:id");
    query.bindValue(":id", res);
    query.bindValue(":type", type);
    query.bindValue(":dated", dated);
    query.bindValue(":datef", datef);
    query.bindValue(":pourcentage", pourcentage);
     return    query.exec();
}
QSqlQueryModel * PROMOTIONS :: rechercher(QString ch)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString str="select * from promotions where id like '"+ch+"%' or type like '"+ch+"%' or dated like '"+ch+"%'    ";
    model->setQuery(str);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("dated"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datef "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("pourcentage"));

    return model;
}

//STAT
QStringList PROMOTIONS::listepromo(){
    QSqlQuery query;
    query.prepare("select DISTINCT TYPE from promotions");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}

int PROMOTIONS::calcultype(QString marque){
    QSqlQuery query;
     query.prepare("select  * from promotions  WHERE TYPE=:marque");
     query.bindValue(":marque", marque );
     query.exec();
      int total=0;

     while(query.next()){
       total++;
     }


     return total;
}


