# Write a function to perform Gram-Schmidt orthonormalization. The input to the function should be
# an m x n numpy array A, with A[i, :] denoting the ith vector. The output should be a r x n numpy array,
# where r is the dimension of the span of the input.

import numpy as np

# Returns the dot product of two vectors
def inner_product(v1, v2):
	ans = 0
	for i in range(min(v1.shape[0], v2.shape[0])):
		ans += v1[i] * v2[i]
	return ans

# Normalizes a vector
def normalize(v):
	norm = inner_product(v, v) ** 0.5
	return v / norm

# Returns the row echlon form of a matrix
def rref(A):
	m, n = A.shape
	reduced_A = np.copy(A)
	for i in range(m):
		for j in range(n):
			if reduced_A[i, j] != 0:
				reduced_A[i, :] /= reduced_A[i, j]
				for k in range(m):
					if k != i:
						reduced_A[k, :] -= reduced_A[i, :] * reduced_A[k, j]
				break
	return reduced_A

# Returns the basis of the span of the vectors in A
def get_basis(A):
	m, n = A.shape
	reduced_A = rref(A)
	basis = []
	for i in range(m):
		if np.count_nonzero(reduced_A[i, :]) != 0:
			basis.append(reduced_A[i, :])
	return np.array(basis)

# Returns the orthonormal basis of the span of the vectors in A
def gram_schmidt_orthonormalization(A):
	v = get_basis(A)
	r, n = v.shape
	u = np.zeros((r, n))
	u[0, :] = normalize(v[0, :])
	for i in range(1, r):
		u[i, :] = v[i, :]
		for j in range(i):
			u[i, :] -= inner_product(u[i, :], u[j, :]) * u[j, :]
		u[i, :] = normalize(u[i, :])
	return u


# Run a demo test of the gram_schmidt_orthonormalization function
A = np.array([[0, -1.0, -5, -1], [1, 0, 1, 2], [2, 0, 2, 4]])
ans = gram_schmidt_orthonormalization(A)
print(ans)
r = ans.shape[0]
for i in range(r):
	print("norm of u" + str(i+1), str(ans[i, :]) + " = " + str(inner_product(ans[i, :], ans[i, :]) ** 0.5))