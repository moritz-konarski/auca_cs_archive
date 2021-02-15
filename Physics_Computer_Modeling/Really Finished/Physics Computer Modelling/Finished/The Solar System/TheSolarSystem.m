%The Solar System

CHOICE = menu ('Choose how to diplay the solar system', 'Heliocentric','Geocentric','w/ Space Time','Mercure-Centric','Jupiter-Centric','Realistic')

                          %using the menu aooutput
if (CHOICE == [1]);       %Heliocentric
    
heliocentric;             %calling on the function           

elseif  (CHOICE == [2]);  %Geocentric

  geocentric;               %calling on the function  

elseif  (CHOICE == [3]);  %Heliocentric w/ Space Time

  spacetime;                %calling on the function  

elseif  (CHOICE == [4]);  %Mercure-Centric

  mercurecentric;           %calling on the function  

elseif  (CHOICE == [5]);  %Jupiter-Centric

  jupitercentric;           %calling on the function  

else;                     %realistic

  realistic;                %calling on the function  

endif