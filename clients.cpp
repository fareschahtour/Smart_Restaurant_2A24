#include "clients.h"

clients::clients(int CIN, int num, QString adresse, QString nom, QString prenom, QString mail)
{
     this->CIN=CIN;
     this->num=num;
     this->adresse=adresse;
     this->nom=nom;
     this->prenom=prenom;
     this->mail=mail;
}

bool clients::ajouter()
{
    QSqlQuery query;
       QString res=QString::number(CIN);

       query.prepare("INSERT INTO CLIENTS (CIN,nom,prenom,adresse,num) VALUES (:CIN,:nom,:prenom,:adresse,:num)");
              query.bindValue(":CIN",res);
              query.bindValue(":prenom",prenom);
              query.bindValue(":nom",nom);
              query.bindValue(":adresse", adresse);
              query.bindValue(":num", num);

             return query.exec();

}


QSqlQueryModel * clients::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT* FROM clients");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("num"));



     return  model;
}

bool clients::modifier(int CIN, int num, QString nom, QString prenom , QString adresse)
{

    QSqlQuery query;
    QString res= QString::number(CIN);
    query.prepare("UPDATE clients SET nom=:nom,prenom=:prenom,adresse=:adresse,num=:num WHERE CIN =:CIN");
    query.bindValue(":CIN",res);
    query.bindValue(":prenom",nom);
    query.bindValue(":nom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":num",num);

    return query.exec();



}


bool clients::supprimer(int CIN)
{
    QSqlQuery query;
     QString res=QString::number(CIN);
     query.prepare("Delete from clients where CIN=:CIN");
      query.bindValue(":CIN",res);

        return query.exec();
}


QSqlQueryModel * clients::trie_az()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients order by nom asc");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("num"));
return model;
}



QSqlQueryModel * clients::trie_qte()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients order by qte");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("num"));
return model;
}



QSqlQueryModel * clients::trie_mont()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients order by montant");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("num"));
return model;
}
QSqlQueryModel * clients::rechercher(QString res)
{

QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients where ref ='"+res+"'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("num"));
return model;
}
