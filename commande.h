#ifndef COMMANDE_H
#define COMMANDE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

        namespace Ui {
        class commande;
        }
        class commande
        {
            QString designation;
            int ref,qte,PrixUnit,montant;

        public:
            commande();
            commande(QString,int,int,int,int);

            QString get_designation(){return designation;}
            int get_ref(){return ref;}
            int get_qte(){return qte;}
            int get_prix_unit(){return PrixUnit;}
            int get_montant(){return montant;}

            void set_designation(QString designation){this->designation=designation;}
            void set_ref(int ref){this->ref=ref;}
            void set_qte(int qte){this->qte=qte;}
            void set_prix_unit(int PrixUnit){this->PrixUnit=PrixUnit;}
            void set_montant(int montant){this->montant=montant;}

            bool ajouter_commande();
            QSqlQueryModel * afficher();
            bool supprimer(int);
            bool update_commande();
            QSqlQueryModel * rechercher(QString);
            QSqlQueryModel * trie_az();
            QSqlQueryModel * trie_qte();
            QSqlQueryModel * trie_mont();


};



#endif // COMMANDE_H
