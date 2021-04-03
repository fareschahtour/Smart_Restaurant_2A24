#ifndef POSTE_H
#define POSTE_H

#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QVariant>
#include<QSqlQueryModel>
#include "employe.h"

class poste
{
    int matricule;
    QString type;
    int salaire;
    int nb_heures;

    employe e;
public:
    poste();
    ~poste();
    poste(int,QString,int,int);

    int getmatricule();
    QString gettype();
    int getsalaire();
    int getnb_heures();



    void setmatricule(int);
    void settype(QString);
    void setsalaire(int);
    void setnb_heures(int);


    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    poste trouver(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel * trisalaire();
    QSqlQueryModel * tritype();
    QSqlQueryModel * tri_matricule();
    QSqlQueryModel * recherche_poste(const QString&);
    QSqlQueryModel * recherche_type_matricule(const QString&);
    QSqlQueryModel * recherche_type_salaire(const QString&);
    QSqlQueryModel * recherche_matricule_salaire(const QString&);
    QSqlQueryModel * recherche_type(const QString&);
    QSqlQueryModel * recherche_matricule(const QString&);
    QSqlQueryModel * recherche_salaire(const QString&);

    QStringList listPoste();


};

#endif // POSTE_H
