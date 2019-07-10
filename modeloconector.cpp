#include "modeloconector.h"
#include "bancodados.h"

ModeloConector::ModeloConector(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

QVariant ModeloConector::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ModeloConector::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[conectorIdRoleIdc] = "conectorIdRole";
    roles[conectorNomeRole] = "conectorNomeRole";
    roles[conectorFotoRole] = "conectorFotoRole";

    return roles;
}

void ModeloConector::updateModel()
{
    this->setQuery("SELECT * FROM " TABELA_CONECTOR);
}

void ModeloConector::updateModel(QString tabela)
{
    this->setQuery("SELECT * FROM " + tabela);
}

int ModeloConector::getId(int row)
{
    return this->data(this->index(row, 0), conectorIdRoleIdc).toInt();
}

// obtém o nome do arquivo do conector a partir da linha do banco
QString ModeloConector::obtemNomeArquivoConector(int linha)
{
    return this->data(this->index(linha,2), conectorFotoRole).toString();
}
