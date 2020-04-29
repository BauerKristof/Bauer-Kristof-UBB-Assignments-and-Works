function Kozrefogas(n)
    alpha=1/sqrt(exp(1));
    beta=1/2;
    gamma=sqrt(2);
    X=zeros(1,n);
    lepesek=0;
    kiertekelesek=0;
    
    for i=1:n
        lepes=0;
        kiertekeles=0;
        
        while(true)
        U=ULEcuyerRNG();
        V=ULEcuyerRNG();
        Y=tan(pi*V);
        S=beta*(Y^2);
        W=(alpha*U)/(beta+S);
        if abs(Y)>gamma
          L=false;
        else
           L=(W<=1-S);
        end
        
        if L==false
            L=(W<=exp(-S));
            kiertekeles=kiertekeles+1;
        end
        lepes=lepes+1;
        
          if(L==1)
            break;
           end
        end
   
          X(i)=Y;    
          lepesek = lepesek + lepes;
          kiertekelesek = kiertekelesek + kiertekeles;
    end
    
    hist(X);
    display(lepesek/n);
    display(kiertekelesek/n);
end
