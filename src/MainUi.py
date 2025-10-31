from PyQt6.QtWidgets import *
from PyQt6.QtGui import QColor, QColor, QPalette

import UiDesign

import sys

class TextDisplayGray(QLabel):
    def __init__(self, text: str):
        super().__init__()
        self.setText(text)


class FunctionDisplayHorizontalLayout(QHBoxLayout):
    def __init__(self):
        super().__init__()
        leftWidget = TextDisplayGray("f(x) = mx+b")
        rightWidget = QWidget()
        self.addWidget(leftWidget)
        self.addWidget(rightWidget)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("MCB characteristics curves UI")
        centralWidget = QWidget()
        self.setCentralWidget(centralWidget)

        # setup general ui layout
        # □ □   » display of the function inside the graph
        # □     » all of the Ui functionality with own layout

        mainVerticalLayout = QVBoxLayout()
        functionDisplayHorizontalLayout = FunctionDisplayHorizontalLayout()
        mainVerticalLayout.addLayout(functionDisplayHorizontalLayout)
        centralWidget.setLayout(mainVerticalLayout)
        

userInterface = QApplication(sys.argv)

mainWindow = MainWindow()
mainWindow.setStyleSheet(UiDesign.darkMode)
mainWindow.show()

userInterface.exec()