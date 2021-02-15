%Projectile with bounce

%-------dialog bos asking user for input-----------
input = inputdlg ({"Starting Velocity v0 (>=2m/s)", "Angle fi (deg.)", "Number of Bounces"},...
"Projectile Motion",[1,20;1,20;1,20],{"10", "45","4"});                %getting user imput
v01=str2double(input{1});                                      %velocity converted from user input
fi0=str2double(input{2});                                     %agnle converted from user input
limn=str2double(input{3});
                                                  

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Projectile Motion");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = [ "Projectile Motion\nv0=" num2str(v01) "m/s ; fi=" num2str(fi0) "° ; " num2str(limn) " Bounces"];     %preparing amplitude string
a : title (txt,'fontsize',[17]);         %titleing diagram
a : ylabel ("Y in m",'fontsize',[17]);    %labeling y axis
a : xlabel ("X in m",'fontsize',[17]);    %labeling x axis
grid on;                                 %turing on the grid in coordinate system
drawnow;                                  %drawing the system

%--------------constants-------------------------
g=9.81;                       %setting g
x0=y0=xs0=ys0=xm=0;           %initializing
v0=v01*(1/.8);            %preparing v0 for the loop

%---------------limit calculation-----------------
fi=deg2rad(fi0);                                            %converting angle from degrees to rad
lxp1=((v01.^2.*sin(2.*fi))./g);                             %x-limit of first bounce
lxp=lxp1;                                                   %duplicating lxp for next loop
for nn=1:1:limn;                                            %calculating x-limit for n bounces
lxp=lxp+lxp1*.8^(2*nn);
endfor;
lxp=lxp*1.02;                                               %adding a bit of room
lyp=((v01.^2.*sin(fi).^2)/(2.*g)).*1.15;                    %calculating y limit
if v01<3;                                                   %correcting x-limit for small values 
  lxp=lxp*1.1;
endif;

axis('equal',[0 lxp 0 lyp]);                                      %setting axis limits
drawnow;                                                          %Drawing it now
h_proj=line(0,0,'marker','o','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[10]); %creating the projectile
drawnow;                                                          %Drawing the ball now

%--------the throw-------------------
for n=0:1:limn;                       %loop for the number of bounces
v0=.8*v0;                             %reducing v0 each bounce

for t=0:.02:1000;                     %loop for drawing the throw
  
  %----modulated function------
  x=v0*cos(fi)*t+xm;                  %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  set(h_proj,'xdata',x,'ydata',y);    %setting projectile there
  line([x0 x],[y0 y],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  
  if y<0;                             %checking to see if y<0 and loop should be stopped
    drawnow;
    xm=x;
    break;                              %---
  endif;                                %---
  drawnow;                              %drawing what the loop created
endfor;

endfor;





