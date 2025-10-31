from PyQt6.QtWidgets import QApplication, QWidget

import sys

userInterface = QApplication(sys.argv)

mainWindow = QWidget()
mainWindow.show()

userInterface.exec()