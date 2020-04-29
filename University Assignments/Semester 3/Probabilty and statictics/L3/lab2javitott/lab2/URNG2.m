function [X, new_init_val] = URNG2(init_val, n)
    m = 2^31-1;
    a = 2^16+3;
    c = 0;
    
    [X, new_init_val] = LinearCongruentialGenerator(m,a,c, init_val, n);
    
    hist(X);
end