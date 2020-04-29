function [n]=optimal(exp)
alpha=0.1;
epsilon=224;
mu=2800;
sigma=708;

probab=1-alpha;
n=0;
p=0;
while (p<probab)
    n=n+1;
    kedv=0;
    for i=1:exp

       x=NormLaplace(n,sigma,mu);
        if (abs(mean(x)-mu)<epsilon)
            kedv=kedv+1;
        end
    end
    p=kedv/exp;
    stem(n,p);
    hold on;
    drawnow;
        
end
end

