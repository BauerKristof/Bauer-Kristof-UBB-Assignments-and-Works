function [megoldas,lepesSzam] = Hurmodszer(f,epsilon, x0,x1,nmax)


lepesSzam=1;
megoldas(lepesSzam)=x0;
lepesSzam=lepesSzam+1;
while lepesSzam<nmax    
    x = x1 - f(x1)*(x1-x0)/(f(x1)-f(x0)); 
    megoldas(lepesSzam)=x;
    
    if (abs(x - x1) < epsilon)
        fprintf('Elertuk az epszilon pontossagot\n');
        break
    end
  
    x0 = x1;
    x1 = x;    
    lepesSzam=lepesSzam+1;
end

if (lepesSzam == nmax)
fprintf('Elertuk az nmaxot!\n');
megoldas(lepesSzam)=x;
end

end