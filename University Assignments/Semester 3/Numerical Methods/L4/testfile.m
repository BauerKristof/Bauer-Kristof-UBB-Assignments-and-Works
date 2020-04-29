function testfile(n, epsilon)
	v1 = 5 .* ones(n, 1);
	v2 = -1 .* ones(n - 1, 1);
	A = diag(v1) + diag(v2, 1) + diag(v2, -1);
	b = sum(A')';

	[xJ, kJ] = Jacobi(A, b, epsilon)
	[xG, kG] = GaussSeidel(A, b, epsilon)
	
end