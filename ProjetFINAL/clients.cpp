#include <QMessageBox>
#include "clients.h"
clients::clients()

{cin=0;nom=" ";prenom=" ";adresse=" ";email=" ";num=0;}

clients::clients(int cin,int num, QString nom, QString prenom, QString adresse, QString email)

{
 this->cin=cin;
 this->num=num;
 this->nom=nom;
 this->prenom=prenom;
 this->adresse=adresse;
 this->email=email;
}

int clients::getcin(){return cin;}
int clients::getnum(){return num;}
QString clients::getnom(){return nom;}
QString clients::getprenom(){return prenom;}
QString clients::getadresse(){return adresse;}
QString clients::getemail(){return email;}

void clients::setcin(int cin){this->cin=cin;}
void clients::setnum(int num){this->num=num;}
void clients::setnom(QString nom){this->nom=nom;}
void clients::setprenom(QString prenom){this->prenom=prenom;}
void clients::setadresse(QString adresse){this->adresse=adresse;}
void clients::setemail(QString email){this->email=email;}

    bool clients::ajouter()
    {
       // bool test=false;
        QSqlQuery query;
        QString cin_string=QString::number(cin);
         QString r=QString::number(num);
        query.prepare("INSERT INTO clients (cin,numero,nom,prenom,adresse,email) "
                      "VALUES (:cin,:numero,:nom,:prenom,:adresse,:email)");
        query.bindValue(":cin", cin_string);
        query.bindValue(":numero", r);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":adresse", adresse);
        query.bindValue(":email",email);
        return query.exec();

       // return test;


}




bool clients::supprimer(int cin){
    QSqlQuery query;
    clients C;
    bool test=C.recherche_cin(cin);
    if(test){
    query.prepare(" Delete from CLIENTS where cin=:cin");
    query.bindValue(":cin", cin);
    }
    return query.exec();
}



QSqlQueryModel* clients::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM  CLIENTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

    return model;
}

bool clients::recherche_nom(QString nom)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM CLIENTS WHERE NOM= :nom");
    query.bindValue(":nom", nom);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {

        msgBox.setText("client n existe pas");
        msgBox.exec();
        return false;
    }
}



bool clients::recherche_num(int num)
{
    QMessageBox msgBox;
    QSqlQuery query;
    //QString n=QString::number(num);

    query.prepare("SELECT * FROM CLIENTS WHERE numero= :num");
    query.bindValue(":num", num);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("client n existe pas");
        msgBox.exec();
        return false;
    }
}



bool clients::recherche_cin(int cin)
{

    QMessageBox msgBox;
    QSqlQuery query;
     QString cin_string=QString::number(cin);
    query.prepare("SELECT * FROM CLIENTS WHERE CIN= :cin");
    query.bindValue(":cin", cin_string);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("CLIENTS n existe pas");
        msgBox.exec();
        return false;
    }
}



QSqlQueryModel* clients::afficher_cin(int cin)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString CIN_string=QString::number(cin);

          model->setQuery("SELECT * FROM CLIENTS WHERE CIN='"+CIN_string+"'");

    return model;
}




QSqlQueryModel* clients::afficher_nom(QString nom)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM CLIENTS WHERE NOM='"+nom+"'");

    return model;
}




QSqlQueryModel* clients::afficher_num(int num)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString num_string=QString::number(num);


          model->setQuery("SELECT * FROM CLIENTS WHERE NUMERO='"+num_string+"'");

    return model;
}





bool clients::modifier(int cin)
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString num_string=QString::number(num);

    if (recherche_cin(cin))
    {

          query.prepare("UPDATE CLIENTS SET nom=:nom, prenom=:prenom, adresse=:adresse, numero=:numero, email=:email WHERE CIN=:cin");
          query.bindValue(":cin", cin_string);
          query.bindValue(":numero", num_string);
          query.bindValue(":nom",nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":email", email);

    }
          return query.exec();
}
