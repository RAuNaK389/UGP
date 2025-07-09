import numpy as np
import matplotlib.pyplot as plt 

data=[]
time =[]
nx =200
ny=1
size=(ny,nx)
nf = 11 #Number of files 

# reading Initial composition
time.append(0)
c=np.empty(size,dtype=float)
f = open("Initial composition.txt","r")
i=0
for line in f:
    c= np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
data.append(c)
f.close()

for i in range(1,nf):
    time.append(i*100)
    composition=np.empty(size,dtype=float)
    filename = "Composition at t= "+ str(i*100) + ".txt"
    f=open(filename,"r")
    for line in f:
        # composition=np.empty(size,dtype=float)
        composition=np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
    f.close()
    data.append(composition)

n=2
op_data = np.empty((nf, nx, n), dtype=np.float64)  # Or np.empty(...) for uninitialized

# data=data.reshape((11,ny,nx,n))
# initial data
values= np.fromfile('Initial order-parm.bin', dtype=np.float64)
values = values.reshape((nx,n))
op_data[0]  = values
# time.append(0)

for i in range(1,nf):
    file_name = "Order-param at t= "+str(i*100)+".bin"
    values= np.fromfile(file_name, dtype=np.float64)
    values = values.reshape((nx,n))
    op_data[i]  = values
    # time.append(i*100)


x_values=np.arange(nx)
fig,axes = plt.subplots(3,4,figsize = (14,8))
axes = axes.flatten()
i=0
# axes.set_ylabel("Order-Param")
# axes.set_xlabel("distance")
for ax in axes:
    if(i<11):
        # ax.set_ylabel("Order-Param")
        ax.set_xlabel("distance")

        name = "t= " + str(time[i])
        l1,=ax.plot(x_values,data[i].T,label="Composition")
        l2,=ax.plot(x_values,op_data[i].T[0],label="n1")
        l3,=ax.plot(x_values,op_data[i].T[1],label="n2")
        ax.set_title(name)
        i+=1
        # ax.legend()
handles = [l1, l2, l3]
labels = [h.get_label() for h in handles]
fig.legend(handles, labels, loc='lower center', ncol=3, fontsize=10)
plt.tight_layout(rect=[0, 0.05, 1, 1])
plt.show()

# x_values.resize(ny,nx)
# #print (x_values.shape)
# fig,ax = plt.subplots()
# ax.set_ylabel("composition")
# ax.set_xlabel("distance")
# for i in range(0,nf):
#     name = "t= " + str(time[i])
#     ax.plot(x_values,data[i].T,label=name)
# ax.legend()

print("Done")



