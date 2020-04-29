function test(n)
%[X1, X2] = Marsagila(n);
%plot(X1,X2,'b.');
%figure;
%hist3([X1', X2']);


[Y] = Korrelalt(-0.79,7,2,16,1,n);
plot(Y(1, :), Y(2, :), 'r.');
figure;
hist3(Y');
end
