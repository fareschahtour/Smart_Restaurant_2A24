#include "login.h"
#include "ui_login.h"
#include "clients.h"
#include "commande.h"
#include "gest_cl_co.h"
#include <QMessageBox>
#include <iostream>
#include <QMessageBox>
#include  <QDebug>
#include "authentification.h"
#include "mainwindow.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setWindowTitle("~~Smart Restaurant~~");
    }


Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_quiter1_clicked()
{
    close();
}

void Login::on_pushButton_connecter_clicked()
{
    authentification A2;
    A2.setid(ui->lineEdit_loginid->text().toInt());
    A2.setmdp(ui->lineEdit_loginmdp->text());
    if(A2.recherche_id_mdp(A2.getid(),A2.getmdp())){
    MainWindow *M = new MainWindow(this);
    M->show();
}
}

void Login::on_pushButton_inscrire_clicked()
{
    G = new gest_cl_co(this);
    G->show();
}

void Login::on_pushButton_mdpoublie_clicked()
{
    authentification A2;
    A2.setid(ui->lineEdit_loginid->text().toInt());
    if(A2.recherche_id(A2.getid())){
    G = new gest_cl_co(this);
    G->show();
    }
}


