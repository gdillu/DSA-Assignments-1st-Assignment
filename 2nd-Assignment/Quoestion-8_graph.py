import matplotlib.pyplot as plt

# Matrix sizes
sizes = [2, 4, 8, 16, 32, 64, 128, 256]

# Times in milliseconds for Standard and Strassen multiplication
standard_times = [0.001, 0.002, 0.006, 0.075, 0.422, 2.758, 22.542, 185.072]
strassen_times = [0.02, 0.122, 0.602, 6.944, 32.845, 217.303, 1539.35, 10637.7]

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(sizes, standard_times, marker='o', label='Standard Multiplication')
plt.plot(sizes, strassen_times, marker='s', label='Strassen\'s Multiplication')

# Adding titles and labels
plt.title('Matrix Multiplication Time Comparison')
plt.xlabel('Matrix Size (n x n)')
plt.ylabel('Time (ms)')
plt.yscale('log')  # Use log scale for better visibility of differences
plt.xticks(sizes)  # Set x-ticks to the matrix sizes
plt.legend()
plt.grid(True)

# Show the plot
plt.tight_layout()
plt.show()
