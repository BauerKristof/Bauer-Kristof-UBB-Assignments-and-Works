function X=NormLaplace(n,sz,m)
a=-1;
b=1;
X=zeros(1,n);
for i=1:n
    A=-log(1-rand());
    B=a+(b-a)*ULEcuyerRNG();
    while ((A-1)^2>-2*log(abs(B)))
        A=-log(1-rand());
        B=a+(b-a)*ULEcuyerRNG();
    end
    X(i)=A*sign(B);
end
X=X.*sz+m;
end

