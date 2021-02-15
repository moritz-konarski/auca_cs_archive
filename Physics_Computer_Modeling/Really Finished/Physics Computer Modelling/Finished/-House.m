%Created: 16.01.18
%Edited: 17.01.18
%Purpose: Homework

%creating Window and Axis
figure('units','norm','position',[.1 .1 .8 .7],'color',[1 1 1],'name', "House") %Creating Window
axes('position',[.1 .1 .8 .8],'color',[.9 .9 .9]) %Creating Axis
view(315,135) %Tilting coordinate system
grid on %Turnig on Grid
a = axis('square', [-2 12 -2 8 -2 10]) %Squaring it up and setting limits
a = xlabel ("X") %labeling axis
a = ylabel ("Y") %labeling axis
a = zlabel ("Z") %labeling axis
a = title ("House") %labeling diagram

%drawing lines to create house

line([0 10],[6 6],[0 0],'linewidth',[2]) %Drawing Foundation
line([10 10],[0 6],[0 0],'linewidth',[2]) %Drawing Foundation
line([0 10],[0 0],[0 0],'linewidth',[2]) %Drawing Foundation
line([0 0],[0 6],[0 0],'linewidth',[2]) %Drawing Foundation
drawnow
line([10 10],[0 0],[0 5],'linewidth',[2]) %Drawing Walls
line([10 10],[6 6],[0 5],'linewidth',[2]) %Drawing Walls
line([0 0],[6 6],[0 5],'linewidth',[2]) %Drawing Walls
line([0 0],[0 0],[0 5],'linewidth',[2]) %Drawing Walls
drawnow
line([10 10],[.7 .7],[0 4],'linewidth',[2]) %Drawing Door
line([10 10],[2.7 2.7],[0 4],'linewidth',[2]) %Drawing Door
line([10 10],[.7 2.7],[4 4],'linewidth',[2]) %Drawing Door
drawnow
line([10 10],[5.5 5.5],[2 4],'linewidth',[2]) %Drawing Window by Door
line([10 10],[3.5 5.5],[2 2],'linewidth',[2]) %Drawing Window by Door
line([10 10],[3.5 5.5],[4 4],'linewidth',[2]) %Drawing Window by Door
line([10 10],[3.5 3.5],[2 4],'linewidth',[2]) %Drawing Window by Door
drawnow
line([0 0],[0 6],[5 5],'linewidth',[2]) %Drawing Ceiling
line([10 10],[0 6],[5 5],'linewidth',[2]) %Drawing Ceiling
drawnow
line([10 0],[3 3],[8 8],'linewidth',[2]) %Drawing roof
line([10 10],[-1 3],[4 8],'linewidth',[2]) %Drawing roof
line([10 10],[7 3],[4 8],'linewidth',[2]) %Drawing roof
line([0 0],[7 3],[4 8],'linewidth',[2]) %Drawing roof
line([0 0],[-1 3],[4 8],'linewidth',[2]) %Drawing roof
line([10 0],[-1 -1],[4 4],'linewidth',[2]) %Drawing roof
line([10 0],[7 7],[4 4],'linewidth',[2]) %Drawing roof
drawnow
line([8.5 1.5],[6 6],[4 4],'linewidth',[2]) %Drawing Window by Door
line([8.5 8.5],[6 6],[2 4],'linewidth',[2]) %Drawing Window by Door
line([1.5 1.5],[6 6],[2 4],'linewidth',[2]) %Drawing Window by Door
line([1.5 8.5],[6 6],[2 2],'linewidth',[2]) %Drawing Window by Door
drawnow