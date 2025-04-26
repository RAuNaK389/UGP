import numpy as np
import matplotlib.pyplot as plt

nx=200
ny=200
n=2
nf = 2   # Total number of data files to be read

time=[]
data = np.empty((nf, ny, nx,n), dtype=np.float64)  # Or np.empty(...) for uninitialized

# data=data.reshape((11,ny,nx,n))
# initial data
values= np.fromfile('Initial Composition.bin', dtype=np.float64)
values = values.reshape((ny,nx,n))
data[0]  = values
time.append(0)


values= np.fromfile('Solution at t= 500.bin', dtype=np.float64)
values = values.reshape((ny,nx,n))
data[1]  = values
time.append(500)
# for i in range(1,nf):
#     file_name = "Solution at t= "+str(i*50)+".bin"
#     values= np.fromfile(file_name, dtype=np.float64)
#     values = values.reshape((ny,nx))
#     data[i]  = values
#     time.append(i*50)



# # print(microstructure[10][0][0])
# fig, axes = plt.subplots(2, 1)
# axes = axes.flatten()  # Flatten 2D array of axes to a 1D list

# i = 0  # starting index
# for ax in axes:
#     im = ax.imshow(data[i], cmap='hot', origin='lower')
#     ax.set_title(f"Time = {time[i]}")
#     i =10

# # # Add a colorbar to the figure
# # fig.colorbar(im, ax=axes.ravel().tolist(), shrink=0.8, label='Final Microstructure')
# # fig.suptitle("Microstructure Evolution", fontsize=16)
# plt.tight_layout()
# plt.show()
x=np.arange(0,nx)
x1=[]
x2=[]
x3=[]
x4=[]
for i in range(0,nx):
    x1.append(data[0][99][i][0])
    x2.append(data[0][99][i][1])
    x3.append(data[1][99][i][0])
    x4.append(data[1][99][i][1])

y=np.array([x1,x2,x3,x4])
fig,axes=plt.subplots(1,2)
i=0
for j, ax in enumerate(axes):
    ax.plot(x,y[i],label="n1")
    ax.plot(x,y[i+1],label="n2")
    i=2
    ax.set_title("T="+str(time[j]))

plt.legend()
plt.show()