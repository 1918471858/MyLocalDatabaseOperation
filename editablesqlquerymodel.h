#pragma once

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QDebug>

class EditableSqlQueryModel : public QSqlQueryModel {
    Q_OBJECT
public:
    explicit EditableSqlQueryModel(QObject *parent = nullptr);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void setCurrentTableName(QString tableName);

signals:
    void requestUpdataView();

private:
    QString m_currentTableName;
};
