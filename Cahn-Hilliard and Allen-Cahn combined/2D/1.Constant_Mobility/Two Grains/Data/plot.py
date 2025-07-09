# import numpy as np
import numpy as np
import matplotlib.pyplot as plt
import math

# filename = "Composition at t=60.bin"  # try a later time step
# data_ = np.fromfile(filename, dtype=np.float64)
# print("Min:", np.min(data_), "Max:", np.max(data_), "Mean:", np.mean(data_))


# Grid size (must match your simulation)
ny = 256
nx = 512
n_files =11
data = np.empty((n_files,ny*nx),dtype=np.float64)
for i in range(0,n_files):
    filename = "c_"+str(i*100) +".bin"
    data[i]= np.fromfile(filename, dtype=np.float64)

# Set subplot grid size
n_cols = math.ceil(np.sqrt(n_files))
n_rows = math.ceil(n_files / n_cols)

# Create figure
fig, axes = plt.subplots(n_rows, n_cols, figsize=(4 * n_cols, 3.5 * n_rows))
axes = axes.flatten()

# Plot each composition snapshot
for i in range(0,n_files):
    comp = data[i].reshape((ny, nx))

    # Plot
    ax = axes[i]
    im = ax.imshow(comp, cmap='viridis', origin='lower', extent=[0, nx, 0, ny])
    timestep = i*100
    ax.set_title(f"t = {timestep}")
    ax.axis('off')

# Hide unused subplots
for idx in range(n_files, len(axes)):
    fig.delaxes(axes[idx])

# Add shared colorbar
# cbar = fig.colorbar(im, ax=axes.tolist(), shrink=0.6, location='right')
# cbar.set_label("Composition")
# Shared colorbar
cbar_ax = fig.add_axes([0.72,0.11,0.2,0.015 ])  # Adjust as needed
cbar = fig.colorbar(im , cax=cbar_ax,orientation='horizontal')
cbar.set_label("Composition")

# Title and layout
plt.suptitle("Composition Profiles at Different Time Steps", fontsize=16)
plt.tight_layout(rect=[0, 0, 0.95, 0.96])
plt.show()
