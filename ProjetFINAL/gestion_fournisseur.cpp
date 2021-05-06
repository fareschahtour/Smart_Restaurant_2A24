#include "gestion_fournisseur.h"
#include "ui_gestion_fournisseur.h"
#include "fournisseur.h"
//#include "poste.h"
#include <QMessageBox>
#include <iostream>
#include <QMessageBox>
#include  <QDebug>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>

#include "smtpp.h"
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
#include "matiere.h"

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
#include <QTextDocument>
#include <QPainter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QStringList>
#include<QPropertyAnimation>
#include<QEasingCurve>
#include<QParallelAnimationGroup>
#include<QGraphicsOpacityEffect>
#include <QRegExpValidator>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QUrl>
#include <QSound>
#include <QtMultimedia>
#include <QWidget>
#include <QMediaPlayer>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include<QDate>
#include<QDateTime>
#include<QDesktopServices>

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


Gestion_fournisseur::Gestion_fournisseur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gestion_fournisseur)
{
    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));


    setWindowTitle("~~Smart Restaurant~~");


    ui->cinAJOUTER->setValidator (new QIntValidator(0,99999999, this));
    ui->cinSUPPRIMER->setValidator (new QIntValidator(0,99999999, this));

    ui->tablefournisseur->setModel(F.afficher());
    ui->tableMatiere->setModel(M.afficher());
    statrefresh();
}

Gestion_fournisseur::~Gestion_fournisseur()
{
    delete ui;
}



void Gestion_fournisseur::on_AJOUTER_clicked()
{
    int cin=ui->cinAJOUTER->text().toInt();

    QString nom=ui->nomAJOUTER->text();
    QString prenom=ui->prenomAJOUTER->text();
    QString adresse=ui->adresseAJOUTER->text();
    QString email=ui->emailAJOUTER->text();
    int num=ui->numAJOUTER->text().toInt();


    Fournisseur F (cin, nom, prenom, adresse, email, num);
    bool test=F.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succès");
    ui->tablefournisseur->setModel(F.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}

void Gestion_fournisseur::on_RECHERCHER_clicked()
{
    Fournisseur F;
        if (ui->RECHERCHE_COMBO->currentText()=="Rechercher par CIN")
        {
            int cin=ui->lineEdit->text().toInt();
            if (F.recherche_cin(cin))
            {
                ui->tablefournisseur->setModel(F.afficher_cin(cin));
            }
        }
        else if(ui->RECHERCHE_COMBO->currentText()=="Rechercher par nom")
        {
            QString nom=ui->lineEdit->text();
            if (F.recherche_nom(nom))
            {
                ui->tablefournisseur->setModel(F.afficher_nom(nom));
            }

        }
        /*else if(ui->comboBox->currentText()=="Rechercher par num")
        {
            int num=ui->lineEdit->text().toInt();
            if(C.recherche_num(num))
            {
                ui->table_commande->setModel(C.afficher_num(num));
            }
        }*/
}

void Gestion_fournisseur::on_cinTRI_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM FOURNISSEUR order by CIN ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numero"));
           ui->tablefournisseur->setModel(model);
           //ui->table_clients->setModel(E.afficher());
           ui->tablefournisseur->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();
}

void Gestion_fournisseur::on_nomTRI_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM FOURNISSEUR order by nom ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numero"));
             ui->tablefournisseur->setModel(model);
             ui->tablefournisseur->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void Gestion_fournisseur::on_numTRI_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM FOURNISSEUR order by num ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));

             ui->tablefournisseur->setModel(model);
             ui->tablefournisseur->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void Gestion_fournisseur::on_rechercheMODIFIER_clicked()
{
    Fournisseur F;
    QSqlQuery query;
    int cin=ui->cinMODIFIER->text().toInt();
    QString cin_string=QString::number(cin);
   if(F.recherche_cin(cin))
   {
       query.prepare("SELECT * FROM FOURNISSEUR WHERE cin like :cin");
       query.bindValue(0,cin_string);
       query.exec();
       while(query.next())
   {

       ui->nomMODIFIER->setText(query.value(1).toString());
       ui->prenomMODIFIER->setText(query.value(2).toString());
       ui->adresseMODIFIER->setText(query.value(3).toString());
       ui->emailMODIFIER->setText(query.value(4).toString());
       ui->numMODIFIER->setText(query.value(5).toString());

    }
   }
}

