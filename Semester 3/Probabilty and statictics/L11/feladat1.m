function feladat1()
X=[253,251,250,252,248,251,252,250,250,248,247,250,251,253,249, 250,250,246,249,246,252,248];
prob=0.06;
value=3.0;

[ci_chi21, ci_std1, chi2_value1, p_value1, H] = Chi2Test(X, value,prob, 'right');
if (H==1)
       disp("Meghaladja 3 grammot");
else
    disp("Nem haladja meg");
end
end

