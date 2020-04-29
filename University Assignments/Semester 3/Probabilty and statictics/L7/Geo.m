function X = Geo(p, n)
lambda = -log(1-p);
X = ceil(ExactInversion('exp', lambda, n));
end