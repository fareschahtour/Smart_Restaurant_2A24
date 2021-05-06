#include "authentification.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>

authentification::authentification()
{
id=0;nomutilisateur=" ";mdp=" ";
}

authentification::authentification(int id,QString nomutilisateur,QString mdp)
{
 this->id=id;
 this->nomutilisateur=nomutilisateur;
 this->mdp=mdp;
}
int authentification::getid(){return id;}
QString authentification::getnomutilisateur(){return nomutilisateur;}
QString authentification::getmdp(){return mdp;}

void authentification::setid(int id){this->id=id;}
void authentification::setnomutilisateur(QString nomutilisateur){this->nomutilisateur=nomutilisateur;}
void authentification::setmdp(QString mdp){this->mdp=mdp;}
bool authentification::ajouter()
{
    bool test=false;
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("INSERT INTO profil (id,nom_utilisateur,mot_de_passe) "
                  "VALUES (:id,:nom_utilisateur,:mot_de_passe)");
    query.bindValue(":id", id_string);
    query.bindValue(":nom_utilisateur",nomutilisateur);
    query.bindValue(":mot_de_passe", mdp);
    return query.exec();
    return test;
}
bool authentification::supprimer(int id){

    QSqlQuery query;
    authentification A;
    bool test=A.recherche_id(id);
    if(test){
    query.prepare(" Delete from profil where id=:id");
    query.bindValue(":id", id);
    }
    return query.exec();
}

QSqlQueryModel* authentification::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM profil");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_utilisateur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("mot_de_passe"));
    return model;
}
bool authentification::modifier(int id){
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("update PROFIL SET nom_utilisateur=:nom_utilisateur , mot_de_passe=:mot_de_passe where id=:id");
    query.bindValue(":id", id_string);
    query.bindValue(":nom_utilisateur",nomutilisateur);
    query.bindValue(":mot_de_passe", mdp);
    return query.exec();
}

bool authentification::recherche_id(int id)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM PROFIL WHERE ID= :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {

        msgBox.setText("Profil n existe pas");
        msgBox.exec();
        return false;
    }
}

bool authentification::recherche_nom(QString nomutilisateur)
{
    QMessageBox msgBox;
    QSqlQuery query;
    query.prepare("SELECT * FROM PROFIL WHERE nom_utilisateur= :nom_utilisateur");
    query.bindValue(":nom_utilisateur", nomutilisateur);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("Profil n existe pas");
        msgBox.exec();
        return false;
    }
}

QSqlQueryModel* authentification::afficher_id(int id)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    QString id_string=QString::number(id);
    model->setQuery("SELECT * FROM PROFIL WHERE id='"+id_string+"'");
    return model;
}

QSqlQueryModel* authentification::afficher_nom(QString nomutilisateur)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROFIL WHERE nom_utilisateur='"+nomutilisateur+"'");
    return model;
}
bool authentification::recherche_id_mdp(int id,QString mdp)
{
    QMessageBox msgBox;
    QSqlQuery query;

    query.prepare("SELECT * FROM PROFIL WHERE ID= :id and mot_de_passe= :mot_de_passe");
    query.bindValue(":id", id);
    query.bindValue(":mot_de_passe", mdp);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        msgBox.setText("Profil n existe pas");
        msgBox.exec();
        return false;
    }
}
