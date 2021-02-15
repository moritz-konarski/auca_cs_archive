%homework for 22.01.18
%stacking cubes

figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "Cube of Cubes") %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1]) %Creating Axis
view(325,135)       %Tilting coordinate system
grid on             %turing on the grid in coordinate system
xlabel ("X-Axis")   %labeling the axis
ylabel ("Y-Axis")   %labeling the axis
zlabel ("Z-Axis")   %labeling the axis

%---------------changeable variables---------------------

l=1;                %length of side of one cube
n=4;                %number of cubes per side of big cube (whole numbers only)
t=1;                %line thickness of cubes

%---------------------------------------------------------

f=(n*l)-l;          %limit for loop repitition
S=0;                %for stacking the cubes
w=0;                %for stacking the cubes
h=0;                %for stacking the cubes

axis('equal',[-1 n*l+1 -1 n*l+1 -1 n*l+1]) %preparing coordinate system limits

for h=0:l:f         %shifting cubes in +z direction

  for w=0:l:f       %shifting cubes in +y direction
  
    for S=0:l:f     %shifting cubes in +x direction
      
    %--------------drawing one cube----------------------
    
    line([l+S l+S],[0+w l+w],[0+h 0+h], 'linewidth', [t])
    line([0+S 0+S],[0+w l+w],[0+h 0+h], 'linewidth', [t])
    line([0+S l+S],[0+w 0+w],[0+h 0+h], 'linewidth', [t])
    line([0+S l+S],[l+w l+w],[0+h 0+h], 'linewidth', [t])
    line([l+S l+S],[0+w l+w],[l+h l+h], 'linewidth', [t])
    line([0+S 0+S],[0+w l+w],[l+h l+h], 'linewidth', [t])
    line([0+S l+S],[0+w 0+w],[l+h l+h], 'linewidth', [t])
    line([0+S l+S],[l+w l+w],[l+h l+h], 'linewidth', [t])
    line([0+S 0+S],[0+w 0+w],[0+h l+h], 'linewidth', [t])
    line([0+S 0+S],[l+w l+w],[0+h l+h], 'linewidth', [t])
    line([l+S l+S],[0+w 0+w],[0+h l+h], 'linewidth', [t])
    line([l+S l+S],[l+w l+w],[0+h l+h], 'linewidth', [t])
  
    drawnow %drawing the cube that was just created into coodinate system
  
    endfor

  endfor

endfor