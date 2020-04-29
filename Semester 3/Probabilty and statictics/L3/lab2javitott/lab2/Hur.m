function X = Hur(dist_type, parameters, alpha, beta, epsilon, n)
        if(n<1)
         error("Error:N>=1");
         end
            
         if(epsilon<=0)
          error("Error:eps>0");
         end


    X = zeros(1,n);
    F = @(x)ContinuousCDF(x, dist_type, parameters);
    
    for i=1:n
        a = alpha;
        b = beta;
        u = ULEcuyerRNG() * (F(b) - F(a)) + F(a);
        
        X(i) = a + (b-a)*((u-F(a))/(F(b)-F(a)));

        if (F(X(i))<u)
            a = X(i);
        else
            b = X(i);
        end

        while (abs(F(X(i))-u)>epsilon)
            X(i) = a + (b-a)*((u-F(a))/(F(b)-F(a)));

            if (F(X(i))<u)
                a = X(i);
            else
                b = X(i);
            end
        end
    end
end

