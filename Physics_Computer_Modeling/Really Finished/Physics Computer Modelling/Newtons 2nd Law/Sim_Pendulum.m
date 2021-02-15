%Class: 28.02.18
%Topic: Newtons 2nd Law, exemplified by spring pendulum (oscillation)

%=====preparing window===========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");   %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);  %Creating Axis
txt = ["Newtons 2nd Law - Spring Pendulum\nBlack - Position ; Red - Velocity"];                                                      %preparing amplitude string
a : title (txt,'fontsize',[17]);      %titleing diagram
a : xlabel ("T in seconds",'fontsize',[17]);  %labeling y axis
a : ylabel ("X in meters",'fontsize',[17]);   %labeling x axis
axis('equal',[0 10 -3 3]);   %setting the area of the coodinate system
grid on;       %turing on the grid in coordinate system
drawnow;       %drawing the system

%=====setting initial conditions==============
t0=0;                           %initializing time
x=x0=1;                         %setting x to starting position
vx=v0=0;                        %setting initial velocity
dt=.05;                         %setting interval

%=====declaring function for acceleration=========
function ax=funVX(t,x,vx);
  
  k=1;                              %stiffness of spring
  m=1;                              %mass of weight
  a=.5;                            %coefficient of drag
  ax=-k*x/m;                        %acceleration
   
endfunction;

%=====declaring function for velocity=========
function Vx=funX(t,x,vx);
  
  Vx=vx;                        %velocity put into another place
  
endfunction;

%=====loop for time progression and graphing====
for t=0:dt:10;
  
  %---calculating k1---
  k1x=funX(t,x,vx);
  k1Vx=funVX(t,x,vx);
  %---calculating k2---
  k2x=funX(t+dt/2,x+k1x*dt/2,vx+k1Vx*dt/2);
  k2Vx=funVX(t+dt/2,x+k1x*dt/2,vx+k1Vx*dt/2);
  %---calculating k3---
  k3x=funX(t+dt/2,x+k2x*dt/2,vx+k2Vx*dt/2);
  k3Vx=funVX(t+dt/2,x+k2x*dt/2,vx+k2Vx*dt/2);
  %---calculating k4---
  k4x=funX(t+dt,x+k3x*dt,vx+k3Vx*dt);
  k4Vx=funVX(t+dt,x+k3x*dt,vx+k3Vx*dt);
  %---calculating new x---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  %---calculating new vx---
  vx=vx+(k1Vx+2*k2Vx+2*k3Vx+k4Vx)*dt/6;
  %---creating line of t and x---
  line([t0 t],[x0 x],'linewidth',[3]);                %line of x
  line([t0 t],[v0 vx],'linewidth',[3],'color',"red"); %line of vx
  %---storing variables for line drawing---
  t0=t;
  x0=x;
  v0=vx;
    
  %---drawing line---
  drawnow;
  
endfor;