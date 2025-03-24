import numpy as np
import matplotlib.pyplot as plt

# Load the composition data (assuming a .txt file with space-separated values)
initial_composition = np.loadtxt("Initial Composition.txt")  # Update with your file path
final_composition = np.loadtxt("solution at t= 1000.txt")

# Plotting
fig, axes = plt.subplots(figsize=(12, 5))
axes.set_ylabel("composition")
axes.set_xlabel("distance")

# Initial Composition Plot
axes.plot(initial_composition,label = "Initial Composition")
axes.plot(final_composition,label="Final Composition")


# Show the plots
axes.legend()
plt.tight_layout()
plt.show()




