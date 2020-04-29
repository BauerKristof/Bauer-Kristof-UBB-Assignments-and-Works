function X = geo(p,n)
%X=ExactInversion('exp',-log(1-p),n);
%X=cell(X);

lambda = -log(1-p);
X = ceil(ExactInversion('exp', lambda, n));

%    if ((p<0)||(p>1))
 %   error('Error:0<=p<=1!');
%end

%X = zeros(1, n);
 %   for i=1:n
  %      U = ULEcuyerRNG();
   %     X(i) = log(1-U) / log(1-p);
   % end

%hist(X);


end