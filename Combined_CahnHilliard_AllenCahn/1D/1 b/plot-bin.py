import numpy as np
import matplotlib.pyplot as plt

nx=200
n=2
nf = 11   # Total number of data files to be read

time=[]
data = np.empty((nf, nx, n), dtype=np.float64)  # Or np.empty(...) for uninitialized

# data=data.reshape((11,ny,nx,n))
# initial data
values= np.fromfile('Initial order-parm.bin', dtype=np.float64)
values = values.reshape((nx,n))
data[0]  = values
time.append(0)

for i in range(1,nf):
    file_name = "Order-param at t= "+str(i*100)+".bin"
    values= np.fromfile(file_name, dtype=np.float64)
    values = values.reshape((nx,n))
    data[i]  = values
    time.append(i*100)



x_values=np.arange(nx)
# x_values.resize(ny,nx)
# #print (x_values.shape)
# fig,axes = plt.subplots(1,2)
# a=0
# for ax in axes:
#     ax.set_ylabel("Order-Param")
#     ax.set_xlabel("distance")
# # for i in range(0,n+1):
#     name = "t= " + str(time[a])
#     ax.plot(x_values,data[a].T[0],label="n1")
#     ax.plot(x_values,data[a].T[1],label="n2")
#     ax.set_title(name)
#     a=10
#     ax.legend()

fig,ax = plt.subplots()

ax.set_ylabel("Order-Param")
ax.set_xlabel("distance")
for i in range(0,n+1):
    name = "t= " + str(time[i])
    ax.plot(x_values,data[i].T[0],label="n1")
    ax.plot(x_values,data[i].T[1],label="n2")
ax.legend()

# print(microstructure[10][0][0])
# fig, axes = plt.subplots(2, 5)
# axes = axes.flatten()  # Flatten 2D array of axes to a 1D list

# i = 0  # starting index
# for ax in axes:
#     im = ax.imshow(data[i], cmap='hot', origin='lower')
#     ax.set_title(f"Time = {time[i]}")
#     i += 2

# # Add a colorbar to the figure
# fig.colorbar(im, ax=axes.ravel().tolist(), shrink=0.8, label='Final Microstructure')
# fig.suptitle("Microstructure Evolution", fontsize=16)
plt.tight_layout()
plt.show()