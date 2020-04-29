function  dobokocka()
X=[1:6]; %X pontokat atirni
N=[69,50,57,64,63,97]; % N-eket atirni
n=sum(N); % csere
%k=6
k=round(length(X)) %darabSzam

p0=1/k*ones(1,k); % ha diszkret - DiscretePDF(adott eloszlasra)
chi2_value=sum(((N-n.*p0).^2)./(n.*p0))

alpha=0.01;

chi2_quantile=chi2inv(1-alpha,k-1) %csere k-1 nel levonni meg valamit
if (chi2_value<chi2_quantile)
    disp("Szabalyos a kocka");
else
    disp("Nem szabalyos a kocka");
end

