function [U,c]=GaussElim(A,b)
 n=length(A);
 U=A;
 c=b;
 
 for i=1:n-1
 
 %max elem kereses    
 segedMatrix=U(i:n,i:n);
 maxElem=max(abs(segedMatrix));
 [I, J] = find(abs(segedMatrix) == maxElem);
  I=I+i-1;
  J=J+i-1;
  %sorcsere
  U([i, I(1)],:) = U([I(1), i],:);
  c([I(1), i]) = c([i, I(1)]);
  

  %oszlopcsere
         U(:,[J(1) , i ]) = U(:,[ i , J(1)]);
  
          
%    for j = i+1 : n   
%             if U(j,i) == 0
%                  error('A matrix szingularis')
%             end
if maxElem==0 
    
    return
end
for j=i+1:n
   %behozzuk a nullakat
   oszt= U(j,i)/ U(i,i) ; %kulonbseg eloallitasa
   U(j,:) = U(j,:) - U(i,:) * oszt; %kivonjuk a matrix soraibol azt ami behozza a 0-akat 
   c(j) = c(j) - c(i) * oszt;% kivonjuk a b-bol is
   end
 end
end
