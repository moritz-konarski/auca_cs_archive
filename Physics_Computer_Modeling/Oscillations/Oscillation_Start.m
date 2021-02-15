%Oscillations

CHOICE = menu ('Choose Modulation', 'Everything', 'Amplitude','Frequency','Phase','Nice Picture','EM Wave','EM Wave-pol.', 'With dampening') %creating choices on menu

                          %using the menu output
                          
if (CHOICE == [1]);       %Amplitude
    
   Multiple_Input;        %calling on the function    

elseif  (CHOICE == [2]);  %Everything

   HarmOscillamplitude;   %calling on the function  

elseif  (CHOICE == [3]);  %Frequency

  HarmOscillfrequency;    %calling on the function  
  
elseif  (CHOICE == [4]);  %Phase

  HarmOscillphase;        %calling on the function  

elseif  (CHOICE == [5]);  %Phase

  NicePicture;        %calling on the function  

elseif  (CHOICE == [6]);  %Phase

  electro;        %calling on the function  
  
elseif  (CHOICE == [7]);  %Phase

  electropolarized;        %calling on the function  

else                      %Nice Picture

  abkling_osc;            %calling on the function

endif