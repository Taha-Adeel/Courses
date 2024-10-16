import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import uniform

uniform_data=np.linspace(0,2,num=10000)
px=uniform.pdf(uniform_data, loc=0, scale =2)
uniform_data=np.append(uniform_data, np.linspace(2,3,num=1000))
px=np.append(px, [0]*1000)
uniform_data=np.append(np.linspace(-0.1,0,num=1000), uniform_data)
px=np.append([0]*1000, px)
plot1=plt.figure
plt.plot(uniform_data, px)

plt.title("probablity density function of x")
plt.xlabel("Time after starting in minutes(x)")
plt.ylabel("$p_{X}(x)$")
plt.xlim(-0.1, 3)
plt.ylim(0, 1)
