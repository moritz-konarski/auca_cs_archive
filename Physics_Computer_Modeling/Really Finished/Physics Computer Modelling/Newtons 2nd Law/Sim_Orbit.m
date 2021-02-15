%Topic: Newtons 2nd Law, exemplified by projectile

%=====dialog box asking user for input========
input = inputdlg ({"Starting Velocity v0", "Coefficient of Drag", "Y0 in 10^6m"},...
                   "Projectile Motion",[1,20;1,20;1,20],{"1000","0.00005","7.4"});  %getting user imput
vx=str2num(input{1});                                                           %velocity converted from user input
alph=str2num(input{2});                                                         %drag converted from user input
y=y0=10^6*str2num(input{3});                                                    %drag converted from user input

%=====preparing window========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");                                              %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Newtons 2nd Law - Satellite\nv0=" num2str(vx) ...
        "m/s ; alpha=" num2str(alph) " ; y0=" num2str(y0) "m"];                 %preparing  title
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("X in m",'fontsize',[17]);                                          %labeling y axis
a : ylabel ("Y in m",'fontsize',[17]);                                          %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
axis('equal',[(-4/3)*y0 (4/3)*y0 (-4/3)*y0 (4/3)*y0]);                          %setting axis limits
drawnow;                                                                        %drawing the system

%=====initializing variables==================
x=x0=vy=n=0;                                    %initializing                                
k=1;                                          %k for circle drawing
dt=10;                                        %interval

%=====drawing earth===========================
for fi=0:.01:2*pi;                            %calculating points of circle
X_earth(k)=6.4*10^6*cos(fi);
Y_earth(k)=6.4*10^6*sin(fi);
k=k+1;
endfor;
h_earth=line(X_earth,Y_earth,'linewidth',...
        [5],'color','blue');                  %drawing earth

%=====declaring function for acceleration x===
function ax=funVX(x,y,vx,vy,alph);
  Me=5.97.*10.^(24);                          %initializing mass of earth
  G=6.67.*10.^(-11);                          %initializing G
  Rs=sqrt(x.^2+y.^2);                         %calculating satellite radius
  f1x=G*Me./Rs.^2;                            %Gravity towards earth
  f2x=-x*f1x./Rs;                             %getting the x part of gravity
  ax=f2x-alph*vx;                             %calculating acceleration with drag
endfunction;

%=====declaring function for velocity x=======
function Vx=funX(vx);
  Vx=vx;
endfunction;

%=====declaring function for acceleration y===
function ay=funVY(x,y,vx,vy,alph);
  Me=5.97.*10.^(24);                          %initializing mass of earth
  G=6.67.*10.^(-11);                          %initializing G
  Rs=sqrt(x.^2+y.^2);                         %calculating satellite radius
  f1y=G*Me./Rs.^2;                            %Gravity towards earth
  f2y=-y*f1y./Rs;                             %getting the y part of gravity
  ay=f2y-alph*vy;                             %calculating acceleration with drag
endfunction;

%=====declaring function for velocity y=======
function Vy=funY(vy);
  Vy=vy;                  
endfunction;

%=====loop for time progression and graphing==
for t=0:dt:100000;
  
  %=====X + Y variable========================
  %---calculating k1---
  k1x=funX(vx);
  k1y=funY(vy);
  k1Vx=funVX(x,y,vx,vy,alph);
  k1Vy=funVY(x,y,vx,vy,alph);
  
  %---calculating k2---
  k2x=funX(vx+k1Vx*dt/2);
  k2y=funY(vy+k1Vy*dt/2);
  k2Vx=funVX(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,vy+k1Vy*dt/2,alph);
  k2Vy=funVY(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,vy+k1Vy*dt/2,alph);
  
  %---calculating k3---
  k3x=funX(vx+k2Vx*dt/2);
  k3y=funY(vy+k2Vy*dt/2);
  k3Vx=funVX(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,vy+k2Vy*dt/2,alph);
  k3Vy=funVY(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,vy+k2Vy*dt/2,alph);
  
  %---calculating k4---
  k4x=funX(vx+k3Vx*dt);
  k4y=funY(vy+k3Vy*dt);
  k4Vx=funVX(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,vy+k3Vy*dt,alph);
  k4Vy=funVY(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,vy+k3Vy*dt,alph);
  
  %---calculating new x & y---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  y=y+(k1y+2*k2y+2*k3y+k4y)*dt/6;
  
  %---calculating new vx & vy---
  vx=vx+(k1Vx+2*k2Vx+2*k3Vx+k4Vx)*dt/6;
  vy=vy+(k1Vy+2*k2Vy+2*k3Vy+k4Vy)*dt/6;

  %===creating line of y and x================
  line([x0  x],[y0 y],'linewidth',[2]);        %line of x and y
  x0=x;
  y0=y; 
  drawnow;
  
  %===Breack if projectile hits the ground====
  if sqrt(x.^2+y.^2)<6.4*10^6;
    break;
  endif;
  
  if x<3*10^6 && x>0;
    n=n+1;
  endif;
  
  if alph==0 && n>60 && x>0 && y>0;
    break;    
  endif;
endfor;