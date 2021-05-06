#include <QMessageBox>
#include "employe.h"

employe::employe()

{cin=0;nom=" ";prenom=" ";adresse=" ";email=" ";num=0;}

employe::employe(int cin,int num, QString nom, QString prenom, QString adresse, QString email)

{
 this->cin=cin;
 this->num=num;
 this->nom=nom;
 this->prenom=prenom;
 this->adresse=adresse;
 this->email=email;
}

int employe::getcin(){return cin;}
int employe::getnum(){return num;}
QString employe::getnom(){return nom;}
QString employe::getprenom(){return prenom;}
QString employe::getadresse(){return adresse;}
QString employe::getemail(){return email;}

void employe::setcin(int cin){this->cin=cin;}
void employe::setnum(int num){this->num=num;}
void employe::setnom(QString nom){this->nom=nom;}
void employe::setprenom(QString prenom){this->prenom=prenom;}
void employe::setadresse(QString adresse){this->adresse=adresse;}
void employe::setemail(QString email){this->email=email;}

    bool employe::ajouter()
    {
       // bool test=false;
        QSqlQuery query;
        QString cin_string=QString::number(cin);
         QString r=QString::number(num);
        query.prepare("INSERT INTO EMPLOYE (cin,num,nom,prenom,adresse,email) "
                      "VALUES (:cin,:num,:nom,:prenom,:adresse,:email)");
        query.bindValue(":cin", cin_string);
        query.bindValue(":num", r);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":adresse", adresse);
        query.bindValue(":email",email);
        return query.exec();

       // return test;


}




bool employe::supprimer(int cin){
    QSqlQuery query;
    employe C;
    bool test=C.recherche_cin(cin);
    if(test){
    query.prepare(" Delete from EMPLOYE where cin=:cin");
    query.bindValue(":cin", cin);
    }
    return query.exec();
}



QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM  EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

    return model;
}

bool employe::recherche_nom(QString nom)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE NOM= :nom");
    query.bindValue(":nom", nom);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {

        msgBox.setText("EMPLOYE n existe pas");
        msgBox.exec();
        return false;
    }
}



bool employe::recherche_num(int)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE NUMERO= :num");
    query.bindValue(":numero", num);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("EMPLOYE n existe pas");
        msgBox.exec();
        return false;
    }
}



bool employe::recherche_cin(int cin)
{

    QMessageBox msgBox;
    QSqlQuery query;
     QString cin_string=QString::number(cin);
    query.prepare("SELECT * FROM EMPLOYE WHERE CIN= :cin");
    query.bindValue(":cin", cin_string);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("employe n existe pas");
        msgBox.exec();
        return false;
    }
}



QSqlQueryModel* employe::afficher_cin(int cin)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString CIN_string=QString::number(cin);

          model->setQuery("SELECT * FROM EMPLOYE WHERE CIN='"+CIN_string+"'");

    return model;
}




QSqlQueryModel* employe::afficher_nom(QString nom)
{
    QSqlQueryModel* model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYE WHERE NOM='"+nom+"'");

    return model;
}




QSqlQueryModel* employe::afficher_num(int)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString num_string=QString::number(num);


          model->setQuery("SELECT * FROM EMPLOYE WHERE NUMERO='"+num_string+"'");

    return model;
}





bool employe::modifier(int cin)
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString num_string=QString::number(num);

    if (recherche_cin(cin))
    {

          query.prepare("UPDATE EMPLOYE SET nom=:nom, prenom=:prenom, adresse=:adresse, num=:num, email=:email WHERE CIN=:cin");
          query.bindValue(":cin", cin_string);
          query.bindValue(":num", num_string);
          query.bindValue(":nom",nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":email", email);

    }
          return query.exec();
}
