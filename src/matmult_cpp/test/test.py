import numpy as np
from matmult import matmult
print("Testing simple multiplication...")
a = np.array([[1., 2.], [3., 4.]])
b = np.array([[1., 0.], [0., 1.]])

c = matmult(a, b)

np.testing.assert_array_equal(a, c)

print("Testing compytibility with transpose...")
a1 = np.array([[1, 3], [2, 4]], dtype=float).T
np.testing.assert_array_equal(a, a1)

c = matmult(a1, b)

np.testing.assert_array_equal(a, c)
