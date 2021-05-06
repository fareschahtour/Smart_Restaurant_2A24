#include "commande.h"
#include <QMessageBox>



commande::commande(int numero,int ref,int qte,int PrixUnit,int montant)
{
    this->numero=numero;
    this->ref=ref;
    this->qte=qte;
    this->PrixUnit=PrixUnit;
    this->montant=montant;
}


bool commande::ajouter_commande()
{

 // bool test=false;
  QSqlQuery query;
  QString res = QString::number(numero);
  QString res1 = QString::number(ref);
  QString res2 = QString::number(qte);
  QString res3 = QString::number(PrixUnit);
  QString res4 = QString::number(montant);

  query.prepare("INSERT INTO COMMANDE (numero, ref, qte, PrixUnit, montant) "
                 " VALUES (:numero, :ref, :qte, :PrixUnit, :montant)");

  query.bindValue(":numero",res);
  query.bindValue(":ref",res1);
  query.bindValue(":qte",res2);
  query.bindValue(":PrixUnit",res3);
  query.bindValue(":montant",res4);

  return query.exec();
  //return test;

}


bool commande::supprimer_commande(int)
{
QSqlQuery query;
QString res = QString::number(ref);
query.prepare("Delete from commande where REF= :ref");
query.bindValue(":ref",res);
return query.exec();
}


QSqlQueryModel * commande::afficher()
{
QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select * from commande");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("numero"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
return model;
}

bool commande::recherche_ref(int ref)
{
    QMessageBox msgBox;
    QSqlQuery query;
    QString ref_string=QString::number(ref);

    query.prepare("SELECT * FROM COMMANDE WHERE REF= :ref");
    query.bindValue(":ref", ref_string);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {

        msgBox.setText("commande n existe pas");
        msgBox.exec();
        return false;
    }
}



bool commande::recherche_numc(int numero)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM COMMANDE WHERE NUMERO= :numero");
    query.bindValue(":numero", numero);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("commande n existe pas");
        msgBox.exec();
        return false;
    }
}



bool commande::recherche_montant(int montant)
{

    QMessageBox msgBox;
    QSqlQuery query;
    query.prepare("SELECT * FROM COMMANDE WHERE MONTANT= :montant");
    query.bindValue(":montant", montant);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("Commande n existe pas");
        msgBox.exec();
        return false;
    }
}


QSqlQueryModel* commande::afficher_numero(int numero)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString num=QString::number(numero);

          model->setQuery("SELECT * FROM COMMANDE WHERE NUMERO='"+num+"'");

    return model;
}




QSqlQueryModel* commande::afficher_ref(int ref)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString r=QString::number(ref);

          model->setQuery("SELECT * FROM COMMANDE WHERE REF='"+r+"'");

    return model;
}




QSqlQueryModel* commande::afficher_montant(int montant)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString m=QString::number(montant);


          model->setQuery("SELECT * FROM COMMANDE WHERE MONTANT='"+m+"'");

    return model;
}


bool commande::modifier_commande(int ref)
{
    QSqlQuery query;
    QString r1=QString::number(numero);
    QString r2=QString::number(ref);
    QString r3=QString::number(qte);
    QString r4=QString::number(PrixUnit);
    QString r5=QString::number(montant);


    if (recherche_numc(numero))
    {

          query.prepare("UPDATE COMMANDE SET REF=:ref, QTE=:qte, PrixUnit=:PrixUnit, montant=:montant WHERE NUMERO=:numero");
          query.bindValue(":numero", r1);
          query.bindValue(":ref", r2);
          query.bindValue(":qte",r3);
          query.bindValue(":PrixUnit", r4);
          query.bindValue(":montant", r5);

    }
          return query.exec();
}
