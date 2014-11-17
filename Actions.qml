import QtQuick 2.3
import Qt.labs.folderlistmodel 2.1

ListView {
    width: 200; height: 400

    FolderListModel {
        id: folderModel
        //nameFilters: ["*.xml"]
        folder: "libraries"
    }

    Component {
        id: fileDelegate
        Text { text: fileName }
    }

    model: folderModel
    delegate: fileDelegate
}
