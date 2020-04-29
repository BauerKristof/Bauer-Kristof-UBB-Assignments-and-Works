function [Y,new_initial_value] = URealRNG(initial_value,generator_type,alpha,beta,n)

switch(generator_type)
    case{'URNG1',1}
        m=2^31-1;
        [Y,new_initial_value]=URNG1(initial_value,n);
        Y=Y./(m-1);
      case{'URNG2',2}
        m=2^31-1;
        [Y,new_initial_value]=URNG2(initial_value,n);
        Y=Y./(m-1);
        
        case {'ULEcuyerRNG',3}
            Y = ULEcuyerRNG(1,n);
        
end

Y=alpha + Y.*(beta-alpha);
end