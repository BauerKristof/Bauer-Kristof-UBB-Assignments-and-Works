% -----------
% Description
% -----------
% The function calculates the values of different discrete probability density functions.
%
% -----
% Input
% -----
% \mathbf{x} = \left[x_i\right]_{i=1}^n} - an increasing sequence of positive integers
% distribution_type                      - a string that identifies the distribution (e.g., 'Bernoulli', 
%                                          'binomial', 'Poisson', 'geometric', etc.)
% parameters                             - an array of parameters which characterize the distribution 
%                                          specified by distribution_type
%
% ------
% Output
% ------
% \mathbf{f} = \left[f(x_i)\right]_{i=1}^n - values of the given probability density function
function f = DiscretePDF(x, distribution_type, parameters)

% for safety reasons
sort(x);
x = round(x);

% get the size of the input array
n = length(x);

% select the corresponding distribution
switch (distribution_type)
    
    case 'geometric'
        % the Geo(p}-distribution has a single parameter p in (0,1)
        p = parameters(1);
        
        % check the validity of the distribution parameter p
        if (p < 0 || p > 1)
            error('Wrong parameter!');
        end
        
        % allocate memory and evaluate the probability density function f_{Geo(p)} 
        % for each element of the input array \mathbf{x} = \left[x_i\right]_{i=1}^n}
        f = zeros(1, n);

        q = 1 - p;
        
        for i = 1:n
            % check the validity of the current value x_i
            if (x(i) < 1)
                error('Incorrect input data!');
            else
                f(i) = q^(x(i) - 1) * p; % i.e., f_{Geo(p)}(x_i) = (1-p)^{x_i} * p, i=1,2,...,n
            end
        end
        
    % handle another discrete distribution type
     
    
         case 'pascal'
            % the pascal(p)-distribution has two parameters: p in (0,1) and N>=1
            N = parameters(1);
            p = parameters(2);

            N = round(N);

            % check the validity of the distribution parameters N,p
            if ((N < 1) || (p <= 0) || (p >= 1))
                error('Wrong parameter !');
            end

            % allocate memory and evaluate the probability density function f_{nbin(N,p)} 
            f = zeros(1,n);

            for i=1:n
                % check the validity of the current value x_i
                if (x(i) < 0)
                    error('Incorrect input data !');
                else
                    f(i) = nchoosek(N+x(i)-1,x(i))*p^N*(1-p)^x(i); % nchoosek(n,k) = n! / ( (n–k)! * k! )
                end
            end
            
            
             case 'poisson'
             lambda = parameters(1);

            % check the validity of the distribution parameter p
            if (lambda < 0)
                error('Wrong parameter!');
            end

            % allocate memory and evaluate the probability density function f_{Poisson(p)} 
            f = zeros(1, n);

            for i = 1:n
                if (x(i)<0)
                    error('Incorrect input data!');
                else
                    f(i) = ( ( lambda^x(i) ) / ( factorial(x(i) ) ) ) * exp(1)^(-lambda);
                end
            end
            
             case 'hypergeometric'
            N = parameters(1);
            M = parameters(2);
            nm = parameters(3);
            
            N = round(N);
            M = round(M);
           nm = round(nm);

            if ((N < 1) || (M < 0) || (M > N) || (nm < 0) || (nm > N))
                error('Wrong parameter !');
            end

            % allocate memory and evaluate the probability density function f_{hyge(p)} 
            f = zeros(1, n);

            for i=1:n
                % check the validity of the current value x_i
                if ((x(i) < max(0,nm-N+M)) || (x(i) > min(nm,M)))
                    error('Incorrect input data !');
                else
                    f(i) = nchoosek(M,x(i))*nchoosek(N-M,nm-x(i))/nchoosek(N,nm); 
                end
            end  
            
            
           
    case 'binomial'
            N = parameters(1);
            p = parameters(2);

            N = round(N);
            if ((N < 1) || (p <= 0) || (p >= 1))
                error('Wrong parameter !');
            end

            % allocate memory and evaluate the probability density function f_{nbin(N,p)} 
         f = zeros(1,n);

            q=1-p;
            for i=1:n
                % check the validity of the current value x_i
                if (x(i) < 0)
                    error('Incorrect input data !');
                else
                    f(i)=nchoosek(N,x(i))* p^x(i) * q^(N-x(i));
                end
            end
    
            
			
end