import matplotlib.pyplot as plt
import argparse
import csv
import numpy as np
import glob
from PIL import Image

def Create_Image(path):
	reader2 = []
	with open(path, 'r') as csv_file:
			reader = list(csv.reader(csv_file))
	reader2 = []
	for row in reader:
			reader2.append([float(row[i]) for i in range(len(row))])
	cm = plt.get_cmap('viridis')
	colored_image = cm(np.asarray(reader2)/np.asarray(reader2).max())
	return Image.fromarray((colored_image[:, :, :3] * 255).astype(np.uint8))

def Load_Images(path):
	glober = [path.replace("*",str(i)) for i in range(720)]
	images = [Create_Image(subpath) for subpath in glober]
	return images

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
	
