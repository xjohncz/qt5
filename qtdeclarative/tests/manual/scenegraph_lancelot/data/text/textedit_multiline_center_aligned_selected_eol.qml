import QtQuick 2.0

Item {
    width: 320
    height: 480

    TextEdit {
        id: textEdit
        anchors.centerIn: parent
        font.family: "Arial"
        font.pixelSize: 16
        width: 200
        wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
        horizontalAlignment: TextEdit.AlignHCenter
        text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In id diam vitae enim fringilla vestibulum. Pellentesque non leo justo, quis vestibulum augue"

        Component.onCompleted: {
            textEdit.select(63, 67)
        }
    }

}
