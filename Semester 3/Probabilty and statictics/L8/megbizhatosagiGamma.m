function  megbizhatosagiGamma( alpha,n )
    a=9;
    b=15;
    X=NewtonRaphson('gamma',a,b,0.01,n);
    x=norminv(1-(alpha./2),0,1);
    s=sum(X);
    l_max=((-2*x/sqrt(n) + 4)/(1/n * s))^(-1)
    l_min=((2*x/sqrt(n) + 4)/(1/n * s))^(-1)
end

