

%-------dialog bos asking user for input-----------
input = inputdlg ({"Number of Fireworks"},...
"Projectile Motion",[1,20],{"3"});                %getting user imput
limn=str2double(input{1});                           %number converted from user input

figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Fireworks");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[.1 .1 .1],'fontsize',[12]);             %Creating Axis
txt = [ "Fireworks"];     %preparing amplitude string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
grid on;                                                                        %turing on the grid in coordinate system
drawnow;    

x0=y0=z0=y=0;
v0=10;
fi=pi/3;
g=9.81;
a0=45;
a=deg2rad(a0);

h_proj=line(0,0,'marker','*','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[10]); %creating the projectile

for n=0:1:limn;

for t=0:.03:1000;                     %loop for drawing the throw
  
  x=v0*cos(fi)*t;                     %calculating x value
  z=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  y=tan(n*a)*x;
  set(h_proj,'xdata',x,'ydata',y,'zdata',z);    %setting projectile there
  line([x0 x],[y0 y],[z0 z],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw 
  z0=z; 
  
  if z<0;                               %checking to see if y<0 and loop should be stopped
    drawnow;                            %draw the projectile 
    break;                              %---
    x0=y0=z0=0;
    drawnow;
  endif;                                %---
  
  drawnow;                              %drawing what the loop created
  
endfor;

endfor;