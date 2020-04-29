function f=DiscretePDF(x,tipus,par)
sort(x);
x=round(x);
n=length(x);

switch (tipus)
    case 'BINOMIAL'
        n3=par(1);
        p=par(2);
        if (n3<1||p<=0||p>=1)
             error('Hibas parameter!');
        end
        f=zeros(1,n);
        for i=1:n
            if (x(i)<0)
                error ('Hibas bemenet!');
            else
                f(i)=kombinacio(n3,x(i))*p^x(i)*(1-p)^(n3-x(i));
            end
        end
    case 'POISSON'
        p=par(1);
        if p<=0 
             error('Hibas parameter!');
        end
        f=zeros(1,n);
        for i=1:n
            if x(i)<0
                error('Hibas bemenet!');
            else
                f(i)=(p^x(i)/(factorial(x(i))))*exp(-p);
            end
        end
        case 'HYPERGEOMETRIC'
        N=par(1);
        M=par(2);
        n2=par(3);
        if N<1
           error('Hibas parameter!'); 
        end
        if M<0||M>N
            error('Hibas parameter!');
        end
        if n2<0||n2>N
            error('Hibas parameter!');
        end
        f=zeros(1,n);
        for i=1:n
            if (x(i)<max(0,n2-N+M)||x(i)>min(n2,M))
                error('Hibas bemenet!');
            else
                k=x(i);
                f(i)=(kombinacio(M,k)*kombinacio(N-M,n2-k))/(kombinacio(N,n2));
            end
        end
        
    case 'GEOMETRIC'
        p=par(1);
        if (p<0||p>1)
            error('Hibas parameter!');
        end
        f=zeros(1,n);
        q=1-p;
        for i=1:n
            %if (x(i)<1)
               % error('Hibas bemenet!');
          %  else
               % f(i)=(q^(x(i)-1))*p; 
               f(i)=q^(x(i))*p;
           % end
        end
        
        
        case 'PASCAL'
        N=par(1);
        if (N<1)
            error('Hibas parameter!');
        end
        p=par(2);
        if (p<0||p>1)
            error('Hibas parameter!');
        end
        f=zeros(1,n);
        for i=1:n
            if (x(i)<0)
                error('Hibas bemenet!');
            else
                k=x(i);
                f(i)=kombinacio(N+k-1,k)*p^N*(1-p)^k;
            end
        end
        
    
        
    
end      
end

function k1=kombinacio(n,k)
    k1 = factorial(n)/(factorial(n-k)*factorial(k));
end

