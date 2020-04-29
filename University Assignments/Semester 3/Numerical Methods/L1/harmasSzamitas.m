%Nev:Bauer Kristof
%Csoport:521
%Felhasznalo:bkim1790

function harmasSzamitas()
Matrix=[10 7 8 7;7 5 6 5;8 6 10 9;7 5 9 10];
pertMatrix=[10 7 8.1 7.2;7.08 5.04 6 5;8 5.98 9.89 9;6.99 4.99 9 9.89];
Vekt=[32;23;33;31];
pertVekt=[32.1;22.9;33.1;30.9];

fprintf("A matrix determinansa\n");
disp(det(Matrix));
fprintf("A matrix inverze\n");
disp(inv(Matrix)); 

fprintf("Helyes - Matrix/Vektor \n");
x=Matrix\Vekt;
disp(x)

fprintf("Hibas - Perturbalt Matrix/Vektor \n");
y=pertMatrix\Vekt;
disp(y);

fprintf("Hibas - Matrix/Perturbalt Vektorral\n");
z=Matrix\pertVekt;
disp(z);

fprintf("Bemeno relativ hiba 1\n");
bHiba1=norm(Matrix-pertMatrix)/norm(Matrix);
display(bHiba1);

fprintf("Bemeno relativ hiba 2\n");
bHiba2=norm(x-y)/norm(x);
display(bHiba2);

fprintf("Bemeno relativ hiba 3\n");
bHiba3=norm(Vekt-pertVekt)/norm(Vekt);
disp(bHiba3);

fprintf("Bemeno relativ hiba 4\n");
bHiba4=norm(x-z)/norm(x);
disp(bHiba4);

fprintf("Kimeneti hiba\n");
kHiba=norm(Matrix)*norm(inv(Matrix));
display(kHiba);
end