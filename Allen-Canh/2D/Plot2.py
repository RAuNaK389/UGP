import numpy as np
import matplotlib.pyplot as plt 

data=[]
time =[]
nx =200
ny=200
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
data.append(c[99])
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
    data.append(composition[99])
radius=[]
for i in range(0,11):
    S = data[i]
    for j in range(0,nx):
        if S[j]>=0.5:
            x = ((0.5-S[j-1])/(S[j]-S[j-1]))+(j-1)
            r=100-x
            radius.append(r)
            break

print(time)
print(radius)
# fig , ax = plt.subplots()
# ax.set_xlabel("Time")
# ax.set_ylabel("R^2")
# ax.plot(time,radius)
# # Show the plots
# plt.tight_layout()
# plt.show()

