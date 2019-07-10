
#ifndef MODELOVEICULO_H
#define MODELOVEICULO_H

#include <QObject>
#include <QSqlQueryModel>

class ModeloVeiculo : public QSqlQueryModel
{
    Q_OBJECT
public:

    enum Roles {
        veiculoIdRole = Qt::UserRole + 1,
        veiculoNomeRole,
        montadoraIdRole,
        montadoraNomeRole
    };

    explicit ModeloVeiculo(QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:

    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void updateModel();
    int getId(int row);
};

#endif // MODELOVEICULO_H
