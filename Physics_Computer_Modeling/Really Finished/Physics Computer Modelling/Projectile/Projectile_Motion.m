%Projectile Motion

CHOICE = menu ('Choose Motion', 'Without Bounce', 'With Bounce', 'Fireworks', 'Cycloid'); %creating choices on menu

                          %using the menu output
                          
if (CHOICE == [1]);       %with bounce
    
   promowo;        %calling on the function   
  
elseif (CHOICE == [2]);       %without bounce
    
   promowio;        %calling on the function    
   
elseif (CHOICE == [4]);       %without bounce
    
   fwit;        %calling on the function    

else;                     %fireworks

   fireworks;   %calling on the function  

endif;