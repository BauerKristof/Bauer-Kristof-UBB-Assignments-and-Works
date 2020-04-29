function X = Felezo(d_t, parameters, alpha, beta, epsilon, n)
    X=zeros(1,n);
	F = @(x) ContinuousCDF(x, d_t, parameters);
            if(n<1)
                error("Error:N>=1");
            end
            
            if(epsilon<=0)
                error("Error:eps>0");
            end
            
            for i = 1:n
            a = alpha;
			b = beta;
            x = (a + b) / 2;
			u = ULEcuyerRNG() * (F(b) - F(a)) + F(a);
			
			while(abs(F(x) - u) > epsilon || abs(b - a) > epsilon)
				if(F(x) <= u)
					a = x;
				else
					b = x;
				end
				x = (a + b) / 2;
			end
			X(i) = x;
		end
end

