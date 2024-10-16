#Code released under GNU/GPL
#Taha Adeel Mohammed
#March 30,2021

import matplotlib.pyplot as plt
import numpy as np
import math


#Sample size
simlen = int(1e6)

#Generating points uniformly in the sample space
x = np.random.uniform(low=0, high=2, size=simlen)
Z_n=- sum(np.log(x))/simlen

print("The value of Zn as n tends to infinity \n Simulation:",Z_n,"\n Analysis: ", 1-np.log(2))
