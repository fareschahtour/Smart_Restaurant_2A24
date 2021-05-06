#include "gest_cl_co.h"
#include "ui_gest_cl_co.h"
#include "clients.h"
#include "commande.h"
#include "mainwindow.h"
#include "QWidget"
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
#include "smtppp.h"
#include "smtppp.cpp"
#include <QAbstractSocket>
#include <QSslSocket>


gest_cl_co::gest_cl_co(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gest_cl_co)
{
    ui->setupUi(this);

    setWindowTitle("~~Smart Restaurant~~");
    ui->chatPage_3->setCurrentWidget(ui->loginPage);



    ui->CIN->setValidator (new QIntValidator(0,99999999, this));
    ui->cinsupp->setValidator (new QIntValidator(0,99999999, this));
    ui->ref->setValidator (new QIntValidator(0,99999999, this));
    ui->refsupp->setValidator (new QIntValidator(0,99999999, this));

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));


    socket = new QTcpSocket(this);

    // This is how we tell Qt to call our readyRead() and connected()
    // functions when the socket has text ready to be read, and is done
    // connecting to the server (respectively):
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));

    ui->table_clients->setModel(C.afficher());
    ui->table_commande->setModel(Co.afficher());
}

gest_cl_co::~gest_cl_co()
{
    delete ui;
}

