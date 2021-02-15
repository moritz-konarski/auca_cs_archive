%Class:
%%%Topic: Runge-Kutta-Method Template

%=====preparing window===========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Runge-Kutta");                                                  %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Runge-Kutta"];                                                          %preparing amplitude string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("Time",'fontsize',[17]);                                            %labeling y axis
a : ylabel ("Other",'fontsize',[17]);                                           %labeling x axis
axis('equal',[0 4*pi -3 3]);                                                    %setting the area of the coodinate system
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system

%=====setting initial conditions==============
dt=.05;                         %setting interval
t0=0;                           %initializing time
%x=x0=1;                        %setting x to starting position
%vx=v0=0;                       %setting initial velocity

%=====declaring function for a=========
function a=fun_a( );
  
  a= ;
     
endfunction;

%=====declaring function for b=========
function b=fun_b( );
  
  b= ;
  
endfunction;

%=====loop for time progression and graphing====
for t=0:dt:4*pi;
  
  %---calculating k1---
  k1=fun1(t,x,vx);
  k1Vx=fun2(t,x,vx);
  
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
  line([t0 t],[- -],'linewidth',[3]);               %line of x
  line([t0 t],[- -],'linewidth',[3],'color',"red"); %line of vx
    
  %---storing variables for line drawing---
  t0=t;
  x0=x;
  v0=vx;
    
  %---drawing line---
  drawnow;
  
endfor;