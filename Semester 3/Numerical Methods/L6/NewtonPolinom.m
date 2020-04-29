function [Lmf] = NewtonPolinom(xx,fxx,x)

n=length(xx);
L=zeros(n);
for i=1:n
    L(i,1)=xx(i);
    L(i,2)=fxx(i);
end

for j=3:n+2
    for i=1:n-j+2
        L(i,j)=(L(i+1,j-1)-L(i,j-1))/ (L(i+j-2,1)-L(i,1));
    end
end

for i=2:n+1
    v(i-1)=L(1,i);
end
Lmf = v(n);
	
	for i = n-1:-1:1
		Lmf = Lmf * (x - xx(i)) + v(i);
    end
end

 
%{
L
Lmf = L(1,2);
szorzat = 1;   
for j = 3 : n+1
    szorzat = szorzat .* (x - xx(j-1));
    Lmf = Lmf + L(1, j)*szorzat;
end
%}

%for j=n:-1:1
 %   Lmf=Lmf*(x-xx(j+1))+L(1,j+1)
%end