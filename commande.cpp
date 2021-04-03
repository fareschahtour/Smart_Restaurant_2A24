#include "commande.h"


commande::commande(QString designation,int ref,int qte,int PrixUnit,int montant)
{
    this->designation=designation;
    this->ref=ref;
    this->qte=qte;
    this->PrixUnit=PrixUnit;
    this->montant=montant;
}
bool commande::ajouter_commande()
{
  QSqlQuery query;
  QString res = QString::number(ref);
  QString res1 = QString::number(qte);
  QString res2 = QString::number(PrixUnit);
  QString res3 = QString::number(montant);

  query.prepare("insert into commande (designation,ref,qte,PrixUnit,montant)""values (:designation,:ref,:qte,:PrixUnit,:montant)");
  query.bindValue(":designation",designation);
  query.bindValue(":ref",res);
  query.bindValue(":qte",res1);
  query.bindValue(":PrixUnit",res2);
  query.bindValue(":montant",res3);

  return query.exec();
}
QSqlQueryModel * commande::afficher()
{
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select * from commande");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Designation"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
return model;
}



bool commande::update_commande()
{
  QSqlQuery query;
  QString res = QString::number(ref);
  QString res1 = QString::number(qte);
  QString res2 = QString::number(PrixUnit);
  QString res3 = QString::number(montant);

  query.prepare("update commande set designation='"+designation+"',qte='"+res1+"',PrixUnit='"+res2+"',montant='"+res3+"' where ref='"+res+"'");
  query.bindValue(":designation",designation);
  query.bindValue(":ref",res);
  query.bindValue(":qte",res1);
  query.bindValue(":PrixUnit",res2);
  query.bindValue(":montant",res3);

  return query.exec();
}



bool commande::supprimer(int ref)
{
QSqlQuery query;
QString res = QString::number(ref);
query.prepare("Delete from commande where ref= :ref");
query.bindValue(":ref",res);
return query.exec();
}



QSqlQueryModel * commande::trie_az()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from commande order by designation");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Designation"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
return model;
}



QSqlQueryModel * commande::trie_qte()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from commande order by qte");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Designation"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
return model;
}



QSqlQueryModel * commande::trie_mont()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from commande order by montant");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Designation"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
return model;
}
QSqlQueryModel * commande::rechercher(QString res)
{

QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from commande where ref ='"+res+"'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Designation"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
return model;
}
