#ifndef CLIENTS_H
#define CLIENTS_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
class clients
{  QString nom, prenom, adresse, mail;
    int CIN, num;
public:

    clients(){}
    clients(int, int, QString, QString, QString, QString );



    QString getAdresse(){return adresse;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getmail(){return mail;}
    int getCIN(){return CIN;}
    int getNum(){return num;}

    /*void setAdresse(QString adresse){adresse=adresse;}
    void setNom(QString nom){nom=nom;}
    void setPrenom(QString prenom){prenom=prenom;}
    void setCIN(int CIN){CIN=CIN;}
    void setNum(int num){num=num;}*/

    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int,int,QString,QString,QString,QString);
    bool supprimer(int);

    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * trie_az();
    QSqlQueryModel * trie_qte();
    QSqlQueryModel * trie_mont();
};

#endif // CLIENTS_H
