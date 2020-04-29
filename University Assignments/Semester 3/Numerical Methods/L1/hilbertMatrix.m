%Nev:Bauer Kristof
%Csoport:521
%Felhasznalo:bkim1790

function [] = hilbertMatrix()

    for i=1:10
          format='n=%i  %f \n';
        fprintf(format,i,hilbertCalc(i));
    end

end

