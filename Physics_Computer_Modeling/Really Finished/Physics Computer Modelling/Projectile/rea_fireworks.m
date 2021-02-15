%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Fireworks");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[.2 .3 .3],'fontsize',[12]);  %Creating Axis
txt = ["Fireworks"];     %preparing amplitude string
a : title (txt,'fontsize',[17]);  %titleing diagram
grid on;                          %turing on the grid in coordinate system
view(3);                          %setting view to 3d
axis ('equal',[-5 5 -5 5 0 12]);                   %setting aspect ration and limits
drawnow;                          %drawing this

%---initial variables---
x0=0;
z0=0;

%---first section of fireworks---
%---drawing projectile---
h_proj=line(0,0,0,'marker','o','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[13]); %creating the projectile
drawnow;                          %drawing this
%---loop---
for z=0:.05:6;    %moving firework upwards
  set(h_proj,'zdata',z);            %setting the projectile to the position
  line(0,0,[z0 z],'color','red','linewidth',[3]);   %drawing the trail
  drawnow;                          %drawing this
  z0=z;                             %storing z for next line
endfor;
set(h_proj,'markersize',[0]); %making first projectile disappear

%---second section of fireworks---
%---drawing projectiles---
h_proj1=line(0,0,6,'marker','o','color',[1 1 0],'markerfacecolor',[1 1 0], 'markersize',[9]); %creating the projectile
h_proj2=line(0,0,6,'marker','o','color',[1 0 1],'markerfacecolor',[1 0 1], 'markersize',[9]); %creating the projectile
h_proj3=line(0,0,6,'marker','o','color',[0 0 1],'markerfacecolor',[0 0 1], 'markersize',[9]); %creating the projectile
h_proj4=line(0,0,6,'marker','o','color',[1 1 1],'markerfacecolor',[1 1 1], 'markersize',[9]); %creating the projectile
h_proj5=line(0,0,6,'marker','o','color',[1 .5 1],'markerfacecolor',[1 .5 1], 'markersize',[9]); %creating the projectile
drawnow;                          %drawing this
%---loop---
for x=0:.07:6;    %moving fireworks like a throw in different directions
  %calculating z value for throw
  z=10*x-.5*9.81*x^2+6;            
  %projectile 1 
  set(h_proj1,'xdata',x,'ydata',x,'zdata',z);            %setting the projectile to the position
  line([x0 x],[x0 x],[z0 z],'color',[1 1 0],'linewidth',[2]);   %drawing the trail
  %projectile 2 
  set(h_proj2,'xdata',x,'ydata',0,'zdata',z);            %setting the projectile to the position
  line([x0 x],0,[z0 z],'color',[1 0 1],'linewidth',[2]);   %drawing the trail
  %projectile 3 
  set(h_proj3,'xdata',-x,'ydata',-.9*x,'zdata',z);            %setting the projectile to the position
  line([-x0 -x],[-.9*x0 -.9*x],[z0 z],'color',[0 0 1],'linewidth',[2]);   %drawing the trail
  %projectile 4 
  set(h_proj4,'xdata',x,'ydata',-.5*x,'zdata',z);            %setting the projectile to the position
  line([x0 x],[-.5*x0 -.5*x],[z0 z],'color',[1 1 1],'linewidth',[2]);   %drawing the trail
  %projectile 5 
  set(h_proj5,'xdata',-x,'ydata',x,'zdata',z);            %setting the projectile to the position
  line([-x0 -x],[x0 x],[z0 z],'color',[1 .5 1],'linewidth',[2]);   %drawing the trail
  %drawing
  drawnow;                          %drawing this
  x0=x;                             %storing x for next line
  y0=y;                             %storing y for next line
  z0=z;                             %storing z for next line
  if z<0;
    break;
  endif;
endfor;



