void gest_cl_co::on_pushButton_2_clicked()
{
    int CIN=ui->CIN->text().toInt();
    int num=ui->num->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString adresse=ui->adresse->text();
    QString email=ui->email->text();


    clients C(CIN, num, nom, prenom, adresse, email);
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");
    ui->table_clients->setModel(C.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}



void gest_cl_co::on_pushButton_clicked()
{
    int numero=ui->numero->text().toInt();
    int ref=ui->ref->text().toInt();
    int qte=ui->qte->text().toInt();
    int PrixUnit =ui->prixUnitaire->text().toInt();
    int montant=ui->montant->text().toInt();


    commande Co (numero, ref, qte, PrixUnit, montant);
    bool test1=Co.ajouter_commande();
    QMessageBox msgBox;
    if(test1)
      {
      msgBox.setText("ajout avec succée");
      ui->table_commande->setModel(Co.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}


void gest_cl_co::on_pushButton_5_clicked()
{
    commande Co;
    Co.set_ref(ui->refsupp->text().toInt());
    bool test=Co.supprimer_commande(Co.get_ref());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("suppression avec succée");
    ui->table_commande->setModel(Co.afficher());}
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void gest_cl_co::on_pushButton_4_clicked()
{

        QMessageBox msgBox;
        clients C1;
        C1.setcin(ui->cinsupp->text().toInt());
        bool test=C1.supprimer(C1.getcin());
        if (test){
            ui->cinsupp->clear();
            ui->table_clients->setModel(C.afficher());
                msgBox.setText("clients supprimé");
                msgBox.exec();
               }
    }



void gest_cl_co::on_pushButton_11_clicked()
{
    clients C;
    QSqlQuery query;
    int cin=ui->cinmodif->text().toInt();
    QString cin_string=QString::number(cin);
   if(C.recherche_cin(cin))
   {
       query.prepare("SELECT * FROM CLIENTS WHERE cin like :cin");
       query.bindValue(0,cin_string);
       query.exec();
       while(query.next())
   {
       ui->nummodif->setText(query.value(5).toString());
       ui->nommodif->setText(query.value(2).toString());
       ui->prenommodif->setText(query.value(3).toString());
       ui->adressemodif->setText(query.value(4).toString());
       ui->emailmodif->setText(query.value(1).toString());

    }
   }
}

void gest_cl_co::on_pushButton_3_clicked()
{
    clients C;
    QMessageBox msg;
    C.setcin(ui->cinmodif->text().toInt());
    C.setnum(ui->nummodif->text().toInt());
    C.setnom(ui->nommodif->text());
    C.setprenom(ui->prenommodif->text());
    C.setadresse(ui->adressemodif->text());
    C.setemail(ui->emailmodif->text());

    bool test=C.modifier(C.getcin());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->table_clients->setModel(C.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}

void gest_cl_co::on_pushButton_8_clicked()
{

  QMessageBox msgBox ;

QSqlQueryModel *model = new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by CIN ASC");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
         ui->table_clients->setModel(model);
         //ui->table_clients->setModel(C.afficher());
         ui->table_clients->show();
         msgBox.setText("Tri avec succès.");
         msgBox.exec();
}

void gest_cl_co::on_pushButton_9_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM CLIENTS order by nom ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
             ui->table_clients->setModel(model);
             ui->table_clients->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void gest_cl_co::on_pushButton_10_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM CLIENTS order by numero ASC");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));

             ui->table_clients->setModel(model);
             ui->table_clients->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void gest_cl_co::on_pushButton_7_clicked()
{
    clients C;
        if (ui->comboBox_3->currentText()=="Rechercher par CIN")
        {
            int cin=ui->lineEdit->text().toInt();
            if (C.recherche_cin(cin))
            {
                ui->table_clients->setModel(C.afficher_cin(cin));
            }
        }
        else if(ui->comboBox_3->currentText()=="Rechercher par nom")
        {
            QString nom=ui->lineEdit->text();
            if (C.recherche_nom(nom))
            {
                ui->table_clients->setModel(C.afficher_nom(nom));
            }

        }
        else if(ui->comboBox_3->currentText()=="Rechercher par numero")
        {
            int num=ui->lineEdit->text().toInt();
            if(C.recherche_num(num))
            {
                ui->table_clients->setModel(C.afficher_num(num));
            }
        }
}

void gest_cl_co::on_pushButton_13_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->table_clients->model()->rowCount();
                  const int columnCount = ui->table_clients->model()->columnCount();

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
                      if (!ui->table_clients->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->table_clients->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->table_clients->isColumnHidden(column)) {
                              QString data = ui->table_clients->model()->data(ui->table_clients->model()->index(row, column)).toString().simplified();
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



void gest_cl_co::on_pushButton_12_clicked()
{
    commande C1;
    QSqlQuery query;
    int numero=ui->numeromodif->text().toInt();
    QString num=QString::number(numero);
   if(C1.recherche_numc(numero))
   {
       query.prepare("SELECT * FROM COMMANDE WHERE NUMERO like :numero");
       query.bindValue(0,num);
       query.exec();
       while(query.next())
   {
       //ui->numeromodif->setText(query.value(1).toString());
       ui->refmodif->setText(query.value(1).toString());
       ui->quantitemodif->setValue(query.value(2).toString().toInt());
       ui->PrixUnitmodif->setText(query.value(3).toString());
       ui->montantmodif->setText(query.value(4).toString());

    }
   }
}



void gest_cl_co::on_pushButton_6_clicked()
{
    commande C;
    QMessageBox msg;
    C.set_numero(ui->numeromodif->text().toInt());
    C.set_ref(ui->refmodif->text().toInt());
    C.set_qte(ui->quantitemodif->text().toInt());
    C.set_prix_unit(ui->PrixUnitmodif->text().toInt());
    C.set_montant(ui->montantmodif->text().toInt());

    bool test=C.modifier_commande(C.get_numero());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->table_commande->setModel(Co.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}




void gest_cl_co::on_pushButton_14_clicked()
{
    commande C;
        if (ui->comboBox->currentText()=="Recherche par numero")
        {
            int numero=ui->lineEdit_2->text().toInt();
            if (C.recherche_numc(numero))
            {
                ui->table_commande->setModel(Co.afficher_numero(numero));
            }
        }
        else if(ui->comboBox->currentText()=="Recherche par reference")
        {
            int ref=ui->lineEdit_2->text().toInt();
            if (C.recherche_ref(ref))
            {
                ui->table_commande->setModel(Co.afficher_ref(ref));
            }

        }
        else if(ui->comboBox->currentText()=="Recherche par montant")
        {
            int montant=ui->lineEdit_2->text().toInt();
            if(C.recherche_montant(montant))
            {
                ui->table_commande->setModel(Co.afficher_montant(montant));
            }
        }
}



void gest_cl_co::on_pushButton_15_clicked()
{
    QMessageBox msgBox ;

  QSqlQueryModel *model = new QSqlQueryModel();
           model->setQuery("SELECT * FROM COMMANDE order by REF ASC");
           model->setHeaderData(0,Qt::Horizontal,QObject::tr("numero"));
           model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
           model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
           model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
           model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
           ui->table_commande->setModel(model);
           //ui->table_clients->setModel(C.afficher());
           ui->table_commande->show();
           msgBox.setText("Tri avec succès.");
           msgBox.exec();
}

void gest_cl_co::on_pushButton_16_clicked()
{

    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM COMMANDE order by NUMERO ASC");
             model->setHeaderData(0,Qt::Horizontal,QObject::tr("numero"));
             model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
             model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
             model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
             model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
             ui->table_commande->setModel(model);
             ui->table_commande->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}

void gest_cl_co::on_pushButton_17_clicked()
{
    QMessageBox msgBox ;

    QSqlQueryModel *model = new QSqlQueryModel();
             model->setQuery("SELECT * FROM COMMANDE order by MONTANT ASC");
             model->setHeaderData(0,Qt::Horizontal,QObject::tr("numero"));
             model->setHeaderData(1,Qt::Horizontal,QObject::tr("Ref"));
             model->setHeaderData(2,Qt::Horizontal,QObject::tr("qte"));
             model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix unit"));
             model->setHeaderData(4,Qt::Horizontal,QObject::tr("montant"));
             ui->table_commande->setModel(model);
             ui->table_commande->show();
             msgBox.setText("Tri avec succès.");
             msgBox.exec();
}





void gest_cl_co::on_pushButton_18_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;

}




void gest_cl_co::browse()
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

void gest_cl_co::sendMail()
{
    Smtppp* smtp = new Smtppp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->text(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->text());
}


void gest_cl_co::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void gest_cl_co::on_pushButton_19_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->table_commande->model()->rowCount();
                  const int columnCount = ui->table_commande->model()->columnCount();

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
                      if (!ui->table_commande->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->table_commande->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->table_commande->isColumnHidden(column)) {
                              QString data = ui->table_commande->model()->data(ui->table_commande->model()->index(row, column)).toString().simplified();
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

void gest_cl_co::on_pushButton_20_clicked()
{
    QPrinter printer;

    printer.setPrinterName("desiered printer name");

  QPrintDialog dialog(&printer,this);

    if(dialog.exec()== QDialog::Rejected)

        return;
}


void gest_cl_co::on_loginButton_clicked()
{
    // Start connecting to the chat server (on port 4200).
    // This returns immediately and then works on connecting
    // to the server in the background. When it's done, we'll
    // get a connected() function call (below). If it fails,
    // we won't get any error message because we didn't connect()
    // to the error() signal from this socket.
    socket->connectToHost(ui->serverLineEdit->text(), 4200);
}

// This gets called when the user clicks the sayButton (next to where
// they type text to send to the chat room):
void gest_cl_co::on_sayButton_clicked()
{
    // What did they want to say (minus white space around the string):
    QString message = ui->sayLineEdit->text().trimmed();

    // Only send the text to the chat server if it's not empty:
    if(!message.isEmpty())
    {
        socket->write(QString(message + "\n").toUtf8());
    }

    // Clear out the input box so they can type something else:
    ui->sayLineEdit->clear();

    // Put the focus back into the input box so they can type again:
   ui->sayLineEdit->setFocus();
}


void gest_cl_co::readyRead()
{
    // We'll loop over every (complete) line of text that the server has sent us:
    while(socket->canReadLine())
    {
        // Here's the line the of text the server sent us (we use UTF-8 so
        // that non-English speakers can chat in their native language)
        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        // These two regular expressions describe the kinds of messages
        // the server can send us:

        //  Normal messges look like this: "username:The message"
        QRegExp messageRegex("^([^:]+):(.*)$");

        // Any message that starts with "/users:" is the server sending us a
        // list of users so we can show that list in our GUI:
        QRegExp usersRegex("^/users:(.*)$");

        // Is this a users message:
        if(usersRegex.indexIn(line) != -1)
        {
            // If so, udpate our users list on the right:
            QStringList users = usersRegex.cap(1).split(",");
            ui->userListWidget->clear();
            foreach(QString user, users)
                new QListWidgetItem(QPixmap(":/user.png"), user, ui->userListWidget);
        }
        // Is this a normal chat message:
        else if(messageRegex.indexIn(line) != -1)
        {
            // If so, append this message to our chat box:
            QString user = messageRegex.cap(1);
            QString message = messageRegex.cap(2);

            ui->roomTextEdit->append("<b>" + user + "</b>: " + message);
        }
    }
}

// This function gets called when our socket has successfully connected to the chat
// server. (see the connect() call in the MainWindow constructor).
void gest_cl_co::connected()
{
    // Flip over to the chat page:
    ui->chatPage_3->setCurrentWidget(ui->chatPage);

    // And send our username to the chat server.
    socket->write(QString("/me:" + ui->userLineEdit->text() + "\n").toUtf8());
}


