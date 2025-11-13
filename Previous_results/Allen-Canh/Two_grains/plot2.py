import numpy as np
import matplotlib.pyplot as plt

nx=200
ny=200
n=2
data= np.fromfile('Microstructure at t= 500.bin', dtype=np.float64)
data = data.reshape((ny,nx,n))
x=np.arange(0,nx)