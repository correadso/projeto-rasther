#include <QObject>
#include <QSqlQueryModel>

#ifndef MODELOMONTADORA_H
#define MODELOMONTADORA_H


class ModeloMontadora: public QSqlQueryModel
{
    Q_OBJECT
public:

    enum Roles {
        montadoraIdRole = Qt::UserRole + 1,
        montadoraNomeRole,

        // tipos sistema
        tiposSistemaIdRole,
        tiposSistemaNomeRole
    };

    explicit ModeloMontadora(QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:

    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void selecionaMontadoras();
    void updateModelTiposSistema();
    void updateModel();
    void updateModel(QString tabela);
    int getId(int row);
};

#endif // MODELOMONTADORA_H

