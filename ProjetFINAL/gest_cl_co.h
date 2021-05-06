#ifndef GEST_CL_CO_H
#define GEST_CL_CO_H

#include <QWidget>
#include <QMainWindow>
#include "clients.h"
#include "commande.h"
#include"smtppp.h"

namespace Ui {
class gest_cl_co;
}

class gest_cl_co : public QWidget
{
    Q_OBJECT

public:
    explicit gest_cl_co(QWidget *parent = nullptr);
    ~gest_cl_co();
private slots:

    void sendMail();
    void mailSent(QString);
    void browse();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();



    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_loginButton_clicked();

    // This gets called when you click the sayButton on
    // the chat page.
    void on_sayButton_clicked();

    // This is a function we'll connect to a socket's readyRead()
    // signal, which tells us there's text to be read from the chat
    // server.
    void readyRead();

    // This function gets called when the socket tells us it's connected.
    void connected();

private:
    Ui::gest_cl_co *ui;
    clients C;
    commande Co;
    QStringList files;
    QTcpSocket *socket;

};

#endif // GEST_CL_CO_H
