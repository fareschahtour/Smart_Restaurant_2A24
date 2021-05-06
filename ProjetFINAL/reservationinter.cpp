#include "reservationinter.h"
#include "ui_reservationinter.h"
#include <QMessageBox>
#include <QMessageBox>
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
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QValidator>
#include <QIntValidator>
#include <QRegExp>
#include <QTabWidget>
#include<QtCharts/QChartView>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>

#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include<QGridLayout>


reservationinter::reservationinter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservationinter)
{
    ui->setupUi(this);

    setWindowTitle("Gestion de reservation");

    //Column size
    ui->tablemodifier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tablemodifier_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList list;
    list << "" << "NBTABLE" << "DATERESERVATION" << "HEURE";

    ui->comboBox_Tri->addItems(list);
    QStringList listtype;
    listtype << "" << "VIP" << "NORMAL" ;

    ui->comboBox_type->addItems(listtype);
    ui->comboBox_type_modif->addItems(listtype);

    //refresh combobox + tableau
    refresh();
    refreshtable();
    statrefresh();
}

void reservationinter::refresh(){
    //remplir tableau
    ui->tablemodifier->setModel(tmpreser.afficher());

    ui->comboBox->setModel(tmpreser.remplircomboreser());
    ui->comboBox_modif->setModel(tmpreser.remplircomboreser());

}

reservationinter::~reservationinter()
{
    delete ui;
}

void reservationinter::on_AjouterBouton_clicked()
{
    reservation ses(ui->nbplace->toPlainText().toInt(),ui->datereser->date(),ui->heure->toPlainText().toInt());
    bool test = ses.ajouter();
    if(test)
{
        QMessageBox::information(nullptr, QObject::tr("Ajouter une Reservation"),
        QObject::tr("Reservation ajouté.\n" "Click Cancel to exit."), QMessageBox::Cancel);

        }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("Ajouter une Reservation"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          }
    //refresh combobox + tableau
    refresh();
    sendMail();


}

void reservationinter::on_ModifierBouton_clicked()
{
    if((ui->nbplace_modif->toPlainText() != "") &&(ui->heure_modif->toPlainText() != ""))
    {
        if(tmpreser.modifier(ui->nbplace_modif->toPlainText(),ui->dateresermodif->date(),ui->heure_modif->toPlainText(),ui->comboBox_modif->currentText()))
        {
            //refresh combobox + tableau
            refresh();
            //message
            QMessageBox::information(this, QObject::tr("Modifier une reservation"),
                        QObject::tr("reservation Modifier.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier une reservation"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }

}

void reservationinter::on_SupprimerBouton_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                          "Supprimer","Voulez-vous vraiment supprimer ?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=tmpreser.supprimer(ui->comboBox->currentText().toInt());
        if(test)
        {
            //refresh combobox + tableau
            refresh();

            //message
            QMessageBox::information(this, QObject::tr("Supprimer une reservation"),
                        QObject::tr("reservation supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Supprimer une reservation"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }
}

void reservationinter::on_recherche_cursorPositionChanged(int arg1, int arg2)
{
    ui->tablemodifier->setModel(tmpreser.afficherecherche(ui->recherche->text()));

    QString test =ui->recherche->text();

    if(test=="")
    {
        ui->tablemodifier->setModel(tmpreser.afficher());//refresh
    }

}

void reservationinter::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->comboBox->currentText();

    query =tmpreser.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->nbplaceval->setText(query.value(1).toString());
            ui->datereserval->setText(query.value(2).toString());
            ui->heureval->setText(query.value(3).toString());
        }
    }

}


void reservationinter::on_comboBox_modif_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->comboBox_modif->currentText();

    query =tmpreser.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->nbplace_modif->setText(query.value(1).toString());
            ui->dateresermodif->setDate(query.value(2).toDate());
            ui->heure_modif->setText(query.value(3).toString());
        }
    }

}

