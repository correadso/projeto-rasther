import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: appWindow

    visible: true
    width: 800
    height: 600
    title: "Tecnomotor Rasther"

    // ações que ocorrem quando iniciam a tela principal
    Component.onCompleted: {

        // primeira tela que será visível
        telaAplicacao.visible = true
        telaVeiculo.visible = false
        telaConector.visible = false
        telaMontadora.visible = false
        telaSistema.visible = false
        telaTiposSistema.visible = false
        appWindow.title = "Tecnomotor Rasther - Aplicação"
    }

    // declarando objeto QML
    Veiculo {
        id: telaVeiculo
        anchors {
            top: rowLayoutSecoes.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }

    // declarando objeto QML
    Montadora {
        id: telaMontadora
        anchors {
            top: rowLayoutSecoes.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }

    Aplicacao {
        id: telaAplicacao
        anchors {
            top: rowLayoutSecoes.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }

    Sistema {
        id: telaSistema
        anchors {
            top: rowLayoutSecoes.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }

    TiposSistema {
        id: telaTiposSistema
        anchors {
            top: rowLayoutSecoes.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }

    Conector {
        id: telaConector
        anchors {
            top: rowLayoutSecoes.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }

    // botões para escolher seções
    RowLayout {
        id: rowLayoutSecoes
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }

        spacing: 10

        Button {
            id: botaoAplicacao
            text: "Aplicação"

            onClicked: {
                appWindow.title = "Tecnomotor Rasther - Aplicação"
                telaAplicacao.visible = true
                telaVeiculo.visible = false
                telaMontadora.visible = false
                telaConector.visible = false
                telaSistema.visible = false
                telaTiposSistema.visible = false
            }
        } // botão aplicação

        Button {
            id: botaoConector
            text: "Conector"

            onClicked: {
                appWindow.title = "Tecnomotor Rasther - Conector"
                telaConector.visible = true
                telaVeiculo.visible = false
                telaMontadora.visible = false
                telaSistema.visible = false
                telaTiposSistema.visible = false
                telaAplicacao.visible = false
            }
        } // botão conector


        Button {
            id: botaoVeiculo
            text: "Veículo"

            onClicked: {
                appWindow.title = "Tecnomotor Rasther - Veículo"
                telaVeiculo.visible = true
                telaMontadora.visible = false
                telaConector.visible = false
                telaSistema.visible = false
                telaTiposSistema.visible = false
                telaAplicacao.visible = false
            }
        } // botão veículo

        Button {
            id: botaoMontadora
            text: "Montadora"

            onClicked: {

                appWindow.title = "Tecnomotor Rasther - Montadora"

                telaVeiculo.visible = false
                telaMontadora.visible = true
                telaConector.visible = false
                telaSistema.visible = false
                telaTiposSistema.visible = false
                telaAplicacao.visible = false
            }
        } // botão montadora

        Button {
            id: botaoSistema
            text: "Sistema"

            onClicked: {
                appWindow.title = "Tecnomotor Rasther - Sistema"
                telaSistema.visible = true
                telaVeiculo.visible = false
                telaMontadora.visible = false
                telaConector.visible = false
                telaTiposSistema.visible = false
                telaAplicacao.visible = false
            }
        } // botão sistema

        Button {
            id: botaoTiposSistema
            text: "Tipos de sistema"

            onClicked: {
                appWindow.title = "Tecnomotor Rasther - Tipos de Sistema"
                telaTiposSistema.visible = true
                telaVeiculo.visible = false
                telaMontadora.visible = false
                telaConector.visible = false
                telaSistema.visible = false
                telaAplicacao.visible = false
            }
        } // botão tipos sistema
    } // RowLayout - escolha telas


}
