import QtQuick 1.1

Rectangle {
    width: 100
    height: 62
    anchors.fill: parent


    Rectangle {
           id: button //Имя кнопки

           //Размещаем в центре
           x: parent.width / 2 - button.width / 2;
           y: parent.height / 2 - button.height / 2;

           //Размеры кнопки
           width: 100
           height: 30

           //Цвет кнопки
           color: "gray"

           //Текст кнопки
           Text {
               id: buttonLabel
               text: "Пуск"
               anchors.centerIn: parent;
           }

           //Действие мыши
           MouseArea {
               anchors.fill: parent
               id: mouseArea
           }
       }
}
