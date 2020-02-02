#!/usr/bin/python

import xml.etree.ElementTree as ET
import operator
import re

#
#   Generate code from ISA.xml
#

# Load xml

tree = ET.parse('ISA.xml')
root = tree.getroot()

# Create histogram of hex masks

masks_dict = {}

for instruction in root.findall('instruction'):
    mask = int(instruction.find('mask').text, 16)    
    try:
        masks_dict[mask] += 1
    except:
        masks_dict[mask] = 1

# Print histogram

sorted_x = sorted(masks_dict.items(), key=operator.itemgetter(1), reverse=True)
#for (mask, freq) in sorted_x:
#    print "%x: %d" % (mask, freq)

# Generate case statements

print "// AUTO Generated: do not edit"
print ""
print "#include \"cortexm0cpu.h\""
print "#include <string>"
print ""
print "bool CortexM0CPU::decodeInstructionHelper(uint16_t thumbInstruction)"
print "{"

for (mask, freq) in sorted_x:
    print "\tswitch (thumbInstruction & 0x%x)" % mask
    print "\t{"

    casesFoundDict = {}

    for instruction in root.findall('instruction'):
        if int(instruction.find('mask').text, 16) == mask:
            encoding = int(instruction.find('encoding').text, 16)
            found = False
            try:
                if casesFoundDict[encoding]:
                    found = True
            except:
                pass           

            casesFoundDict[encoding] = 1
 
            if not found:    
                print "\t\t// %s" % instruction.find('name').text
                print "\t\tcase 0x%x:" % encoding
                print "\t\t{"
                print "\t\t\t%s" % instruction.find('decodefunc').text
                print "\t\t\treturn true;"
                print "\t\t}"
            else:
                print "\t\t// Encoding 0x%x already found" % encoding
                print "\t\t// %s" % instruction.find('name').text    

    print "\t\tdefault: break;"
    print "\t}"
print "\t return false;"
print "}"

print ""
print "std::string CortexM0CPU::disassembleInstructionHelper(uint16_t thumbInstruction, uint16_t thumbInstruction2)"
print "{"
print "\tstd::string disasString;"

for (mask, freq) in sorted_x:
    print "\tswitch (thumbInstruction & 0x%x)" % mask
    print "\t{"

    casesFoundDict = {}

    for instruction in root.findall('instruction'):
        if int(instruction.find('mask').text, 16) == mask:
            encoding = int(instruction.find('encoding').text, 16)
            found = False
            try:
                if casesFoundDict[encoding]:
                    found = True
            except:
                pass           

            casesFoundDict[encoding] = 1
 
            if not found:   
 
                print "\t\t// %s" % instruction.find('name').text
                print "\t\tcase 0x%x:" % encoding
                print "\t\t{"
                print "\t\t\t%s" % instruction.find('disasfunc').text
                print "\t\t\treturn disasString;"
                print "\t\t}"
            else:
                print "\t\t// Encoding 0x%x already found" % encoding
                print "\t\t// %s" % instruction.find('name').text    

    print "\t\tdefault: break;"
    print "\t}"

print "\treturn std::string(\"UNKNOWN INSTRUCTION\");"
print "}"

print "\n\n"
for instruction in root.findall('instruction'):
    print "// %s" % instruction.find('name').text
    print "// %s" % instruction.find('decodefunc').text
    print "// %s"  % instruction.find('disasfunc').text


