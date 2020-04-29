function test


figure;
    hist(ExactInversion('exponential', 1, 1000), 30);
    title('exponential');
figure;
    hist(ExactInversion('cauchy', 1, 1000), 30);
    title('cauchy');

    figure;
    hist(ExactInversion('rayleigh', 1, 1000), 30);
    title('rayleigh');

    figure;
    hist(ExactInversion('triangular', 1, 1000), 30);
    title('triangular');

    figure;
    hist(ExactInversion('rayleigh-end', 1, 1000), 30);
    title('rayleigh-end');

    figure;
    hist(ExactInversion('pareto', [1, 2], 1000), 30);
    title('pareto');


figure;
    hist(ExactInversion('pelda', 0.5 , 1000));
    title('Feladat 1');
    
figure;
         x = 0:0.001:1;
         s1 = subplot(2,1,1);
         plot(x,ContinuousPDF(x,'pelda',[1,2]))
         title('ContinuousPDF - Feladat 1');
         
         s2 = subplot(2, 1, 2);
         plot(x,ContinuousCDF(x,'pelda',[1,2]))
         title('ContinuousCDF - Feladat 1');


figure;
    hist(Felezo('normal',[0,1],-3,3,0.001,1000));
    title('Felezo');

figure;
    hist(Hur('normal',[0,1],-3,3,0.001,1000),30);
    title('Hur');

figure;
    hist(NewtonRaphson([2,2], 0,8, 0.001,1000));
    title('Newton Raphson  (2,2)');

figure;
    hist(NewtonRaphson([1/2 1], 0,8, 0.001,1000));
    title('Newton Raphson  (1/2,1)');
figure;
    hist(Poisson(5, 1000));
    title('Poisson')


figure;
    hist(geo(1/3, 1000));
    title('Geometriai');
    
%[val1,val2]=fagyi2(10000);
%display(val1);
%display(val2);


