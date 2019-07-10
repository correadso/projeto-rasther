#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bancodados.h"
#include "modeloveiculo.h"
#include "modelomontadora.h"
#include "modelotipossistema.h"
#include "modeloconector.h"
#include "modeloaplicacao.h"
#include "modelosistema.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;


    BancoDados database;
    database.connectToDataBase();

    // exposição do C++ para ser utilizado no QML (interface)
    ModeloVeiculo *modeloVeiculo = new ModeloVeiculo();
    ModeloMontadora *modelMontadora = new ModeloMontadora();
    ModeloTiposSistema *modelTiposSistema = new ModeloTiposSistema();
    ModeloSistema *modelSistema = new ModeloSistema();
    ModeloConector *modeloConector = new ModeloConector();
    ModeloAplicacao *modeloAplicacao = new ModeloAplicacao();

    engine.rootContext()->setContextProperty("modeloVeiculo", modeloVeiculo);
    engine.rootContext()->setContextProperty("modeloMontadora", modelMontadora);
    engine.rootContext()->setContextProperty("modeloTiposSistema", modelTiposSistema);
    engine.rootContext()->setContextProperty("modeloSistema", modelSistema);
    engine.rootContext()->setContextProperty("modeloConector", modeloConector);
    engine.rootContext()->setContextProperty("modeloAplicacao", modeloAplicacao);
    engine.rootContext()->setContextProperty("database", &database);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
