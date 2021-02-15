%Topic: Newtons 2nd Law, exemplified by projectile

%=====dialog box asking user for input========
input = inputdlg ({"Starting Velocity v0", "Angle fi (deg.)", ...
                   "Coefficient of Drag"},"Projectile Motion",...
                   [1,20;1,20;1,20],{"10", "45", ".005"});                       %getting user imput
v0=str2num(input{1});                                                           %velocity converted from user input
fi0=str2num(input{2});                                                          %angle converted from user input
alpha=str2num(input{3});                                                        %coef. of drag converted from user input

%=====preparing window========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");                                              %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Newtons 2nd Law - Projectile Motion\nv0=" num2str(v0) ...
       "m/s ; fi=" num2str(fi0) "° ; alpha=" num2str(alpha)];                   %preparing amplitude string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("X in meters",'fontsize',[17]);                                     %labeling y axis
a : ylabel ("Y in meters",'fontsize',[17]);                                     %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system

%=====setting initial conditions==============
x=x0=y0=y=0;                                  %setting x/y to starting position
g=9.81;                                       %setting g
%dt=.02;                                       %setting interval

%=====calculating initial values==============
fi=deg2rad(fi0);                              %converting angle from degrees to rad
vx=cos(fi)*v0;                                %calculating x-component of vector
vy=sin(fi)*v0;                                %calculating y-component of vector

%=====calculating limits======================
lxp=((v0.^2.*sin(2.*fi))./g)*1.02;            %x-limit of first bounce
lyp=((v0.^2.*sin(fi).^2)/(2.*g)).*1.15;       %calculating y limit
axis('equal',[0 lxp 0 lyp]);                  %setting axis limits
line([lxp/1.02 lxp/1.02],[0 lyp],'color',...   
      "red",'linewidth',[1.5]);               %drawing line at idealized end of trajectory
drawnow;                                      %Drawing it now
limit_t=lxp/vx;                               %calculating limit of loop
dt=limit_t/500;
if limit_t<3;                                 %setting more accurate parameters for low v0's
  limit_t=3;
  dt=.01;
endif;

%=====declaring function for acceleration x===
function ax=funVX(t,x,vx,alpha);
  m=1;
  ax=-alpha*vx^2/(2*m);                             %influence of drag
endfunction;

%=====declaring function for velocity x=======
function Vx=funX(t,x,vx,alpha);
  Vx=vx;
endfunction;

%=====declaring function for acceleration y===
function ay=funVY(t,y,vy,alpha);
  m=1;
  ay=-9.81-alpha*vy^2/(2*m);                        %influence of gravity and drag
endfunction;

%=====declaring function for velocity y=======
function Vy=funY(t,y,vy,alpha);
  Vy=vy;                  
endfunction;

%=====loop for time progression and graphing==
for t=0:dt:limit_t;
  
  %=====X variable============================
  %---calculating k1---
  k1x=funX(t,x,vx,alpha);
  k1Vx=funVX(t,x,vx,alpha);
  %---calculating k2---
  k2x=funX(t+dt/2,x+k1x*dt/2,vx+k1Vx*dt/2,alpha);
  k2Vx=funVX(t+dt/2,x+k1x*dt/2,vx+k1Vx*dt/2,alpha);
  %---calculating k3---
  k3x=funX(t+dt/2,x+k2x*dt/2,vx+k2Vx*dt/2,alpha);
  k3Vx=funVX(t+dt/2,x+k2x*dt/2,vx+k2Vx*dt/2,alpha);
  %---calculating k4---
  k4x=funX(t+dt,x+k3x*dt,vx+k3Vx*dt,alpha);
  k4Vx=funVX(t+dt,x+k3x*dt,vx+k3Vx*dt,alpha);
  %---calculating new x---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  %---calculating new vx---
  vx=vx+(k1Vx+2*k2Vx+2*k3Vx+k4Vx)*dt/6;
  
  %=====Y variable============================
  %---calculating k1---
  k1y=funY(t,y,vy,alpha);
  k1Vy=funVY(t,y,vy,alpha);
  %---calculating k2---
  k2y=funY(t+dt/2,y+k1y*dt/2,vy+k1Vy*dt/2,alpha);
  k2Vy=funVY(t+dt/2,y+k1y*dt/2,vy+k1Vy*dt/2,alpha);
  %---calculating k3---
  k3y=funY(t+dt/2,y+k2y*dt/2,vy+k2Vy*dt/2,alpha);
  k3Vy=funVY(t+dt/2,y+k2y*dt/2,vy+k2Vy*dt/2,alpha);
  %---calculating k4---
  k4y=funY(t+dt,y+k3y*dt,vy+k3Vy*dt,alpha);
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
  
  %===Breack if projectile hits the ground====
  if y<0;
    break;
  endif;
    
endfor;