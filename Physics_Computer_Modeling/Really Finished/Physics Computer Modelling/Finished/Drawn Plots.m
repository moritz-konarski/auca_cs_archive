%homework for 24.01.18

%------------preparation------------------------------------------------------------------------------------  
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],'name', "Drawing Functions") %Creating Window
axes('position',[.1 .1 .8 .8],'color',[1 1 1]) %Creating Axis
grid on                   %turing on grid in coordinate system
xlabel ("X-Axis")         %labeling the axis
ylabel ("Y-Axis")         %labeling the axis
zlabel ("Z-Axis")         %labeling the axis

%---Sinus function------------------------------------------------------------------------------------------
subplot (2,3,1);          %create plot
drawnow;                  %draw this plot
x = -2*pi:0.01:2*pi;      %set x limits
plot (x, sin (5*x));      %plot the function
grid on;                  %turn on the grid
xlabel ("t");             %label x axis
ylabel ("sin(5t)");       %label y axis
title ("y=sin(5t)");      %label plot
axis('equal');            %set axis to equal proportions
drawnow;
%---e-function----------------------------------------------------------------------------------------------
subplot (2,3,2);          %See Sinus Function for more info
drawnow;
x = -2:0.01:2;
plot (x, e.^(-4*x.^(2)));
grid on;
xlabel ("t");
ylabel ("e(-4t^2)");
title ("y=e(-4t^2)");
axis('equal');
drawnow;

%---Root function-------------------------------------------------------------------------------------------
subplot (2,3,3);          %See Sinus Function for more info
drawnow;
x = -1:0.01:1;
plot (x, 1./(sqrt(1-x.^(2))));
grid on;
xlabel ("t");
ylabel ("1/(sqrt(1-t^2))");
title ("y=1/(sqrt(1-t^2))");
axis('equal');
drawnow;

%---Arctan function-----------------------------------------------------------------------------------------
subplot (2,3,4);          %See Sinus Function for more info
drawnow;
x = -7:0.01:7;
plot (x, atan(x));
grid on;
xlabel ("t");
ylabel ("arctan(x)");
title ("y=arctan(x)");
axis('equal');
drawnow;

%---Curve of second order-----------------------------------------------------------------------------------
subplot (2,3,5);          %See Sinus Function for more info
drawnow;
x = -7:0.5:7;
plot (x, 3.*x.^2+2.*x+1);
grid on;
xlabel ("t");
ylabel ("3t^2+2t+1");
title ("y=3t^2+2t+1");
ylimit ([-7 50]);
axis('equal');
drawnow;






















