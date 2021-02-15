%------creating figure-------------------------
figure('units','norm','position',[.1 .1 .8 .7],...
       'name', "Electromagnetic Oscillation");                                  %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = [ "Electromagnetic Wave-Polarized"];    %labeling diagram
a : title (txt,'fontsize',[17]);              %titleing diagram
a : ylabel ("E",'fontsize',[17]);             %labeling y axis
a : xlabel ("t",'fontsize',[17]);             %labeling x axis
a : zlabel ("B",'fontsize',[17]);             %labeling z axis
view(325,-35);                                %setting view for 3d aspect
grid on;                                      %turing on the grid in coordinate system
drawnow;                                      %drawing this now

%-------variables----------------------------
c=1;                         %speed of light (no need to change)
T=3;                         %number of periods
i=.1;                        %interval of loop
x=0;                         %intializing x

%--------calculations------------------------
xlim=2*pi*T+.1;                              %calculating x limit
axis('equal',[0 xlim -1.5 1.5 -1.5 1.5]);    %setting limits
m_fe=-1;          %setting magnetic field
e_fe=0;           %setting electric field
Xe=0;             %initializing
n=0;              %initializing
line([0 xlim],[0 0]); %drawing a line where the center of the wave is

for t=0:i:xlim;     %loop for drawing the function
  
  x=c*t;
  
%----in y-plane--------
  e_f=sin(x);
  X=[x x];
  Ye=[0 e_f];
  Ze=[0 0];  
%----in z-plane--------
  m_f=sin(x-(pi/2));
  X=[x x];
  Ym=[0 0];
  Zm=[0 m_f];
%-----line of polarization---------
  Xl=[Xe x];
  Yl=[e_fe e_f];
  Zl=[m_fe m_f];
  line(Xl,Yl,Ze,'color',[1 0 0],'linewidth',[3]); %electric field (E)
  line(Xl,Ym,Zl,'color',[0 0 1],'linewidth',[3]); %magnetic field (M)
  line(Xl,Yl,Zl,'linewidth',[3]);                %polarization 

%drawing lines from waves to the central line
  line(x,[0 0],[0 m_f],'linewidth',[1],'color',[0 0 1]);
  line(x,[0 e_f],[0 0],'linewidth',[1],'color',[1 0 0]);
  drawnow;
  
  Xe=x;       %storing variable for nest line
  e_fe=e_f;   %storing variable for nest line
  m_fe=m_f;   %storing variable for nest line
    
endfor;








