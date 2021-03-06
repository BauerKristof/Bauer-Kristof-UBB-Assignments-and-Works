% X=[X_i]_{i=1}^n - denotes the sample that has to be generated
%
% distribution_type - a string that identifies the distribution of the random variate X
%
% parameters - an array that stores the parameters of the given distribution
%
% n - denotes the sample size
function X = ExactInversion(distribution_type, parameters, n)
    X = zeros(1,n);
    switch distribution_type

        
         case 'exp'
        U = UMersenneTwisterRNG(n);
        lambda = parameters(1);
        if (lambda <= 0)
            error('Hibas parameter lambda!');
        end
        X = (-1/lambda) * log(U);
        

        case 'cauchy'
            % one parameter: \sigma>0
            sigma = parameters(1);

            if (sigma<=0)
                error("Sigma has to be strictly greater than zero!")
            end

            % fx = @(x)(sigma/(pi*(x^2+sigma^2)));
            % Fx = @(x)(1/2 + 1/pi * arctan(x/sigma));

            for i=1:n
                U = ULEcuyerRNG;
                X(i) = sigma*tan(pi*U);
            end

        case 'rayleigh'
            % one parameter: \sigma>0
            sigma = parameters(1);

            if (sigma<=0)
                error("Sigma has to be strictly greater than zero!")
            end

            % fx = @(x)((x/sigma^2)*exp((a^2-x^2)/2));
            % Fx = @(x)(1-exp(-((x^2)/(x*sigma^2))));

            for i=1:n
                U = ULEcuyerRNG;
                X(i) = sigma*sqrt(-2*log(U));
            end

        case 'triangular'
            % one parameter: a>=0
            a = parameters(1);

            if (a<0)
                error("a has to be positive!")
            end

            % fx = @(x)((2/a)*(1-(x/a)));
            % Fx = @(x)((x/a)*(x-((x^2)/2*a)));

            for i=1:n
                U = ULEcuyerRNG;
                X(i) = a*(1-sqrt(U));
            end

        case 'rayleigh-end'
            % one parameter: a>0
            a = parameters(1);

            if (a<=0)
                error("a has to be strictly greater than zero!")
            end

            % fx = @(x)(x*exp((a^2 - x^2)/2));
            % Fx = @(x)(1 - exp((a^2 - x^2)/2));

            for i=1:n
                U = ULEcuyerRNG;
                X(i) = sqrt(a^2 - 2*log(U));
            end

        case 'pareto'
            % two parameters: a>0 , b>0
            a = parameters(1);
            b = parameters(2);

            if (a<=0 || b<=0)
                error("A and B has to be strictly greater than zero!")
            end

            % fx = @(x)((a*(b^a))/(x^(a+1)));
            % Fx = @(x)(1-(b/x)^a);

            for i=1:n
                U = ULEcuyerRNG;
                X(i) = b/(U^(1/a));
            end

            
           
        case 'pelda'

            for i=1:n
                U = ULEcuyerRNG;
                if (U<=0)
                    X(i) = 0;
                elseif (0<U && U<1/2)
                    X(i) = sqrt(U/2);
                elseif(1/2<U && U<=1)
                    X(i)=-(-4+sqrt(-8*U+8))/4;
                 elseif(U>1)
                        X(i)=1;
                 end
                            
                end
    end

    end