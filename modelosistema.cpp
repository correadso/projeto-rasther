#include "modelosistema.h"
#include "bancodados.h"

ModeloSistema::ModeloSistema(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

QVariant ModeloSistema::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ModeloSistema::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[sistemaIdRole] = "sistemaId";
    roles[sistemaNomeRole] = "sistemaNome";
    roles[tiposSistemaIdRole] = "tiposSistemaId";
    roles[tiposSistemaNomeRole] = "tiposSistemaNome";

    return roles;
}

void ModeloSistema::updateModel()
{
    this->setQuery("SELECT "
                        "sistema.sistemaId, sistema.sistemaNome, "
                        "sistema.tiposSistemaId, tipos_sistema.tiposSistemaNome "
                   "FROM sistema "
                   "LEFT JOIN tipos_sistema "
                   "WHERE sistema.tiposSistemaId = tipos_sistema.tiposSistemaId"
                   );
}

int ModeloSistema::getId(int row)
{
    return this->data(this->index(row, 0), sistemaIdRole).toInt();
}
