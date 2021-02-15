clear;    %clearing variables for good fresh start
%=====dialog box asking user for input========
input1 = inputdlg ({"Enter the values for the simulation\nUa (voltage for acceleration)"},...
                    "CRT",[1,10],{"1"}); %getting user input
Ua=str2num(input1{1});     %voltage for acceleration of the electron

%=====initializing variables================== 
x=x0=0;               %initializing
y=y0=vy=0;            %initializing
z=z0=vz=0;            %initializing
e=1.602176*10^(-19);  %charge of an electron
me=9.109381*10^(-31); %mass of an electron
%---must be l<2*d---
d=.75;                %setting space between the plates of the capacitor
l=1.2;                %setting length of the capacitor

%===calculating variables===
vx=sqrt((2*Ua*e)/(me));               %calculating vx
U_max=(d^2*me*vx^2)/(e*l^2);          %calculating maximal voltage to not hit the capacitors
U_max_hit=.98*(10*d*me*vx^2)/(2*l*e*(10-l)+e*l^2); %calculating the U max while hitting the screen
U_max_str=[ "(U<=|" num2str(round(100*U_max)/100) ...
          "|)\nTo hit the screen U<=|" ...
          num2str(round(10000*U_max_hit)/10000) ...
          "|\nTo hit the corner, leave the set values"]; %preparing string stating the limits
dt=10/(vx*400);   %interval so that one full loop has 400 steps
limt=11/vx;       %setting limit of loop 

%===second user input===
input2 = inputdlg ({["Enter the values for the simulation\nUy " U_max_str ""],...
          ["\nUz " U_max_str ""]},"CRT",...
          [1,10;1,10],{ [ U_max_hit ] , [ U_max_hit ] }); %getting user input2
Uy=str2num(input2{1});          %Voltage for y-capacitor
Uz=str2num(input2{2});          %Voltage for z-capacitor

%=====preparing window========================
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Newtons 2nd Law");                                   %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);  %Creating Axis
txt = ["Newtons 2nd Law - Cathode Ray Tube\nUa=" num2str(Ua) " V ; Uy=" num2str(Uy) ...
        "V ; Uz=" num2str(Uz) " V\nvx=" num2str(round(vx)) " m/s"]; %preparing  title, stating variables
a : title (txt,'fontsize',[17]);     %titleing diagram
a : xlabel ("X",'fontsize',[17]);    %labeling y axis
a : ylabel ("Y",'fontsize',[17]);    %labeling x axis
a : zlabel ("Z",'fontsize',[17]);    %labeling z axis
grid on;                             %turing on the grid
axis('equal',[-1 10.1 -6 6 -6 6]);   %setting axis limits
view(3);                             %setting the view to 3d
drawnow;       %drawing the system
%===drawing screen===
line([10 10],[-5 5],[5 5],'linewidth',[3]);
line([10 10],[-5 5],[-5 -5],'linewidth',[3]);
line([10 10],[5 5],[-5 5],'linewidth',[3]);
line([10 10],[-5 -5],[-5 5],'linewidth',[3]);
line([10 10],[0 0],[-5 5],'linewidth',[1]);
line([10 10],[-5 5],[0 0],'linewidth',[1]);
%===drawing the two capacitors===
sl=d/2;     %getting lenght of sides from space between plates
line([0 0],[-sl sl],[sl sl],'linewidth',[2]);
line([0 0],[-sl sl],[-sl -sl],'linewidth',[2]);
line([0 0],[sl sl],[-sl sl],'linewidth',[2]);
line([0 0],[-sl -sl],[-sl sl],'linewidth',[2]);
line([l l],[-sl sl],[sl sl],'linewidth',[2]);
line([l l],[-sl sl],[-sl -sl],'linewidth',[2]);
line([l l],[sl sl],[-sl sl],'linewidth',[2]);
line([l l],[-sl -sl],[-sl sl],'linewidth',[2]);
line([0 l],[-sl -sl],[sl sl],'linewidth',[2]);
line([0 l],[-sl -sl],[-sl -sl],'linewidth',[2]);
line([0 l],[sl sl],[-sl -sl],'linewidth',[2]);
line([0 l],[sl sl],[sl sl],'linewidth',[2]);
%===drawing the electron===
h_electron=line(0,0,'marker','o', 'markersize',[5],'color','blue',...
'markerfacecolor','blue');    %creating an electron
drawnow;       %drawing the system

