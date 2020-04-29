function feladat1(n)
    
    fprintf('Exponencialis\n\n');
    Exponencialis=2;
    X=ExactInversion('exp',Exponencialis,n);
    ExpE=1/Exponencialis;
    ExpD2=1/(Exponencialis^2);
    fprintf('Sajat E(X)= %d\nMatlab E(X)= %d\nSajat D2(X)=%d\nMatlab D2(X)= %d\n\n',ExpE,mean(X),ExpD2,var(X));
    
    
    fprintf('Geometriai\n\n');
    Geometriai=1/4;
    X=Geo(Geometriai,7000);
    GeoE=1/Geometriai;
    GeoD2=(1-Geometriai)/(Geometriai^2);
    fprintf('Sajat E(X)= %d\nMatlab E(X)= %d\nSajat D2(X)=%d\nMatlab D2(X)= %d\n\n',GeoE,mean(X),GeoD2,var(X));

    fprintf('Binomialis\n\n');
    Binomialis=1/3;
    m=12;
   %X=binornd(12,1/3,1,1000);
    B(1,:) = 0:11;
    B(2,:) = DiscretePDF(B(1,:),'binomial',[12,1/3]);
    B(1,13)=12;
    B(2,14)=1-sum(B(2,1:12));
    sample = InversionBySequentialSearch(B,'MersenneTwister',7000);
    
    BinoE=m*Binomialis;
    BinoD2=m*Binomialis*(1-Binomialis);
    
    fprintf('Sajat E(X)= %d\nMatlab E(X)= %d\nSajat D2(X)=%d\nMatlab D2(X)= %d\n\n',BinoE,mean(sample),BinoD2,var(sample));

    
    fprintf('Haromszog\n\n');
    Haromszog=6;
    X=ExactInversion('triangular',Haromszog,n);
    TriE=Haromszog/3;
    TriD2=(Haromszog^2)/18;
    
    fprintf('Sajat E(X)= %d\nMatlab E(X)= %d\nSajat D2(X)=%d\nMatlab D2(X)= %d\n\n',TriE,mean(X),TriD2,var(X));
    
    fprintf('Pareto\n\n');
    Pareto=[4,2];
    X=ExactInversion('pareto',Pareto,n);
    ParE=(Pareto(1)*Pareto(2))/(Pareto(1)-1);
    ParD2=(Pareto(1)*Pareto(2)^2)/((Pareto(1)-1)^2*(Pareto(1)-2));
    
    fprintf('Sajat E(X)= %d\nMatlab E(X)= %d\nSajat D2(X)=%d\nMatlab D2(X)= %d\n\n',ParE,mean(X),ParD2,var(X));


end

