import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2

Item {
    id: telaConector

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
            role: "conectorIdRole"
            title: "ID Conector"
        }
        TableViewColumn {
            role: "conectorNomeRole"
            title: "Conector"
        }
        TableViewColumn {
            role: "conectorFotoRole"
            title: "Arquivo"
        }

        model: modeloConector

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

                }
            }
        }
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

        source: "file:///C:/tecnomotor/Conectores/" + modeloConector.obtemNomeArquivoConector(tableView.currentRow)
    }

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

        Text {text: qsTr("Nome Conector")}
        TextField { id: fnameField}
        Text {text: qsTr("Arquivo Conector")}
        TextField {id: nikField}

        Button {
            text: qsTr("Adicionar")

            onClicked: {
                database.inserIntoTableConector(fnameField.text, nikField.text)
                modeloConector.updateModel() // And updates the data model with a new record
                fnameField.text = ""
                nikField.text = ""
            }
        } // botão adicionar
    } // rowlayout - campos de cadastro

}