void Gestion_fournisseur::on_MODIFIER_clicked()
{
    Fournisseur F;
    QMessageBox msg;
    F.setcin(ui->cinMODIFIER->text().toInt());
    F.setnum(ui->numMODIFIER->text().toInt());
    F.setnom(ui->nomMODIFIER->text());
    F.setprenom(ui->prenomMODIFIER->text());
    F.setadresse(ui->adresseMODIFIER->text());
    F.setemail(ui->emailMODIFIER->text());

    bool test=F.modifier(F.getcin());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->tablefournisseur->setModel(F.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}

void Gestion_fournisseur::on_SUPPRIMER_clicked()
{
    QMessageBox msgBox;
    Fournisseur F1;
    F1.setcin(ui->cinSUPPRIMER->text().toInt());
    bool test=F1.supprimer(F1.getcin());
    if (test){
        ui->cinSUPPRIMER->clear();
        ui->tablefournisseur->setModel(F.afficher());
            msgBox.setText("fournisseur supprimé");
            msgBox.exec();
           }
}

void Gestion_fournisseur::on_AJOUTER_M_clicked()
{
    int id=ui->idAJOUTER->text().toInt();

    QString nom=ui->nomAJOUTER_2->text();
    int qte=ui->qteAJOUTER->text().toInt();
    QString type=ui->typeAJOUTER->text();




    Matiere M (id, nom, qte, type);
    bool test=M.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succès");
    ui->tableMatiere->setModel(M.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();

}

void Gestion_fournisseur::on_SUPPRIMER_M_clicked()
{
    QMessageBox msgBox;
    Matiere M1;
     M1.setid(ui->idSUPPRIMER->text().toInt());
    bool test= M1.supprimer( M1.getid());
    if (test){
        ui->idSUPPRIMER->clear();
        ui->tableMatiere->setModel(M.afficher());
            msgBox.setText("Matiere supprimé");
            msgBox.exec();
           }
}

void Gestion_fournisseur::on_rechercheMODIFIER_M_clicked()
{
    Matiere F;
    QSqlQuery query;
    int id=ui->idMODIFIER->text().toInt();
    QString id_string=QString::number(id);
   if(F.recherche_id(id))
   {
       query.prepare("SELECT * FROM MATIERE WHERE id like :id");
       query.bindValue(0,id_string);
       query.exec();
       while(query.next())
   {

       ui->nomMODIFIER_2->setText(query.value(1).toString());
       ui->qteMODIFIER->setText(query.value(3).toString());
       ui->typeMODIFIER->setText(query.value(2).toString());


    }
   }

}

void Gestion_fournisseur::on_MODIFIER_M_clicked()
{
    Matiere M;
    QMessageBox msg;
    M.setid(ui->idMODIFIER->text().toInt());

    M.setnom(ui->nomMODIFIER_2->text());
    M.setqte(ui->qteMODIFIER->text().toInt());
    M.settype(ui->typeMODIFIER->text());
    bool test=M.modifier(M.getid());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->tableMatiere->setModel(M.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();

}

void Gestion_fournisseur::on_RECHERCHER_M_clicked()
{
    Matiere M;
        if (ui->RECHERCHE_COMBO_M->currentText()=="Rechercher par id")
        {
            int id=ui->lineEdit_recherche->text().toInt();
            if (M.recherche_id(id))
            {
                ui->tableMatiere->setModel(M.afficher_id(id));
            }
        }
        else if(ui->RECHERCHE_COMBO_M->currentText()=="Rechercher par nom")
        {
            QString nom=ui->lineEdit_recherche->text();
            if (M.recherche_nom(nom))
            {
                ui->tableMatiere->setModel(M.afficher_nom(nom));
            }

        }
        else if (ui->RECHERCHE_COMBO_M->currentText()=="Rechercher par qte")
        {
            int qte=ui->lineEdit_recherche->text().toInt();
            if (M.recherche_qte(qte))
            {
                ui->tableMatiere->setModel(M.afficher_qte(qte));
            }
        }
       else if(ui->RECHERCHE_COMBO_M->currentText()=="Rechercher par type")
        {
            QString type=ui->lineEdit_recherche->text();
            if(M.recherche_type(type))
            {
                ui->tableMatiere->setModel(M.afficher_type(type));
            }
        }

}

void Gestion_fournisseur::on_idTRI_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM MATIERE order by ID ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte"));
           //model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
           //model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numero"));
           ui->tableMatiere->setModel(model);
           //ui->table_clients->setModel(E.afficher());
           ui->tableMatiere->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();
}

void Gestion_fournisseur::on_NOM_M_TRI_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM MATIERE order by nom ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte"));
             ui->tableMatiere->setModel(model);
             ui->tableMatiere->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();

}

void Gestion_fournisseur::on_qteTRI_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM MATIERE order by QTE ASC");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("qte"));

           ui->tableMatiere->setModel(model);

           ui->tableMatiere->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();

}

void Gestion_fournisseur::on_PDF_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->tableMatiere->model()->rowCount();
                  const int columnCount = ui->tableMatiere->model()->columnCount();

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
                      if (!ui->tableMatiere->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableMatiere->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableMatiere->isColumnHidden(column)) {
                              QString data = ui->tableMatiere->model()->data(ui->tableMatiere->model()->index(row, column)).toString().simplified();
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


void Gestion_fournisseur::on_imprimer_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;
}

