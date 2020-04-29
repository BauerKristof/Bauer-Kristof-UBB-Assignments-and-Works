function [Y]= Korrelalt(p,mu1,sigma1,mu2,sigma2,n)
    mu = [mu1 ; mu2];
    summa = [sigma1^2 , p*sigma1*sigma2 ; p*sigma1*sigma2 , sigma2^2];
    L = [sigma1 , 0 ; p*sigma2 , sqrt(1-p^2)*sigma2];
    T = 2*pi;
    Y = zeros(2,n);

    for k=1:n
        U1 = ULEcuyerRNG();
        U2 = ULEcuyerRNG();
        
        R = sqrt(-2*log(U1));
        theta = T*U2;
        X = [R*cos(theta) ; R*sin(theta)];
        Y(:, k) = L * X + mu;    
    end
end

