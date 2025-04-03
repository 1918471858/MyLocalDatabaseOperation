#include <QSqlQuery>

#include "editablesqlquerymodel.h"

EditableSqlQueryModel::EditableSqlQueryModel(QObject *parent) : QSqlQueryModel(parent) {}

Qt::ItemFlags EditableSqlQueryModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.isValid()) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool EditableSqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        QSqlRecord record = this->record(index.row());
        record.setValue(index.column(), value);

        QSqlQuery query;
        QString whereClause = QString("WHERE %1 = '%2'")
                                  .arg(record.fieldName(0))
                                  .arg(this->record(index.row()).value(0).toString());

        QString updateQuery = QString("UPDATE %1 SET %2 = '%3' %4")
                                  .arg(m_currentTableName)
                                  .arg(record.fieldName(index.column()))
                                  .arg(value.toString())
                                  .arg(whereClause);

        if (query.exec(updateQuery)) {
            emit requestUpdataView();
            return true;
        } else {
            qDebug() << "Update failed:" << query.lastError().text();
            return false;
        }
    }
    return false;
}

void EditableSqlQueryModel::setCurrentTableName(QString tableName)
{
    m_currentTableName = tableName;
}
