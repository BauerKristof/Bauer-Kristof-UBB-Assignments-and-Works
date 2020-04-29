function [Megoldas] = Aitken(xx,fxx,x,epsilon)
n=length(xx);

for i=1:n
    for j=1:n
        if abs(x-xx(i))<abs(x-xx(j))
            csere=xx(i);
            xx(i)=xx(j);
            xx(j)=csere;
            
            csere=fxx(i);
            fxx(i)=fxx(j);
            fxx(j)=csere;
        end
    end
end
Q=zeros(n);
Q(1,1)=fxx(1);

for i=2:n
    Q(i,1)=fxx(i);
    for j = 1 : i-1
       Q(i, j+1) = ((xx(i) - x)*Q(j, j) - (xx(j) - x)*Q(i, j)) / (xx(i) - xx(j));
    end
    
    if epsilon > abs(Q(i,i) - Q(i-1, i-1))
        Megoldas = Q(i,i);
        return
    end
end

display(Q);
fprintf('HIBA:Nem elegendo a csomopontok szama!\n');
Megoldas=0;
end
    

