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
        functionDisplay = TextDisplayGray("f(x) = mx+b")
        spacer = QWidget()
        self.addWidget(functionDisplay)
        self.addWidget(spacer)


class PlaceholderBackground(QLabel):
    def __init__(self):
        super().__init__()


class FunctionalHorizontalLayout(QHBoxLayout):
    def __init__(self):
        super().__init__()
        text = TextDisplayGray("adhadhadha")
        self.addWidget(text)


class MainWidget(QWidget):
    def __init__(self):
        super().__init__()
        functionalHorizontalLayout = FunctionalHorizontalLayout()
        self.setLayout(functionalHorizontalLayout)


class CentralWidget(QWidget):
    def __init__(self):
        super().__init__()
        # setup general ui layout
        # □ □   » display of the function inside the graph
        # □     » black placeholder label
        # □     » all of the Ui functionality with own layout

        mainVerticalLayout = QVBoxLayout()

        functionDisplayHorizontalLayout = FunctionDisplayHorizontalLayout()
        mainVerticalLayout.addLayout(functionDisplayHorizontalLayout)

        placeholderBackground = PlaceholderBackground()
        mainVerticalLayout.addWidget(placeholderBackground)

        functionalHorizontalLayout = FunctionalHorizontalLayout()
        mainVerticalLayout.addLayout(functionalHorizontalLayout)

        self.setLayout(mainVerticalLayout)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("MCB characteristics curves UI")
        centralWidget = CentralWidget()
        self.setCentralWidget(centralWidget)

        

userInterface = QApplication(sys.argv)

mainWindow = MainWindow()
mainWindow.setStyleSheet(UiDesign.darkMode)
mainWindow.show()

userInterface.exec()