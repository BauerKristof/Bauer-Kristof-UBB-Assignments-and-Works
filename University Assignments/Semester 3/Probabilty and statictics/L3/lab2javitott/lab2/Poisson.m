 function X = Poisson(lambda, r)

 if (lambda<=0 || r<1)
        error("Error: Lambda >0 es r>=1 !")
    end


X = zeros(1,r);

for k = 1:r       
    U = ULEcuyerRNG();
    i = 0;
    p = exp(-lambda);
    S = p;
    while(U > S)
        i = i + 1;
        p = (lambda / i) * p;
        S = S + p;
    end       
    X(k) = i;
end    
end
