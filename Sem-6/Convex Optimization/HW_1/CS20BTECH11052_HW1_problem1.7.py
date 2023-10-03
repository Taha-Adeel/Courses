# Gradient Descent
import numpy as np

T = 1000
delta = 0.02

def gradient_descent(x0, f, f_grad):
	x = x0
	for t in range(T):
		x = x - delta * f_grad(x)
	return x, f(x)

# Q1
A = np.array([
	[2, -1, -1], 
	[-1, 2, 0], 
	[-1, 0, 1]
])
b = np.array([1])

def f_q1(x):
	return x.T @ A @ x + b

def f_grad_q1(x):
	return (A + A.T) @ x

x0 = np.random.rand(3)
x, f = gradient_descent(x0, f_q1, f_grad_q1)
print("Q1: x = {}, f(x) = {}".format(x, f))


# Q2
A = np.array([
	[1, 2],
	[2, 4],
	[3, 1]
])
b = np.array([1, 3, 1])

def f_q2(x):
	return np.linalg.norm(A @ x - b) ** 2

def f_grad_q2(x):
	return 2 * A.T @ (A @ x - b)

x0 = np.random.rand(2)
x, f = gradient_descent(x0, f_q2, f_grad_q2)
print("Q2: x = {}, f(x) = {}".format(x, f))


# Q3
A = np.array([
	[1, 2, 1],
	[2, 4, 2],
	[3, 1, 9],
	[4, 1, 0],
	[2, 1, 4]
])
b = np.array([1, 3, 1, 0, 9])

def f_q3(x):
	return np.linalg.norm(A @ x - b) ** 2

def f_grad_q3(x):
	return 2 * A.T @ (A @ x - b)

x0 = np.random.rand(3)
delta = 0.002 # We reduce delta to get a better solution 
x, f = gradient_descent(x0, f_q3, f_grad_q3)
print("Q3: x = {}, f(x) = {}".format(x, f))