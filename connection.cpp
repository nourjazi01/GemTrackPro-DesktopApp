#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A27");
db.setUserName("Nour");//inserer nom de l'utilisateur
db.setPassword("azerty");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
