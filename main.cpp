#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto m_pDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));

    if (m_pDatabase != nullptr) {
        m_pDatabase->setConnectOptions();
        m_pDatabase->setHostName("localhost");
        m_pDatabase->setPort(5432);
        m_pDatabase->setUserName("postgres");
        m_pDatabase->setPassword("");
    }

    if (m_pDatabase->open()) {
        qDebug() << "database open";
    } else {
        qDebug() << "database not open." << m_pDatabase->lastError().text();
    }

    QString sDatabaseName = "myDB";
    QSqlQuery query(*m_pDatabase);
    bool bCorrect = query.exec("CREATE DATABASE " + sDatabaseName);
    if (!bCorrect) {
        qDebug() << "[DATABASE ERROR]: " << m_pDatabase->lastError().text();
    } else {
        query.exec("USE " + sDatabaseName);
    }

    return a.exec();
}
