#ifndef POSTE_H
#define POSTE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>


        namespace Ui {
        class poste;
        }
        class poste
        {
            QString type;
            int matricule,salaire,nb_heures;

        public:
            poste(){}
            poste(int,QString,int,int);

            int get_matricule(){return matricule;}
            QString get_type(){return type;}
            int get_salaire(){return salaire;}
            int get_nb_heures(){return nb_heures;}

            void set_matricule(int matricule){this->matricule=matricule;}
            void set_type(QString type){this->type=type;}
            void set_salaire(int salaire){this->salaire=salaire;}
            void set_nb_heures(int nb_heures){this->nb_heures=nb_heures;}


            bool recherche_matricule(int);
            bool ajouter_poste();

            QSqlQueryModel* afficher_poste();

            bool modifier_poste(int);
            bool supprimer_poste(int);

            QStringList listeposte();
            int calcultype(QString);

};



#endif // POSTE_H
