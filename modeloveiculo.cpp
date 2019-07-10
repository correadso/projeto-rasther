#include "modeloveiculo.h"
#include "bancodados.h"

ModeloVeiculo::ModeloVeiculo(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

QVariant ModeloVeiculo::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ModeloVeiculo::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[veiculoIdRole] = "veiculoId";
    roles[veiculoNomeRole] = "veiculoNome";
    roles[montadoraIdRole] = "montadoraId";
    roles[montadoraNomeRole] = "montadoraNome";

    return roles;
}

void ModeloVeiculo::updateModel()
{
    this->setQuery("SELECT "
                        "veiculo.veiculoId, veiculo.veiculoNome, "
                        "veiculo.montadoraId, montadora.montadoraNome "
                   "FROM veiculo "
                   "LEFT JOIN montadora "
                   "WHERE veiculo.montadoraId = montadora.montadoraId"
                   );
}

int ModeloVeiculo::getId(int row)
{
    return this->data(this->index(row, 0), veiculoIdRole).toInt();
}
