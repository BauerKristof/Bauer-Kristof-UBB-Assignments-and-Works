%Nev:Bauer Kristof
%Csoport:521
%Felhasznalo:bkim1790

function [sinErt,cosErt] = elsoSzamitas(x,epsilon)

x=x-floor(x/(2*pi))*2*pi;
y=x;
n=1;
sValt=x*(x^2)/(2*n*(2*n+1));


while abs(sValt)>=epsilon
     sValt=sValt*(-1);
     y=y+sValt;
     n=n+1;
     sValt=sValt*(x^2)/(2*n*(2*n+1));
   
end
sinErt=y;


y=1;
n=1;
sValt=1*(x^2)/((2*n)*(2*n-1));

while abs(sValt)>=epsilon
        sValt=sValt*(-1);
        y=y+sValt;
        n=n+1;
        sValt=sValt*(x^2)/((2*n)*(2*n-1));
end

cosErt=y;


end

