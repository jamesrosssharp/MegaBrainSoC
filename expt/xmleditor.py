# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'xmleditor.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(800, 600)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.horizontalLayout = QtGui.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.listWidget = QtGui.QListWidget(self.centralwidget)
        self.listWidget.setObjectName(_fromUtf8("listWidget"))
        self.horizontalLayout.addWidget(self.listWidget)
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.label_2 = QtGui.QLabel(self.centralwidget)
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.gridLayout.addWidget(self.label_2, 2, 0, 1, 1)
        self.Encoding = QtGui.QLineEdit(self.centralwidget)
        self.Encoding.setObjectName(_fromUtf8("Encoding"))
        self.gridLayout.addWidget(self.Encoding, 3, 1, 1, 3)
        self.label_3 = QtGui.QLabel(self.centralwidget)
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.gridLayout.addWidget(self.label_3, 3, 0, 1, 1)
        self.InstructionName = QtGui.QLineEdit(self.centralwidget)
        self.InstructionName.setObjectName(_fromUtf8("InstructionName"))
        self.gridLayout.addWidget(self.InstructionName, 1, 1, 1, 3)
        self.NewButton = QtGui.QPushButton(self.centralwidget)
        self.NewButton.setObjectName(_fromUtf8("NewButton"))
        self.gridLayout.addWidget(self.NewButton, 7, 0, 1, 4)
        self.HexMask = QtGui.QLineEdit(self.centralwidget)
        self.HexMask.setObjectName(_fromUtf8("HexMask"))
        self.gridLayout.addWidget(self.HexMask, 2, 1, 1, 3)
        self.DisasFunc = QtGui.QTextEdit(self.centralwidget)
        self.DisasFunc.setObjectName(_fromUtf8("DisasFunc"))
        self.gridLayout.addWidget(self.DisasFunc, 5, 1, 1, 3)
        self.label_4 = QtGui.QLabel(self.centralwidget)
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.gridLayout.addWidget(self.label_4, 4, 0, 1, 1)
        self.label_5 = QtGui.QLabel(self.centralwidget)
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.gridLayout.addWidget(self.label_5, 5, 0, 1, 1)
        self.SaveButton = QtGui.QPushButton(self.centralwidget)
        self.SaveButton.setObjectName(_fromUtf8("SaveButton"))
        self.gridLayout.addWidget(self.SaveButton, 6, 0, 1, 4)
        self.label = QtGui.QLabel(self.centralwidget)
        self.label.setObjectName(_fromUtf8("label"))
        self.gridLayout.addWidget(self.label, 1, 0, 1, 1)
        self.DecodeFunc = QtGui.QTextEdit(self.centralwidget)
        self.DecodeFunc.setObjectName(_fromUtf8("DecodeFunc"))
        self.gridLayout.addWidget(self.DecodeFunc, 4, 1, 1, 3)
        self.Encoding_2 = QtGui.QPushButton(self.centralwidget)
        self.Encoding_2.setObjectName(_fromUtf8("Encoding_2"))
        self.gridLayout.addWidget(self.Encoding_2, 8, 0, 1, 2)
        self.binaryString = QtGui.QLineEdit(self.centralwidget)
        self.binaryString.setObjectName(_fromUtf8("binaryString"))
        self.gridLayout.addWidget(self.binaryString, 8, 2, 1, 1)
        self.horizontalLayout.addLayout(self.gridLayout)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "ISA.xml Editor", None))
        self.label_2.setText(_translate("MainWindow", "Hex Mask", None))
        self.label_3.setText(_translate("MainWindow", "Encoding", None))
        self.NewButton.setText(_translate("MainWindow", "New Instruction", None))
        self.label_4.setText(_translate("MainWindow", "DecodeFunc", None))
        self.label_5.setText(_translate("MainWindow", "DisasFunc", None))
        self.SaveButton.setText(_translate("MainWindow", "Save", None))
        self.label.setText(_translate("MainWindow", "Instruction", None))
        self.Encoding_2.setText(_translate("MainWindow", "Binary Encoding", None))

