function C=splineEgyutthato(xx,fxx)

%kiszamit h vektor
n = length(xx);
h= zeros(1,n);
for j = 1:n-1
    h(j+1) = xx(j+1) - xx(j);
end

% kiszamit mu lambda etc 
l=zeros(n,1);
d=zeros(n,1);
mu=zeros(n,1);

l(1)=1;
d(1)=0;
mu(1)=0;

l(n)=0;
mu(n)=1;
d(n)=0;

for j=2:n-1
    l(j)=h(j+1)/(h(j)+h(j+1));
    mu(j)=1-l(j);
    d(j) = 6/(h(j)+h(j + 1))*((fxx(j+1)-fxx(j))/h(j + 1)-(fxx(j)-fxx(j - 1))/h(j));

end

% kiszamit e.r -diagokkal
%n darab kettes foatlo
%mu-bol n-1-ig foatlo fole
A = diag(2 .* ones(n, 1)) + diag(mu(2:n),-1) + diag(l(1:n-1),1);

%er megoldasa
M = linsolve(A,d);

C = zeros(4, n-1);
for j=1:n-1
    C(1,j) = fxx(j); %alpha
    C(2,j) = (fxx(j + 1)-fxx(j))/h(j + 1)-(h(j + 1)*(2 * M(j)+M(j + 1)))/6; %beta
    C(3,j) = M(j)/2; %gamma
    C(4,j) = (M(j + 1)-M(j))/(6 * h(j+1)); %delta
end
%display(C);
end

