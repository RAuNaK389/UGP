import numpy as np
import matplotlib.pyplot as plt
import math
ny = 256
nx = 256
n_orient = 2
n_files = 11
time_step = 20

data = np.empty((n_files, ny * nx), dtype=np.float32)  # concentration
# data_h = np.empty((n_files, n_orient * ny * nx), dtype=np.float32)  # eta fields
values = np.empty((n_files, ny * nx), dtype=np.float32)  # product of eta_i

# Load data from files
for i in range(n_files):
    filename_c = f"c_new_{i * time_step}.bin"
    data[i] = np.fromfile(filename_c, dtype=np.float32)
    # filename_h = f"h_new_{i * time_step}.bin"
    # data_h[i] = np.fromfile(filename_h, dtype=np.float32)

# Compute product of eta_i at each grid point
# for i in range(n_files):
#     for j in range(ny * nx):
#         sum = 0
#         for k in range(n_orient):
#             sum += data_h[i, k * ny * nx + j]*data_h[i, k * ny * nx + j]
#         values[i, j] = sum

n_cols = math.ceil(math.sqrt(n_files))  # Round up square root
n_rows = math.ceil(n_files / n_cols)


fig, axes = plt.subplots(n_rows, n_cols, figsize=(4 * n_cols, 3.5 * n_rows))
axes = axes.flatten()

for i in range(n_files):
    comp = data[i].reshape((ny, nx))

    # orient = values[i].reshape((ny, nx))

    ax = axes[i]
    img = ax.imshow(comp, cmap='RdBu_r', origin='lower')
    # im = ax.imshow(orient, cmap='hot', origin='lower', alpha=0.4)  # adjust alpha to taste
 
    ax.set_title(f"t = {i * time_step}")
    ax.axis('off')

# Delete unused axes if n_files < total subplots
for idx in range(n_files, len(axes)):
    fig.delaxes(axes[idx])

# Shared colorbar
cbar_ax = fig.add_axes([0.72,0.11,0.2,0.015 ])  # Adjust as needed
cbar = fig.colorbar(img , cax=cbar_ax,orientation='horizontal')
cbar.set_label("Composition")

plt.suptitle("Microstructure Evolution with Grain Boundary Overlay", fontsize=16)
plt.tight_layout(rect=[0, 0, 0.95, 0.96])  # Optional
plt.show()