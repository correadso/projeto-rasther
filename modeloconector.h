#include <QObject>
#include <QSqlQueryModel>

#ifndef MODELOCONECTOR_H
#define MODELOCONECTOR_H

class ModeloConector : public QSqlQueryModel
{
    Q_OBJECT
public:

    enum Roles {
        conectorIdRoleIdc = Qt::UserRole + 1,
        conectorNomeRole,
        conectorFotoRole
    };

    explicit ModeloConector(QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:

// slots são invocáveis pelo QML
// quando o objeto é exposto no main.cpp
public slots:
    void updateModel();
    void updateModel(QString tabela);
    int getId(int row);
    QString obtemNomeArquivoConector(int linha);
};

#endif // MODELOCONECTOR_H