void reservationinter::on_comboBox_Tri_currentIndexChanged(const QString &arg1)
{
    if(!(ui->comboBox_Tri->currentText()==""))
    {
        ui->tablemodifier->setModel(tmpreser.triafficher(ui->comboBox_Tri->currentText()));
    }

}


void reservationinter::sendMail()
{
    Smtp* smtp = new Smtp("makrem.benayed@esprit.tn", "benayed10", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("makrem.benayed@esprit.tn", "makrem.benayed@esprit.tn" ," objet test","Reservation ajouter");
}

void reservationinter::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void reservationinter::on_AjouterBouton_2_clicked()
{
    tables ses(ui->Num->toPlainText().toInt(),ui->nbplacedispo->toPlainText().toUInt(),ui->comboBox_type->currentText());
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
    refreshtable();

}

void reservationinter::on_comboBox_modif_2_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->comboBox_modif_2->currentText();

    query =tmptables.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->Num_modif->setText(query.value(1).toString());
            ui->nbplacedispomodif->setText(query.value(2).toString());
            ui->comboBox_type_modif->setCurrentText(query.value(3).toString());
        }
    }

}

void reservationinter::on_ModifierBouton_2_clicked()
{
    if((ui->Num_modif->toPlainText() != "") &&(ui->nbplacedispomodif->toPlainText() != "") )
    {
        if(tmptables.modifier(ui->Num_modif->toPlainText(),ui->nbplacedispomodif->toPlainText(),ui->comboBox_type_modif->currentText(),ui->comboBox_modif_2->currentText()))
        {
            //refresh combobox + tableau
            refreshtable();
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

void reservationinter::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->comboBox_2->currentText();

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

void reservationinter::on_SupprimerBouton_2_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                          "Supprimer","Voulez-vous vraiment supprimer ?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=tmptables.supprimer(ui->comboBox_2->currentText().toInt());
        if(test)
        {
            //refresh combobox + tableau
            refreshtable();

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

void reservationinter::refreshtable(){
    //remplir tableau
    ui->tablemodifier_2->setModel(tmptables.afficher());

    ui->comboBox_2->setModel(tmptables.remplircomboreser());
    ui->comboBox_modif_2->setModel(tmptables.remplircomboreser());

}

void reservationinter::on_pushButton_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->tablemodifier->model()->rowCount();
                  const int columnCount = ui->tablemodifier->model()->columnCount();

                  out <<  "<html>\n"
                      "<head>\n"
                      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      <<  QString("<title>%1</title>\n").arg("strTitle")
                      <<  "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"

                     //     "<align='right'> " << datefich << "</align>"
                      "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                  // headers
                  out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tablemodifier->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tablemodifier->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tablemodifier->isColumnHidden(column)) {
                              QString data = ui->tablemodifier->model()->data(ui->tablemodifier->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table> </center>\n"
                      "</body>\n"
                      "</html>\n";

            QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
              if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

             QPrinter printer (QPrinter::PrinterResolution);
              printer.setOutputFormat(QPrinter::PdfFormat);
             printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(fileName);

             QTextDocument doc;
              doc.setHtml(strStream);
              doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
              doc.print(&printer);
}

void reservationinter::on_pushButton_2_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;
}

// STATISTIQUE

void reservationinter::statrefresh(){

    QtCharts::QPieSeries *series=new QtCharts::QPieSeries();
    QStringList l=tmptables.listetables();
   for (int i = 0; i < l.size(); ++i){

       series->append("Vehicule marque :"+l[i] ,tmptables.calcultype(l[i]));
   }


    QtCharts::QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QtCharts::QChart *chart =new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("statistiques");
    chart->setAnimationOptions(QtCharts::QChart::AllAnimations);

    QtCharts::QChartView *chartview=new QtCharts::QChartView(chart);

    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(chartview,0,0);
    ui->statistiques->setLayout(mainLayout);

}

