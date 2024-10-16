#Code released under GNU/GPL
#Taha Adeel Mohammed
#May 26,2021

import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson

#Sample size
simlen = int(5e6)

#Poisson parameters
mu_1 = 2
mu_2 = 10

X = poisson.rvs(mu_1, size = simlen )
Y = poisson.rvs(mu_2, size = simlen )
pr_X_is_0 = np.count_nonzero(X==0)/simlen
pr_Y_is_12 = np.count_nonzero(Y==12)/simlen

Z1 = X + Y
pr_X_plus_Y_is_12 = np.count_nonzero(Z1==12)/simlen

simulated_prob = pr_X_is_0 * pr_Y_is_12/ pr_X_plus_Y_is_12
theoretical_prob = (5/6)**12
print("Pr(X=0|X+Y=12) through simulation is ",simulated_prob)
print("Pr(X=0|X+Y=12) through theory is ",theoretical_prob)

#Simulation
Z2 = X - Y
z2, sim_freq = np.unique(Z2, return_counts=True)
sim_prob = sim_freq / simlen

#Theoretical
k_lower_lim = -20
k_upper_lim = 5
upper_lim = 200 #Calculating first $(upper_lim) terms of infinite summation
th_prob = []
for k in range(k_lower_lim, k_upper_lim+1):
  summation = 0
  for i in range(max(0, -k), upper_lim+1):
    num = ((mu_1**(k+i))*(mu_2**(i)))/(math.factorial(i) * math.factorial(k+i))
    summation += num
  th_prob.append(math.exp(-(mu_1 + mu_2)) * summation)

#plotting X-Y
plt.stem(z2, sim_prob, markerfmt='o', use_line_collection=True, label="Simulation")
plt.stem(range(k_lower_lim, k_upper_lim+1), th_prob, markerfmt='o', use_line_collection=True, label="Analysis")
plt.xlim(k_lower_lim, k_upper_lim)
plt.ylim(0, 0.13)
plt.title("PMF of $X-Y$")
plt.xlabel('$k$')
plt.ylabel('Pr$(X - Y = k)$')
plt.legend()
plt.grid()
plt.show()

print("Mean of X-Y through simulation is",sum(Z2)/simlen, "and is -8 through analysis")
