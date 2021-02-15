
%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Aristotle's Wheel");                                            %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
txt = ["Aristotle's Wheel"];                                                    %preparing title string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
%a : ylabel ("y",'fontsize',[17]);                                              %labeling y axis
a : xlabel ("X",'fontsize',[17]);                                               %labeling x axis
grid on;                                                                       %toggleling the grid in coordinate system
axis('equal',[-1.5 7 -1.5 1.5]);                                                  %axis config
drawnow;                                           

r=1;
v = linspace(0,2*pi,100)'; 
circsx = r.*cos(v) + x; 
circsy = r.*sin(v) + y; 
plot(circsx,circsy); 
axis('equal',[-1.5 7 -1.5 3.5]);  