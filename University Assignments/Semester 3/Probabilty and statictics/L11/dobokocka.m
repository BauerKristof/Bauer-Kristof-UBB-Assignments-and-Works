function dobokocka()

X=[1:6]; %osszesito tablazat vagy x
N=[69,50,57,64,63,97]; %kell hivni egy histogrammot ha nincs meghat N
n=sum(N); 
k=6; 
p0=1/6*ones(1,6); %altalunk tippelt eloszlasnak megfeleloen - discreptepdf eloszlalasra

chi2_value=sum( ((N-n .* p0) .^2) ./ ((n .* p0)))
alpha= 0.01;
chi2_quantile = chi2inv(1 - alpha,k-1)

if(chi2_value < chi2_quantile)
    disp('Szabalyos a kocka');
else
    disp('Nem szabalyos a kocka');
end
end