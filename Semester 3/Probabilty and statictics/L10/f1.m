function f1()
    X = [501, 497, 500, 498, 500, 497, 498, 498, 500, 497, 497, 498, 497, 498,01, 501, 502, 496];
    
    alpha = 0.04;
    mu_guess = 500;

   [ci_t, ci_mu, t_value, p_value, H] = TTest(X,mu_guess,alpha,'left');

        if (H==0)
            fprintf('Kevesebbet osztott ki\n')
        else
            fprintf('Nem osztott ki kevesebbet\n')
        end
end