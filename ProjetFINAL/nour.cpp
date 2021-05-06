#include "nour.h"
#include "ui_nour.h"
#include "employe.h"
#include "poste.h"
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


#include "smtpp.h"
#include "smtpp.cpp"
#include <QThread>
#include <QPixmap>
#include <QMessageBox>
#include <QTimer>
#include <QDate>
//#include <SmtpMime>
#include <QDateTime>
#include <QPlainTextEdit>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTextBrowser>
#include <QIntValidator>
#include <QAbstractSocket>

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



Nour::Nour(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Nour)
{
    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    setWindowTitle("~~Smart Restaurant~~");


    ui->cin1->setValidator (new QIntValidator(0,99999999, this));
    ui->cin3->setValidator (new QIntValidator(0,99999999, this));

    ui->tableemploye->setModel(E.afficher());
    ui->tablepostes->setModel(P.afficher_poste());
    statrefresh();
}

Nour::~Nour()
{
    delete ui;
}


void Nour::on_ajouter_clicked()
{
    int cin=ui->cin1->text().toInt();
    int num=ui->num1->text().toInt();
    QString nom=ui->nom1->text();
    QString prenom=ui->prenom1->text();
    QString adresse=ui->adresse1->text();
    QString email=ui->email1->text();


    employe E(cin, num, nom, prenom, adresse, email);
    bool test=E.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succès");
    ui->tableemploye->setModel(E.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}



void Nour::on_rechercher_clicked()
{
    employe E;
        if (ui->Recherche->currentText()=="Rechercher par CIN")
        {
            int cin=ui->lineEdit_17->text().toInt();
            if (E.recherche_cin(cin))
            {
                ui->tableemploye->setModel(E.afficher_cin(cin));
            }
        }
        else if(ui->Recherche->currentText()=="Rechercher par nom")
        {
            QString nom=ui->lineEdit_17->text();
            if (E.recherche_nom(nom))
            {
                ui->tableemploye->setModel(E.afficher_nom(nom));
            }

        }
        /*else if(ui->comboBox->currentText()=="Rechercher par numéro")
        {
            int num=ui->lineEdit->text().toInt();
            if(C.recherche_num(num))
            {
                ui->table_commande->setModel(C.afficher_num(num));
            }
        }*/
}

void Nour::on_supprimer_clicked()
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
}

void Nour::on_modifier_clicked()
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

void Nour::on_recherchemodif_clicked()
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
       ui->nom2->setText(query.value(4).toString());
       ui->prenom2->setText(query.value(3).toString());
       ui->adresse2->setText(query.value(2).toString());
       ui->email2->setText(query.value(1).toString());

    }
   }
}

void Nour::on_tricin_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM EMPLOYE order by CIN ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
           ui->tableemploye->setModel(model);
           //ui->table_clients->setModel(E.afficher());
           ui->tableemploye->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();
}

void Nour::on_trinom_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM EMPLOYE order by nom ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
             ui->tableemploye->setModel(model);
             ui->tableemploye->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void Nour::on_trinum_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM EMPLOYE order by num ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));

             ui->tableemploye->setModel(model);
             ui->tableemploye->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void Nour::on_pdf_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->tableemploye->model()->rowCount();
                  const int columnCount = ui->tableemploye->model()->columnCount();

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
                      if (!ui->tableemploye->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableemploye->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableemploye->isColumnHidden(column)) {
                              QString data = ui->tableemploye->model()->data(ui->tableemploye->model()->index(row, column)).toString().simplified();
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

void Nour::on_imprimer_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;
}

//maintenant les fonctions de postes

void Nour::on_trisalaire_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM POSTE order by SALAIRE ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Salaire"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nb_heures"));
           ui->tablepostes->setModel(model);

           ui->tablepostes->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();

}

void Nour::on_trinbheures_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM POSTE order by NB_HEURES ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Salaire"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nb_heures"));
           ui->tablepostes->setModel(model);

           ui->tablepostes->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();

}

