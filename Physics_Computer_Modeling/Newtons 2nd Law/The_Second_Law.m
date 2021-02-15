%Newtons 2nd Law

CHOICE = menu ('Choose Programm', 'Pendulum', 'Projectile Motion - Ideal',...
               'Projectile Motion - Real', 'Orbital Motion', ...
               'Magnetic Field - Orbit', 'Magnetic Field - Change');       %creating choices on menu

%using the menu output
                          
if (CHOICE == [1]);       
    
  Sim_Pendulum;               %calling on the function   
  
elseif (CHOICE == [2]);   

  Sim_Proj_Ideal;              %calling on the function 

elseif (CHOICE == [3]);   

  Sim_Proj_Real;              %calling on the function 

elseif (CHOICE == [4]);   

  Sim_Orbit;                  %calling on the function 

elseif (CHOICE == [5]);   

  Sim_Magn_Orbit;             %calling on the function 
  
elseif (CHOICE == [6]);   

  Sim_Magn_Change;            %calling on the function 

endif;