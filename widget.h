#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>


#include "databaseconnectionwgt.h"
#include "editablesqlquerymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_messageIsFinished(QString ip,QString port,SqlType sqlType,QString root,QString password,QString databaseName);

    void on_unconnect_btn_clicked();

private:
    Ui::Widget *ui;
    DatabaseConnectionWgt* m_connectionWgt;
    QSqlDatabase m_needToShowDatabase;
    EditableSqlQueryModel* m_tableModel;
    QSqlQueryModel* m_treeModel;
    QString m_currentTableName;
};
#endif // WIDGET_H
