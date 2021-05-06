#ifndef TABLESINTER_H
#define TABLESINTER_H

#include <QDialog>
#include "tables.h"
namespace Ui {
class tablesinter;
}

class tablesinter : public QDialog
{
    Q_OBJECT

public:
    explicit tablesinter(QWidget *parent = nullptr);
    ~tablesinter();

private slots:
    void on_AjouterBouton_clicked();

    void on_comboBox_modif_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_ModifierBouton_clicked();

    void on_SupprimerBouton_clicked();

    void refresh();

private:
    tables tmptables;
    Ui::tablesinter *ui;
};

#endif // TABLESINTER_H
