figure('units','norm','position',[.1 .1 .8 .8],'color',[.9 .9 .9],'name', "Drawing Functions") %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1]) %Creating Axis
grid on             %turing on grid in coordinate system
xlabel ("X-Axis")   %labeling the axis
ylabel ("Y-Axis")   %labeling the axis
zlabel ("Z-Axis")   %labeling the axis
%------------creating the buttons---------------------------------------------------------------------------

subplot (2,3,1) 
drawnow
x = -7:0.01:7;
plot (x, sin (5*x));
grid on
xlabel ("t");
ylabel ("sin(5t)");
title ("y=sin(5t)");
axis('equal')
drawnow