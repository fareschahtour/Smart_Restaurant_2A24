#include "tables.h"

tables::tables()
{

}

tables::tables(int id,int num,int nbplacedispo,QString type)
{
    this->id=id;
    this->num=num;
    this->nbplacedispo=nbplacedispo;
    this->type=type;
}

tables::tables(int num,int nbplacedispo,QString type)
{
    this->num=num;
    this->nbplacedispo=nbplacedispo;
    this->type=type;
}



//*******AJOUTER

bool tables::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO TABLES (NUM, NBPLACEDISPO, TYPE) "
                    "VALUES (:num, :nbplacedispo, :type)");


query.bindValue(":num", num);
query.bindValue(":nbplacedispo", nbplacedispo);
query.bindValue(":type", type);


return    query.exec();
}

//******AFFICHER

QSqlQueryModel * tables::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from TABLES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero de table"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de table disponible"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));


    return model;
}

//*******SUPPRIMPER

bool tables::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from TABLES where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool tables::modifier(QString num, QString nbplacedispo,QString type,QString id)
{
QSqlQuery query;

query.prepare("UPDATE TABLES SET NUM= :num, NBPLACEDISPO= :nbplacedispo, TYPE= :type "
                    " WHERE  ID = :id ");


query.bindValue(":id", id);
query.bindValue(":num", num);
query.bindValue(":nbplacedispo", nbplacedispo);
query.bindValue(":type", type);


return    query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * tables::remplircomboreser()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from TABLES");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery tables::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from TABLES where ID= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}

//******RECHERCHE AVANCEE

QSqlQueryModel * tables::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from TABLES  where (NBTABLE LIKE '%"+res+"%' OR ID LIKE '%"+res+"%' OR HEURE LIKE '%"+res+"%' )");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero de table"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de table disponible"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));


    return model;
}

//******AFFICHER TRI

QSqlQueryModel * tables::triafficher(QString col)
{QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from TABLES order by "+col);
    query.exec();


model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero de table"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de table disponible"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));

return model;
}


//STAT
QStringList tables::listetables(){
    QSqlQuery query;
    query.prepare("select DISTINCT TYPE from TABLES");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}

int tables::calcultype(QString marque){
    QSqlQuery query;
     query.prepare("select  * from TABLES  WHERE TYPE=:marque");
     query.bindValue(":marque", marque );
     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}

