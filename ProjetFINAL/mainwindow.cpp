#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reservationinter.h"
#include "tablesinter.h"
#include "gestion_fournisseur.h"
#include "aicha.h"
#include "gest_cl_co.h"
#include "nour.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Home");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    reservationinter *ev= new reservationinter();
    ev->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Gestion_fournisseur *four= new Gestion_fournisseur();
    four->show();

}

void MainWindow::on_pushButton_3_clicked()
{
    gest_cl_co *gl = new gest_cl_co();
    gl->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    aicha *aic = new aicha();
    aic->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    Nour *no = new Nour();
    no->show();
}
