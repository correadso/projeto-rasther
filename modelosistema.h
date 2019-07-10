#ifndef MODELOSISTEMA_H
#define MODELOSISTEMA_H

#include <QObject>
#include <QSqlQueryModel>

class ModeloSistema : public QSqlQueryModel
{
    Q_OBJECT
public:

    enum Roles {
        sistemaIdRole = Qt::UserRole + 1,
        sistemaNomeRole,
        tiposSistemaIdRole,
        tiposSistemaNomeRole
    };

    explicit ModeloSistema(QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:

    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void updateModel();
    int getId(int row);
};

#endif // MODELOSISTEMA_H
