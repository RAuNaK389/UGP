import numpy as np
import matplotlib.pyplot as plt

# Load the composition data (assuming a .txt file with space-separated values)
initial_composition = np.loadtxt("Initial Composition.txt")  # Update with your file path
final_composition = np.loadtxt("solution at t= 1000.txt")

# Plotting
fig, axes = plt.subplots(1, 2, figsize=(12, 5))

# Initial Composition Plot
im1 = axes[0].imshow(initial_composition, cmap='viridis', origin='lower')
axes[0].set_title("Initial Composition")
fig.colorbar(im1, ax=axes[0])

# Final Composition Plot
im2 = axes[1].imshow(final_composition, cmap='viridis', origin='lower')
axes[1].set_title("Final Composition")
fig.colorbar(im2, ax=axes[1])

# Show the plots
plt.tight_layout()
plt.show()