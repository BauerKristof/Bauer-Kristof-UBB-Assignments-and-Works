    case 'hyge'
        N = round(parameters(1));
        M = round(parameters(2));
        n = round(parameters(3));
        if (N<1)
            error("Wrong parameter N!");
        end
        if (M < 0 || M > N)
            error ("Wrong parameter M!");
        end
        if (n<0 || n>N)
            error ("Wrong parameter n!");
        end
        
        f = zeros(1,length(x));
        for i = 1 : length(x)
            felt1 = max(0,n-N+M);
            felt2 = min(n,M);
            if (x(i) < felt1 || x(i) > felt2)
                error("Wrong input!");
            else
                f(i) = nchoosek(M,x(i))*nchoosek(N-M,n-x(i))/nchoosek(N,n);
                
            end
        end