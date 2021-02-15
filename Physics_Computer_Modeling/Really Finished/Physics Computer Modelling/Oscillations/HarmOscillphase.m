%class 05.02.
%Harmonic Oscillation

%dialog bos asking user for Phase
fiinput = inputdlg ('Type in Phase (number)','Oscillation');         %getting user imput for phse
fi=str2double(fiinput);                                                   %phse converted from user input

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Harmonic Oscillation Phase");                       %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);     %Creating Axis
txt= [ "Phase Modulation\ny=sin(x+" num2str(fi) ")"];                          %preparing frequency string
a : title (txt,'fontsize',[17]); %titleing diagram
a : ylabel ("y",'fontsize',[17]);   %labeling y axis
a : xlabel ("t",'fontsize',[17]);   %labeling x axis
grid on;                            %turing on the grid in coordinate system
drawnow;

%---------------changeable variables---------------------
A=1;                            %Amplitude
w=1;                            %frequency
%fi=0;                           %initial phase
i=.05;                          %interval of loop
nplus=1.5;                      %number of oscillations in positive x direction
nneg=.5;                        %number of oscillations in negative x direction

%----------calculating limits of coodinate system--------
lxp=nplus*2*pi;                   %x-limit positive
lxn=-nneg*2*pi;                   %x-limit negative
lyp=A+.5;                         %y-limit positive
lyn=-A-.5;                        %y-limit negative
axis('equal',[lxn-.5 lxp+.5 lyn lyp]) %preparing coordinate system limits
drawnow;                          %drawing the prepared system

%---------------initializing variables-------------------
t=0;                              %time (==x)
y=0;                              %y, the elongation                         
t1=lxn;                           %additional t variable
y1=0;                             %additional y variable                
n=0;

%-------------creating ball for function-----------------
h_Ball=line(lxn,0,'marker','o','markersize',[10],'color',[1 0 0],'markerfacecolor',[1 0 0]); %creating the ball
drawnow;                                                                                     %drawing the ball initially

%--------drawing the lines indicating pi and 2*pi--------
for limit=lxn:pi:lxp;
  
  line([limit limit],[lyn lyp],'linewidth', [.7],'linestyle','--');
  
endfor;

%-----------------fuction--------------------------------
y1=A*sin(w*lxn+fi);                       %creating first point used to draw trail
yf1=sin(t);
for t=lxn:i:lxp                 %loop to draw the function
    yf=sin(t);            %function
    y=A*sin(w*t+fi);            %function
    set(h_Ball,'xdata',t,'ydata',y); %drawing ball at point specified by function
    line([t1 t],[y1 y],'linewidth',[2],'linestyle','--') %drawing trail of the ball
    line([t1 t],[yf1 yf],'linewidth',[.5]) %drawing trail of the ball
    drawnow;                    %drawing trail of function
    t1=t;                       %saving old variables for next turn to draw trail
    y1=y;                       %saving old variables for next turn to draw trail
    yf1=yf;      
endfor


















