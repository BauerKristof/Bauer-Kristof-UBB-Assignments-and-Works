function [n]=optimal2(exp)
alpha=0.05;
epsilon=0.05;
mu=1/2;
sigma=1/2;

probab=1-alpha;
n=360;
p=0;
while (p<probab)
    n=n+1;
    kedv=0;
    for i=1:exp
       M=[0,1;1/2,1/2];
       x=InversionBySequentialSearch(M,'MersenneTwister',n);
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

