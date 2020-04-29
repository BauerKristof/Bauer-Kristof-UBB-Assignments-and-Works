function F=ContinuousCDF(x,tip,parameter)

sort(x);
n=length(x);
f=@(x)ContinuousPDF(x,tip,parameter);

switch(tip)
    case 'GAMMA'
        mini=0;
    case 'BETA'
        mini=0;
    case 'STUDENT'
        mini=-Inf;
    case 'NORMAL'
        mini=-Inf;
end
F = zeros(1,n);
F(1) = integral(f,mini,x(1));
for i=2:n
   F(i) = F(i-1)+integral(f,x(i-1),x(i)); 
end
end
