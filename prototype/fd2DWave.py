import numpy as np 
import matplotlib.pyplot as plt

def main():
  '''
  fd1DWave prototypes a finite difference wave equation simulator

  A ricker wavelet is injected onto a string and the wave equation
  is calculated using 2nd order time and space derivatives 

  A dataset is written with the pressure waves recorded every N frames
  '''

  #physical parameters 
  cHigh = 3000.0   # speed of wave
  n = 1024     # number of points
  L = 600      # string length
  dx = float(L)/float(n)     # increment spacing
  tL = 0.7     # Length of simulation 
  dt = dx/cHigh    # time increment
  tn = tL/dt

  dy = dx 
  
  #initialize time and space arrays
  t = np.arange(0,tL, dt)
  t = t.reshape(len(t),1)
  x = np.arange(0, L, dx).reshape(n,1)
  y = np.arange(0, L, dx).reshape(1,n)
  

  c = np.zeros(n*n).reshape(n,n)
  c[:int(3*n/4),:] = 1500
  c[int(3*n/4):,:] = 2000

  #initialize pressure values
  p0 =  np.zeros(n*n).reshape(n,n)
  p1 =  np.zeros(n*n).reshape(n,n)
  p2 = np.zeros(n*n).reshape(n,n)
  spaceDerive2x =  np.zeros(n*n).reshape(n,n)
  spaceDerive2y = np.zeros(n*n).reshape(n,n)
  
  #Ricker wavelet for injection as a function of time 
  fc = 20
  t0 = 1.5/fc
  tau = np.pi*(t-t0)*fc
  inputWave = np.multiply( np.exp(-np.square(tau)), (1 - 2*np.square(tau)) )
  
  # frames inc
  N = 8
#
#  # Write the datafile headers
#  with open("data.dat", 'w') as fh:
#    fh.write("{}\n".format(n))
#    fh.write("{}\n".format(dx))
#    fh.write("{}\n".format(L))
#  
#  with open("data.dat", 'ab') as fh:
  frame_number = 0
  for j in range(int(tn)):
    #inject source
    p1[int(n/3),int(n/3)]= p1[int(n/3),int(n/3)] + inputWave[j]*dt*dt/dx*c[int(n/3),int(n/3)]*2
  
    #order 2 FD space derivative X
    for k in range(n):
      spaceDerive2x[1:n-1,k] = (p1[0:n-2,k] - 2*p1[1:n-1,k] + p1[2:n,k])/dx/dx

    ##order 2 FD space derivative y
    for k in range(n):
      spaceDerive2y[k,1:n-1] = (p1[k,0:n-2] - 2*p1[k,1:n-1] + p1[k,2:n])/dx/dx

    ###order 2 FD time derivative
    csquared = np.multiply(c,c)
    p2 = dt*dt*np.multiply(csquared,(spaceDerive2x + spaceDerive2y)) + 2*p1 - p0
  
    ##Set boundary condition at X=L so that wave does not reflect from there
    p2[:,-1] = -(p1[:,-1] - p1[:,-2])*c[:,-1]*dt/dx + p1[:,-1] 
    p2[:, 0] = -(p1[:,0] - p1[:,1])*c[:,0]*dt/dx + p1[:,0] 
    p2[-1,:] = -(p1[-1:,] - p1[-2,:])*c[-1,:]*dt/dx + p1[-1,:] 
  
    ##swap the pressure waves to increment to the next time
    p0 = p1
    p1 = p2
    
    if (j%20 == 0):
      frame_number = frame_number + 1
      plt.imshow(p1, cmap='hot', interpolation='nearest', vmin=-.00005, vmax=.00005)
      plt.savefig("image_{:03d}.png".format(frame_number))
      plt.clf()
#    
#      #write ever N frames to dataset
#      if(j%N == 0):
#        np.savetxt(fh, p2, delimiter=",")
   


main()
