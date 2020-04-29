function x = UTriangSolve(U,b)

    display(U);
    display(b);
    n = length(b);
    x = zeros(1,n);

    for i = n-1 : -1 : 1
		felsomSum = 0;
		for j = i + 1:n
			felsomSum = felsomSum + U(i, j) * x(j); %kiszamit felso haromszog matrix osszeget
		end
		x(i) = (b(i, 1) - felsomSum) / U(i, i); %elvegzi a kulonbseget
    end
end

