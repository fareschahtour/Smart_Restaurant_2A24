#include "fournisseur.h"
#include <QMessageBox>

Fournisseur::Fournisseur(int CIN, QString nom, QString prenom, QString adresse, QString email, int num)
{
    this->CIN=CIN;

    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->email=email;
    this->num=num;
}
bool Fournisseur::ajouter()
{
    QSqlQuery query;
       QString res=QString::number(CIN);

       query.prepare("INSERT INTO FOURNISSEUR (CIN,nom,prenom,adresse,email,num) VALUES (:CIN,:nom,:prenom,:adresse,:email,:num)");
              query.bindValue(":CIN",res);
              query.bindValue(":nom",nom);
              query.bindValue(":prenom",prenom);
              query.bindValue(":adresse", adresse);
              query.bindValue(":email", email);
              query.bindValue(":num", num);

             return query.exec();

}

QSqlQueryModel * Fournisseur::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT * FROM FOURNISSEUR");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("numero"));

     return  model;
}

bool Fournisseur::recherche_nom(QString nom)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM FOURNISSEUR WHERE NOM= :nom");
    query.bindValue(":nom", nom);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {

        msgBox.setText("fournisseur n existe pas");
        msgBox.exec();
        return false;
    }
}



bool Fournisseur::recherche_num(int)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM FOURNISSEUR WHERE NUMERO= :num");
    query.bindValue(":numero", num);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("Fournisseur n existe pas");
        msgBox.exec();
        return false;
    }
}



bool Fournisseur::recherche_cin(int cin)
{

    QMessageBox msgBox;
    QSqlQuery query;
     QString cin_string=QString::number(cin);
    query.prepare("SELECT * FROM FOURNISSEUR WHERE CIN= :cin");
    query.bindValue(":cin", cin_string);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("Fournisseur n existe pas");
        msgBox.exec();
        return false;
    }
}



QSqlQueryModel* Fournisseur::afficher_cin(int cin)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString CIN_string=QString::number(cin);

          model->setQuery("SELECT * FROM FOURNISSEUR WHERE CIN='"+CIN_string+"'");

    return model;
}




QSqlQueryModel* Fournisseur::afficher_nom(QString nom)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM FOURNISSEUR WHERE NOM='"+nom+"'");

    return model;
}




QSqlQueryModel* Fournisseur::afficher_num(int)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString num_string=QString::number(num);


          model->setQuery("SELECT * FROM FOURNISSEUR WHERE NUMERO='"+num_string+"'");

    return model;
}



bool Fournisseur::supprimer(int cin){
    QSqlQuery query;
    Fournisseur C;
    bool test=C.recherche_cin(cin);
    if(test){
    query.prepare(" Delete from FOURNISSEUR where cin=:cin");
    query.bindValue(":cin", cin);
    }
    return query.exec();
}



bool Fournisseur::modifier(int cin)
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString num_string=QString::number(num);

    if (recherche_cin(cin))
    {

          query.prepare("UPDATE FOURNISSEUR SET nom=:nom, prenom=:prenom, adresse=:adresse, email=:email, num=num  WHERE CIN=:cin");
          query.bindValue(":cin", cin_string);
          query.bindValue(":num", num_string);
          query.bindValue(":nom",nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":email", email);

    }
          return query.exec();
}

