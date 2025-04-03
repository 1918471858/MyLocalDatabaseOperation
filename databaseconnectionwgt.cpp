#include "databaseconnectionwgt.h"
#include "ui_databaseconnectionwgt.h"
#include <QMessageBox>

DatabaseConnectionWgt::DatabaseConnectionWgt(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatabaseConnectionWgt)
{
    ui->setupUi(this);
}

DatabaseConnectionWgt::~DatabaseConnectionWgt()
{
    delete ui;
}

void DatabaseConnectionWgt::on_yes_btn_clicked()
{
    //按下确定后检查数据是否存在(这里不做字符串是否合法检查)
    m_ip = ui->ip_line->text();
    m_port = ui->port_line->text();
    m_sqlType = MySql;
    m_root = ui->root_line->text();
    m_password = ui->password_line->text();
    m_databaseName = ui->databaseName_line->text();
    if(m_ip.isEmpty()){
        QMessageBox::warning(this,"IP:","请输入ip");
        return;
    }
    else if(m_port.isEmpty()){
        QMessageBox::warning(this,"Port:","请输入端口");
        return;
    }
    else if(ui->sqlType_combobox->currentText().isEmpty()){
        QMessageBox::warning(this,"SqlType:","请输入数据库类型");
        return;
    }
    else if(m_root.isEmpty()){
        QMessageBox::warning(this,"Root:","请输入用户名");
        return;
    }
    else if(m_password.isEmpty()){
        QMessageBox::warning(this,"Password:","请输入用户密码");
        return;
    }
    else if(m_databaseName.isEmpty()){
        QMessageBox::warning(this,"DatabaseName:","请输入数据库名称");
        return;
    }
    emit messageIsFinished(m_ip,m_port,m_sqlType,m_root,m_password,m_databaseName);
    this->hide();
}


void DatabaseConnectionWgt::on_cancel_btn_clicked()
{
    this->hide();
}

