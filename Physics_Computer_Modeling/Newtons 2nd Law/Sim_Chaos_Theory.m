%Topic: Newtons 2nd Law, chaos theory

clear;                                                                          %resetting everything for good new start
%=====menu that lets user choose the mode of the programm=======================
CHOICE = menu ('Sigma, Rho, Beta', 'User Input', '20, 40, 16/3',...
               '5, 45, 8');                                                     %creating choices on menu
               
if CHOICE==1;                                                                   %showing input dialog only if user wants
%=====dialog box asking user for input==========================================
input = inputdlg ({"Enter the values for the simulation\nx", "\ny","\nz",...
                   "\nsigma","\nrho","\nbeta"},"Chaos Theory",[1,10;1,10;1,...
                   10;1,10;1,10;1,10],{"1","1","1","10","28","8/3"});           %getting user imput
endif;

%=====setting initial variables=================================================
dt=.005;                                                                        %interval of loop
limt=20000*dt;                                                                  %setting limit of loop

%=====creating figure===========================================================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");                                              %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis

%=====declaring functions=======================================================
%===============================================================================

%=====declaring functions for velocity x========================================
function Vx=funX(x,y,z,sigma,rho,beta);
  Vx=sigma*(y-x);                             %speed x
endfunction;

%=====declaring function for velocity y=========================================
function Vy=funY(x,y,z,sigma,rho,beta);
  Vy=x*(rho-z)-y;                             %speed y
endfunction;

%=====declaring function for velocity z=========================================
function Vz=funZ(x,y,z,sigma,rho,beta);
  Vz=x*y-beta*z;                              %speed z
endfunction;

%===creating the left plot window===============================================
%===============================================================================
subplot(1,2,1);

%===setting variables===
k=1;                                                            
x=1;                                                            
y=1;                                                            
z=1;                                                            
sigma=10;                                                       
rho=28;                                                         
beta=8/3; 

%===setting up the coordinate system============================================                                                 
txt = ["Newtons 2nd Law - Chaos Theory - Standard\nx=" num2str(x) " ; y=" num2str(y) ...
       " ; z=" num2str(z) "\nsigma=" num2str(sigma) " ; rho=" num2str(rho) " ; beta=" ...
       num2str(beta) ];                                                         %preparing  title, stating variables
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("X",'fontsize',[17]);                                               %labeling y axis
a : ylabel ("Y",'fontsize',[17]);                                               %labeling x axis
a : zlabel ("Z",'fontsize',[17]);                                               %labeling z axis
axis('equal',[-40 40 -40 40 -10 60]);                                           %setting axis limits
view(3);                                                                        %settig viewing angle
grid on;                                                                        %turning on the grid
drawnow;                                                                        %drawing the system

%=====loop for time progression and graphing====================================
for t=0:dt:limt;                                                                %loop from 0 to limit with interval dt
  
  %=====X + Y + Z variable====================
  %---calculating k1---
  k1x=funX(x,y,z,sigma,rho,beta);
  k1y=funY(x,y,z,sigma,rho,beta);
  k1z=funZ(x,y,z,sigma,rho,beta);
    
  %---calculating k2---
  k2x=funX(x+k1x*dt/2,y+k1y*dt/2,z+k1z*dt/2,sigma,rho,beta);
  k2y=funY(x+k1x*dt/2,y+k1y*dt/2,z+k1z*dt/2,sigma,rho,beta);
  k2z=funZ(x+k1x*dt/2,y+k1y*dt/2,z+k1z*dt/2,sigma,rho,beta);
  
  %---calculating k3---
  k3x=funX(x+k2x*dt/2,y+k2y*dt/2,z+k2z*dt/2,sigma,rho,beta);
  k3y=funY(x+k2x*dt/2,y+k2y*dt/2,z+k2z*dt/2,sigma,rho,beta);
  k3z=funZ(x+k2x*dt/2,y+k2y*dt/2,z+k2z*dt/2,sigma,rho,beta);

  %---calculating k4---
  k4x=funX(x+k3x*dt,y+k3y*dt,z+k3z*dt,sigma,rho,beta);
  k4y=funY(x+k3x*dt,y+k3y*dt,z+k3z*dt,sigma,rho,beta);
  k4z=funZ(x+k3x*dt,y+k3y*dt,z+k3z*dt,sigma,rho,beta);
  
  %---calculating new x & y & z---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  y=y+(k1y+2*k2y+2*k3y+k4y)*dt/6;
  z=z+(k1z+2*k2z+2*k3z+k4z)*dt/6;
  
  %==creating variable for line of y, x and z=
  X_path1(k)=x;
  Y_path1(k)=y;
  Z_path1(k)=z;
  k=k+1;
