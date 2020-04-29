function [eredmenyMatrix] = cholesky(a)

n = length(a);
l = eye(n);

for i = 1:n
    for j = 1:i
        s = 0;
  
        for k = 1:(j-1)
            s = s +l(i,k)*l(j,k);
        end
        
        if (i ~= j)
            l(i,j) = 1 / l(j,j) * (a(i,j) - s);
        else
            l(i,j) = sqrt(a(i,i) - s);
        end
    end
end

eredmenyMatrix=l;
end

