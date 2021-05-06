#include "poste.h"
#include <QMessageBox>



poste::poste(int matricule,QString type,int salaire,int nb_heures)
{
    this->matricule=matricule;
    this->type=type;
    this->salaire=salaire;
    this->nb_heures=nb_heures;

}


bool poste::ajouter_poste()
{

 // bool test=false;
  QSqlQuery query;
  QString res = QString::number(matricule);
  QString res1 = QString::number(salaire);
  QString res2 = QString::number(nb_heures);

  query.prepare("INSERT INTO POSTE (matricule, type, salaire, nb_heures) "
                 " VALUES (:matricule, :type, :salaire, :nb_heures)");

  query.bindValue(":matricule",res);
  query.bindValue(":type",type);
  query.bindValue(":salaire",res1);
  query.bindValue(":nb_heures",res2);

  return query.exec();
  //return test;

}


bool poste::supprimer_poste(int)
{
QSqlQuery query;
QString res = QString::number(matricule);
query.prepare("Delete from POSTE where matricule= :matricule");
query.bindValue(":matricule",matricule );
return query.exec();
}


QSqlQueryModel * poste::afficher_poste()
{
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select * from POSTE");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("salaire"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("nb_heures"));
return model;
}

bool poste::recherche_matricule(int matricule)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM POSTE WHERE MATRICULE= :matricule");
    query.bindValue(":matricule", matricule);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("poste n existe pas");
        msgBox.exec();
        return false;
    }
}

bool poste::modifier_poste(int matricule)
{
    QSqlQuery query;
    QString r1=QString::number(matricule);
    QString r2=QString::number(salaire);
    QString r3=QString::number(nb_heures);


    if (recherche_matricule(matricule))
    {

          query.prepare("UPDATE POSTE SET MATRICULE=:matricule, TYPE=:type, SALAIRE=:salaire, NB_HEURES=:nb_heures WHERE MATRICULE=:matricule");
          query.bindValue(":matricule", r1);
          query.bindValue(":type", type);
          query.bindValue(":salaire", r2);
          query.bindValue(":nb_heures",r3);

    }
          return query.exec();
}
//STAT
QStringList poste::listeposte(){
    QSqlQuery query;
    query.prepare("select DISTINCT TYPE from POSTE");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}

int poste::calcultype(QString marque){
    QSqlQuery query;
     query.prepare("select  * from POSTE  WHERE TYPE=:marque");
     query.bindValue(":marque", marque );
     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}

