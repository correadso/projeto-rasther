import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2

Item {
    //anchors.fill: parent

    // tabela com visualização dados
    TableView {
        id: tableView
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            rightMargin: 150
            bottom: rowLayoutCampos.top
            margins: 10
        }

        TableViewColumn {
            width: 100
            role: "montadoraNome"
            title: "Montadora"
        }
        TableViewColumn {
            role: "veiculoNome"
            title: "Veículo"
        }
        TableViewColumn {
            width: 100
            role: "tiposSistemaNome"
            title: "Tipo Sistema"
        }
        TableViewColumn {
            width: 100
            role: "sistemaNome"
            title: "Sistema"
        }
        TableViewColumn {
            width: 70
            role: "aplicacaoAnoInicial"
            title: "Ano Inicial"
        }
        TableViewColumn {
            width: 70
            role: "aplicacaoAnoFinal"
            title: "Ano Final"
        }

        model: modeloAplicacao

        // Setting lines in TableView to intercept mouse left click
        rowDelegate: Rectangle {
            anchors.fill: parent
            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked: {
                    tableView.selection.clear()
                    tableView.selection.select(styleData.row)
                    tableView.currentRow = styleData.row
                    tableView.focus = true

                } // onClicked
            } // mousearea
        } // Rectangle - row delegate
    } // tabela com visualização dados


    // foto conector
    Image {
        id: imageConector
        height: 135
        width: 135
        anchors {
            top: parent.top
            right: parent.right
            topMargin: 10
            rightMargin: 10
        }
        source: "file:///C:/tecnomotor/Conectores/" + modeloAplicacao.obtemNomeArquivoConector(tableView.currentRow)
    }

    // campos de cadastro
    GridLayout {
        id: rowLayoutCampos
        anchors {
            //top: tableView.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }

        columns: 8

        Text {text: "Montadora"}
        ComboBox {
            id: comboBoxMontadora
            model: modeloMontadora
            textRole: "montadoraNomeRole"
        }

        Text {text: "Veículo"}
        ComboBox {
            id: comboBoxVeiculo
            model: modeloVeiculo
            textRole: "veiculoNome"
        }

        Text {text: "Tipos Sistema"}
        ComboBox {
            id: comboBoxTiposSistema
            model: modeloTiposSistema
            textRole: "tiposSistemaNomeRole"
        }

        Text {text: "Sistema"}
        ComboBox {
            id: comboBoxSistema
            model: modeloSistema
            textRole: "sistemaNome"
        }

        Text {text: "Conector"}
        ComboBox {
            id: comboBoxConector
            model: modeloConector
            textRole: "conectorNomeRole"
        }

        Text {text: "Ano Inicial"}
        TextField {
            id: anoInicial
            validator: IntValidator {bottom: 1900; top: 3000;}
        }

        Text {text: "Ano Final"}
        TextField {
            id: anoFinal
            validator: IntValidator {bottom: 1900; top: 3000;}
        }

        Text {text: ""} // elemento vazio para manter layout

        Button {
            text: "Adicionar"
            onClicked: {

                database.inserIntoTableAplicacao(
                            anoInicial.text,
                            anoFinal.text,
                            modeloMontadora.getId(comboBoxMontadora.currentIndex),
                            modeloVeiculo.getId(comboBoxVeiculo.currentIndex),
                            modeloTiposSistema.getId(comboBoxTiposSistema.currentIndex),
                            modeloSistema.getId(comboBoxSistema.currentIndex),
                            modeloConector.getId(comboBoxConector.currentIndex)
                            )
                modeloAplicacao.updateModel() // And updates the data model with a new record

                anoInicial.text = ""
                anoFinal.text = ""
            }
        } // botão adicionar
    }
}
