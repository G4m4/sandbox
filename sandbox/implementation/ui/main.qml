import QtQuick 2.0
import ImGui 1.0

Rectangle {
    id: root
    color: "lightGray"

    Text {
        anchors.centerIn: parent
        text: "Qt Quick + ImGui"
    }

    ImGui {
        objectName: "imgui"
        anchors.fill: parent
        focus: true // for keybord input
    }
}
