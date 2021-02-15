%Created: 15.01.2018
%Edited: 
%Purpose: First Try; First Lesson

figure('units','norm','position',[.25 .25 .5 .5],'color',[1 1 1])  %Creating Window
axes('position',[.15 .15 .7 .7],'color',[.9 .9 .9]) %Creating Axis
view(45,45) %Tilting coordinate system
grid on %Turnig on Grid
line([-5 1],[0 1],[0 1],'color',[0 0 0]) %Drawing Line through points
axis('square') %Squaring it up