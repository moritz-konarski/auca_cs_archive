%in class work 17.01.18

figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "House") %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1]) %Creating Axis
view(45,15) %Tilting coordinate system
grid on
axis('square')
xlabel ("X")
ylabel ("Y")
zlabel ("Z")

%creating house
X0=0; Y0=0; Z0=0; %defining zero varibles
W=5; h=3; %defining house dimensions
H=-h;
for Z0=0:h:50
%Base
X=[X0 X0+W]; Y=[Y0 Y0]; Z=[Z0 Z0] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates

X=[X0 X0+W]; Y=[Y0+W Y0+W]; Z=[Z0 Z0] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates

X=[X0 X0]; Y=[Y0 Y0+W]; Z=[Z0 Z0] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates

X=[X0+W X0+W]; Y=[Y0 Y0+W]; Z=[Z0 Z0] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates
H=H+3;
drawnow;
endfor

X=[X0 X0]; Y=[Y0 Y0]; Z=[0 0+H] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates
drawnow
X=[X0+W X0+W]; Y=[Y0 Y0]; Z=[0 0+H] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates
drawnow
X=[X0+W X0+W]; Y=[Y0+W Y0+W]; Z=[0 0+H] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates
drawnow
X=[X0 X0]; Y=[Y0+W Y0+W]; Z=[0 0+H] %defining new coordinates
line(X,Y,Z, 'linewidth' ,[3]) %drawing line with new coordinates
drawnow





























































































































































