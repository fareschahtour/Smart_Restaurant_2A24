#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterf_clicked();

    void on_suppf_clicked();

    void on_trie_par_CINf_clicked();

    void on_trie_par_nomf_clicked();

    void on_trie_par_numerof_clicked();

    void on_recherche_f_clicked();

    void on_pushButton_clicked();

    void on_modifier_f_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
