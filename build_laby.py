import matplotlib.image as mpimg
import numpy as np
import sys

size=int(sys.argv[1])
fichier=open("walls.txt","w")
fichier.write(str(size))
fichier.close()

img_width=1+4*size;

img = np.zeros((img_width, img_width, 3), dtype=np.uint8)

# draw #

for i in range(0,size) :
	for j in range(0,size) :
		img[i*4][j*4+1]=(255,255,255)
		img[i*4][j*4+2]=(255,255,255)
		img[i*4][j*4+3]=(255,255,255)

		img[i*4+1][j*4]=(255,255,255)
		img[i*4+2][j*4]=(255,255,255)
		img[i*4+3][j*4]=(255,255,255)

		for k in range(0,3) :
			for l in range(0,3) :
				img[i*4+1+k][j*4+1+l]=(150,150,150)

for i in range(0,size) :
	img[i*4+1][0]=(255,0,0)
	img[i*4+2][0]=(255,0,0)
	img[i*4+3][0]=(255,0,0)

for j in range(0,size) :
	img[0][j*4+1]=(255,0,0)
	img[0][j*4+2]=(255,0,0)
	img[0][j*4+3]=(255,0,0)

for i in range(0,size) :
	img[i*4+1][size*4]=(255,0,0)
	img[i*4+2][size*4]=(255,0,0)
	img[i*4+3][size*4]=(255,0,0)

for j in range(0,size) :
	img[size*4][j*4+1]=(255,0,0)
	img[size*4][j*4+2]=(255,0,0)
	img[size*4][j*4+3]=(255,0,0)

mpimg.imsave("maze.png", img)