%=====declaring function for acceleration x===
function ax=funVX(Uy,Uz,e,me,d,lock);
  ax=0;       %acceleration for x
endfunction;

%=====declaring function for velocity x=======
function Vx=funX(vx);
  Vx=vx;     %speed x
endfunction;

%=====declaring function for acceleration y===
function ay=funVY(Uy,Uz,e,me,d);
  ay=(Uy*e)/(d*me);    %acceleration for y
endfunction;

%=====declaring function for velocity y=======
function Vy=funY(vy);
  Vy=vy;       %speed y
endfunction;

%=====declaring function for acceleration z===
function az=funVZ(Uy,Uz,e,me,d);
  az=(Uz*e)/(d*me);    %acceleration for z
endfunction;

%=====declaring function for velocity z=======
function Vz=funZ(vz);
  Vz=vz;     %speed z
endfunction;

%=====loop for time progression and graphing==
for t=0:dt:limt;                              %loop from 0 to limt with interval dt
  %=====X + Y variable========================
  %---calculating k1---
  k1x=funX(vx);
  k1y=funY(vy);
  k1z=funZ(vz);
  k1Vx=funVX(Uy,Uz,e,me,d);
  k1Vy=funVY(Uy,Uz,e,me,d);
  k1Vz=funVZ(Uy,Uz,e,me,d);
  
  %---calculating k2---
  k2x=funX(vx+k1Vx*dt/2);
  k2y=funY(vy+k1Vy*dt/2);
  k2z=funZ(vz+k1Vz*dt/2);
  k2Vx=funVX(Uy,Uz,e,me,d);
  k2Vy=funVY(Uy,Uz,e,me,d);
  k2Vz=funVZ(Uy,Uz,e,me,d);
  
  %---calculating k3---
  k3x=funX(vx+k2Vx*dt/2);
  k3y=funY(vy+k2Vy*dt/2);
  k3z=funZ(vz+k2Vz*dt/2);
  k3Vx=funVX(Uy,Uz,e,me,d);
  k3Vy=funVY(Uy,Uz,e,me,d);
  k3Vz=funVZ(Uy,Uz,e,me,d);
  
  %---calculating k4---
  k4x=funX(vx+k3Vx*dt);
  k4y=funY(vy+k3Vy*dt);
  k4z=funZ(vz+k3Vz*dt);
  k4Vx=funVX(Uy,Uz,e,me,d);
  k4Vy=funVY(Uy,Uz,e,me,d);
  k4Vz=funVZ(Uy,Uz,e,me,d);
  
  %---calculating new x & y---
  x=x+(k1x+2*k2x+2*k3x+k4x)*dt/6;
  y=y+(k1y+2*k2y+2*k3y+k4y)*dt/6;
  z=z+(k1z+2*k2z+2*k3z+k4z)*dt/6;
  
  %---calculating new vx & vy---
  vx=vx+(k1Vx+2*k2Vx+2*k3Vx+k4Vx)*dt/6;
  vy=vy+(k1Vy+2*k2Vy+2*k3Vy+k4Vy)*dt/6;
  vz=vz+(k1Vz+2*k2Vz+2*k3Vz+k4Vz)*dt/6;

  %===creating line of y and x================
  line([x0  x],[y0 y],[z0 z],'linewidth',[2],'color',"blue");%line of x and y
  set(h_electron,'xdata',x,'ydata',y,'zdata',z);  %setting the electron to its position
  x0=x;                                       %storing x for next line
  y0=y;                                       %storing y for next line
  z0=z;                                       %storing z for next line
  drawnow;                                    %drawing line and electron
  
  if x>l;    %setting voltages to 0 when electron leaves the capacitor
    Uy=Uz=0;
  endif;
  if x>10;   %stopping loop when screen is hit
    break;
    set(h_electron,'xdata',x,'ydata',y,'zdata',z);  %setting the electron to the position
  endif;
endfor;