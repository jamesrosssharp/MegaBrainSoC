

pixelsx = 640
pixelsy = 360

depth = 32

fbsize = pixelsx * pixelsy * depth / 3

print "fbsize = %d %x" % (fbsize, fbsize)

fbsize2 = 0x300000

print "fbsize = %d %x" % (fbsize2, fbsize2)

print "total ram: %x" % (1024*1024*16)

