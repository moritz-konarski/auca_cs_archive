%=====dialog box asking user for input========
input = inputdlg ({"Enter the values for the simulation\nvx", "\nB",...
                   "\nm","\nE","\nQ"},"Object in Magnetic Field",...
                   [1,10;1,10;1,10;1,10;1,10],{"2","1","1","1","2"});   %getting user imput
vx=str2num(input{1});  %velocity x converted from user input
B0=str2num(input{2});  %B converted from user input
m=str2num(input{3});   %m converted from user input
E0=str2num(input{4});  %E converted from user input
Q=str2num(input{5});   %Q converted from user input

%=====calculating variables==================
x=x0=0;     %initializing
y=y0=z0=0;  %initializing
vz=vy=z=0;  %initializing
dt=.02;     %interval
limt=1000;  %setting limit of loop

%=====preparing window========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");       %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);  %Creating Axis
txt = ["Newtons 2nd Law - Magnetic Field\nvx=" num2str(vx) " ; B=" num2str(B0) ...
       " ; m=" num2str(m) "\nE=" num2str(E0) " ; Q=" num2str(Q) " ; Q/m=" num2str(Q/m) ];  %preparing  title, stating variables
a : title (txt,'fontsize',[17]);     %titleing diagram
a : xlabel ("X",'fontsize',[17]);    %labeling y axis
a : ylabel ("Y",'fontsize',[17]);    %labeling x axis
a : zlabel ("Z",'fontsize',[17]);    %labeling z axis
grid on;                             %turing on the grid in coordinate system
axis('equal',[-1 26 -11 11 ]);       %setting axis limits based on radius of circle
h_center1=line(0,0,'marker','o', 'markersize',[10],'color','red',...
              'markerfacecolor','red'); %setting a ball to  center circle
drawnow;                                %drawing the system

%=====declaring function for acceleration x===
function ax=funVX(x,y,vx,vy,vz,B,Q,m,E);
  ax=(Q*vy*B)/(m);   %acceleration for x
endfunction;

%=====declaring function for velocity x=======
function Vx=funX(vx);
  Vx=vx;             %speed x
endfunction;

%=====declaring function for acceleration y===
function ay=funVY(x,y,vx,vy,vz,B,Q,m,E);
  ay=Q*(E-B*vx);     %acceleration for y +vy*B
endfunction;

%=====declaring function for velocity y=======
function Vy=funY(vy);
  Vy=vy;             %speed y
endfunction;

%=====declaring function for acceleration z===
function az=funVZ(x,y,vx,vy,vz,B,Q,m,E);
  az=0;              %acceleration for z E+
endfunction;

%=====declaring function for velocity z=======
function Vz=funZ(vz);
  Vz=vz;             %speed z
endfunction;

%=====loop for time progression and graphing==
for t=0:dt:limt;       %loop from 0 to limt with interval dt
  %---changing B and E periodically---
  B=B0*sin(t);
  E=E0*sin(t);
  %=====X + Y variable========================
  %---calculating k1---
  k1x=funX(vx);
  k1y=funY(vy);
  k1z=funZ(vz);
  k1Vx=funVX(x,y,vx,vy,vz,B,Q,m,E);
  k1Vy=funVY(x,y,vx,vy,vz,B,Q,m,E);
  k1Vz=funVZ(x,y,vx,vy,vz,B,Q,m,E);
  
  %---calculating k2---
  k2x=funX(vx+k1Vx*dt/2);
  k2y=funY(vy+k1Vy*dt/2);
  k2z=funZ(vz+k1Vz*dt/2);
  k2Vx=funVX(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,vy+k1Vy*dt/2,vz+k1Vy*dt/2,B,Q,m,E);
  k2Vy=funVY(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,vy+k1Vy*dt/2,vz+k1Vy*dt/2,B,Q,m,E);
  k2Vz=funVZ(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,vy+k1Vy*dt/2,vz+k1Vy*dt/2,B,Q,m,E);
  
  %---calculating k3---
  k3x=funX(vx+k2Vx*dt/2);
  k3y=funY(vy+k2Vy*dt/2);
  k3z=funZ(vz+k2Vz*dt/2);
  k3Vx=funVX(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,vy+k2Vy*dt/2,vz+k2Vy*dt/2,B,Q,m,E);
  k3Vy=funVY(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,vy+k2Vy*dt/2,vz+k2Vy*dt/2,B,Q,m,E);
  k3Vz=funVZ(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,vy+k2Vy*dt/2,vz+k2Vy*dt/2,B,Q,m,E);
  
  %---calculating k4---
  k4x=funX(vx+k3Vx*dt);
  k4y=funY(vy+k3Vy*dt);
  k4z=funZ(vz+k3Vz*dt);
  k4Vx=funVX(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,vy+k3Vy*dt,vz+k3Vy*dt,B,Q,m,E);
  k4Vy=funVY(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,vy+k3Vy*dt,vz+k3Vy*dt,B,Q,m,E);
  k4Vz=funVZ(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,vy+k3Vy*dt,vz+k3Vy*dt,B,Q,m,E);
  
  %---calculating new x & y---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  y=y+(k1y+2*k2y+2*k3y+k4y)*dt/6;
  z=z+(k1z+2*k2z+2*k3z+k4z)*dt/6;
  
  %---calculating new vx & vy---
  vx=vx+(k1Vx+2*k2Vx+2*k3Vx+k4Vx)*dt/6;
  vy=vy+(k1Vy+2*k2Vy+2*k3Vy+k4Vy)*dt/6;
  vz=vz+(k1Vz+2*k2Vz+2*k3Vz+k4Vz)*dt/6;

  %===creating line of y and x================
  line([x0  x],[y0 y],[z0 z],'linewidth',[2]);%line of x and y
  set(h_center1,'xdata',x,'ydata',y,'zdata',z);  %setting the ball to the center
  x0=x;                                       %storing x for next line
  y0=y;                                       %storing y for next line
  z0=z;                                       %storing z for next line
  drawnow;
  
  if x>25 | y>10 | y<-10;   %stops the loop if the ball leaves the coordinate system
    break;
    set(h_center1,'xdata',x,'ydata',y,'zdata',z);  %setting the ball to the center
  endif;
endfor;