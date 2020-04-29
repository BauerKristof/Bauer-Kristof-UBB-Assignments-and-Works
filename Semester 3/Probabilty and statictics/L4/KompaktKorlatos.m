function X = KompaktKorlatos(n)
    f = @(x)((3/4)*x^2*(2-x));
    X = zeros(1,n);

    a = 0;
    b = 2;
    M = 8/9;
    
    for i=1:n
        U = ULEcuyerRNG();
        V = ULEcuyerRNG();
        
        Y = a+(b-a)*V;
        
        while ~(U*M<=f(Y))
            U = ULEcuyerRNG();
            V = ULEcuyerRNG();

            Y = a+(b-a)*V;
        end
        
        X(i) = Y;
    end
    
    hist(X);
end