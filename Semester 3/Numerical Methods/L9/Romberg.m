function [ertek] = Romberg(f,a,b,epsilon,nmax)
%soronkent elso keplet (j=1)
%kulonben richardson
%egeszen addig amig foatlon levo ket elem > eps

h=b-a;
Q=zeros(nmax);
Q(1,1)=(h/2) * (f(a) + f(b));

for k=2:nmax     

        sum=0;
        for i=1:2^(k-2)
          sum=f(a+(2*i-1)*h/(2^(k-1)));
        end
       Q(k,1)=1/2*Q(k-1,1)+h/(2^(k-1))*sum;

        
      for j=2:k
      Q(k,j)=((4^(j-1))*Q(k,j-1)-Q(k-1,j-1)) / (4^(j-1)-1);
      end
        
      if (k == nmax)
       fprintf('Elertuk a maximalis iteracio szamot\n');
       ertek=Q(k,k);
       break;
      end
       
      leallasi=abs(Q(k-1,k-1) - Q(k,k));
      if (leallasi) < epsilon
        fprintf('Elertuk az epszilon pontossagot\n');
        ertek=Q(k,k);
        break;
      end
end

integral(f,a,b)
end

