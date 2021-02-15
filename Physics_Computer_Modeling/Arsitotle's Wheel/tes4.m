%test of circle

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Aristotle's Wheel");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Aristotle's Wheel"];                                                    %preparing title string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
%a : ylabel ("y",'fontsize',[17]);                                              %labeling y axis
a : xlabel ("X",'fontsize',[17]);                                               %labeling x axis
%axis('equal',[-1.5 7 -1.5 3.5]);
%grid on;                                                                        %toggleling the grid in coordinate system
drawnow;                                                                        %drawing it now
%axis('equal',[-1.5 7 -2.5 1.5]);

y0=1;
x0=0;

h_Line1=line(0,0,'color',[1 0 0],'linewidth',[3]);
h_Line2=line(0,0,'color',[0 1 0],'linewidth',[3]);
h_Line3=line(0,0,'color',[0 0 1],'linewidth',[3]);
t0=0;
xd0=yd0=0;
for t=0:.5:2*pi;

  %clf;
  axis('equal',[-1.5 7 -5 1.5]);
  grid on;  
  drawnow
h_Line1=line(0,0);
h_Line2=line(0,0);
h_Line3=line(0,0);
  x=sin(t);
  y=cos(t);
  
  set(h_Line1,'xdata',[t x+t],'ydata',[0 y],'color',[1 0 0],'linewidth',[3]);
  
  set(h_Line2,'xdata',[t (x/2+t)],'ydata',[-3 y/2-3],'color',[0 1 0],'linewidth',[3]);
  
  set(h_Line3,'xdata',[t (3*x/4+t)],'ydata',[-1.75 3/4*y-1.75],'color',[0 0 1],'linewidth',[3]);
  
  t0=t;
  
  
  %drawnow;

for r=0:.3:2*pi+.1;
  
  xd=sin(r);
  yd=cos(r);
     
  line([xd0+t xd+t],[yd0 yd],'color',[1 0 0]);
  line([(xd0/2+t) (xd/2+t)],[yd0/2-3 yd/2-3],'color',[0 1 0]);
  line([(3*xd0/4+t) (3*xd/4+t)],[3*yd0/4-1.75 3*yd/4-1.75],'color',[0 0 1]);
  
  
  %drawnow;
  xd0=xd;
  yd0=yd;
endfor;
drawnow
%pause(.7);
endfor;