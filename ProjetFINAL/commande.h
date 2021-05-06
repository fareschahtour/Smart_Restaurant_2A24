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
            int numero,ref,qte,PrixUnit,montant;

        public:
            commande(){}
            commande(int,int,int,int,int);

            int get_numero(){return numero;}
            int get_ref(){return ref;}
            int get_qte(){return qte;}
            int get_prix_unit(){return PrixUnit;}
            int get_montant(){return montant;}

            void set_numero(int numero){this->numero=numero;}
            void set_ref(int ref){this->ref=ref;}
            void set_qte(int qte){this->qte=qte;}
            void set_prix_unit(int PrixUnit){this->PrixUnit=PrixUnit;}
            void set_montant(int montant){this->montant=montant;}

            bool ajouter_commande();

            QSqlQueryModel* afficher();
            QSqlQueryModel* afficher_numero(int);
            QSqlQueryModel* afficher_ref(int);
            QSqlQueryModel* afficher_montant(int);

            bool modifier_commande(int);
            bool recherche_ref(int);
            bool recherche_numc(int);
            bool recherche_montant(int);
            bool supprimer_commande(int);


};



#endif // COMMANDE_H
