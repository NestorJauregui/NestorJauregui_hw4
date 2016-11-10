import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

n_times = 200
data_temp = np.loadtxt('data.txt')
n_points = len(data_temp)/n_times
data = data_temp.reshape((n_times, n_points))
x = np.linspace(0.0, 100.0, n_points)

fig, ax = plt.subplots()
ax.plot(x, data[0][:], '--', alpha=0.3)
line, = ax.plot([], [])

ax.set_xlim(0.0, 100.0)
ax.set_ylim(-1.5, 1.5)

def update(time):
    line.set_data(x, data[time][:])
    return line,

image = FuncAnimation(fig, update, np.arange(n_times))
image.save('cuerda.gif', writer='imagemagick')
