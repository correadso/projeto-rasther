#include "modeloaplicacao.h"
#include "bancodados.h"

ModeloAplicacao::ModeloAplicacao(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

QVariant ModeloAplicacao::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ModeloAplicacao::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[aplicacaoIdRole] = "aplicacaoId";
    roles[aplicacaoAnoInicialRole] = "aplicacaoAnoInicial";
    roles[aplicacaoAnoFinalRole] = "aplicacaoAnoFinal";
    roles[montadoraNomeRole] = "montadoraNome";
    roles[veiculoNomeRole] = "veiculoNome";
    roles[tiposSistemaNomeRole] = "tiposSistemaNome";
    roles[sistemaNomeRole] = "sistemaNome";
    roles[conectorNomeRole] = "conectorNome";
    roles[conectorIdRole] = "conectorId";

    return roles;
}

void ModeloAplicacao::updateModel()
{

    this->setQuery(
                "SELECT  "
                    "a.aplicacaoId,  "
                    "a.aplicacaoAnoInicial,  "
                    "a.aplicacaoAnoFinal,  "
                    "m.montadoraNome,  "
                    "v.veiculoNome,  "
                    "ts.tiposSistemaNome, "
                    "s.sistemaNome, "
                    "c.conectorNome, "
                    "a.conectorId "
                "FROM aplicacao a, montadora m, veiculo v, tipos_sistema ts, sistema s, conector c "
                "WHERE a.montadoraId = m.montadoraId "
                "AND a.veiculoId = v.veiculoId "
                "AND a.tiposSistemaId = ts.tiposSistemaId "
                "AND a.sistemaId = s.sistemaId "
                "AND a.conectorId = c.conectorId "
                );
}

// obtém id da aplicação informando a linha na tabela
int ModeloAplicacao::getId(int row)
{
    return this->data(this->index(row, 0), aplicacaoIdRole).toInt();
}

// obtém o nome do arquivo do conector a partir do id do conector
QString ModeloAplicacao::obtemNomeArquivoConector(int linha)
{

    QString idConector = this->data(this->index(linha,8), conectorIdRole).toString();

    QString comando = "select conectorFoto from conector where conectorId = " + idConector;
    QSqlQuery query(comando);

    QString nomeArquivo;
    if (query.next())
        nomeArquivo = query.value(0).toString();

    return nomeArquivo;
}
