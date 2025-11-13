import numpy as np
import matplotlib.pyplot as plt

nx=200
ny=200
n=36
nf = 20   # Total number of data files to be read

time=[]
data = np.empty((nf, ny, nx), dtype=np.float64)  # Or np.empty(...) for uninitialized

# data=data.reshape((11,ny,nx,n))
# initial data
values= np.fromfile('Initial Microstructure.bin', dtype=np.float64)
values = values.reshape((ny,nx))
data[0]  = values
time.append(0)

for i in range(1,nf):
    file_name = "Microstructure at t= "+str(i*50)+".bin"
    values= np.fromfile(file_name, dtype=np.float64)
    values = values.reshape((ny,nx))
    data[i]  = values
    time.append(i*50)



# print(microstructure[10][0][0])
fig, axes = plt.subplots(2, 5)
axes = axes.flatten()  # Flatten 2D array of axes to a 1D list

i = 0  # starting index
for ax in axes:
    im = ax.imshow(data[i], cmap='hot', origin='lower')
    ax.set_title(f"Time = {time[i]}")
    i += 2

# # Add a colorbar to the figure
# fig.colorbar(im, ax=axes.ravel().tolist(), shrink=0.8, label='Final Microstructure')
# fig.suptitle("Microstructure Evolution", fontsize=16)
plt.tight_layout()
plt.show()