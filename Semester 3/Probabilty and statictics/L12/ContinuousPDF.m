function f=ContinuousPDF(x,tip,parameter)
x=sort(x);
n=length(x);
switch (tip)
    
   case 'GAMMA'
        a=parameter(1);
        a2=parameter(2);
        if(a<=0) 
            error('Hibas parameter!');
        end
        if(a2<=0) 
            error('Hibas parameter!');
        end
        if (x>=0)
            f=((1/(a2.^a.*gamma(a)).*x.^(a-1).*exp(-x/a2)));
        else
            f=zeros(1,n);
        end
    
   case 'BETA'
        a=parameter(1);
        a2=parameter(2);
        if (a<=0) 
            error('Hibas parameter!');
        end
        if (a2<=0) 
            error('Hibas parameter!');
        end
        if (x<=1)
            if (x>=0)
                f=(1/beta(a,a2).*x.^(a-1).*(1-x).^(a2-1));
            else
                f=zeros(1,n);
            end
        else
            f=zeros(1,n);
        end
        
    case 'STUDENT'
       a=parameter(1);
       if (a<1)
           error('Hibas parameter!');
       end
       f=((gamma((a+1)/2))/(sqrt(a*pi)*gamma(a/2))).*((1+((x.^2)./a)).^((-(a+1)/2)));
        
   case 'NORMAL'
        a=parameter(1);
        a2=parameter(2);
        if(a2<=0)
            error('Nem pozitiv!');
        end
        f=(1.0/sqrt(2.0*pi)/a2)*exp(-(x-a).^2/2.0/a2^2); 
  
end
end