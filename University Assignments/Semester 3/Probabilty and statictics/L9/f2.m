function f2()
  X = [249.96; 250.90; 249.46; 250.20; 249.96; 250.70; 249.60; 250.00;250.40; 250.03; 250.76; 250.03; 249.66; 249.76];
  Y = [249.10; 251.40; 249.56; 250.56; 249.70; 250.86; 249.33; 249.23; 248.93; 250.46; 249.96; 249.80];

    sigma1 = 0.4;
    sigma2 = 0.8;
    p = 0.02;
        
    [ci_u, ci_delta, u_value,p_value, H] = UTest2D(X, Y, sigma1, sigma2, p,'right');
    
    if(H == 0)
        disp('Nem tolt tobb mogyorovajat az elso gep');
    else
        disp('Tobb mogyorovajat tolt az elso gep');
    end
end