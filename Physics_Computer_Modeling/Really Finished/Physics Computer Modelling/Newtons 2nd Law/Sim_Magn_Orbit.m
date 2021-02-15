%Topic: Newtons 2nd Law, exemplified by lorentz-force in magnetic field

%=====dialog box asking user for input========
input = inputdlg ({"Enter the values for the simulation\nvx", "\nvy","\nvz",...
                   "\nB","\nm","\nQ","\nw"},"Object in Magnetic Field",[1,10;1,10;1,...
                   10;1,10;1,10;1,10;1,10],{"0","1","0","1","1","1","0"});      %getting user imput
vx1=str2num(input{1});                                                          %velocity x converted from user input
vy1=str2num(input{2});                                                          %velocity y converted from user input
vz=str2num(input{3});                                                           %velocity z converted from user input
B0=str2num(input{4});                                                           %B converted from user input
m=str2num(input{5});                                                            %m converted from user input
Q=str2num(input{6});                                                            %Q converted from user input
w=str2num(input{7});                                                            %w converted from user input

%=====calculating variables================== 
x=x0=1;                                       %initializing
y=y0=z0=z=vx=0;                               %initializing
vy=sqrt(vx1^2+vy1^2);                         %calculating vy from both vx1 and vy1 for simplicity
r=abs((m*vy)/(Q*B0));                         %calculating radius of circle
dt=2*pi*r/500;                                %interval so that one full circle has 500 steps
limt=2*pi*r;                                  %setting limit of loop to stop after one full radius
tz=limt/vy;                                   %calculating time the movement takes
limz=vz*tz;                                   %calculating limit for z coordinate axis

%=====preparing window========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");                                              %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Newtons 2nd Law - Magnetic Field\nv0x=" num2str(vx1) "m/s ; v0y=" num2str(vy1) ...
        "m/s ; v0z=" num2str(vz) "\nm=" num2str(m) "kg ; Q=" num2str(Q) "C ; B=" ...
        num2str(B0) "T ; w=" num2str(w)];                                       %preparing  title, stating variables
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("X in m",'fontsize',[17]);                                          %labeling y axis
a : ylabel ("Y in m",'fontsize',[17]);                                          %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
axis('equal',[x-1 x+2*r+1 -r-1 r+1 0 2*limz+1]);                             %setting axis limits based on radius of circle
h_center=line(r+1,0,'marker','o', 'markersize',[15],'color','red',...
'markerfacecolor','red');                                                       %setting a ball to  center circle
if vz!=0;                                                                       %in case there is a z-velocity
  view(3);                                                                      %setting view to also see z movement 
  limt=limt*2;                                                                  %doubling length of loop
  a : zlabel ("Z in m",'fontsize',[17]);                                        %labeling z axis
endif;
drawnow;                                                                        %drawing the system

%=====declaring function for acceleration x===
function ax=funVX(x,y,vx,vy,B,Q,m);
  ax=(Q*vy*B)/(m);                            %acceleration for x
endfunction;

%=====declaring function for velocity x=======
function Vx=funX(vx);
  Vx=vx;                                      %speed x
endfunction;

%=====declaring function for acceleration y===
function ay=funVY(x,y,vx,vy,B,Q,m);
  ay=-(Q*vx*B)/(m);                           %%acceleration for y
endfunction;

%=====declaring function for velocity y=======
function Vy=funY(vy);
  Vy=vy;                                      %speed y
endfunction;

%=====declaring function for acceleration z===
function az=funVZ(vz);
  az=0;                                       %acceleration for z
endfunction;

%=====declaring function for velocity z=======
function Vz=funZ(vz);
  Vz=vz;                                      %speed z
endfunction;

%=====loop for time progression and graphing==
for t=0:dt:limt;                              %loop from 0 to limt with interval dt
  B=B0+sin(w*t);
  %=====X + Y variable========================
  %---calculating k1---
  k1x=funX(vx);
  k1y=funY(vy);
  k1z=funZ(vz);
  k1Vx=funVX(x,y,vx,vy,B,Q,m);
  k1Vy=funVY(x,y,vx,vy,B,Q,m);
  k1Vz=funVZ(vz);
  
  %---calculating k2---
  k2x=funX(vx+k1Vx*dt/2);
  k2y=funY(vy+k1Vy*dt/2);
  k2z=funZ(vz+k1Vz*dt/2);
  k2Vx=funVX(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,vy+k1Vy*dt/2,B,Q,m);
  k2Vy=funVY(x+k1x*dt/2,y+k1y*dt/2,vx+k1Vx*dt/2,vy+k1Vy*dt/2,B,Q,m);
  k2Vz=funVZ(vz+k1Vz*dt/2);
  
  %---calculating k3---
  k3x=funX(vx+k2Vx*dt/2);
  k3y=funY(vy+k2Vy*dt/2);
  k3z=funZ(vz+k2Vz*dt/2);
  k3Vx=funVX(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,vy+k2Vy*dt/2,B,Q,m);
  k3Vy=funVY(x+k2x*dt/2,y+k2y*dt/2,vx+k2Vx*dt/2,vy+k2Vy*dt/2,B,Q,m);
  k3Vz=funVZ(vz+k2Vz*dt/2);
  
  %---calculating k4---
  k4x=funX(vx+k3Vx*dt);
  k4y=funY(vy+k3Vy*dt);
  k4z=funZ(vz+k3Vz*dt);
  k4Vx=funVX(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,vy+k3Vy*dt,B,Q,m);
  k4Vy=funVY(x+k3x*dt,y+k3y*dt,vx+k3Vx*dt,vy+k3Vy*dt,B,Q,m);
  k4Vz=funVZ(vz+k3Vz*dt);
  
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
  set(h_center,'xdata',r+1,'ydata',0,'zdata',z);  %setting the ball to the center
  x0=x;                                       %storing x for next line
  y0=y;                                       %storing y for next line
  z0=z;                                       %storing z for next line
  drawnow;                                    %drawing line and ball
  
endfor;