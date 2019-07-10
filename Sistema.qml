import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2

Item {

    // tabela com visualização dados
    TableView {
        id: tableView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: rowLayoutCampos.top
        anchors.margins: 10


        TableViewColumn {
            role: "sistemaId"
            title: "ID Sistema"
        }
        TableViewColumn {
            role: "sistemaNome"
            title: "Sistema"
        }
        TableViewColumn {
            role: "tiposSistemaNome"
            title: "Tipo de Sistema"
        }

        model: modeloSistema

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
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
        spacing: 10

        Text {text: qsTr("Nome do Sistema")}
        TextField { id: campoSistema }

        Text {text: qsTr("Tipo de Sistema")}
        ComboBox {
            id: comboBox
            model: modeloTiposSistema
            textRole: "tiposSistemaNomeRole"
        }

        Button {
            text: qsTr("Adicionar")

            // Make a new entry in the database
            onClicked: {

                // adiciona o nome do veículo e o id da montadora selecionada no comboBox
                database.inserIntoTableSistema(campoSistema.text, modeloTiposSistema.getId(comboBox.currentIndex))
                modeloSistema.updateModel() // And updates the data model with a new record

                campoSistema.text = ""
            }
        } // botão adicionar
    } // rowlayout - campos de cadastro

}
