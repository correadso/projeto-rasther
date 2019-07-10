#include "modelotipossistema.h"
#include "bancodados.h"

ModeloTiposSistema::ModeloTiposSistema(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

QVariant ModeloTiposSistema::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ModeloTiposSistema::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[tiposSistemaIdRole] = "tiposSistemaIdRole";
    roles[tiposSistemaNomeRole] = "tiposSistemaNomeRole";

    return roles;
}

void ModeloTiposSistema::selecionaTiposSistema()
{
    this->setQuery("SELECT tiposSistemaNome FROM " TABELA_TIPOS_SISTEMA);
}


void ModeloTiposSistema::updateModel()
{
    this->setQuery("SELECT * FROM " TABELA_TIPOS_SISTEMA);
}

int ModeloTiposSistema::getId(int row)
{
    return this->data(this->index(row, 0), tiposSistemaIdRole).toInt();
}