endfor;
h_path=line(X_path1,Y_path1,Z_path1,'linewidth',[1]);                           %drawing path
drawnow;                                                                        %really drawing path

%===creating the right plot window==============================================
%===============================================================================
subplot(1,2,2);
%===setting variables===
k=1;

if CHOICE==1;                                                                   %if user chose input, use it
  x=str2num(input{1});                                                          % x converted from user input
  y=str2num(input{2});                                                          % y converted from user input
  z=str2num(input{3});                                                          % z converted from user input
  sigma=str2num(input{4});                                                      %sigma converted from user input
  rho=str2num(input{5});                                                        %rho converted from user input
  beta=str2num(input{6});                                                       %beta converted from user input

elseif CHOICE==2;                                                               %if user chose 1 preset, use it
  x=1;
  y=1;
  z=1;
  sigma=20;
  rho=40;
  beta=16/3;

elseif CHOICE==3;                                                               %if user chose 2 preset, use it
  x=1;
  y=1;
  z=1;
  sigma=5;
  rho=45;
  beta=8,
endif;           

%===setting up the coordinate system============================================                                                   
txt = ["Newtons 2nd Law - Chaos Theory - User Input\nx=" num2str(x) " ; y=" num2str(y) ...
        " ; z=" num2str(z) "\nsigma=" num2str(sigma) " ; rho=" num2str(rho) " ; beta=" ...
        num2str(beta) ];                                                        %preparing  title, stating variables
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : xlabel ("X",'fontsize',[17]);                                               %labeling y axis
a : ylabel ("Y",'fontsize',[17]);                                               %labeling x axis
a : zlabel ("Z",'fontsize',[17]);                                               %labeling z axis
axis('equal',[-40 40 -40 40 -10 60]);                                           %setting axis limits
view(3);                                                                        %settig viewing angle
grid on;                                                                        %turning on the grid
drawnow;                                                                        %drawing the system

%=====loop for time progression and graphing====================================
for t=0:dt:limt;                                                                %loop from 0 to limit with interval dt
  
  %=====X + Y + Z variable====================
  %---calculating k1---
  k1x=funX(x,y,z,sigma,rho,beta);
  k1y=funY(x,y,z,sigma,rho,beta);
  k1z=funZ(x,y,z,sigma,rho,beta);
    
  %---calculating k2---
  k2x=funX(x+k1x*dt/2,y+k1y*dt/2,z+k1z*dt/2,sigma,rho,beta);
  k2y=funY(x+k1x*dt/2,y+k1y*dt/2,z+k1z*dt/2,sigma,rho,beta);
  k2z=funZ(x+k1x*dt/2,y+k1y*dt/2,z+k1z*dt/2,sigma,rho,beta);
  
  %---calculating k3---
  k3x=funX(x+k2x*dt/2,y+k2y*dt/2,z+k2z*dt/2,sigma,rho,beta);
  k3y=funY(x+k2x*dt/2,y+k2y*dt/2,z+k2z*dt/2,sigma,rho,beta);
  k3z=funZ(x+k2x*dt/2,y+k2y*dt/2,z+k2z*dt/2,sigma,rho,beta);

  %---calculating k4---
  k4x=funX(x+k3x*dt,y+k3y*dt,z+k3z*dt,sigma,rho,beta);
  k4y=funY(x+k3x*dt,y+k3y*dt,z+k3z*dt,sigma,rho,beta);
  k4z=funZ(x+k3x*dt,y+k3y*dt,z+k3z*dt,sigma,rho,beta);
  
  %---calculating new x & y & z---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  y=y+(k1y+2*k2y+2*k3y+k4y)*dt/6;
  z=z+(k1z+2*k2z+2*k3z+k4z)*dt/6;
  
  %==creating variable for line of y, x and z=
  X_path2(k)=x;
  Y_path2(k)=y;
  Z_path2(k)=z;
  k=k+1;
endfor;
h_path=line(X_path2,Y_path2,Z_path2,'linewidth',[1], 'color', 'blue');          %drawing path
drawnow;                                                                        %really drawing path