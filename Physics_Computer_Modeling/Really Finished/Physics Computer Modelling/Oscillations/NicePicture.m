%class 05.02.
%Harmonic Oscillation

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Nice Picture");                                       %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);   %Creating Axis
a : title ("Nice Picture",'fontsize',[17]);                           %titleing diagram
a : ylabel ("y",'fontsize',[17]);                                     %labeling y axis
a : xlabel ("x",'fontsize',[17]);                                     %labeling x axis
grid on;                                                              %turing on the grid in coordinate system
drawnow;                                                              %drawing the coodinate system

%---------------changeable variables---------------------
A1=1;                             %Amplitude y
A2=1;                             %Amplitude x
w1=5;                             %frequency for y
w2=7;                             %frequency for x
i=.02;                            %interval of loop

%----------calculating limits of coodinate system--------
axis('equal',[-1.5 1.5 -1.5 1.5]) %preparing coordinate system limits
drawnow;                          %drawing the prepared system

%---------------initializing variables-------------------
t=0;                              %time (==x)
y=0;                              %y, the elongation                         
x1=0;                             %additional t variable
y1=0;                             %additional y variable                

%-------------creating ball for function-----------------
h_Ball=line(0,0,'marker','o','markersize',[10],'color',[1 0 0],'markerfacecolor',[1 0 0]);    %creating the ball
drawnow;                                                                                      %drawing the ball initially

%-----------------fuction--------------------------------
y1=A1*sin(w1*0);                        %creating first point used to draw trail
x1=A2*cos(w2*0);                        %creating first point used to draw trail

for t=0:i:(2*pi)+.01;                   %loop to draw the function
    y=A1*sin(w1*t);                     %function
    x=A2*cos(w2*t);                     %function
    set(h_Ball,'xdata',x,'ydata',y);    %drawing ball at point specified by function
    line([x1 x],[y1 y],'linewidth',[2]) %drawing trail of the ball
    drawnow;                            %drawing trail of function
    x1=x;                               %saving old variables for next turn to draw trail
    y1=y;                               %saving old variables for next turn to draw trail
        
endfor;


















