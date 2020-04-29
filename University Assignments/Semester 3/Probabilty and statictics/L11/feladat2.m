function feladat2()
X=[6.8,7.4,7.2,7.5,6.4,6.9,7.1,6.9,7.0,6.8,7.3,6.5,7.2,7.5,7.6, 6.8,7.2,6.9,7.0,7.1];
Y=[6.8,7.2,6.7,7.0,6.8,7.2,6.8,7.1,6.8,6.7,7.0,6.7,6.8,6.9,7.1, 6.6,7.0,6.6,6.8,6.7];

%1
prob1=0.03;
[ci_f21, ci_lambda21, f_value21, p_value21, H1] = FTest2D(X, Y, prob1, 'both');
if (H1==0)
    disp("Nincs kulombseg a ket gep kozott");
    equality=1;
else
    disp("Van kulombseg a ket gep kozott");
    equality=0;
end

%2
prob2=0.04;
[ci_t22, ci_delta22, t_value22, p_value22, H2] = TTest2D(X, Y, equality, prob2, 'right');
if (H2==1)
    disp("Tobb selejtes termeket allit elo az elso");
else
    disp("Tobb selejtes termeket allit elo a masodik");
end

end

