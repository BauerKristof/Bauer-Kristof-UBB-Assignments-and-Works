function Kirajzol(a,b)

%fuggveny finomfelosztasa
f=@(x)1./(1+x.^2);
xx=linspace(a,b,500);
fx=f(xx);
hold on;
plot(xx,fx,'r');


%polinom felosztasa
xxx=linspace(a,b,25);
fxx=f(xxx);

syms x
fdxx=vpa(subs(diff(f,x),xxx));

lx=Hermite(xxx,fxx,fdxx,xx);
plot(xx,lx,'b');
axis([a b a b]);
end
