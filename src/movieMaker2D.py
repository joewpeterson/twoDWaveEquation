import numpy as np 
import matplotlib.pyplot as plt
import glob
import os

def main():
    datFiles = glob.glob("*.dat");

   # for entry in datFiles:
   #     p1 = np.loadtxt(entry)
   #     p1 = p1.reshape(1024,1024)

   #     imgName = entry.replace("data", "image").replace(".dat", ".png")
   #     plt.imshow(p1, cmap='hot', interpolation='nearest', vmin=-.00005, vmax=.00005)
   #     plt.savefig(imgName)
   #     plt.clf()

    os.system("ffmpeg -i image_%03d.png -c:v libx264 -vf fps=25 -pix_fmt yuv420p out_easy_mode.mp4")


#if (j%20 == 0):
#      frame_number = frame_number + 1
#      plt.imshow(p1, cmap='hot', interpolation='nearest', vmin=-.00005, vmax=.00005)
#      plt.savefig("image_{:03d}.png".format(frame_number))
#      plt.clf()

main()