void Gestion_fournisseur::on_browseBtn_clicked()
{
    QMessageBox msgBox ;

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

    //msg

    msgBox.setText("Mail envoyé avec succès.");
}

void Gestion_fournisseur::on_sendBtn_clicked()
{
    Smtpp* smtp = new Smtpp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void Gestion_fournisseur::on_Excel_clicked()
{
    QTableView *table;

                        table = ui->tableMatiere;


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

void Gestion_fournisseur::on_listematiere_clicked()
{
    QString strStream;
                           QTextStream out(&strStream);
                           const int rowCount = ui->tableMatiere->model()->rowCount();
                           const int columnCount =ui->tableMatiere->model()->columnCount();

                           out <<  "<html>\n"
                                   "<head>\n"
                                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                   <<  QString("<title>%1</title>\n").arg("PRODUIT")
                                   <<  "</head>\n"
                                   "<body bgcolor=#ffffff link=#5000A0>\n"
                                       "<img src='C:/Users/uxser/Desktop/Smart_Factory_2A5/Smart_Factory_2A5/logo.png' width='100' height ='100'>\n"
                                       "<h1>liste des formations </h1>"



                                       "<table border=1 cellspacing=0 cellpadding=2>\n";


                           // headers
                               out << "<thead><tr bgcolor=#f0f0f0>";
                               for (int column = 0; column < columnCount; column++)
                                   if (!ui->tableMatiere->isColumnHidden(column))
                                       out << QString("<th>%1</th>").arg(ui->tableMatiere->model()->headerData(column, Qt::Horizontal).toString());
                               out << "</tr></thead>\n";
                               // data table
                                  for (int row = 0; row < rowCount; row++) {
                                      out << "<tr>";
                                      for (int column = 0; column < columnCount; column++) {
                                          if (!ui->tableMatiere->isColumnHidden(column)) {
                                              QString data = ui->tableMatiere->model()->data(ui->tableMatiere->model()->index(row, column)).toString().simplified();
                                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                          }
                                      }
                                      out << "</tr>\n";
                                  }
                                  out <<  "</table>\n"
                                      "</body>\n"
                                      "</html>\n";

                   QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);


                     //  QTextDocument document;
                      // document.setHtml(html);
                       QPrinter printer(QPrinter::PrinterResolution);
                       printer.setOutputFormat(QPrinter::PdfFormat);
                       printer.setOutputFileName("formations.pdf");
                       document->print(&printer);
                       QDesktopServices::openUrl(QUrl::fromLocalFile("formations.pdf"));
}

void Gestion_fournisseur::on_listefournisseur_clicked()
{
    QString strStream;
                           QTextStream out(&strStream);
                           const int rowCount = ui->tablefournisseur->model()->rowCount();
                           const int columnCount =ui->tablefournisseur->model()->columnCount();

                           out <<  "<html>\n"
                                   "<head>\n"
                                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                   <<  QString("<title>%1</title>\n").arg("PRODUIT")
                                   <<  "</head>\n"
                                   "<body bgcolor=#ffffff link=#5000A0>\n"
                                       "<img src='C:/Users/uxser/Desktop/Smart_Factory_2A5/Smart_Factory_2A5/logo.png' width='100' height ='100'>\n"
                                       "<h1>liste des formations </h1>"



                                       "<table border=1 cellspacing=0 cellpadding=2>\n";


                           // headers
                               out << "<thead><tr bgcolor=#f0f0f0>";
                               for (int column = 0; column < columnCount; column++)
                                   if (!ui->tablefournisseur->isColumnHidden(column))
                                       out << QString("<th>%1</th>").arg(ui->tablefournisseur->model()->headerData(column, Qt::Horizontal).toString());
                               out << "</tr></thead>\n";
                               // data table
                                  for (int row = 0; row < rowCount; row++) {
                                      out << "<tr>";
                                      for (int column = 0; column < columnCount; column++) {
                                          if (!ui->tablefournisseur->isColumnHidden(column)) {
                                              QString data = ui->tablefournisseur->model()->data(ui->tablefournisseur->model()->index(row, column)).toString().simplified();
                                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                          }
                                      }
                                      out << "</tr>\n";
                                  }
                                  out <<  "</table>\n"
                                      "</body>\n"
                                      "</html>\n";

                   QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);


                     //  QTextDocument document;
                      // document.setHtml(html);
                       QPrinter printer(QPrinter::PrinterResolution);
                       printer.setOutputFormat(QPrinter::PdfFormat);
                       printer.setOutputFileName("matierePremiere.pdf");
                       document->print(&printer);
                       QDesktopServices::openUrl(QUrl::fromLocalFile("matierePremiere.pdf"));
}

// STATISTIQUE

void Gestion_fournisseur::statrefresh(){

    QtCharts::QPieSeries *series=new QtCharts::QPieSeries();
    QStringList l=M.listemat();
   for (int i = 0; i < l.size(); ++i){

       series->append("Type :"+l[i] ,M.calcultype(l[i]));
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


