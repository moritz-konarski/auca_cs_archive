%Projectile with bounce

%-------dialog bos asking user for input-----------
input = inputdlg ({"Number of Fireworks"},...
"Projectile Motion",[1,20],{"4"});                            %getting user imput
n0=str2double(input{1});                                      %number converted from user input

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Projectile Motion");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = [num2str(n) " Fireworks"];     %preparing amplitude string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("Y",'fontsize',[17]);                                          %labeling y axis
a : xlabel ("X",'fontsize',[17]);                                          %labeling x axis
a : zlabel ("Z",'fontsize',[17]);                                          %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system

%--------------constants-------------------------
g=9.81;                                                           %setting g
x0=y0=xs0=ys0=z0=0;                                               %initializing

%---------------limit calculation-----------------
axis('equal',[-10 10 0 6 -10 10]);                                      %setting axis limits
drawnow;                                                          %Drawing it now
h_proj=line(0,0,'marker','*','color',[1 0 0],'markerfacecolor',[1 0 0], 'markersize',[10]); %creating the projectile
drawnow;                                                          %Drawing the ball now

%--------the throw-------------------
for n=0:1:n0;                       %loop for the number of bounces
v0=rand(1);
fi=rand(.15,pi-.15);
%za=rand(0,

for t=0:.02:1000;                     %loop for drawing the throw
  
  %----modulated function------
  x=v0*cos(fi)*t;                  %calculating x value
  y=v0*sin(fi)*t-.5*g*t^2;            %calculating y value
  z=0;
  set(h_proj,'xdata',x,'ydata',y,'zdata',z);    %setting projectile there
  line([x0 x],[y0 y],[z0 z],'color',[1 0 0]);%drawing trail of projectile
  x0=x;                               %setting the values for next line draw
  y0=y;                               %setting the values for next line draw  
  z0=z;                               %setting the values for next line draw  
  if y<0;                             %checking to see if y<0 and loop should be stopped
    drawnow;
    break;                              %---
  endif;                                %---
  drawnow;                              %drawing what the loop created
endfor;

endfor;

