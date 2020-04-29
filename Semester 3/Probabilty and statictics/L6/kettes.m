function [X,Fx] = kettes(n)
  f=@(x,y) (6/7)*(x^2+((x*y)/2));
  M=1.71;
  ax=0;
  bx=1;
  ay=0;
  by=2;
  
  
  X=zeros(n,2);
  Fx=zeros(n,1);
    if(n<1)
       error('Wrong parameter! n');
    end
   
  for i=1:n
    U=ULEcuyerRNG();
    V1=ULEcuyerRNG();
    V2=ULEcuyerRNG();
    Y1=ax+(bx-ax)*V1;
    Y2=ay+(by-ay)*V2;
    
    while (U*M > f(Y1,Y2))
        U=ULEcuyerRNG();
        V1=ULEcuyerRNG();
        V2=ULEcuyerRNG();
        Y1=ax+(bx-ax)*V1;
        Y2=ay+(by-ay)*V2;
    end
    Fx(i)=f(Y1,Y2);
    X(i,1)=Y1;
    X(i,2)=Y2;
    
  end  
  plot3(X(:,1),X(:,2),Fx,('g.'));
  figure(2);
  hist3(X);
  figure(3);
  [Z,T]=meshgrid(0:0.1:1,0:0.1:2);
  f=@(x,y) (6/7).*(x.^2+((x.*y)/2));
  surf(Z,T,f(Z,T));
end