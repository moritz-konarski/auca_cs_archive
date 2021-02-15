%Topic: Newtons 2nd Law, exemplified by projectile

%=====dialog box asking user for input========
input = inputdlg ({"Starting Velocity v0"},...
                   "Projectile Motion",[1,20],{"1000"});           %getting user imput
vx=v0=str2num(input{1});                                                           %velocity converted from user input

%=====preparing window========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");                                              %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Newtons 2nd Law - Satellite\nv0=" num2str(v0) "m/s"];                  %preparing  string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("X in 10^3 km",'fontsize',[17]);                                         %labeling y axis
a : ylabel ("Y in 10^3 km",'fontsize',[17]);                                         %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system

%=====setting initial conditions==============
Me=5.97*10^24;                                  %setting mass of earth
Re=6400;                                      %setting radius of earth
G=6.67*10^(-11);                              %setting G
GMe=Me*G;                                     %getting new single constant
Rs=Re+1000;                                   %setting satellite radius
x=x0=vy=0;                                       %setting intial values
y0=7.4;
y=7.4;                                        %setting y to starting position
dt=.02;                                       %setting interval
k=1;                                          %initializing k
axis('equal',[-10 10 -10 10]);                %setting axis limits
vy=0;
alpha=pi/2;

%=====drawing earth===========================
for fi=0:.01:2*pi;                            
X_earth(k)=6.4*cos(fi);
Y_earth(k)=6.4*sin(fi);
k=k+1;
endfor;
h_earth=line(X_earth,Y_earth,'linewidth',[5],'color','blue');                   %drawing earth

%=====declaring function for acceleration x===
function ax=funVX(t,x,vx,alpha,y);
  GMe=5.*10^24*6.67*10^(-11);                 %product of G and Me
  Rs=6400000+1000000;                               %setting satellite radius
  ax=-abs(cos(alpha))*GMe/((Rs^2));
endfunction;

%=====declaring function for velocity x=======
function Vx=funX(t,x,vx,alpha,v0);
  Vx=vx;
endfunction;

%=====declaring function for acceleration y===
function ay=funVY(t,y,vy,alpha);
  GMe=5.*10^24*6.67*10^(-11);                 %product of G and Me
  Rs=6400000+1000000;                               %setting satellite radius
  ay=-abs(sin(alpha))*GMe/((Rs^2));
endfunction;

%=====declaring function for velocity y=======
function Vy=funY(t,y,vy,alpha,v0);
  Vy=vy;                  
endfunction;

%=====loop for time progression and graphing==
for t=0:dt:10000;
  %=====X variable============================
  %---calculating k1---
  k1x=funX(t,x,vx,alpha,v0);
  k1Vx=funVX(t,x,vx,alpha,y);
  %---calculating k2---
  k2x=funX(t+dt/2,x+k1x*dt/2,vx+k1Vx*dt/2,alpha,v0);
  k2Vx=funVX(t+dt/2,x+k1x*dt/2,vx+k1Vx*dt/2,alpha,y);
  %---calculating k3---
  k3x=funX(t+dt/2,x+k2x*dt/2,vx+k2Vx*dt/2,alpha,v0);
  k3Vx=funVX(t+dt/2,x+k2x*dt/2,vx+k2Vx*dt/2,alpha,y);
  %---calculating k4---
  k4x=funX(t+dt,x+k3x*dt,vx+k3Vx*dt,alpha,v0);
  k4Vx=funVX(t+dt,x+k3x*dt,vx+k3Vx*dt,alpha,y);
  %---calculating new x---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6000;
  %---calculating new vx---
  vx=vx+(k1Vx+2*k2Vx+2*k3Vx+k4Vx)*dt/6;
  
  %=====Y variable============================
  %---calculating k1---
  k1y=funY(t,y,vy,alpha,v0);
  k1Vy=funVY(t,y,vy,alpha);
  %---calculating k2---
  k2y=funY(t+dt/2,y+k1y*dt/2,vy+k1Vy*dt/2,alpha,v0);
  k2Vy=funVY(t+dt/2,y+k1y*dt/2,vy+k1Vy*dt/2,alpha);
  %---calculating k3---
  k3y=funY(t+dt/2,y+k2y*dt/2,vy+k2Vy*dt/2,alpha,v0);
  k3Vy=funVY(t+dt/2,y+k2y*dt/2,vy+k2Vy*dt/2,alpha);
  %---calculating k4---
  k4y=funY(t+dt,y+k3y*dt,vy+k3Vy*dt,alpha,v0);
  k4Vy=funVY(t+dt,y+k3y*dt,vy+k3Vy*dt,alpha);
  %---calculating new y---
  y=y+(k1y+2*k2y+2*k3y+k4y)*dt/6;
  %---calculating new vy---
  vy=vy+(k1Vy+2*k2Vy+2*k3Vy+k4Vy)*dt/6;

  %===creating line of y and x================
  line([x0 x],[y0 y],'linewidth',[2]);        %line of x and y
  %---storing variables for next line---------
  x0=x;
  y0=y; 
  %---drawing line----------------------------
  drawnow;
  alpha=atan2(y,x);
  %===Breack if projectile hits the ground====
  if sqrt(x^2+y^2)<6.4;
    break;
  endif;
    
  if sqrt(x^2+y^2)>104;
    break;
  endif;  
endfor;