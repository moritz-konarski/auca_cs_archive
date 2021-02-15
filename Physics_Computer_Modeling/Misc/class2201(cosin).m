%class 22.01.18

%------------preparation------------------------------------------------------------------------------------
figure('units','norm','position',[.1 .1 .8 .8],'color',[.9 .9 .9],'name', "Cube of Cubes") %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1]) %Creating Axis
grid on             %turing on the grid in coordinate system
xlabel ("X-Axis")   %labeling the axis
ylabel ("Y-Axis")   %labeling the axis
zlabel ("Z-Axis")   %labeling the axis
axis('equal',[0 4*pi -1.1 1.1])
%-----------------------------------------------------------------------------------------------------------

t=0;

%drawing cosin
for t=0:.01:4*pi
  x=t;
  y=cos(t);
  line(x,y,'marker','*')
  drawnow
endfor