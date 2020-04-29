function X = Laplace2(mu, sigma, n)
	X = Cauchy(n);
	for i = 1:n
		X(i) = X(i) / sigma + mu;
	end
end


