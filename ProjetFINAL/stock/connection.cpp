#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_project2A");//inserer le nom de la source de données ODBC
db.setUserName("fares");//inserer nom de l'utilisateur
db.setPassword("Fares123456789");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
