import matplotlib.image as mpimg
import numpy as np
import sys

size=int(sys.argv[1])

img = mpimg.imread("maze.png")

walls_h=np.zeros((size+1,size), dtype=int)
walls_v=np.zeros((size,size+1), dtype=int)

# h walls
for i in range(0,size+1) :
	for j in range(0,size) :
		if img[i*4][j*4+1][0]==1 and img[i*4][j*4+1][1]==0 and img[i*4][j*4+1][2]==0:
			walls_h[i][j]=1

# v walls
for i in range(0,size) :
	for j in range(0,size+1) :
		if img[i*4+1][j*4][0]==1 and img[i*4+1][j*4][1]==0 and img[i*4+1][j*4][2]==0:
			walls_v[i][j]=1

print(walls_h)
print(walls_v)

fichier = open("walls.txt", "w")
for i in range(0,size+1):
	for j in range(0,size):
		if walls_h[i][j]==1:
			print(i,j)
			line=str(size-i)+","+str(j)+'\n'
			fichier.write(line)

fichier.write('\n')
print('\n')

for i in range(0,size):
	for j in range(0,size+1):
		if walls_v[i][j]==1:
			print(i,j)
			line=str(size-i-1)+","+str(j)+'\n'
			fichier.write(line)

fichier.write('\n')

fichier.close()
