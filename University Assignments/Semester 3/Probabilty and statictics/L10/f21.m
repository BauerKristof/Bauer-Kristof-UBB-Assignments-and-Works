function f21()

X = [1195; 1197; 1202; 1193; 1195; 1196; 1195; 1197; 1202; 1194; 1196;1198; 1202; 1196; 1197; 1200; 1195];
Y = [1197; 1199; 1198; 1201; 1202; 1196; 1197; 1201; 1203; 1198; 1196;1197; 1203; 1199; 1196; 1204; 1199];
alpha = 0.03;
    
[ci_t, ci_delta, t_value, p_value, H] = TTest2D(X, Y, 0, alpha, 'both');
    
if(H==1)
        [ci_t, ci_delta, t_value, p_value, H1] = TTest2D(X, Y, 0, alpha, 'right');
            
        if(H1==1)
            disp("Az elso gep atlagosan nagyobbakat darabol darabol");
        else
            disp("A masodik gep atlagosan nagyobbakat darabol");
        end
else
    disp("Nincs kulonbseg a ket gep kozott");
end
