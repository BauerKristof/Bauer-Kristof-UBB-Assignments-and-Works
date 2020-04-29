function [x1,x2] = Marsagila(n)
x1=zeros(1,n);
x2=zeros(1,n);

for i=1:n
		U1 = ULEcuyerRNG();
		U2 = ULEcuyerRNG();
		Z1 = 2*U1 - 1;
		Z2 = 2*U2 - 1;
		S = Z1^2 + Z2^2;
		
		while (~(S>0 && S<=1))
			U1 = ULEcuyerRNG();
			U2 = ULEcuyerRNG();
			Z1 = 2*U1 - 1;
			Z2 = 2*U2 - 1;
			S = Z1^2 + Z2^2;
		end
		
		T = sqrt(-((2*log(S))/(S)));
		x1(i) = T*Z1;
		x2(i) = T*Z2;
end
end