void Nour::on_trimatricule_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM POSTE order by MATRICULE ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Salaire"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nb_heures"));
           ui->tablepostes->setModel(model);

           ui->tablepostes->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();

}


void Nour::on_recherchermatricule_clicked()
{

    poste P;
    QSqlQuery query;
    int matricule=ui->matricule2->text().toInt();
    QString matricule_string=QString::number(matricule);
   if(P.recherche_matricule(matricule))
   {
       query.prepare("SELECT * FROM POSTE WHERE matricule like :matricule");
       query.bindValue(0,matricule_string);
       query.exec();
       while(query.next())
   {
       ui->type2->setText(query.value(3).toString());
       ui->salaire2->setText(query.value(2).toString());
       ui->nb_heures2->setText(query.value(1).toString());

    }
   }
}


void Nour::on_modifier2_clicked()
{
    poste P;
    QMessageBox msg;
    P.set_matricule(ui->matricule2->text().toInt());
    P.set_type(ui->type2->text());
    P.set_salaire(ui->salaire2->text().toInt());
    P.set_nb_heures(ui->nb_heures2->text().toInt());

    bool test=P.modifier_poste(P.get_matricule());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->tablepostes->setModel(P.afficher_poste());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}


void Nour::on_supprimer2_clicked()
{
    QMessageBox msgBox;
    poste P1;
    P1.set_matricule(ui->matricule3->text().toInt());
    bool test=P1.supprimer_poste(P1.get_matricule());
    if (test){
        ui->matricule3->clear();
        ui->tablepostes->setModel(P.afficher_poste());
            msgBox.setText("poste supprimé");
            msgBox.exec();
           }
}

void Nour::on_ajouter2_clicked()
{
    int matricule=ui->matricule->text().toInt();
    QString type=ui->type->text();
    int salaire=ui->salaire->text().toInt();
    int nb_heures=ui->nb_heures->text().toInt();



    poste P (matricule, type, salaire, nb_heures);
    bool test=P.ajouter_poste();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succès");
    ui->tablepostes->setModel(P.afficher_poste());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}


//maintenant les fonctions se mailing


/*void Nour::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}*/


void Nour::on_sendBtn_clicked()
{
    Smtpp* smtp = new Smtpp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void Nour::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void Nour::on_Excel_clicked()
{
    QTableView *table;

                        table = ui->tableemploye;


                        QString filters("Excel Files (.xls)");

                        QString defaultFilter("Excel Files (*.xls)");

                        QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),

                                           filters, &defaultFilter);

                        QFile file(fileName);


                        QAbstractItemModel *model =  table->model();

                        if (file.open(QFile::WriteOnly | QFile::Truncate)) {

                            QTextStream data(&file);

                            QStringList strList;

                            for (int i = 0; i < model->columnCount(); i++) {

                                if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)

                                    strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");

                                else

                                    strList.append("");

                            }

                            data << strList.join(";") << "\n";

                            for (int i = 0; i < model->rowCount(); i++) {

                                strList.clear();

                                for (int j = 0; j < model->columnCount(); j++) {


                                    if (model->data(model->index(i, j)).toString().length() > 0)

                                        strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");

                                    else

                                        strList.append("");

                                }

                                data << strList.join(";") + "\n";

                            }

                            file.close();

                            QMessageBox::information(nullptr, QObject::tr("Export excel"),

                                                      QObject::tr("Export avec succes .\n"

                                                                  "Click OK to exit."), QMessageBox::Ok);
        }
}

// STATISTIQUE

void Nour::statrefresh(){

    QtCharts::QPieSeries *series=new QtCharts::QPieSeries();
    QStringList l=P.listeposte();
   for (int i = 0; i < l.size(); ++i){

       series->append("Type :"+l[i] ,P.calcultype(l[i]));
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

