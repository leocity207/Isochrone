import matplotlib.pyplot as plt
import argparse
import csv
import numpy as np
import glob
from PIL import Image
from PIL import ImageDraw
from datetime import timedelta

def GetText(i,draw):
	minutes = 8*60+i
	text = str(minutes//60)+":"+str(minutes%60)
	draw.text((10, 10), text)
	
def Make_Into_Matrix(path):
	with open(path, 'r') as csv_file:
			reader = list(csv.reader(csv_file))
	reader2 = []
	for row in reader:
			reader2.append([float(row[i]) for i in range(len(row))])
	return reader2

def GetMax(matrixs):
	max = 0
	for matrix in matrixs:
		test_max = np.asarray(matrix).max()
		if(test_max > max):
			max = test_max
	print(max)
	return max/30

def Create_Image(matrix,max,i):
	cm = plt.get_cmap('Set3')#'viridis')
	colored_image = cm(np.asarray(matrix)/max)
	img = Image.fromarray((colored_image[:, :, :3] * 255).astype(np.uint8))
	draw = ImageDraw.Draw(img)
	GetText(i,draw)
	return img

def Load_Images(path):
	glober = [[path.replace("*",str(i)),i] for i in range(0,900)]
	matrixs = [Make_Into_Matrix(subpath[0]) for subpath in glober]
	max = GetMax(matrixs)
	return [Create_Image(matrixs[i],max,i) for i in range(0,900)]

def Make_GIF(frames,outfile):
	frame_one = frames[0]
	frame_one.save(outfile, format="GIF", append_images=frames,
               save_all=True, duration=100, loop=0)

if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument('path')
	parser.add_argument('out')
	args = parser.parse_args()
	images_arrays = Load_Images(args.path)
	Make_GIF(images_arrays,args.out)
	
