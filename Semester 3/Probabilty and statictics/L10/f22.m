function f22()

X = [249.96; 250.90; 249.46; 250.20; 249.96; 250.70; 249.60; 250.00;250.40; 250.03; 250.76; 250.03; 249.66; 249.76];
Y = [249.10; 251.40; 249.56; 250.56; 249.70; 250.86; 249.33; 249.23; 248.93; 250.46; 249.96; 249.80];

alpha = 0.02;
        
[ci_t, ci_delta, t_value, p_value, H] = TTest2D(X, Y, 0, alpha, 'right');
    
if(H == 0)
    disp('Nem tolt tobb mogyorovajat az elso gep');
else
    disp('Tobb mogyorovajat tolt az elso gep');
end
