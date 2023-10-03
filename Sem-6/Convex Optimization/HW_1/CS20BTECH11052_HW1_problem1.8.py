import numpy as np
import matplotlib.pyplot as plt
import math

# Defining the activation function g(x)
def g(x):
    return (math.e**x)/(1 + math.e**x)


# Plot the activation function g(x)
x = np.linspace(-10, 10, 100)
y = g(x)
plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('g(x)')
plt.title('Activation Function')
plt.savefig('CS20BTECH11052_HW1_problem1.8.png')


# Generating the random data
d, N = 4, 100
X = np.random.rand(N, d)
y = []
for j in range(N):
    if 2 * X[j][0] - 3 * X[j][1] + X[j][3] >= 0 :
        y.append(1)
    else:
        y.append(0)
        

# f(w) = || g(X^T w) - y ||^2. This indicates that f_grad(w) = 2 * X * (g(X^T w) - y)
def f_grad(W, X, Y):
    w, x, y = np.asarray(W), np.asarray(X), np.asarray(Y)
    t = 2 * (w.dot(x) - y) * np.exp(w.dot(x)) / pow(1 + np.exp(w.dot(x)), 2)
    return t * x
    

# Running the gradient descent algorithm for 100 steps and finding the optimal w
w = np.array([1, 1, 1, 1])
N = 100
delta = 0.05
for i in range(N):
    w = w - delta * f_grad(w, X[i], y[i])

print("The optimal w is: ", w)