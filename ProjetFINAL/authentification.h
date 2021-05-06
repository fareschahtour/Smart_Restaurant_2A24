#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>

class authentification
{
public:

    authentification();
    authentification(int,QString,QString);
    int getid();
    QString getnomutilisateur();
    QString getmdp();

    void setid(int id);
    void setnomutilisateur(QString nometprenom);
    void setmdp(QString mdp);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id(int);
    QSqlQueryModel* afficher_nom(QString);
    bool modifier(int);
    bool recherche_id(int);
    bool recherche_id_mdp(int,QString);
    bool recherche_nom(QString);
    bool supprimer(int);
private:
    int id;
    QString nomutilisateur,mdp;
};

#endif // AUTHENTIFICATION_H
