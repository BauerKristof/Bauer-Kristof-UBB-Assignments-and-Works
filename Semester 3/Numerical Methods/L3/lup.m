function [L, U, P] = lup(A)
n = size(A);
n = n(1);
P = eye(n);
L = zeros(n);
U = zeros(n);

for j = 1 : n-1
    
    [oszlopMax,oszlopMaxIndex] = max(abs(A(j:n,j))); %ki kell valasztani a foelemet!!!
    oszlopMaxIndex = oszlopMaxIndex + j - 1;
    
    if(oszlopMax ~= 0)
    seged = A(oszlopMaxIndex,:);
    A(oszlopMaxIndex, :) = A(j, :);
    A(j, :) = seged;
    
    seged = P(oszlopMaxIndex,:);
    P(oszlopMaxIndex, :) = P(j, :);
    P(j, :) = seged;
    
    seged = L(oszlopMaxIndex,:);
    L(oszlopMaxIndex, :) = L(j, :);
    L(j, :) = seged;
    
    else
        error("Hiba:Szingularis");
    end
    
    for i = j+1 : n %gauss eliminacio
        
        szorzo = A(i,j)/A(j,j);
        L(i,j) = szorzo;
        TEMP = A(j,:)*szorzo;
        A(i,:) = A(i, :) - TEMP;
        
    end
end
U = A;
L = L+eye(n);

