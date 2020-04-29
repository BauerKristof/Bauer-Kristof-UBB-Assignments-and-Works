N=[1,9,14,15,21,17,10,9,1,2,1];
n=sum(N);
k=length(N);
alpha=0.01;
x=0:(k-1);
lambda=(N*x')/n;
p0_=DiscretePDF(0:(k-2),'POISSON',lambda);
p0=[p0_,1-sum(p0_)];
chi2_value=sum(((N-n .*p0).^2)./(n.*p0))
chi2_quatile=chi2inv(1-alpha,k-1-1)
if (chi2_value<chi2_quatile)
    fprintf("Poisson eloszlas parameter: %f\n",lambda);
else
    fprintf("Nem poisson eloszlas");
end