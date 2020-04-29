function f1()
    X = [1195; 1197; 1202; 1193; 1195; 1196; 1195; 1197; 1202; 1194; 1196;1198; 1202; 1196; 1197; 1200; 1195];
    Y = [1197; 1199; 1198; 1201; 1202; 1196; 1197; 1201; 1203; 1198; 1196;
1197; 1203; 1199; 1196; 1204; 1199];
    sigma1 = 2.8;
    sigma2 = 2.6;
    p = 0.03;
    
    [ci_u,ci_delta,u_value,p_value,H] = UTest2D(X, Y, sigma1, sigma2, p, 'both');
    
    if(H==1)
            [ci_u1,ci_delta1,u_value1,p_value1,H1] = UTest2D(X, Y, sigma1, sigma2, p, 'right');
            
            if(H1==1)
                disp("Az elso gep atlagosan nagyobbakat darabol darabol");
            else
                disp("A masodik gep atlagosan nagyobbakat darabol");
            end
    else
        disp("Nincs kulonbseg a ket gep kozott");
    end
end