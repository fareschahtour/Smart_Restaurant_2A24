#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <iostream>
#include <QMessageBox>
#include  <QDebug>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include <QMessageBox>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>

#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QValidator>
#include <QIntValidator>
#include <QRegExp>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Fournisseur C;
    ui->setupUi(this);


    ui->CIN->setValidator (new QIntValidator(0,999999999, this));
    ui->cinsupp->setValidator (new QIntValidator(0,999999999, this));
    //ui->ref->setValidator (new QIntValidator(0,999999999, this));
//    ui->refsupp->setValidator (new QIntValidator(0,999999999, this));

    ui->table_fournisseurr->setModel(C.afficher());
    //ui->table_commande->setModel(C1.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouterf_clicked()
{
    int CIN=ui->CIN->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString adresse=ui->adresse->text();
    QString email=ui->email->text();
    int num=ui->num->text().toInt();


    Fournisseur C(CIN, nom, prenom, adresse, email, num);
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");

   // ui->table_founisseur->setModel(C.afficher());
    ui->table_fournisseurr->setModel(C.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();

}

void MainWindow::on_suppf_clicked()
{
    QMessageBox msgBox;
    Fournisseur C;
    C.setCIN(ui->cinsupp->text().toInt());
    bool test=C.supprimer(C.getCIN());
    if (test){
        ui->cinsupp->clear();
        ui->table_fournisseurr->setModel(C.afficher());
            msgBox.setText("fournisseur supprimé");
            msgBox.exec();
           }

}
/*void MainWindow::on_supprimer_clicked()
{
    QMessageBox msgBox;
    employe E1;
    E1.setcin(ui->cin3->text().toInt());
    bool test=E1.supprimer(E1.getcin());
    if (test){
        ui->cin3->clear();
        ui->tableemploye->setModel(E.afficher());
            msgBox.setText("employe supprimé");
            msgBox.exec();
           }
}*/

void MainWindow::on_trie_par_CINf_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM FOURNISSEUR order by CIN ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
           ui->table_fournisseurr->setModel(model);
           //ui->table_clients->setModel(C.afficher());
           ui->table_fournisseurr->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();


}

void MainWindow::on_trie_par_nomf_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM FOURNISSEUR order by nom ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
             ui->table_fournisseurr->setModel(model);
             ui->table_fournisseurr->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();

}

void MainWindow::on_trie_par_numerof_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM FOURNISSEUR order by numero ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));

             ui->table_fournisseurr->setModel(model);
             ui->table_fournisseurr->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();

}

void MainWindow::on_recherche_f_clicked()
{
    Fournisseur C;
        if (ui->comboBox->currentText()=="Rechercher par CIN")
        {
            int cin=ui->lineEdit->text().toInt();
            if (C.recherche_cin(cin))
            {
                ui->table_fournisseurr->setModel(C.afficher_cin(cin));
            }
        }
        else if(ui->comboBox->currentText()=="Rechercher par nom")
        {
            QString nom=ui->lineEdit->text();
            if (C.recherche_nom(nom))
            {
                ui->table_fournisseurr->setModel(C.afficher_nom(nom));
            }

        }
        else if(ui->comboBox->currentText()=="Rechercher par numero")
        {
            int num=ui->lineEdit->text().toInt();
            if(C.recherche_num(num))
            {
                ui->table_fournisseurr->setModel(C.afficher_num(num));
            }
        }

}

void MainWindow::on_pushButton_clicked()
{
    Fournisseur C;
    QSqlQuery query;
    int cin=ui->cin_modif_f->text().toInt();
    QString cin_string=QString::number(cin);
   if(C.recherche_cin(cin))
   {
       query.prepare("SELECT * FROM FOURNISSEUR WHERE cin like :cin");
       query.bindValue(0,cin_string);
       query.exec();
       while(query.next())
   {
       ui->num_modif_f->setText(query.value(5).toString());
       ui->nom_modif_f->setText(query.value(2).toString());
       ui->prenom_modif_f->setText(query.value(3).toString());
       ui->adresse_modif_f->setText(query.value(4).toString());
       ui->email_modif_f->setText(query.value(1).toString());

    }
   }
}

/*void MainWindow::on_recherchemodif_clicked()
{
    employe E;
    QSqlQuery query;
    int cin=ui->cin2->text().toInt();
    QString cin_string=QString::number(cin);
   if(E.recherche_cin(cin))
   {
       query.prepare("SELECT * FROM EMPLOYE WHERE cin like :cin");
       query.bindValue(0,cin_string);
       query.exec();
       while(query.next())
   {
       ui->num2->setText(query.value(5).toString());
       ui->nom2->setText(query.value(2).toString());
       ui->prenom2->setText(query.value(3).toString());
       ui->adresse2->setText(query.value(4).toString());
       ui->email2->setText(query.value(1).toString());

    }
   }
}

void MainWindow::on_modifier_clicked()
{
    employe E;
    QMessageBox msg;
    E.setcin(ui->cin2->text().toInt());
    E.setnum(ui->num2->text().toInt());
    E.setnom(ui->nom2->text());
    E.setprenom(ui->prenom2->text());
    E.setadresse(ui->adresse2->text());
    E.setemail(ui->email2->text());

    bool test=E.modifier(E.getcin());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->tableemploye->setModel(E.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}

void MainWindow::on_recherchemodif_clicked()
{
    employe E;
    QSqlQuery query;
    int cin=ui->cin2->text().toInt();
    QString cin_string=QString::number(cin);
   if(E.recherche_cin(cin))
   {
       query.prepare("SELECT * FROM EMPLOYE WHERE cin like :cin");
       query.bindValue(0,cin_string);
       query.exec();
       while(query.next())
   {
       ui->num2->setText(query.value(5).toString());
       ui->nom2->setText(query.value(2).toString());
       ui->prenom2->setText(query.value(3).toString());
       ui->adresse2->setText(query.value(4).toString());
       ui->email2->setText(query.value(1).toString());

    }
   }
}*/
void MainWindow::on_modifier_f_clicked()
{
    Fournisseur C;
    QMessageBox msg;
    C.setCIN(ui->cin_modif_f->text().toInt());
    C.setNum(ui->num_modif_f->text().toInt());
    C.setNom(ui->nom_modif_f->text());
    C.setPrenom(ui->prenom_modif_f->text());
    C.setAdresse(ui->adresse_modif_f->text());
    C.setEmail(ui->email_modif_f->text());


    bool test=C.modifier(C.getCIN());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->table_fournisseurr->setModel(C.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();

}
