function [Hxf] = Hermite(xx, fxx, dxx, x)

n = length(xx)*2;
hermiteMatrix = zeros(n);

i = 1;
j = 1;

%Megduplaz az XX-eket z0=x1,z1=x1, Elment duplazott z0,z1-eket
while i <= n
    
    hermiteMatrix(i, 1) = fxx(j);
    xxDuplazott(i) = xx(j);
    i = i+1;
    
    hermiteMatrix(i, 1) = fxx(j);
    xxDuplazott(i) = xx(j);
    i = i+1;
    j = j+1;
end

%Kiszamol masodik oszlop- ha paros derivalt / ha nem keplet
hanyadik = 1;
for i = 1 : n-1

    if mod(i,2)==1
        hermiteMatrix(i,2) = dxx(hanyadik);
        hanyadik = hanyadik+1;
    else
        hermiteMatrix(i,2) = (hermiteMatrix(i+1, 1) - hermiteMatrix(i, 1)) / (xxDuplazott(i+1) - xxDuplazott(i));
    end
end

%Kiszamol osszes tobbi oszlop
for j = 3 : n
    for i = 1 : n-j+1
       hermiteMatrix(i,j) = (hermiteMatrix(i+1, j-1) - hermiteMatrix(i, j-1)) / (xxDuplazott(i+j-1) - xxDuplazott(i));  
    end
   
end

%Polinom kiszamitasa
Hxf = hermiteMatrix(1,1);
szorzat = 1;


for j = 2 : n   
    szorzat = szorzat .* (x - xxDuplazott(j-1));
    Hxf = Hxf + hermiteMatrix(1, j)*szorzat; 
end

end