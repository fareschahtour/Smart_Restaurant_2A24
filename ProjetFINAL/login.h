#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "clients.h"
#include "commande.h"
#include"smtp.h"
#include "gest_cl_co.h"
#include "aicha.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:



    void on_pushButton_quiter1_clicked();


    void on_pushButton_connecter_clicked();

    void on_pushButton_inscrire_clicked();

    void on_pushButton_mdpoublie_clicked();



private:
    Ui::Login *ui;
    clients C;
    commande Co;
    QStringList files;
    gest_cl_co *G;
    aicha *A;

};

#endif // LOGIN_H
