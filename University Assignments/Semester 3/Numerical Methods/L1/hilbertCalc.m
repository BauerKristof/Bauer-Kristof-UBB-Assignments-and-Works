%Nev:Bauer Kristof
%Csoport:521
%Felhasznalo:bkim1790

function [condition] = hilbertCalc(n)
    H=zeros(n); 
    for i = 1:n
         for j=1:n
             H(i,j)=1/(i+j-1);
         end
     end
     
     condition=norm(H)*norm(inv(H));
end

