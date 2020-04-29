function [xG,kG] = GaussSeidel(A,b,epsilon)
%soronkent dominans foatloju
%-ha nem kilep mert nem konvergens
%megszerkeszt d,l,u d-diag
%mj,fj, x1,x2

n=length(A);

dominans=0;
    for i=1:n
        sum=0;
        for j=1:n
            if i~=j sum=sum+A(i,j);
            end
        end
        if A(i,i)<sum dominans=1;
        break;
        end
    end
    
    if(dominans==1)
        error("HIBA:Nem konvergens Matrix");
    else
        D=zeros(1,n);
        L=zeros(n);
        U=zeros(n);
        
        D=diag(diag(A));
        L=-A+tril(A);
        U=-A+triu(A);
        
        P = D-L;
        Q = U;
        
        
        M = P \ Q;
        f = P \ b;
        
        x1=zeros(n,1); 
        xG=M*x1+f;
        
        kG=0;
        while norm(xG-x1) >= ((1-norm(M))/norm(M))*epsilon
            x1=xG;
            xG=M*x1+f;
            kG=kG+1;
        end
    end       
end
