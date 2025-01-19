import numpy as np
import matplotlib.pyplot as plt 

data=[]
time =[]
nx =100
ny=1
size=(ny,nx)
n = 10 #Number of files 

# reading Initial composition
time.append(0)
c=np.empty(size,dtype=float)
f = open("Initial Composition.txt","r")
i=0
for line in f:
    c= np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
data.append(c)
f.close()

for i in range(1,n+1):
    time.append(i*100)
    composition=np.empty(size,dtype=float)
    filename = "solution at t= "+ str(i*100) + ".txt"
    f=open(filename,"r")
    for line in f:
        # composition=np.empty(size,dtype=float)
        composition=np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
    f.close()
    data.append(composition)



x_values=np.arange(100)
# x_values.resize(ny,nx)
# #print (x_values.shape)
fig,ax = plt.subplots()
ax.set_ylabel("composition")
ax.set_xlabel("distance")
for i in range(0,n+1):
    name = "t= " + str(time[i])
    ax.plot(x_values,data[i].T,label=name)
ax.legend()
plt.show()
print("Done")



