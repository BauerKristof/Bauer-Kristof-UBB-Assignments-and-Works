function GaussElimSolve(A,b)
    n = length(b);
    display(n);
    rang = rank(A);
    display(rang);
    [U,c] = GaussElim(A,b)
    display(c);
    
        if(rang == n)
        x = UTriangSolve(U,c);
        display("A rendszer megoldasa:");
        display(x);
        else
       
       if(rang<n)
           for i=rang+1:n
                 if c(i)~=0        
                 display("A rendszer osszeferhetetlen");
                 return;
                 end
           end
          display("A rendszer osszeferheto hatarozatlan");
       end

end

