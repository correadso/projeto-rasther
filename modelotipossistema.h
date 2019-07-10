#ifndef MODELOTIPOSSISTEMA_H
#define MODELOTIPOSSISTEMA_H

#include <QObject>
#include <QSqlQueryModel>

class ModeloTiposSistema: public QSqlQueryModel
{
    Q_OBJECT
public:

    enum Roles {
        tiposSistemaIdRole = Qt::UserRole + 1,
        tiposSistemaNomeRole
    };

    explicit ModeloTiposSistema(QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:

    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void selecionaTiposSistema();
    void updateModel();
    int getId(int row);
};

#endif // MODELOTIPOSSISTEMA_H
