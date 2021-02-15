%electromagnetic oscillations, clockwise, 12.02.


%------creating figure-------------------------
figure('units','norm','position',[.1 .1 .8 .7],...
       'name', "Electromagnetic Oscillation");                                  %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = [ "Electromagnetic Wave"];                                                %labeling diagram
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("y",'fontsize',[17]);                                               %labeling y axis
a : xlabel ("t",'fontsize',[17]);                                               %labeling x axis
a : zlabel ("z",'fontsize',[17]);                                               %labeling z axis
view(325,-35);                      %setting view to 3d
grid on;                                                                        %turing on the grid in coordinate system
drawnow;           

%-------variables----------------------------
c=1;                          %speed of light (no need to change)
T=3;                          %number of periods
i=.1;                         %interval of loop

%--------calculations------------------------
xlim=2*pi*T;                                    %calculating x limits
axis('equal',[0 xlim -1.5 1.5 -1.5 1.5]);       %setting limits

for t=0:i:xlim;
  
  x=c*t;
  
%----in y-plane--------
  e_f=sin(x);
  Xe=[x x];
  Ye=[0 e_f];
  Ze=[0 0];
  line(Xe,Ye,Ze,'marker','d','color',[1 0 0]); %drawing the line of the electric field

%----in z-plane--------
  m_f=sin(x);
  Xm=[x x];
  Ym=[0 0];
  Zm=[0 m_f];
  line(Xm,Ym,Zm,'marker','d','color',[0 0 1]); %drawing the line of the magnetic field
  
  drawnow;
  
endfor;








