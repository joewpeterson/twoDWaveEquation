import numpy as np 
import matplotlib.pyplot as plt
import os

def main():
  '''
  movieMaker1D reads a 1D text dataset with a specifically fromated
  header and data section.

  It used pyplot to generate an image for sections of the dataset and
  then stitches the images together with ffmgpeg
  '''

  #Read header information
  with open("data.dat", 'r') as fh:
    n  = int(fh.readline())
    dx = float(fh.readline())
    L  = int(fh.readline())
  
  #Read the data
  p0 = np.loadtxt("data.dat", skiprows=3)
  x = np.arange(0,L,dx)
  x = x.reshape(n,1)

  #clean any images
  os.system("rm .image_*.png")

  #Create the frames
  frame_number = 0
  for i in range(int(p0.size/n)):
    frame_number += 1
  
    plt.plot(x,p0[i*n:(i+1)*n])
    plt.ylim(-.018, .018)
    plt.savefig(".image_{:03d}.png".format(frame_number))
    plt.clf()
  
  #make the movie
  os.system("ffmpeg -i .image_%03d.png -c:v libx264 -vf fps=25 -pix_fmt yuv420p out_easy_mode.mp4")

  #clean any images
  os.system("rm .image_*.png")

main()
