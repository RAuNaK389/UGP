import numpy as np
import matplotlib.pyplot as plt 

data=[]
time =[]
nx =200
ny=50
size=(ny,nx)
n = 10 #Number of files 

# reading Initial composition
time.append(0)
c=np.empty(size,dtype=float)
f = open("Initial Composition.txt","r")
i=0
for line in f:
    c[i] = np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
    i+=1
data.append(c)
f.close()

for i in range(1,n+1):
    time.append(i*100)
    composition=np.empty(size,dtype=float)
    filename = "solution at t= "+ str(i*100) + ".txt"
    f=open(filename,"r")
    j=0
    for line in f:
        # composition=np.empty(size,dtype=float)
        composition[j]=np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
        j+=1
    f.close()
    data.append(composition)

x_values=np.arange(nx)

fig,ax = plt.subplots()
ax.set_ylabel("composition")
ax.set_xlabel("distance")
for i in range(0,11):
    name = "t= " + str(time[i])
    ax.plot(x_values,data[i][24],label=name)
ax.legend()
plt.show()
print("Done")
