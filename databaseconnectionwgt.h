#ifndef DATABASECONNECTIONWGT_H
#define DATABASECONNECTIONWGT_H

#include <QDialog>

enum SqlType{
    MySql=0,
};

namespace Ui {
class DatabaseConnectionWgt;
}

class DatabaseConnectionWgt : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseConnectionWgt(QWidget *parent = nullptr);
    ~DatabaseConnectionWgt();

signals:
    void messageIsFinished(QString ip,QString port, SqlType sqlType,QString root,QString password,QString databaseName);

private slots:
    void on_yes_btn_clicked();

    void on_cancel_btn_clicked();

private:
    Ui::DatabaseConnectionWgt *ui;
    QString m_ip;
    QString m_port;
    SqlType m_sqlType;
    QString m_root;
    QString m_password;
    QString m_databaseName;
};

#endif // DATABASECONNECTIONWGT_H
