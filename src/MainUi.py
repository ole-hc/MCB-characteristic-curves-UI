from PyQt6.QtWidgets import *
from PyQt6.QtGui import QColor, QColor, QPalette
from pyqtgraph import *

import UiDesign

import sys

class TextDisplayGray(QLabel):
    def __init__(self, text: str):
        super().__init__()
        self.setText(text)


class FunctionDisplayHorizontalLayout(QHBoxLayout):
    def __init__(self):
        super().__init__()
        self.functionDisplay = TextDisplayGray("f(x) = mx+b")
        self.spacer = QWidget()
        self.addWidget(self.functionDisplay)
        self.addWidget(self.spacer)


class PlaceholderBackground(QLabel):
    def __init__(self):
        super().__init__()


class CoordinateSystem(QWidget):
    def __init__(self):
        super().__init__()
        


class FunctionalHorizontalLayout(QHBoxLayout):
    def __init__(self):
        super().__init__()
        self.text = TextDisplayGray("adhadhadha")
        self.addWidget(self.text)


class MainWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.functionalHorizontalLayout = FunctionalHorizontalLayout()
        self.setLayout(self.functionalHorizontalLayout)


class CentralWidget(QWidget):
    def __init__(self):
        super().__init__()
        # setup general ui layout
        # □ □   » display of the function inside the graph
        # □     » black placeholder label
        # □     » all of the Ui functionality with own layout

        self.mainVerticalLayout = QVBoxLayout()

        self.functionDisplayHorizontalLayout = FunctionDisplayHorizontalLayout()
        self.mainVerticalLayout.addLayout(self.functionDisplayHorizontalLayout)

        self.placeholderBackground = PlaceholderBackground()
        self.mainVerticalLayout.addWidget(self.placeholderBackground)

        self.functionalHorizontalLayout = FunctionalHorizontalLayout()
        self.mainVerticalLayout.addLayout(self.functionalHorizontalLayout)

        self.setLayout(self.mainVerticalLayout)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("MCB characteristics curves UI")
        self.centralWidget = CentralWidget()
        self.setCentralWidget(self.centralWidget)

        

userInterface = QApplication(sys.argv)

mainWindow = MainWindow()
mainWindow.setStyleSheet(UiDesign.darkMode)
mainWindow.show()

userInterface.exec()