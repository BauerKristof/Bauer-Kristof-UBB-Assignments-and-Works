function [megoldas,lepesSzam] = NewtonRaphsonErinto(f,fd,epsilon,x0,nmax,a,b)
%megoldas + lepesszam
s=linspace(a,b,500);
hold on;
plot(s,f(s),'r');
plot([a b],[0,0]);


lepesSzam=1;
while lepesSzam<=nmax
  x=x0-f(x0)/fd(x0);
  megoldas(lepesSzam)=x;
   y=@(x)(f(x0)+fd(x0)*(x-x0));
   pause(1);
   plot(s,y(s));
  
  if (abs(x-x0) < epsilon)
       fprintf('Elertuk az epszilon pontossagot\n');
            megoldas(lepesSzam)=x;

        break
  end  
  x0=x;
  lepesSzam=lepesSzam+1;
end

if lepesSzam==nmax
     fprintf('Elertuk az maximalis elemszamot\n');
     megoldas(lepesSzam)=x;
end

end

