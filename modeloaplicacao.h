#include <QObject>
#include <QSqlQueryModel>

#ifndef MODELOAPLICACAO_H
#define MODELOAPLICACAO_H

class ModeloAplicacao : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Roles {
        aplicacaoIdRole = Qt::UserRole + 1,
        aplicacaoAnoInicialRole,
        aplicacaoAnoFinalRole,
        montadoraNomeRole,
        veiculoNomeRole,
        tiposSistemaNomeRole,
        sistemaNomeRole,
        conectorNomeRole,
        conectorIdRole
    };

    explicit ModeloAplicacao(QObject *parent = nullptr);

    // método sobrescrito
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:

// slots são invocáveis pelo QML
// quando o objeto é exposto no main.cpp
public slots:
    void updateModel();
    int getId(int row);
    QString obtemNomeArquivoConector(int linha);
};

#endif // MODELOAPLICACAO_H


