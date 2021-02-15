%Projectile with bounce

%-------dialog bos asking user for input-----------
input = inputdlg ({"Starting Velocity v0 (>1m/s)", "Angle fi (deg.)"},...
"Projectile Motion",[1,20;1,20],{"10", "45"});                %getting user imput
v0=str2double(input{1});                                      %velocity converted from user input
fi0=str2double(input{2});                                     %agnle converted from user input
                                                  

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Projectile Motion");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = [ "Projectile Motion\nv0=" num2str(v0) "m/s ; fi=" num2str(fi0) "°"];     %preparing amplitude string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("Y in m",'fontsize',[17]);                                          %labeling y axis
a : xlabel ("X in m",'fontsize',[17]);                                          %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system

%--------------constants-------------------------
g=9.81;                                                           %setting g
x0=y0=xb=0;                                                       %initializing

%---------------limit calculation-----------------
fi=fi0/(360/(2*pi));
lxp=2.7*((v0.^2.*sin(2.*fi))./g);                                %calculating x limit
lyp=((v0.^2.*sin(fi).^2)/(2.*g)).*1.15;                           %calculating y limit
axis('equal',[0 lxp 0 lyp]);                                      %setting axis limits
drawnow;                                                          %Drawing it now
in=200/lxp;
h_proj=line(0,0,'marker','o','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[10]); %creating the projectile
drawnow;                                                          %Drawing the ball now

%------------bounce 0-----------------
for t=0:.03:1000;                     %loop for drawing the throw
  
  x=v0*cos(fi)*t;                     %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  set(h_proj,'xdata',x,'ydata',y);    %setting projectile there
  line([x0 x],[y0 y],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  
if y<0;                               %checking to see if y<0 and loop should be stopped
  xb=x;                               %Getting x to puch next bounce
  drawnow;                            %draw the projectile 
  break;                              %---
endif;                                %---
drawnow;                              %drawing what the loop created
endfor;

%-------------bounce 1----------------
v0=.8*v0;
for t=0:.03:1000;                     %loop for drawing the throw
  
  x=v0*cos(fi)*t+xb;                     %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  set(h_proj,'xdata',x,'ydata',y);    %setting projectile there
  line([x0 x],[y0 y],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  
if y<0;                               %checking to see if y<0 and loop should be stopped
  xb=x;                               %Getting x to puch next bounce
  drawnow;                            %draw the projectile 
  break;                              %---
endif;                                %---
drawnow;                              %drawing what the loop created
endfor;

%----------------------bounce 2-------
v0=.8*v0;
for t=0:.03:1000;                     %loop for drawing the throw
  
  x=v0*cos(fi)*t+xb;                  %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  set(h_proj,'xdata',x,'ydata',y);    %setting projectile there
  line([x0 x],[y0 y],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  
if y<0;                               %checking to see if y<0 and loop should be stopped
  xb=x;                               %Getting x to puch next bounce
  drawnow;                            %draw the projectile 
  break;                              %---
endif;                                %---
drawnow;                              %drawing what the loop created
endfor;

%---------------bounce 3--------------
v0=.8*v0;
for t=0:.03:1000;                     %loop for drawing the throw
  
  x=v0*cos(fi)*t+xb;                  %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  set(h_proj,'xdata',x,'ydata',y);    %setting projectile there
  line([x0 x],[y0 y],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  
if y<0;                               %checking to see if y<0 and loop should be stopped
  xb=x;                               %Getting x to puch next bounce
  drawnow;                            %draw the projectile 
  break;                              %---
endif;                                %---
drawnow;                              %drawing what the loop created
endfor;

%------------------bounce 4--------------------------
v0=.8*v0;
for t=0:.03:1000;                     %loop for drawing the throw
  
  x=v0*cos(fi)*t+xb;                  %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  set(h_proj,'xdata',x,'ydata',y);    %setting projectile there
  line([x0 x],[y0 y],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  
if y<0;                               %checking to see if y<0 and loop should be stopped
  xb=x;                               %Getting x to puch next bounce
  drawnow;                            %draw the projectile 
  break;                              %---
endif;                                %---
drawnow;                              %drawing what the loop created
endfor;

