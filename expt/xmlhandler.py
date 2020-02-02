import xml.etree.ElementTree as ET
from PyQt4 import QtCore, QtGui
import re

class XMLHandler(object):

    def __init__(self, ui):

        self.tree = ET.parse('ISA.xml')
        self.root = self.tree.getroot()

        self.ui = ui

        # Find instructions and create list        

        print "Loaded ISA.xml"

        self.buildListWidget()

        self.ui.InstructionName.textEdited.connect(self.nameChanged)
        self.ui.HexMask.textEdited.connect(self.maskChanged)        
        self.ui.Encoding.textEdited.connect(self.encodingChanged)        
        self.ui.DisasFunc.textChanged.connect(self.disasChanged)        
        self.ui.DecodeFunc.textChanged.connect(self.decodeChanged)        
        
        self.ui.SaveButton.clicked.connect(self.save)
        self.ui.Encoding_2.clicked.connect(self.binary)
       
    def buildListWidget(self):

        self.ui.listWidget.clear()

        sortedlist = []

        for instruction in self.root.findall('instruction'):
            name = instruction.find('name').text
            sortedlist.append(name)
            instruction.find('decodefunc').text = self.to_func_name("decode", name)
            instruction.find('disasfunc').text = "disasString = " + self.to_func_name2("disas", name)

        sortedlist.sort()

        for s in sortedlist:
            self.ui.listWidget.addItem(s)       
 
        self.ui.listWidget.itemDoubleClicked.connect(self.handleListClick)

    def handleListClick(self, item):
        print item.text()

        theIns = None
        theItem = None
        for instruction in self.root.findall('instruction'):
            if instruction.find('name').text == item.text():
                theIns = instruction
                theItem = item

        if theIns is not None:
            self.loadInstruction(theIns, theItem)
    
    def loadInstruction(self, instruction, item):

        self.curInstruction = instruction       
        self.curItem = item 
        name                = self.curInstruction.find('name').text
        mask                = self.curInstruction.find('mask').text
        encoding            = self.curInstruction.find('encoding').text
        decodeFunc          = self.curInstruction.find('decodefunc').text
        disasFunc           = self.curInstruction.find('disasfunc').text

        if not mask:
            mask = "?"

        if not encoding:
            encoding = "?"

        if not decodeFunc:
            decodeFunc = self.to_func_name("decode", name)

        if not disasFunc:
            disasFunc = "disasString = " + self.to_func_name("disas", name)

        self.ui.InstructionName.setText(name)
        self.ui.HexMask.setText(mask)
        self.ui.Encoding.setText(encoding)
        self.ui.DisasFunc.setText(disasFunc)
        self.ui.DecodeFunc.setText(decodeFunc)
        
    def nameChanged(self):

        name = self.ui.InstructionName.text()

        if not name:
            name = "?"
        self.curInstruction.find('name').text = str(name)
        self.curItem.setText(name) 

    def save(self):

        self.tree.write("ISA.xml")     

    def maskChanged(self):
        mask = self.ui.HexMask.text()

        if not mask:
            mask = "?"
        self.curInstruction.find('mask').text = str(mask)
 
    def encodingChanged(self):
        mask = self.ui.Encoding.text()

        if not mask:
            mask = "?"
        self.curInstruction.find('encoding').text = str(mask)
 

    def disasChanged(self):
        disas = self.ui.DisasFunc.toPlainText()

        if not disas:
            disas = "disasString = " + self.to_func_name("disas", name)

        self.curInstruction.find('disasfunc').text = str(disas)

    def decodeChanged(self):
        decode = self.ui.DecodeFunc.toPlainText()

        if not decode:
            decode = self.to_func_name("decode", name)

        self.curInstruction.find('decodefunc').text = str(decode)

    def binary(self):
        binstr = str(self.ui.binaryString.text())

        i = 15
        val = 0
        mask = 0
        for c in binstr:
            if (c == '1'):
                val |= (1 << i)
                mask |= (1 << i)
            elif (c == '0'):
                mask |= (1 << i)
            i -= 1

        mask = self.ui.HexMask.setText("0x%04x" % mask)
        val  = self.ui.Encoding.setText("0x%04x" % val)
        self.maskChanged()
        self.encodingChanged()

    def to_func_name(self, pref, name):
        thestr = pref + '_' + re.sub(r'\W+', '_', name)
        thestr = re.sub(r'\_^','', thestr).lower() + "(thumbInstruction);"
        return thestr

    def to_func_name2(self, pref, name):
        thestr = pref + '_' + re.sub(r'\W+', '_', name)
        thestr = re.sub(r'\_^','', thestr).lower() + "(thumbInstruction, thumbInstruction2);"
        return thestr

