#Code released under GNU/GPL
#Taha Adeel Mohammed
#May 26,2021

import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson

#Sample size
simlen = int(5e6)

X = poisson.rvs(2, size = simlen )
Y = poisson.rvs(10, size = simlen )
pr_X_is_0 = np.count_nonzero(X==0)/simlen
pr_Y_is_12 = np.count_nonzero(Y==12)/simlen

Z = X + Y
pr_X_plus_Y_is_12 = np.count_nonzero(Z==12)/simlen

simulated_prob = pr_X_is_0 * pr_Y_is_12/ pr_X_plus_Y_is_12
theoretical_prob = (5/6)**12
print("Pr(X=0|X+Y=12) through simulation is ",simulated_prob)
print("Pr(X=0|X+Y=12) through theory is ",theoretical_prob) 
