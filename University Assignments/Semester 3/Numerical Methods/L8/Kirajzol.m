function Kirajzol(a, b)
    f = @(x) 1./(1+x.^2);
    %fgv felosztasa egyenletesen
    small = linspace(a, b, 11);
    fSmall = f(small);
   
    %fgv kozelitese
    big = linspace(a, b, 50);
    fbig = zeros(50, 1);   
    for i = 1:50  
        fbig(i) = splinePontban(small, fSmall, big(i));
    end
    
    plot(big, f(big));
    hold on;
    plot(big, fbig);

end