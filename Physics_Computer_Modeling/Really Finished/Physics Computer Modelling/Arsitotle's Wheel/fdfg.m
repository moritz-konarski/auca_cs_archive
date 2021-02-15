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

y0=1;
x0=0;

h_c=line([0 0],[0 0]);

 
  plot([x^2=y^2-1]);
