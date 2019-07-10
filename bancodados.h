#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

//#define DATABASE_HOSTNAME     "NameDataBase"
#define DATABASE_NAME           "banco.sqlite"

// nomes tabelas e dos campos
#define TABELA_VEICULO          "veiculo"
#define VEICULO_ID              "veiculoId"
#define VEICULO_NOME            "veiculoNome"

#define TABELA_MONTADORA        "montadora"
#define MONTADORA_ID            "montadoraId"
#define MONTADORA_NOME          "montadoraNome"

#define TABELA_APLICACAO        "aplicacao"
#define APLICACAO_ID            "aplicacaoId"
#define APLICACAO_ANO_INICIAL   "aplicacaoAnoInicial"
#define APLICACAO_ANO_FINAL     "aplicacaoAnoFinal"

#define TABELA_CONECTOR         "conector"
#define CONECTOR_ID             "conectorId"
#define CONECTOR_NOME           "conectorNome"
#define CONECTOR_FOTO           "conectorFoto"

#define TABELA_SISTEMA          "sistema"
#define SISTEMA_ID              "sistemaId"
#define SISTEMA_NOME            "sistemaNome"

#define TABELA_TIPOS_SISTEMA    "tipos_sistema"
#define TIPOS_SISTEMA_ID        "tiposSistemaId"
#define TIPOS_SISTEMA_NOME      "tiposSistemaNome"

class BancoDados : public QObject
{
    Q_OBJECT
public:
    explicit BancoDados(QObject *parent = nullptr);
    ~BancoDados();
    void connectToDataBase();

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool criaTabela(QString comando);
    bool createTables();
    void inicializaBanco();

public slots:
    bool inserIntoTableVeiculo(const QVariantList &data);
    bool inserIntoTableVeiculo(const QString &veiculoNome, const QString &montadoraId);

    bool inserIntoTableMontadora(const QVariantList &data);
    bool inserIntoTableMontadora(const QString &montadoraNome);

    bool inserIntoTableSistema(const QVariantList &data);
    bool inserIntoTableSistema(const QString &veiculoNome, const QString &montadoraId);

    bool inserIntoTableTiposSistema(const QVariantList &data);
    bool inserIntoTableTiposSistema(const QString &tiposSistemaNome);

    bool inserIntoTableConector(const QVariantList &data);
    bool inserIntoTableConector(const QString &conectorNome, const QString &conectorFoto);

    bool inserIntoTableAplicacao(const QVariantList &data);
    bool inserIntoTableAplicacao(const QString &aplicacaoAnoInicial,
                                 const QString &aplicacaoAnoFinal, const QString &montadoraId,
                                 const QString &veiculoId, const QString &tiposSistemaId,
                                 const QString &sistemaId, const QString &conectorId);

    bool removeRecord(const int id);
};

#endif // DATABASE_H
