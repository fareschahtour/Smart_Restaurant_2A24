#include "connection.h"

Connection::Connection()
{}

bool Connection::ouvrirConnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_project2A");//inserer le nom de la source de données ODBC
db.setUserName("Fares");//inserer nom de l'utilisateur  ///fares
db.setPassword("Fares123456789");//inserer mot de passe de cet utilisateur  ///Fares123456789

if (db.open())
    test=true;
return  test;
}
QSqlDatabase Connection::getdb()
{
    return db;
}

void Connection::fermerConnexion()
{db.close();}
