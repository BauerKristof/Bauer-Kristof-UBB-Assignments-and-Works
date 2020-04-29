
function X = Laplace(n)

X = zeros(1, n);
    
for i=1:n
    Y = ExactInversion('exponential',1,1);
    V = 2*ULEcuyerRNG()-1;
        
    while ((Y-1)^2 > -2*log(abs(V)))
        Y = ExactInversion('exponential',1,1);
        V = 2*ULEcuyerRNG()-1;
    end
        
    X(i) = Y*sign(V);
end
hist(X);
     
end