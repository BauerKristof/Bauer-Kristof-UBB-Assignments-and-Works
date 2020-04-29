function [X] = NewtonRaphson(d_t, a,b,eps,n)


X = zeros(1, n);

switch d_t
    case {'gamma'}
      F = @(x) ContinuousCDF(x, d_t, [a,b]);
      f = @(x) ContinuousPDF(x, d_t, [a,b]);
    otherwise
           F = @(x) gamcdf(x, a, b);
        f = @(x) gampdf(x, a, b);
          
        
end
max=n;
kezdo=a*b;
i=1;
while (i<=n)
    U=F(0)+(F(kezdo*5)-F(0))*ULEcuyerRNG();
    x1 =kezdo ;
    x2 = x1 + ((U-F(x1))/f(x1));
    
    while x2 < 0
        x1 = x1 / 2.0;
        x2 = x1 + ((U - F(x1)) / f(x1));
    end
    
    x = x2;
    lep=0;
    while (abs(F(x) - U) > eps && lep < max)
        x = x - ((F(x) - U) / f(x));
        lep=lep+1;
    end
    
    if (lep<max)
        X(i)=x;
        i=i+1;
    end
end
end