function test_d
     figure(1);
                x = 1:1:10;
            [a] = DiscretePDF(x,'geometric',1/2); 
                subplot(1,2,1);
                plot(x,a,'b.');
                hold on;
                
              [b] = DiscreteCDF(x,'geometric',1/3);
                stairs(x,b,'b');
                title('Geometric - Us')

                
               [c] = geopdf(x,1/2);
                subplot(1,2,2);
                plot(x,c,'g.');
                hold on;
                
               [d] = geocdf(x,1/3);
                stairs(x,d,'g');  
                title('Geometric - MatLab')

               
                
                
                
        figure(2);
                x = 1:1:10;
            [a] = DiscretePDF(x,'pascal',[3,1/2]); 
                subplot(1,2,1);
                plot(x,a,'b.');
                hold on;
                
             [b] = DiscreteCDF(x,'pascal',[3,1/2]);
                stairs(x,b,'b');
                title('Pascal - Us')
 
              [c] = nbinpdf(x,3,1/2);
                subplot(1,2,2);
                plot(x,c,'g.');
                hold on;
                
              [d] = nbincdf(x,3,1/2);
                stairs(x,d,'g');
                title('Pascal - MatLab')

                
                
      figure(3);
                x = 1:1:10;
            [a] = DiscretePDF(x,'poisson',1/2); 
                subplot(1,2,1);
                plot(x,a,'b.');
                hold on;
                
              [b] = DiscreteCDF(x,'poisson',1/2);
                stairs(x,b,'b');
                title('Poisson - Us')

                
             [c] = poisspdf(x,1/2);
                subplot(1,2,2);
                plot(x,c,'g.');
                hold on;
                  
               [d] = poisscdf(x,1/2);
                stairs(x,d,'g');
                title('Poisson - MatLab')

                
            figure(4);
                x = 1:1:10;
            [a] = DiscretePDF(x,'hypergeometric',[20,11,10]); 
                subplot(1,2,1);
                plot(x,a,'b.');
                hold on;
               
                
              [b] = DiscreteCDF(x,'hypergeometric',[20,11,10]);
                stairs(x,b,'b');
                title('Hypergeometric - Us');

                
                [c] = hygepdf(x,20,11,10);
                subplot(1,2,2);
                plot(x,c,'g.');
                hold on; 
                
              [d] = hygecdf(x,20,11,10);
                stairs(x,d,'g');
                title('Hypergeometric - MatLab')

                
                
            figure(5);
                x = 1:1:10;
            [a] = DiscretePDF(x,'binomial',[10,1/2]); 
                subplot(1,2,1);
                plot(x,a,'b.');
                hold on;
                
             [b] = DiscreteCDF(x,'binomial',[10,1/2]);
                stairs(x,b,'b');
                title('Binomial - Us')

                
              [c] = binopdf(x,10,1/2);
                subplot(1,2,2);
                plot(x,c,'g.');
                hold on;
                
              [d] = binocdf(x,10,1/2);
                stairs(x,d,'g');
                title('Binomial - MatLab')
                
               

    figure(6);
                x = 1:0.001:10;
            [a] = ContinuousPDF(x,'normal',[0 3]); 
                subplot(1,2,1);
                plot(x,a,'g');
                hold on;
            [b] = ContinuousCDF(x,'normal',[0 3]);
                plot(x,b,'b')
                title('Normal - Us')

            [c] = normpdf(x,0,3);
                subplot(1,2,2);
                plot(x,c,'g');
                hold on;
            [d] = normcdf(x,0,3);
                plot(x,d,'b');
                title('Normal - MatLab');
                
           figure(7);
                 x = 1:0.001:10;
            [a] = ContinuousPDF(x,'exponential', 1/2); 
                subplot(1,2,1);
                plot(x,a,'g');
                hold on;
            [b] = ContinuousCDF(x,'exponential',1/2);
                plot(x,b,'b')
                title('Exponential - Us')

            [c] = exppdf(x,2);
                subplot(1,2,2);
                plot(x,c,'g');
                hold on;
            [d] = expcdf(x,2);
                plot(x,d,'b');
                title('Exponential - MatLab')

        figure(8);
                x = 1:0.001:10;
            [a] = ContinuousPDF(x,'gamma',[2 1]); 
                subplot(1,2,1);
                plot(x,a,'g');
                hold on;
            [b] = ContinuousCDF(x,'gamma',[2 1]);
                plot(x,b,'b')
                title('Gamma - Us')

            [c] = gampdf(x,2,1);
                subplot(1,2,2);
                plot(x,c,'g');
                hold on;
            [d] = gamcdf(x,2,1);
                plot(x,d,'b');
                title('Gamma - MatLab')
                
                
               figure(9);
                x = -4:0.001:4;
     
              [a] = ContinuousPDF(x,'student',2); 
                subplot(1,2,1);
                plot(x,a,'g');
                hold on;
                
            [b] = ContinuousCDF(x,'student',2);
                 plot(x,b,'b')
                title('Student - Us')
                
            [c] = tpdf(x,2);
                subplot(1,2,2);
                plot(x,c,'g');
                hold on;
                
            [d] = tcdf(x,2);
                plot(x,d,'b');
                title('Student - MatLab')
                
             figure(10);
             x = 0:0.001:1;
            [a] = ContinuousPDF(x,'beta',[2 5]); 
                subplot(1,2,1);
                plot(x,a,'g');
                hold on;
            [b] = ContinuousCDF(x,'beta',[2 5]);
                plot(x,b,'b');
                title('Beta - Us');

            [c] = betapdf(x,2,5);
                subplot(1,2,2);
                plot(x,c,'g');
                hold on;
            [d] = betacdf(x,2,5);
                plot(x,d,'b');
                title('Beta - MatLab');


         

end

