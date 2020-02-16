#/usr/bin/python

import png
import re

pngfiles = ["MegaBrain3.png"]

for pngfile in pngfiles:

    mbpng = png.Reader(file=open(pngfile))
    (width, height, rowiter, info) = mbpng.read()
    print "w: %d h: %d\n" % (width, height)

    #for row in rowiter:
    #    print row

    #print info

    # Create C header file

    thename = re.sub("\\.png", "", pngfile) 

    cheader = open("%s_asset.h" % thename, "w")

    cheader.write("// Automatically generated do not edit")
    cheader.write("\n\n")

    cheader.write("const uint32_t %s_palette[] = {\n" % thename)

    i = 0
    for (r,g,b,a) in info['palette']:
        val = r | (g << 8) | (b << 16)
        c = '\t'
        d = ''
        if (i % 4) != 0:
            c = ','
        if (i % 4) == 3 and i != 255:
            d = ','
        
        cheader.write("%s0x%08x%s" % (c, val, d))
        if i % 4 == 3:
            cheader.write("\n")
        i += 1

    cheader.write("};\n")

    cheader.close()

