% -----------
% Description
% -----------
% The function evaluates different continuous probability density functions.
%
% -----
% Input
% -----
% \mathbf{x} = \left[x_i\right]_{i=1}^n - an increasing sequence of real numbers
% distribution_type                     - a string that identifies the distribution (e.g., 'exponential', 
%                                         'normal', 'chi2', 'gamma', 'beta', 'Student', etc.)
% parameters                            - an array of parameters which characterize the distribution 
%                                         specified by distribution_type
%
% ------
% Output
% ------
% \mathbf{f} = \left[f_i\right]_{i=1}^n  = \left[f(x_i)\right]_{i=1}^n} - values of the given probability density function
%
function f = ContinuousPDF(x, distribution_type, parameters)

% for safety reasons
x = sort(x);

% get the size of the input array
n = length(x);
% select the corresponding distribution
switch (distribution_type)
    
    case 'normal'
        % the N(mu,sigma)-distribution has two parameters, where mu in \mathbb{R} and sigma > 0
        mu    = parameters(1);
        sigma = parameters(2);
        
        % check the validity of the distribution parameters 
        if (sigma <= 0)
            error('The standard deviation must be a strictly positive number!');
        end

        % Allocate memory and evaluate the probability density function f_{N(mu,sigma) 
        % for each element of the input array \mathbf{x} = \left[x_i\right]_{i=1}^n.
        %
        % Note that, in this special case, this can be done in a single line of code,
        % provided that one uses the dotted arithmetical operators of MATLAB.
        
        f = (1.0 / sqrt(2.0 * pi) / sigma) * exp(-(x - mu).^ 2 / 2.0 / sigma^2); 
        
    % handle another continuous distribution type
    ...
end