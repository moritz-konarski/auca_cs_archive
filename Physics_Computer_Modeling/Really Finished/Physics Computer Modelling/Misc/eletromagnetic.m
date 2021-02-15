%electromagnetic oscillations, 12.02.

figure('units','norm','position',[.1 .1 .8 .7],...
       'name', "Electromagnetic Oscillation");                               %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12],'xlim',[0 20], 'ylim', [-1.5 1.5], 'zlim', [-1.5 1.5]);             %Creating Axis
%txt = [ "Modulation\ny=" num2str(A) "*e^-" num2str(d) "*t*sin(" num2str(w) "*t+" num2str(fi) ")"];  %preparing amplitude string
%a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("y",'fontsize',[17]);                                               %labeling y axis
a : xlabel ("t",'fontsize',[17]); 
a : zlabel ("z",'fontsize',[17]);    
a : ylim ([-1.5 1.5]);                                          %labeling x axis
view(3);
%axis('equal');
grid on;                                                                        %turing on the grid in coordinate system
drawnow;           

c=1;
for t=0:.1:20;
  
  x=c*t;
%----in y-plane--------
  e_f=sin(x);
  Xe=[x x];
  Ye=[0 e_f];
  Ze=[0 0];
  line(Xe,Ye,Ze,'marker','d','color',[1 0 0]);

%----in z-plane--------
  m_f=sin(x);
  Xm=[x x];
  Ym=[0 0];
  Zm=[0 m_f];
  line(Xm,Ym,Zm,'marker','d','color',[0 0 1]);  
  drawnow;
endfor;