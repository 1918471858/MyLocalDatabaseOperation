#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QSqlError>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_connectionWgt = nullptr;
    m_treeModel = nullptr;
    m_tableModel = nullptr;
    connect(ui->connect_btn,&QPushButton::clicked,this,&Widget::on_pushButton_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    if(m_connectionWgt==nullptr){
        m_connectionWgt = new DatabaseConnectionWgt(this);
    }
    connect(m_connectionWgt,&DatabaseConnectionWgt::messageIsFinished,this,&Widget::on_messageIsFinished,Qt::UniqueConnection);
    m_connectionWgt->exec();
}

void Widget::on_messageIsFinished(QString ip,QString port, SqlType sqlType, QString root, QString password,QString databaseName)
{
    //根据连接信息窗口设置数据库的连接
    m_needToShowDatabase = QSqlDatabase::addDatabase("QMYSQL");
    m_needToShowDatabase.setHostName(ip);
    m_needToShowDatabase.setPort(port.toInt());
    m_needToShowDatabase.setUserName(root);
    m_needToShowDatabase.setPassword(password);
    m_needToShowDatabase.setDatabaseName(databaseName);

    //检查mysql驱动是否存在以及可用
    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "Available drivers:";
    foreach(QString driver, drivers)
        qDebug() << driver;
    if (!drivers.contains("QMYSQL")) {
        qDebug() << "MySQL driver is not available.";
    }

    //检查数据库是否打开成功
    if(!m_needToShowDatabase.open()){
        QMessageBox::warning(this,"数据库打开失败",m_needToShowDatabase.lastError().text().toUtf8());
        return;
    }

    //数据库打开成功后的ui逻辑操作
    ui->connect_btn->setEnabled(false);
    ui->unconnect_btn->setEnabled(true);

    //显示数据库中的表格树
    m_treeModel = new QSqlQueryModel(this);
    QString sql1 = "show tables";
    m_treeModel->setQuery(sql1);
    ui->treeView->setModel(m_treeModel);

    //为树节点设置点击后进行操作的信号与槽
    connect(ui->treeView,&QTreeView::doubleClicked,[=](const QModelIndex &index){
        QString tableName = index.data(0).toString();
        //判断双击的是否是原有表格，是则不进行任何操作
        if(tableName==m_currentTableName)
            return;
        //清除原有模型
        if(m_tableModel!=nullptr){
            m_tableModel->clear();
            delete m_tableModel;
            m_tableModel=nullptr;
        }
        //创建新模型以及设置新模型给视图
        m_tableModel = new EditableSqlQueryModel(this);
        QString sql2 = QString("select * from %1").arg(tableName);
        m_tableModel->setQuery(sql2);
        ui->tableView->setModel(m_tableModel);
        // 设置编辑触发方式
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        //更新当前表格名
        m_currentTableName=tableName;
        m_tableModel->setCurrentTableName(m_currentTableName);
        //编辑后更新view
        connect(m_tableModel,&EditableSqlQueryModel::requestUpdataView,[=](){
            m_tableModel->setQuery(sql2);
            ui->tableView->setModel(m_tableModel);
        });
    });
}


void Widget::on_unconnect_btn_clicked()
{
    if(m_treeModel!=nullptr)
    {
        m_treeModel->clear();
        delete m_treeModel;
        m_treeModel=nullptr;
    }
    if(m_tableModel!=nullptr){
        m_tableModel->clear();
        delete m_tableModel;
        m_tableModel=nullptr;
    }
    ui->connect_btn->setEnabled(true);
    ui->unconnect_btn->setEnabled(false);
}

