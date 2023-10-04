import matplotlib.pyplot as plt

# Initialize empty lists to store the data
times = []
x1_values = []
x2_values = []
v1_values = []
v2_values = []

# Read and parse the log file
with open("states.log", "r") as file:
    for line in file:
        time, x1, x2, v1, v2 = map(float, line.strip().split(","))
        times.append(time)
        x1_values.append(x1)
        x2_values.append(x2)
        v1_values.append(v1)
        v2_values.append(v2)

# Plot the results
plt.figure(figsize=(10, 8))

plt.subplot(2, 1, 1)
plt.plot(times, x1_values, label="x1 (Position of M1)")
plt.plot(times, x2_values, label="x2 (Position of M2)")
plt.xlabel("Time")
plt.ylabel("Position")
plt.legend()
plt.title("Positions vs Time")

plt.subplot(2, 1, 2)
plt.plot(times, v1_values, label="v1 (Velocity of M1)")
plt.plot(times, v2_values, label="v2 (Velocity of M2)")
plt.xlabel("Time")
plt.ylabel("Velocity")
plt.legend()
plt.title("Velocities vs Time")

plt.tight_layout()
plt.show()
