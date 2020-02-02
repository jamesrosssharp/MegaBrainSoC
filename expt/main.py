import xmleditor
from PyQt4 import QtCore, QtGui
import sys

import xmlhandler


app = QtGui.QApplication(sys.argv)
MainWindow = QtGui.QMainWindow()
ui = xmleditor.Ui_MainWindow()
ui.setupUi(MainWindow)

h = xmlhandler.XMLHandler(ui)

MainWindow.show()
sys.exit(app.exec_())

