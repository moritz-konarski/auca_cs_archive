%electromagnetic oscillations, clockwise, 12.02.


%------creating figure-------------------------
figure('units','norm','position',[.1 .1 .8 .7],...
       'name', "Electromagnetic Oscillation");                                  %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = [ "Electromagnetic Wave-Polarized"];                                                %labeling diagram
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("E",'fontsize',[17]);                                               %labeling y axis
a : xlabel ("t",'fontsize',[17]);                                               %labeling x axis
a : zlabel ("B",'fontsize',[17]);                                               %labeling z axis
view(325,-35);
grid on;                                                                        %turing on the grid in coordinate system
drawnow;           

%-------variables----------------------------
c=1;                          %speed of light (no need to change)
T=3;                          %number of periods
i=.1;                        %interval of loop
x=0;

%--------calculations------------------------
xlim=2*pi*T+.1;
axis('equal',[0 xlim -1.5 1.5 -1.5 1.5]);                                       %setting limits
m_fe=-1;
e_fe=0;
Xe=0;
n=0;
line([0 xlim],[0 0]);

for t=0:i:xlim;
  
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
  
  if mod(n,1)==0;
  %line(x,[0 e_f],[0 m_f],'linewidth',[1]);
  line(x,[0 0],[0 m_f],'linewidth',[1],'color',[0 0 1]);
  line(x,[0 e_f],[0 0],'linewidth',[1],'color',[1 0 0]);
  endif
  n++;
  drawnow;
  
  Xe=x;
  e_fe=e_f;
  m_fe=m_f; 
    
endfor;








