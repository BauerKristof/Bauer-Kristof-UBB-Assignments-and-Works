function feladat3(n)
    X = zeros(1, n);
    
    for i = 1:n
        vizsgaltSzam = 0;
        megtalalt = 0;
        
        while megtalalt == 0
            emberTipus = ULEcuyerRNG();
            kategoriaTipus = 0;
            
            if emberTipus > 0 && emberTipus < 0.3
                kategoriaTipus = 1; %fiatal
            end
            if emberTipus >= 0.3 && emberTipus < 0.8
                kategoriaTipus = 2; %kozepkoru

            end
            if emberTipus >= 0.8 && emberTipus < 1
                kategoriaTipus = 3; %idos
            end
            vizsgaltSzam = vizsgaltSzam + 1;
            
            beteg = ULEcuyerRNG();
            switch(kategoriaTipus)
                case 1 %fiatal
                    if beteg > 0 && beteg <= 0.01
                        megtalalt = 1;
                    end
                case 2 %kozepkoru
                    if beteg > 0.01 && beteg <= 0.03
                        megtalalt = 1;
                    end
                case 3 %idos
                    if beteg > 0.03 && beteg <= 0.13
                        megtalalt = 1;
                    end
            end
        end
        X(i) = vizsgaltSzam;
    end
    
    disp('E(X) = ');
    disp(mean(X));
    disp('D2(X) = ');
    disp(var(X));
   % hist(X);
end

