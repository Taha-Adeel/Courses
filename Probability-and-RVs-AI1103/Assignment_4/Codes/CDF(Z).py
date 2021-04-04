import numpy as np
from scipy.stats import uniform
from matplotlib import pyplot as plt

def cdf(a):
    x, counts = np.unique(a, return_counts=True)
    cusum = np.cumsum(counts)
    return x, cusum / cusum[-1]

X = uniform.rvs(loc=0, scale=2,size=1000)
Z=-np.log(2-X)
x, y = cdf(Z)
x = np.insert(x, 0, x[0])
y = np.insert(y, 0, 0.)
plt.plot(x, y,'o',label='Simulation')
plt.grid(True)
z=np.linspace(-np.log(2),6,100)
plt.plot(z,1-0.5*np.exp(-z),label='Analysis')
plt.xlim(-1,6)
ax=plt.gca()
ax.set_xticks([-np.log(2),0,1,2,3,4,5,6])
ax.set_xticklabels(["-ln(2)",0,1,2,3,4,5,6])
plt.title("CDF of random variable $Z$")
plt.xlabel("$z$")
plt.ylabel("$F_Z(z)$")
plt.legend(loc='best')
#plt.show()
