function [eperHuzas,csokiHuzas] = fagyi2(itNum)
    global_steps = 0; 

      for i=1:itNum
         vanillia=18.0;
         csoki=12.0;
         eper=20.0;
         osszdarabSzam=50.0;
         avg_steps=0;
         
         while (1)
            avg_steps=avg_steps+1;
            prob = [1:3 ; [ (vanillia/osszdarabSzam) , (csoki/osszdarabSzam) , (eper/osszdarabSzam)]];
            fagyiMinta = InversionBySequentialSearch( prob , 'LEcuyer' , 1 );
            osszdarabSzam=osszdarabSzam-1;

            if(fagyiMinta==1) %vanillias
                vanillia=vanillia-1;
            end
            
            if(fagyiMinta==2) %csokolades
                csoki=csoki-1;
            end
            
            if(fagyiMinta==3) %epres
                eper=eper-1;
                break;
            end
         end
         global_steps=global_steps+avg_steps;
    end
    
    eperHuzas=global_steps/itNum;
    
    %3csokis
    haromszorCsoki=0;
    
    for i=1:itNum
         vanillia=18.0;
         csoki=12.0;
         eper=20.0;
         osszdarabSzam=50.0;
         csokiDarab=0;
        
          for j=1:15
            prob = [1:3 ; [vanillia/osszdarabSzam , csoki/osszdarabSzam , eper/osszdarabSzam]];
            fagyiMinta = InversionBySequentialSearch( prob , 'LEcuyer' , 1 );
            osszdarabSzam=osszdarabSzam-1;

            if(fagyiMinta==1) %vanillias
                vanillia=vanillia-1;
            end
            
            if(fagyiMinta==2) %csokolades
                csoki=csoki-1;
                csokiDarab=csokiDarab+1;
            end
            
            if(fagyiMinta==3)%epres
                 eper=eper-1;
            end
          end
          
          if(csokiDarab==3)
              haromszorCsoki=haromszorCsoki+1;
          end       
    end
    
    csokiHuzas=haromszorCsoki/itNum;
    
end
