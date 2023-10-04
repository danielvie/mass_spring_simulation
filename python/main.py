import numpy as np
import matplotlib.pyplot as plt

# System Parameters
M1 = 1.0  # Mass of Block 1
M2 = 1.0  # Mass of Block 2
k = 1.0  # Spring constant
c = 0.1  # Damping constant

# External Force
def F1(t):
    A = 1.0;
    omega = 1.0;
    return A * np.sin(omega * t)*0

# Equations of motion
def system_dynamics(t, states):
    x1, x2, v1, v2 = states
    delta = x2 - x1
    a1 = (-k*x1 - c*v1 + k*delta + c*(v2 - v1) + F1(t)) / M1
    a2 = (-k*delta - c*(v2 - v1)) / M2
    return [v1, v2, a1, a2]

# 4th Order Runge-Kutta Integration
def runge_kutta(t, states, dt):
    k1 = system_dynamics(t, states)
    k2 = system_dynamics(t + 0.5*dt, [states[i] + 0.5*dt*k1[i] for i in range(4)])
    k3 = system_dynamics(t + 0.5*dt, [states[i] + 0.5*dt*k2[i] for i in range(4)])
    k4 = system_dynamics(t + dt, [states[i] + dt*k3[i] for i in range(4)])
    
    new_states = [states[i] + dt/6.0 * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]) for i in range(4)]
    return new_states

# Initial Conditions
x1 = 0  # Initial displacement of M1
x2 = 0.5  # Initial displacement of M2
v1 = 0  # Initial velocity of M1
v2 = 0  # Initial velocity of M2

dt = 0.01  # Time step
t_end = 10  # Simulation time

t_values = np.arange(0, t_end, dt)
x1_values = []
x2_values = []

states = [x1, x2, v1, v2]

for t in t_values:
    x1_values.append(states[0])
    x2_values.append(states[1])

    states = runge_kutta(t, states, dt)

# Plot the results
plt.plot(t_values, x1_values, label="M1")
plt.plot(t_values, x2_values, label="M2")
plt.xlabel('Time (s)')
plt.ylabel('Position (m)')
plt.legend()
plt.title('Block Movements over Time with External Force on M1')
plt.show()