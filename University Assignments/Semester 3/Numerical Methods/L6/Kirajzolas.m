function Kirajzolas(a, b)
	n = 5000;
	f=@(x)1./(1+x.^2)
	x = linspace(a, b, n); 
	
	feloszt = 50;
	xx = linspace(a, b, feloszt);
	fxx=f(xx);
	f1 = zeros(1, n);
	
	for i = 1:n
		f1(i) = NewtonPolinom(xx, fxx, x(i));
    end
    
	plot(x, f1);
	hold on;
	plot(x, f(x), "r");
	
	axis([-5 5 -5 5])
end