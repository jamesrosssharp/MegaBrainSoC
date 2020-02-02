#!/usr/bin/python

import xml.sax.saxutils as su
import re

print "<?xml version='1.0' ?>"
print "<isa>" 

theFile = open("../doc/M0.txt")

for line in theFile.readlines():
    print "\t<instruction>"
    print "\t\t<name>%s</name>" % su.escape(re.sub("\n", "", line))
    print "\t\t<mask></mask>"
    print "\t\t<encoding></encoding>"
    print "\t\t<decodefunc></decodefunc>"
    print "\t\t<disasfunc></disasfunc>"
    print "\t</instruction>"

print "</isa>"

