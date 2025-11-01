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


class CoordinateSystem(PlotWidget):
    def __init__(self):
        super().__init__()
        minutes = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        temperature = [30, 32, 34, 32, 33, 31, 29, 32, 35, 30]
        self.plot()

class FunctionalHorizontalLayout(QHBoxLayout):
    def __init__(self):
        super().__init__()
        self.coordinateSystem = CoordinateSystem()
        self.addWidget(self.coordinateSystem)


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