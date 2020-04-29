function [X]=Poisson(a,n)
    if(a<=0||n<1)
        error('ROSSZ parameter!');
    end
     X=zeros(1,n);
    for k=1:n
        U=ULEcuyerRNG();
        i=0;
        p=exp(-a);
        S=p;
        while (U>S)
            i=i+1;
            p=(a/i)*p;
            S=S+p;
        end
        X(k)=i;
    end
end