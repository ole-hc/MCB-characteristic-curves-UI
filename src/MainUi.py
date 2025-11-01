from PyQt6.QtWidgets import *
from PyQt6.QtGui import QColor, QColor, QPalette
from pyqtgraph import *

import UiDesign

import sys

GRAPH_AMOUNT = 5

class TextDisplayGray(QLabel):
    def __init__(self, text: str):
        super().__init__()
        self.setText(text)


class TextDisplayBackground(QLabel):
    def __init__(self, text: str):
        super().__init__()
        self.setText(text)


class GraphSelectionBox(QCheckBox):
    def __init__(self, text: str):
        super().__init__(text) 


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


class TextInput(QLineEdit):
    def __init__(self, placeholderText: str):
            super().__init__()
            self.setPlaceholderText(placeholderText)


class SwitchTimeIdentifier(QVBoxLayout):
    def __init__(self):
            super().__init__()
            self.placeholder = PlaceholderBackground()
            self.addWidget(self.placeholder)

            for graph in range(0, GRAPH_AMOUNT):
                descriptionText = "Graph " + str(graph)
                self.graphIdentifier = TextDisplayBackground(descriptionText)
                self.addWidget(self.graphIdentifier)


class SwitchTimeSolution(QVBoxLayout):
    def __init__(self):
            super().__init__()
            self.outputIdentifier = TextDisplayBackground("Time in seconds:")
            self.addWidget(self.outputIdentifier)

            for graph in range(0, GRAPH_AMOUNT):
                self.textDisplayGray = TextDisplayGray("")
                self.addWidget(self.textDisplayGray)


class SwitchCurrentInput(QVBoxLayout):
     def __init__(self):
            super().__init__()
            self.topInputIdentifier = TextDisplayBackground("Current")
            self.addWidget(self.topInputIdentifier)

            self.textInput = TextInput("Enter rated current")
            self.addWidget(self.textInput)

            self.bottomInputIdentifier = TextDisplayBackground("[x * rated current]")
            self.addWidget(self.bottomInputIdentifier)


class SwitchTimeCalculator(QHBoxLayout):
    def __init__(self):
            super().__init__()
            self.switchCurrentInput = SwitchCurrentInput()
            self.addLayout(self.switchCurrentInput)

            self.switchTimeSolution = SwitchTimeSolution()
            self.addLayout(self.switchTimeSolution)

            self.switchTimeIdentifier = SwitchTimeIdentifier()
            self.addLayout(self.switchTimeIdentifier)


class GraphSelector(QVBoxLayout):
    def __init__(self):
            super().__init__()
            for graph in range(0, GRAPH_AMOUNT):
                checkboxText = "Graph " + str(graph)
                self.graphSelectionBox = GraphSelectionBox(checkboxText)
                self.addWidget(self.graphSelectionBox)


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

        self.graphSelector = GraphSelector()
        self.addLayout(self.graphSelector)

        self.switchTimeCalculator = SwitchTimeCalculator()
        self.addLayout(self.switchTimeCalculator)


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