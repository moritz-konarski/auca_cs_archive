%Aristotle's Wheel

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Aristotle's Wheel");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Aristotle's Wheel"];                                                    %preparing title string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
%a : ylabel ("y",'fontsize',[17]);                                              %labeling y axis
a : xlabel ("X",'fontsize',[17]);                                               %labeling x axis
axis('equal',[-1.5 7 -1.5 3.5]);
grid on;                                                                        %toggleling the grid in coordinate system
drawnow;                                                                        %drawing it now
axis('equal',[-1.5 7 -2.5 1.5]);

%h_ball=line(0,0,'maker','o', 'markersize', [1]);

h_Line=line(0,0,'color',[1 0 0],'linewidth',[3]);
h_Line2=line(0,0,'color',[0 1 0],'linewidth',[3]);
h_Line3=line(0,0,'color',[0 0 1],'linewidth',[3]);
t0=0;
for t=0:.1:2*pi+.1;
  
  x=sin(t);
  y=cos(t);
  
  set(h_Line,'xdata',[t x+t],'ydata',[0 y],'color',[1 0 0],'linewidth',[3]);
  set(h_Line2,'xdata',[t/2 (x+t)/2],'ydata',[-.5 y/2-.5],'color',[0 1 0],'linewidth',[3]);
  set(h_Line3,'xdata',[3*t/4 3/4*(x+t)],'ydata',[-.25 3/4*y-.25],'color',[0 0 1],'linewidth',[3]);
  
  drawnow;
  %line([x+t],[y],'marker', 'd','color',[1 0 0]);
  %line([(x+t)/2],[y/2-.5],'marker', 'd','color',[0 1 0]);
  %line([3/4*(x+t)],[3/4*y-.25],'marker', 'd','color',[0 0 1]);
  
  line([t0 t],[-1 -1],'color',[1 0 0],'linewidth',[3]);
  line([[t0/2 (t)/2]],[-2 -2],'color',[0 1 0],'linewidth',[3]);
  line([3*t0/4 3/4*(t)],[-1.5 -1.5],'color',[0 0 1],'linewidth',[3]);
    
  t0=t;
  
  
  drawnow;
endfor;