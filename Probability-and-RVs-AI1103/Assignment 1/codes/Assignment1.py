#Code released under GNU/GPL
#Taha Adeel Mohammed
#March 17,2021

#Generating points on the time axis uniformly within 2 minutes
#Finding the probability of those points  lying within the first 0,5 minute
import matplotlib.pyplot as plt
import numpy as np

#if using termux
#import subprocess
#import shlex
#end if

#Sample size
simlen = int(2e2)

#Sample space
S = 2
#Event
E = 0.5

#Generating points uniformly in the sample space
x = np.random.uniform(low=0, high=2, size=simlen)
x.sort()

for i in range(simlen):
    if x[i] <= 0.5:
      continue
    else:
      count = i #No. of favourable outcomes
      break

prob_sim = count / simlen
prob_theory = E/S

print("Simulated probablity: ", prob_sim, "\nTheoretical probablity: ", prob_theory)

# Setup a plot such that only the bottom spine is shown
def setup(ax):
    ax.yaxis.set_major_locator(ticker.NullLocator())
    ax.spines['top'].set_color('none')
    ax.xaxis.set_ticks_position('bottom')
    ax.tick_params(which='major', width=1.00)
    ax.tick_params(which='major', length=12)
    ax.tick_params(which='minor', width=0.75)
    ax.tick_params(which='minor', length=7.5)
    ax.set_xlim(0, 2)
    ax.set_ylim(-1, 2)
    ax.patch.set_alpha(0.0)

plt.figure()

#plotting the simulation
ax = plt.subplot(3, 1, 1)
ax.plot(x, [0]*simlen, 'bo', markersize=10, mfc='None', mew=2, alpha=0.4, 
        linewidth=1.5, label="Simulation")
plt.axvline(x=0.01, color='r', ymax=0.7, linestyle='--')
plt.axvline(x=0.5, color='r', ymax=0.7, linestyle='--')
plt.xlabel("Time after starting in minutes")
plt.legend()
setup(ax)
ax.xaxis.set_major_locator(ticker.MultipleLocator(0.5))
ax.xaxis.set_minor_locator(ticker.MultipleLocator(0.1))
plt.gcf().text(0.1, 0.47,"Probablity derived from this simulation is {}".format(prob_sim) )

#if using termux
    #plt.savefig('./Figures/musical_chairs.pdf')
    #plt.savefig('./Figures/musical_chairs.png')
    #subprocess.run(shlex.split("termux-open ./Figures/musical_chairs.pdf"))
#else
    #plt.show()