import numpy as np
import matplotlib.pyplot as plt 

data=[]
time =[]
nx =100
ny=100
size=(ny,nx)
n = 10 #Number of files 

# reading data from the files 
c=np.empty((100,1),dtype=float)
f=open("1D Explicit_t= 200.txt","r")
for line in f:
    c = np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
data.append(c)

# c=np.empty((100,1),dtype=float)
f=open("1D Implicit_t= 200.txt","r")
for line in f:
    c = np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
data.append(c)


c1=np.empty(size,dtype=float)
f = open("2D Explicit_t= 200.txt","r")
i=0
for line in f:
    c1[i] = np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
    i+=1
data.append(c1[49])
f.close()

# c1=np.empty(size,dtype=float)
f = open("2D Implicit_t= 200.txt","r")
i=0
for line in f:
    c1[i] = np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
    i+=1
data.append(c1[49])
f.close()

f=open("1D Explicit_varD_t=200.txt","r")
for line in f:
    c = np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
data.append(c)

x_values=np.arange(100)

fig,ax = plt.subplots()
ax.set_ylabel("composition")
ax.set_xlabel("distance")

ax.plot(x_values,data[0].T,label="1D Explicit t=200")
ax.plot(x_values,data[4].T,label="1D Explicit_varD t=200",linestyle='dashed')
# ax.plot(x_values,data[2],label="2D Explicit t=200",)
# ax.plot(x_values,data[3],'r+',label="2D Implicit t=200",)

# for i in range(1,2):
#     name = "t= " + str(time[i])
#     ax.plot(x_values,data[i][49],label=name)
ax.legend()
plt.show()
# print(data[1])
# reading Initial composition
# time.append(0)
# c=np.empty(size,dtype=float)
# f = open("Initial Composition.txt","r")
# i=0
# for line in f:
#     c[i] = np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
#     i+=1
# data.append(c)
# f.close()

# for i in range(1,n+1):
#     time.append(i*100)
#     composition=np.empty(size,dtype=float)
#     filename = "solution at t= "+ str(i*100) + ".txt"
#     f=open(filename,"r")
#     j=0
#     for line in f:
#         # composition=np.empty(size,dtype=float)
#         composition[j]=np.array([list(map((lambda x : float(x)),line.split(" ")[:-1]))])
#         j+=1
#     f.close()
#     data.append(composition)


