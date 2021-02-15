%Projectile without bounce

%-------dialog bos asking user for input-----------
input = inputdlg ({"Starting Velocity v0 (m/s)", "Angle fi (deg.)"},...
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
x0=y0=xs0=ys0=0;                                                  %initializing

%---------------limit calculation-----------------
fi=fi0/(360/(2*pi));
lxp=((v0.^2.*sin(2.*fi))./g).*1.15;                               %calculating x limit
if lxp<11.8;
  lxp=11.9;
endif;

lyp=((v0.^2.*sin(fi).^2)/(2.*g)).*1.15;                           %calculating y limit
if lyp<2.6;
  lyp=2.7;
endif;

axis('equal',[0 lxp 0 lyp]);                                      %setting axis limits
drawnow;                                                          %Drawing it now
h_proj=line(0,0,'marker','o','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[10]); %creating the projectile
drawnow;                                                          %Drawing the ball now

for t=0:.02:1000;                     %loop for drawing the throw
  
  %----modulated function------
  x=v0*cos(fi)*t;                     %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  set(h_proj,'xdata',x,'ydata',y);    %setting projectile there
  line([x0 x],[y0 y],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  

  %----standard function----------
  xs=10*cos(pi/4)*t;                  %calculating x value
  ys=10*sin(pi/4)*t-.5*g*t^2;         %calculating y value
  line([xs0 xs],[ys0 ys]);            %drawing trail of projectile
  xs0=xs;                             %setting the values for next line draw
  ys0=ys;                             %setting the values for next line draw  
  
  if y<0 & ys<0;                      %checking to see if y<0 and loop should be stopped
    drawnow;
  break;                              %---
endif;                                %---
drawnow;                              %drawing what the loop created
endfor;