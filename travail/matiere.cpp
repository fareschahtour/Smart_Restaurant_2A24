#include "matiere.h"
#include <QMessageBox>

Matiere::Matiere()

{id=0;nom=" ";qte=0;type=" ";}

Matiere::Matiere(int id,QString nom, int qte, QString type)
{
    this->id=id;
    this->nom=nom;
    this->qte=qte;
    this->type=type;

}

int Matiere::getid(){return id;}
QString Matiere::getnom(){return nom;}
int Matiere::getqte(){return qte;}
QString Matiere::gettype(){return type;}



void Matiere::setid(int id){this->id=id;}
void Matiere::setnom(QString nom){this->nom=nom;}
void Matiere::setqte(int qte){this->qte=qte;}
void Matiere::settype(QString type){this->type=type;}

bool Matiere::ajouter()
{
   // bool test=false;
    QSqlQuery query;
    QString id_string=QString::number(id);
     QString r=QString::number(qte);
    query.prepare("INSERT INTO MATIERE (id,nom,qte,type) "
                  "VALUES (:id,:nom,:qte,:type)");
    query.bindValue(":id", id_string);
    query.bindValue(":nom",nom);
    query.bindValue(":qte", r);
    query.bindValue(":type",type);

    return query.exec();

   // return test;


}


QSqlQueryModel* Matiere::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM  MATIERE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));


    return model;
}

bool Matiere::supprimer(int id){
    QSqlQuery query;
    Matiere M;
    bool test=M.recherche_id(id);
    if(test){
    query.prepare(" Delete from MATIERE where id=:id");
    query.bindValue(":id", id);
    }
    return query.exec();
}

QSqlQueryModel* Matiere::afficher_id(int id)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString id_string=QString::number(id);

          model->setQuery("SELECT * FROM MATIERE WHERE ID='"+id_string+"'");

    return model;
}

QSqlQueryModel* Matiere::afficher_qte(int qte)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString qte_string=QString::number(qte);

          model->setQuery("SELECT * FROM MATIERE WHERE QTE='"+qte_string+"'");

    return model;
}




QSqlQueryModel* Matiere::afficher_nom(QString nom)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM MATIERE WHERE NOM='"+nom+"'");

    return model;
}

QSqlQueryModel* Matiere::afficher_type(QString type)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM MATIERE WHERE NOM='"+type+"'");

    return model;
}


bool Matiere::recherche_id(int id)
{

    QMessageBox msgBox;
    QSqlQuery query;
     QString id_string=QString::number(id);
    query.prepare("SELECT * FROM MATIERE WHERE ID= :id");
    query.bindValue(":id", id_string);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("Matiere n existe pas");
        msgBox.exec();
        return false;
    }
}
bool Matiere::recherche_qte(int qte)
{

    QMessageBox msgBox;
    QSqlQuery query;
     QString qte_string=QString::number(qte);
    query.prepare("SELECT * FROM MATIERE WHERE QTE= :qte");
    query.bindValue(":qte", qte_string);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("Matiere n existe pas");
        msgBox.exec();
        return false;
    }
}


bool Matiere::recherche_nom(QString nom)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM MATIERE WHERE NOM= :nom");
    query.bindValue(":nom", nom);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {

        msgBox.setText("Matiere n existe pas");
        msgBox.exec();
        return false;
    }
}

bool Matiere::recherche_type(QString type)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM MATIERE WHERE TYPE= :type");
    query.bindValue(":type", type);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {

        msgBox.setText("Matiere n existe pas");
        msgBox.exec();
        return false;
    }
}

bool Matiere::modifier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString qte_string=QString::number(qte);

    if (recherche_id(id))
    {

          query.prepare("UPDATE MATIERE SET nom=:nom, qte=:qte, type=:type WHERE ID=:id");
          query.bindValue(":id", id_string);

          query.bindValue(":nom",nom);
          query.bindValue(":qte", qte_string);
          query.bindValue(":type", type);



    }
          return query.exec();
}




//STAT
QStringList Matiere::listemat(){
    QSqlQuery query;
    query.prepare("select DISTINCT TYPE from MATIERE");
    query.exec();
    QStringList list;
    while(query.next()){
        list.append(query.value(0).toString());
    }

    return list;
}

int Matiere::calcultype(QString marque){
    QSqlQuery query;
     query.prepare("select  * from MATIERE  WHERE TYPE=:marque");
     query.bindValue(":marque", marque );
     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}

