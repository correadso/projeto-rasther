#include "modelomontadora.h"
#include "bancodados.h"

ModeloMontadora::ModeloMontadora(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

QVariant ModeloMontadora::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ModeloMontadora::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[montadoraIdRole] = "id";
    roles[montadoraNomeRole] = "montadoraNomeRole";

    roles[tiposSistemaIdRole] = "tiposSistemaIdRole";
    roles[tiposSistemaNomeRole] = "tiposSistemaNomeRole";

    return roles;
}

void ModeloMontadora::selecionaMontadoras()
{
    this->setQuery("SELECT montadoraNome FROM " TABELA_MONTADORA);
}

void ModeloMontadora::updateModelTiposSistema()
{
    this->setQuery("SELECT * FROM " TABELA_TIPOS_SISTEMA);
}

void ModeloMontadora::updateModel()
{
    this->setQuery("SELECT * FROM " TABELA_MONTADORA);
}

void ModeloMontadora::updateModel(QString tabela)
{
    this->setQuery("SELECT * FROM " + tabela);
}

int ModeloMontadora::getId(int row)
{
    return this->data(this->index(row, 0), montadoraIdRole).toInt();
}
