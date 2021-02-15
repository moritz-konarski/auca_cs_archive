%Topic: Newtons 2nd Law, exemplified by projectile

%=====dialog box asking user for input========
input = inputdlg ({"Starting Velocity v0 (km/s)"},...
                   "Projectile Motion",[1,20],{"1"});                        %getting user imput
vx=v0=str2num(input{1});                                                        %velocity converted from user input

%=====preparing window========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");                                              %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Newtons 2nd Law - Satellite\nv0=" num2str(v0) "km/s"];                   %preparing  string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("X in 10^3 km",'fontsize',[17]);                                    %labeling y axis
a : ylabel ("Y in 10^3 km",'fontsize',[17]);                                    %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system

%=====setting initial conditions==============
x=x0=vy=0;                                    %setting intial values
y0=7.4;                                       %initializing y0 
y=7.4;                                        %setting y to starting position
dt=.02;                                       %setting interval
k=1;                                          %initializing k
axis('equal',[-10 10 -10 10]);                %setting axis limits
alpha=pi/2;
v0=v0*1000;

%=====drawing earth===========================
for fi=0:.01:2*pi;                            
X_earth(k)=6.4*cos(fi);
Y_earth(k)=6.4*sin(fi);
k=k+1;
endfor;
h_earth=line(X_earth,Y_earth,'linewidth',[5],'color','blue');                   %drawing earth

%=====declaring function for acceleration x===
function ax=funVX(x,y,v0,alpha);
  GMe=5.*10^(24)*6.67^(-11);                 %product of G and Me
  Rs=1000000*sqrt(x^2+y^2);                               %setting satellite radius
  ax=-GMe/(Rs^2);
endfunction;

%=====declaring function for velocity x=======
function Vx=funX(x,y,vx,alpha);
  Vx=vx;
endfunction;

%=====declaring function for acceleration y===
function ay=funVY(x,y,v0,alpha);
  GMe=5.*10^(24)*6.67^(-11);                 %product of G and Me
  Rs=1000000*sqrt(x^2+y^2);                               %setting satellite radius
  ay=-GMe/(Rs^2);
endfunction;

%=====declaring function for velocity y=======
function Vy=funY(x,y,vy,alpha);
  Vy=vy;
endfunction;

%=====loop for time progression and graphing==
for t=0:dt:1000;
  %=====X variable============================
  %---calculating k1---
  k1x=funX(x,y,vx,alpha);
  k1Vx=funVX(x,y,vx,alpha);
  %---calculating k1---
  k1y=funY(x,y,vy,alpha);
  k1Vy=funVY(x,y,vy,alpha);
  %---calculating k2---
  k2x=funX(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,alpha);
  k2Vx=funVX(x+k1x*dt/2,y+k1y*dt/2,v0,alpha);
  %---calculating k2---
  k2y=funY(x+k1x*dt/2,y+k1y*dt/2,vy+k1Vy*dt/2,alpha);
  k2Vy=funVY(x+k1x*dt/2,y+k1y*dt/2,v0,alpha);
  %---calculating k3---
  k3x=funX(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,alpha);
  k3Vx=funVX(x+k2x*dt/2,y+k2y*dt/2,v0,alpha);
  %---calculating k3---
  k3y=funY(x+k2x*dt/2,y+k2y*dt/2,vy+k2Vy*dt/2,alpha);
  k3Vy=funVY(x+k2x*dt/2,y+k2y*dt/2,v0,alpha);
  %---calculating k4---
  k4x=funX(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,alpha);
  k4Vx=funVX(x+k3x*dt,y+k3y*dt,v0,alpha);
  %---calculating k4---
  k4y=funY(x+k3x*dt,y+k3y*dt,vy+k3Vy*dt,alpha);
  k4Vy=funVY(x+k3x*dt,y+k3y*dt,v0,alpha);
  %=====Y variable============================
  
  %=====Calculating new variables=============
  %---calculating new x---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  
  %---calculating new vx---
  vx=vx+(k1Vx+2*k2Vx+2*k3Vx+k4Vx)*dt/6;
    
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
  
  %===Breack if satellite hits the ground=====
  if sqrt(x^2+y^2)<6400;
    break;
  endif;
  
  %=Breack if satellite leaves coordinatesystem
  if sqrt(x^2+y^2)>10000;
    break;
  endif;
  alpha=atan2(y,x);
endfor;

