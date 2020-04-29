function megbizhatosagiPoisson( alpha,n )
    l=20;
    X=Poisson(l,n);
    x=norminv(1-(alpha./2),0,1);
    A=1;
    B=-(2.*mean(X)+(1./n).*(x.^2));
    C=mean(X).^2;
    delta=B.^2-(4.*A.*C);
    l_min=(-B-sqrt(delta))./(2.*A)
    l_max=(-B+sqrt(delta))./(2.*A)

end