import matplotlib.pyplot as plt
import argparse
import csv
import numpy as np


if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument('filename')
	args = parser.parse_args()
	reader = []
	with open(args.filename, 'r') as csv_file:
		reader = list(csv.reader(csv_file))
	reader2 = []
	for row in reader:
		reader2.append([float(row[i]) for i in range(len(row))])
	plt.figure()
	plt.imshow(reader2,aspect="equal")
	plt.show()


	
