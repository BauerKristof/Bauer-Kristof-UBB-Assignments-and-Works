function S = splinePontban( xx, fxx, x )
C = splineEgyutthato(xx, fxx);
%kiszamit a pontok hossza
n = length(xx);
%kiszamit azoknak a pontoknak az indexet amelyek kissebbek mint a x pontunk
kissebbIndex = find(x >= xx);
%j=kissebb pontok indexe kozul a legutolsoval
j = kissebbIndex(length(kissebbIndex));

if(j == n)
    j = j -1;
end

%kiszamit harmadfoku polinom
S = C(1,j) + C(2,j)*(x - xx(j)) + C(3,j)*(x - xx(j))^2 + C(4,j)*(x - xx(j))^3;

end