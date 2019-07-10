#include "bancodados.h"

BancoDados::BancoDados(QObject *parent) : QObject(parent)
{

}

BancoDados::~BancoDados()
{

}

void BancoDados::connectToDataBase()
{
    // verifica se banco de dados existe
    if(!QFile("C:/example/" DATABASE_NAME).exists()){
    {
        this->restoreDataBase(); // cria banco
        this->inicializaBanco(); // insere valores
    }
    } else {
        // banco de dados existe, apenas abre
        this->openDataBase();
    }
}

// cria banco e tabelas
bool BancoDados::restoreDataBase()
{
    if(this->openDataBase()){
        return (this->createTables()) ? true : false;
    } else {
        qDebug() << "Falha ao tentar recuperar o banco de dados.";
        return false;
    }
}

bool BancoDados::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/example/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void BancoDados::closeDataBase()
{
    db.close();
}

bool BancoDados::criaTabela(QString comando)
{
    QSqlQuery query;
    if(!query.exec(comando)){
        qDebug() << "Banco de dados: erro durante a criação. ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool BancoDados::createTables()
{
    QString comando;
    bool sqlOk;

    comando = "CREATE TABLE " TABELA_MONTADORA " ("
                  MONTADORA_ID " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                  MONTADORA_NOME " TEXT NOT NULL"
              ");";
    sqlOk = criaTabela(comando);

    comando = "CREATE TABLE " TABELA_VEICULO " ("
                  VEICULO_ID " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                  VEICULO_NOME " TEXT NOT NULL,"
                  MONTADORA_ID " INTEGER NOT NULL,"
                  "FOREIGN KEY (" MONTADORA_ID ") REFERENCES " TABELA_MONTADORA "(" MONTADORA_ID ") ON DELETE CASCADE"
              ");";
    sqlOk = criaTabela(comando);

    comando = "CREATE TABLE " TABELA_TIPOS_SISTEMA " ("
                  TIPOS_SISTEMA_ID " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                  TIPOS_SISTEMA_NOME " TEXT NOT NULL"
              ");";
    sqlOk = criaTabela(comando);

    comando = "CREATE TABLE " TABELA_SISTEMA " ("
                  SISTEMA_ID " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                  SISTEMA_NOME " TEXT NOT NULL,"
                  TIPOS_SISTEMA_ID " INTEGER NOT NULL,"
                  "FOREIGN KEY (" TIPOS_SISTEMA_ID ") REFERENCES " TABELA_TIPOS_SISTEMA "(" TIPOS_SISTEMA_ID ") ON DELETE CASCADE"
              ");";
    sqlOk = criaTabela(comando);

    comando = "CREATE TABLE " TABELA_CONECTOR " ("
                  CONECTOR_ID " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                  CONECTOR_NOME " TEXT NOT NULL,"
                  CONECTOR_FOTO " TEXT NOT NULL"
              ");";
    sqlOk = criaTabela(comando);

    comando = "CREATE TABLE " TABELA_APLICACAO " ("
                    APLICACAO_ID "	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                    APLICACAO_ANO_INICIAL "	INTEGER, "
                    APLICACAO_ANO_FINAL "	INTEGER, "
                    MONTADORA_ID "	INTEGER NOT NULL, "
                    VEICULO_ID "	INTEGER NOT NULL, "
                    TIPOS_SISTEMA_ID "	INTEGER NOT NULL, "
                    SISTEMA_ID "	INTEGER NOT NULL, "
                    CONECTOR_ID "	INTEGER NOT NULL, "
                    "FOREIGN KEY (" MONTADORA_ID ") REFERENCES " TABELA_MONTADORA "(" MONTADORA_ID ") ON DELETE CASCADE, "
                    "FOREIGN KEY (" VEICULO_ID ") REFERENCES " TABELA_VEICULO "(" VEICULO_ID ") ON DELETE CASCADE, "
                    "FOREIGN KEY (" TIPOS_SISTEMA_ID ") REFERENCES " TABELA_TIPOS_SISTEMA "(" TIPOS_SISTEMA_ID ") ON DELETE CASCADE, "
                    "FOREIGN KEY (" SISTEMA_ID ") REFERENCES " TABELA_SISTEMA "(" SISTEMA_ID ") ON DELETE CASCADE, "
                    "FOREIGN KEY (" CONECTOR_ID ") REFERENCES " TABELA_CONECTOR "(" CONECTOR_ID ") ON DELETE CASCADE "
                ");";
    sqlOk = criaTabela(comando);

    return sqlOk;
}

// quando banco não existe esta função é utilizada para popular o banco
void BancoDados::inicializaBanco()
{
    // montadoras
    this->inserIntoTableMontadora("Audi");       // id 1
    this->inserIntoTableMontadora("Fiat");       // id 2
    this->inserIntoTableMontadora("Ford");       // id 3
    this->inserIntoTableMontadora("GM");         // id 4
    this->inserIntoTableMontadora("Honda");      // id 5
    this->inserIntoTableMontadora("Mercedes");   // id 6

    // veículos
    this->inserIntoTableVeiculo("A3 1.8-T", "1");           // audi id 1
    this->inserIntoTableVeiculo("A4 1.8", "1");             // audi id 2
    this->inserIntoTableVeiculo("Argo 1.3", "2");           // fiat id 3
    this->inserIntoTableVeiculo("Brava 1.6-16V", "2");      // fiat id 4
    this->inserIntoTableVeiculo("Ecosport 2.0-16V", "3");   // ford id 5
    this->inserIntoTableVeiculo("C1119", "3");              // ford id 6
    this->inserIntoTableVeiculo("Agile 1.4", "4");          // GM   id 7
    this->inserIntoTableVeiculo("Astra 1.8", "4");          // GM   id 8
    this->inserIntoTableVeiculo("Civic 1.8-16V", "5");      // honda id 9
    this->inserIntoTableVeiculo("Fit 1.4", "5");            // honda id 10
    this->inserIntoTableVeiculo("Sprinter 2.2", "6"); // mercedes id 11

    // tipos sistema
    this->inserIntoTableTiposSistema("ABS");          // id 1
    this->inserIntoTableTiposSistema("Airbag");       // id 2
    this->inserIntoTableTiposSistema("Motor Diesel"); // id 3

    // sistemas
    this->inserIntoTableSistema("FRONT MK60-2", "1"); // abs
    this->inserIntoTableSistema("Bosch 5.7", "1"); // abs
    this->inserIntoTableSistema("Ford ABS-3", "1"); // abs
    this->inserIntoTableSistema("ABS Knorr 8", "1"); // abs
    this->inserIntoTableSistema("Honda SRS-3", "2"); // airbag
    this->inserIntoTableSistema("Honda SRS-4", "2"); // airbag
    this->inserIntoTableSistema("Bosch EDC-15C6", "3"); // motor diesel

    // conectores
    this->inserIntoTableConector("D1", "Con1.jpg");
    this->inserIntoTableConector("D2", "Con2.jpg");
    this->inserIntoTableConector("D3", "Con3.jpg");
    this->inserIntoTableConector("D4", "Con4.jpg");
    this->inserIntoTableConector("D5", "Con5.jpg");
    this->inserIntoTableConector("D6", "Con6.jpg");
    this->inserIntoTableConector("D7", "Con7.jpg");
    this->inserIntoTableConector("D8", "Con8.jpg");
    this->inserIntoTableConector("D9", "Con9.jpg");

    // aplicações
    // audi - abs
    // A3 1.8-T         FRONT MK60-2	2001	*       D1
    this->inserIntoTableAplicacao("2001", "", "1", "1", "1", "1", "1");
    // A4 1.8           Bosch 5.7       2001	2002	D1

    // ford - abs
    // Ecosport 2.0-16V Ford ABS-3      2003	2011	D1
    // C1119            ABS Knorr 8     2013	*       D5

    // honda - airbag
    // Civic 1.8-16V	Honda SRS-3     2006	*       D1
    // Fit 1.4          Honda SRS-4     2007	*       D1

    // mercedes - motor diesel
    // Sprinter 2.2     Bosch EDC-15C6	2002	2012	D2
}


bool BancoDados::inserIntoTableVeiculo(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABELA_VEICULO " ( " VEICULO_NOME ", " MONTADORA_ID " ) "
                  "VALUES (:veiculoNome, :montadoraId)");
    query.bindValue(":veiculoNome",       data[0].toString());
    query.bindValue(":montadoraId",       data[1].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABELA_VEICULO;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool BancoDados::inserIntoTableVeiculo(const QString &veiculoNome, const QString &montadoraId)
{
    QVariantList data;
    data.append(veiculoNome);
    data.append(montadoraId);

    if(inserIntoTableVeiculo(data))
        return true;
    else
        return false;
}

bool BancoDados::inserIntoTableMontadora(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABELA_MONTADORA " ( " MONTADORA_NOME " ) "
                  "VALUES (:montadoraNome)");
    query.bindValue(":montadoraNome",       data[0].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABELA_MONTADORA;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool BancoDados::inserIntoTableMontadora(const QString &montadoraNome)
{
    QVariantList data;
    data.append(montadoraNome);

    if(inserIntoTableMontadora(data))
        return true;
    else
        return false;
}

bool BancoDados::inserIntoTableSistema(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABELA_SISTEMA " ( " SISTEMA_NOME ", " TIPOS_SISTEMA_ID " ) "
                  "VALUES (:sistemaNome, :tiposSistemaId)");
    query.bindValue(":sistemaNome",       data[0].toString());
    query.bindValue(":tiposSistemaId",    data[1].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABELA_SISTEMA;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool BancoDados::inserIntoTableSistema(const QString &sistemaNome, const QString &tiposSistemaId/*, const QString &nik*/)
{
    QVariantList data;
    data.append(sistemaNome);
    data.append(tiposSistemaId);

    if(inserIntoTableSistema(data))
        return true;
    else
        return false;
}

bool BancoDados::inserIntoTableTiposSistema(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABELA_TIPOS_SISTEMA " ( " TIPOS_SISTEMA_NOME " ) "
                  "VALUES (:tiposSistemaNome)");
    query.bindValue(":tiposSistemaNome",       data[0].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABELA_TIPOS_SISTEMA;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool BancoDados::inserIntoTableTiposSistema(const QString &tipoSistemaNome)
{
    QVariantList data;
    data.append(tipoSistemaNome);

    if(inserIntoTableTiposSistema(data))
        return true;
    else
        return false;
}

bool BancoDados::inserIntoTableConector(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABELA_CONECTOR " ( " CONECTOR_NOME ", " CONECTOR_FOTO " ) "
                  "VALUES (:conectorNome, :conectorFoto)");
    query.bindValue(":conectorNome", data[0].toString());
    query.bindValue(":conectorFoto",  data[1].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABELA_CONECTOR;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
    } else {
        return true;
    }
}

bool BancoDados::inserIntoTableConector(const QString &conectorNome, const QString &conectorFoto/*, const QString &nik*/)
{
    QVariantList data;
    data.append(conectorNome);
    data.append(conectorFoto);

    if(inserIntoTableConector(data))
        return true;
    else
        return false;
}

bool BancoDados::inserIntoTableAplicacao(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABELA_APLICACAO" ( "
                  APLICACAO_ANO_INICIAL ", " APLICACAO_ANO_FINAL ", "
                  MONTADORA_ID ", " VEICULO_ID ", "
                  TIPOS_SISTEMA_ID ", " SISTEMA_ID ", " CONECTOR_ID " ) "
                  "VALUES (:aplicacaoAnoInicial, :aplicacaoAnoFinal, :montadoraId, :veiculoId, :tiposSistemaId, :sistemaId, :conectorId)");

    query.bindValue(":aplicacaoAnoInicial", data[0].toString());
    query.bindValue(":aplicacaoAnoFinal",   data[1].toString());
    query.bindValue(":montadoraId",         data[2].toString());
    query.bindValue(":veiculoId",           data[3].toString());
    query.bindValue(":tiposSistemaId",      data[4].toString());
    query.bindValue(":sistemaId",           data[5].toString());
    query.bindValue(":conectorId",          data[6].toString());

    if(!query.exec()){
        qDebug() << "error insert into " << TABELA_SISTEMA;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool BancoDados::inserIntoTableAplicacao(const QString &aplicacaoAnoInicial,
                             const QString &aplicacaoAnoFinal, const QString &montadoraId,
                             const QString &veiculoId, const QString &tiposSistemaId,
                             const QString &sistemaId, const QString &conectorId)
{
    QVariantList data;
    data.append(aplicacaoAnoInicial);
    data.append(aplicacaoAnoFinal);
    data.append(montadoraId);
    data.append(veiculoId);
    data.append(tiposSistemaId);
    data.append(sistemaId);
    data.append(conectorId);

    if(inserIntoTableAplicacao(data))
        return true;
    else
        return false;
}


bool BancoDados::removeRecord(const int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM " TABELA_VEICULO " WHERE id= :ID ;");
    query.bindValue(":ID", id);

    if(!query.exec()){
        qDebug() << "error delete row " << TABELA_VEICULO;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}
