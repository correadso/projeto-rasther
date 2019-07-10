import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.2

Item {
    id: telaMontadora
    //anchors.fill: parent

    // tabela com visualização dados
    TableView {
        id: tableView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: rowLayoutCampos.top
        anchors.margins: 10


        TableViewColumn {
            role: "id"
            title: "ID Montadora"
        }
        TableViewColumn {
            role: "montadoraNomeRole"
            title: "Montadora"
        }

        model: modeloMontadora

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

        Text {text: qsTr("Nome Montadora")}
        TextField { id: fnameField}

        Button {
            text: qsTr("Adicionar")

            // Make a new entry in the database
            onClicked: {
                database.inserIntoTableMontadora(fnameField.text)
                modeloMontadora.updateModel() // And updates the data model with a new record
                fnameField.text = ""
            }
        } // botão adicionar
    } // rowlayout - campos de cadastro
}
