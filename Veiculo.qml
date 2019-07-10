import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2

Item {

    id: telaVeiculo

    // tabela com visualização dados
    TableView {
        id: tableView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: rowLayoutCampos.top
        anchors.margins: 10

        TableViewColumn {
            role: "veiculoId"
            title: "ID Veículo"
        }
        TableViewColumn {
            role: "veiculoNome"
            title: "Veículo"
        }
        TableViewColumn {
            role: "montadoraNome"
            title: "Montadora"
        }

        model: modeloVeiculo

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

                }
            }
        }
    } // tabela com visualização dados


    // campos de cadastro
    RowLayout {
        id: rowLayoutCampos
        anchors {
            //top: tableView.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        spacing: 10

        Text {text: qsTr("Nome Veículo")}
        TextField { id: fnameField}

        Text {text: qsTr("Montadora")}
        ComboBox {
            id: comboBox
            //currentIndex: 2
            model: modeloMontadora
            textRole: "montadoraNomeRole"
        }

        Button {
            text: qsTr("Adicionar")

            // Make a new entry in the database
            onClicked: {

                // adiciona o nome do veículo e o id da montadora selecionada no comboBox
                database.inserIntoTableVeiculo(fnameField.text, modeloMontadora.getId(comboBox.currentIndex))
                modeloVeiculo.updateModel() // And updates the data model with a new record

                fnameField.text = ""
            }
        } // botão adicionar
    } // rowlayout - campos de cadastro

}
