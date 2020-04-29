function [sum] = GaussKvadHermite(f, m)
	
	alpha = zeros(1, m);
	beta = zeros(1, m);
    
    alpha(1)=0;
	beta(1) = sqrt(pi);
    
	for k = 1:m
		beta(k + 1) = k / 2;
	end
		
	J = diag(alpha) + diag(sqrt(beta(2:m)), 1) + diag(sqrt(beta(2:m)), -1);
	[V, L] = eig(J);
    x = diag(L);
    
    A = zeros(1, m);
	
	for k = 1:m
		A(k) = beta(1) * (V(1, k) / norm(V(:, k))) ^ 2;
	end
		
	sum = 0;
	for k = 1:m
		sum = sum + A(k) * f(x(k));
	end

end