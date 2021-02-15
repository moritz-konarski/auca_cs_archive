figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "Cube of Cubes") %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1]) %Creating Axis
view(325,135)       %Tilting coordinate system
grid on             %turning on the grid in coordinate system
xlabel ("X-Axis")   %labeling the axis
ylabel ("Y-Axis")   %labeling the axis
zlabel ("Z-Axis")   %labeling the axis
title ("Block House")

%---------------changeable variables---------------------

l=1;                %length of side of one cube
n=4;                %number of cubes per side of big cube (whole numbers only)
t=1;                %line thickness of cubes

%---------------------------------------------------------

f=(n*l)-l;          %limit for loop repetition
S=0;                %for stacking the cubes
w=0;                %for stacking the cubes
h=0;                %for stacking the cubes

axis('equal',[-1 n*l+1 -1 n*l+1 -1 n*l+1]) %preparing coordinate system limits

for h=0:l:f         %shifting cubes in +z direction

 
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
    
    line([0+S+.25 0+S+.25],[l+w l+w],[-.25+l+h -.75+l+h], 'linewidth', [t])
    line([0+S+.75 0+S+.75],[l+w l+w],[-.25+l+h -.75+l+h], 'linewidth', [t])
    line([0+S+.25 0+S+.75],[l+w l+w],[-.25+l+h -.25+l+h], 'linewidth', [t])
    line([0+S+.25 0+S+.75],[l+w l+w],[-.75+l+h -.75+l+h], 'linewidth', [t])
  
    drawnow %drawing the cube that was just created into coordinate system
  
    endfor

  endfor
