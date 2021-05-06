#include "tablesinter.h"
#include "ui_tablesinter.h"
#include <QMessageBox>

tablesinter::tablesinter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tablesinter)
{
    ui->setupUi(this);
    setWindowTitle("Gestion des Tables");

    //Column size
    ui->tablemodifier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //refresh combobox + tableau
    refresh();


}

tablesinter::~tablesinter()
{
    delete ui;
}

void tablesinter::refresh(){
    //remplir tableau
    ui->tablemodifier->setModel(tmptables.afficher());

    ui->comboBox->setModel(tmptables.remplircomboreser());
    ui->comboBox_modif->setModel(tmptables.remplircomboreser());

}

void tablesinter::on_AjouterBouton_clicked()
{
    tables ses(ui->Num->toPlainText().toInt(),ui->nbplacedispo->toPlainText().toUInt(),ui->type->toPlainText());
    bool test = ses.ajouter();
    if(test)
{
        QMessageBox::information(nullptr, QObject::tr("Ajouter une Table"),
        QObject::tr("Table ajouté.\n" "Click Cancel to exit."), QMessageBox::Cancel);

        }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("Ajouter une Table"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          }
    //refresh combobox + tableau
    refresh();

}

void tablesinter::on_comboBox_modif_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->comboBox_modif->currentText();

    query =tmptables.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->Num_modif->setText(query.value(1).toString());
            ui->nbplacedispomodif->setText(query.value(2).toString());
            ui->Type_modif->setText(query.value(3).toString());
        }
    }

}

void tablesinter::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->comboBox->currentText();

    query =tmptables.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->Numval->setText(query.value(1).toString());
            ui->nbplacedispoval->setText(query.value(2).toString());
            ui->Typeval->setText(query.value(3).toString());
        }
    }


}

void tablesinter::on_ModifierBouton_clicked()
{
    if((ui->Num_modif->toPlainText() != "") &&(ui->nbplacedispomodif->toPlainText() != "") &&(ui->type->toPlainText() != ""))
    {
        if(tmptables.modifier(ui->Num_modif->toPlainText(),ui->nbplacedispomodif->toPlainText(),ui->Type_modif->toPlainText(),ui->comboBox_modif->currentText()))
        {
            //refresh combobox + tableau
            refresh();
            //message
            QMessageBox::information(this, QObject::tr("Modifier une Table"),
                        QObject::tr("Table Modifier.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier une Table"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }

}

void tablesinter::on_SupprimerBouton_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                          "Supprimer","Voulez-vous vraiment supprimer ?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=tmptables.supprimer(ui->comboBox->currentText().toInt());
        if(test)
        {
            //refresh combobox + tableau
            refresh();

            //message
            QMessageBox::information(this, QObject::tr("Supprimer une table"),
                        QObject::tr("table supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Supprimer une table"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }

}
