#include "employe.h"

employe::employe()
{
    this->id=0;
    this->nom="";
    this->prenom="";
    this->date_naiss=date_naiss.currentDate();
    this->sexe="";
}
employe::employe(int id,QString nom,QString prenom,QDate date_naiss,QString sexe,int id_post){
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->date_naiss=date_naiss;
    this->sexe=sexe;
    this->id_poste=id_post;
}
employe::~employe()
{

}
int employe::getid(){
    return id;
}
QString employe::getprenom(){
    return prenom;
}
QString employe::getnom(){
    return nom;
}
QDate employe::getdate_naiss(){
    return date_naiss;
}
QString employe::getsexe(){
    return sexe;
}
int employe::getid_poste(){
    return id_poste;
}


void employe::setid(int id){
    this->id=id;
}
void employe::setnom(QString nom){
    this->nom=nom;
}
void employe::setprenom(QString prenom){
    this->prenom=prenom;
}
void employe::setdate_naiss(QDate date_naiss){
    this->date_naiss=date_naiss;
}
void employe::setsexe(QString sexe){
    this->sexe=sexe;
}
void employe::setid_poste(int id_post){
    this->id_poste=id_poste;
}

bool employe::ajouter(){
    QSqlQuery query;
    query.prepare("insert into employe (id,nom,prenom,date_naissance,sexe,poste,id_departement) values (:id,:nom,:prenom,:date_naissance,:sexe,:poste,:id_departement)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naissance",date_naiss);
    query.bindValue(":sexe",sexe);
    query.bindValue(":id_poste",id_poste);
    return query.exec();
}


QSqlQueryModel * employe::afficher(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select employe.id,employe.nom,employe.prenom,employe.date_naissance,employe.sexe,departement.type from employe inner join poste on poste.matricule=employe.id_poste");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Poste"));
    return model;
}

bool employe::supprimer(int id){
    QSqlQuery q;
    q.prepare("select * from employe where id=:id");
    q.bindValue(":id",id);
    q.exec();
    int total=0;
    while(q.next()){
        total++;
    }
    if(total==1){
        QSqlQuery query;
        query.prepare("delete from employe where id=:id");
        query.bindValue(":id",id);
        return query.exec();
    }
    else{
        return false;
    }


}

employe employe::trouver(int id){
    QSqlQuery query;
    query.prepare("select * from employe where id=:id");
    query.bindValue(":id",id);
    query.exec();
    employe e;
    while(query.next()){
        e.setid(query.value(0).toInt());
        e.setnom(query.value(1).toString());
        e.setprenom(query.value(2).toString());
        e.setdate_naiss(query.value(3).toDate());
        e.setsexe(query.value(4).toString());
    }
    return e;
}


bool employe::modifier(int idr){
    QSqlQuery query;
    query.prepare("update employe set id=:id,nom=:nom,prenom=:prenom,date_naissance=:date_naissance,sexe=:sexe,poste=:poste,id_departement=:id_departement where id=:idr");
    query.bindValue(":idr",idr);
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date_naissance",date_naiss);
    query.bindValue(":sexe",sexe);
    query.bindValue(":id_poste",id_poste);
    return query.exec();
}

QSqlQueryModel * employe::recherche(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where nom like '"+str+"%' or prenom like '"+str+"%' or Extract(year from date_naissance) like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}

QSqlQueryModel * employe::recherche_n_p(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where nom like '"+str+"%' or prenom like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}

QSqlQueryModel * employe::recherche_n_d(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where nom like '"+str+"%' or Extract(year from date_naissance) like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}

QSqlQueryModel * employe::recherche_p_d(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where prenom like '"+str+"%' or Extract(year from date_naissance) like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}


QSqlQueryModel * employe::recherche_n(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where nom like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}
QSqlQueryModel * employe::recherche_p(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where prenom like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}
QSqlQueryModel * employe::recherche_d(const QString &str){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe where extract(year from date_naissance) like '"+str+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}
QSqlQueryModel * employe::tridate_naissance(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from employe order by date_naissance ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}
QSqlQueryModel* employe:: tri_prenom()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from employe order by prenom");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}
QSqlQueryModel* employe:: tri_id()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from employe order by id");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE N"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("SEXE"));

    return model;
}
