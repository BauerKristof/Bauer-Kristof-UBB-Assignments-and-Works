function X = NewtonRaphson(parameters, a, b, epsilon, n)

    X = zeros(1,n);
       if(n<1)
                error("Error:N>=1");
            end
            
            if(epsilon<=0)
                error("Error:eps>0");
            end
    
     F = @(x)gamcdf(x, parameters(1), parameters(2));
     f = @(x)gampdf(x,parameters(1),parameters(2));    
    for i = 1:n
			u = ULEcuyerRNG() * (F(b) - F(a)) + F(a);
            x1=rand();
            x2=x1-(F(x1)-u)/f(x1);
            
            while (x2<0.0)
                x1=x1/2.0;
                x2=x1-(F(x1)-u)/f(x1);
            end
       
            x=x1;
            x=x-(F(x)-u)/f(x);
			
           while(abs(F(x) - u) > epsilon)
				x = x-(F(x)-u)/f(x);
			end
		    X(i) = x;
            
            
	end

    hist(X);
    title("Newton Raphson");
end