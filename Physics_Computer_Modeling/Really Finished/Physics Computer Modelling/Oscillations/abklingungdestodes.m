%-------dialog box asking user for input-----------
input = inputdlg ({"Amplitude", "Frequency", "Phase","Dampening Coefficient (best if <0.5)"},...
"Non-Harmonic Oscillation",[1,25;1,25;1,25;1,25],{"1", "1", "0","0"});   %getting user imput
A=str2double(input{1});                                     %amplitude converted from user input
w=str2double(input{2});                                     %frequency converted from user input
fi=str2double(input{3});                                    %phase converted from user input
d=str2double(input{4});                                     %coefficient converted from user input

%-----------preparing window----------------------------
figure('units','norm','position',[.1 .1 .8 .7],'color',[.9 .9 .9],...
       'name', "Harmonic Oscillation");                               %Creating Window
a = axes('position',[.1 .1 .8 .8],'color',[1 1 1],'fontsize',[12]);             %Creating Axis
dtxt = [ num2str(d) ];
txt = [ "Modulation\ny=" num2str(A) "*e^^(" dtxt "*t)*sin("...
         num2str(w) "*t+" num2str(fi) ")"];  %preparing title string
a : title (txt,'fontsize',[17]);                                                %titleing diagram
a : ylabel ("y",'fontsize',[17]);                                               %labeling y axis
a : xlabel ("x",'fontsize',[17]);                                               %labeling x axis
grid on;                                                                        %turing on the grid in coordinate system
drawnow;                                                                        %drawing the system

%---------------changeable variables---------------------
i=.05;                                %interval of loop
nplus=1.5;                            %number of oscillations in positive x direction
nneg=.5;                              %number of oscillations in negative x direction

%----------calculating limits of coodinate system--------
lxp=nplus*2*pi;                       %x-limit positive
lxn=-nneg*2*pi;                       %x-limit negative
lyp=A*e^(-d*lxn)+.5;                  %y-limit positive
lyn=-A*e^(-d*lxn)-.5;                 %y-limit negative
axis('equal',[lxn-.5 lxp+.5 lyn lyp]) %preparing coordinate system limits
drawnow;                              %drawing the prepared system

%---------------initializing variables-------------------
t=0;                                  %time (==x)
y=0;                                  %y, the elongation                         
t1=lxn;                               %additional t variable
y1=0;                                 %additional y variable                
n=0;                                  %initializing n

%-------------creating ball for function-----------------
h_Ball=line(lxn,0,'marker','o','markersize',[10],'color',...
            [1 0 0],'markerfacecolor',[1 0 0]);   %creating the ball
drawnow;       %drawing the ball initially

%--------drawing lines indicating segments of legnth pi--------
for limit=lxn:pi:lxp;
  
  line([limit limit],[lyn lyp],'linewidth', [.7],'linestyle','--');
  
endfor;

line([0 0],[lyn lyp],'linewidth', [1.5]); %drawing a line indicating x=0

%-----------------function--------------------------------
y1=A*e^(-d*lxn)*sin(w*lxn+fi);            %creating first point used to draw trail user
yf1=sin(lxn);                             %creating first point used to draw trail standard
for t=lxn:i:lxp+.02                       %loop to draw the function
    
    yf=sin(t);                  % standard function
    y=A*e^(-d*t)*sin(w*t+fi);   %user function
    set(h_Ball,'xdata',t,'ydata',y); %drawing ball at point specified by user function
    line([t1 t],[y1 y],'linewidth',[2],'linestyle','--') %drawing trail of the ball (user func)
    line([t1 t],[yf1 yf],'linewidth',[.5]) %drawing trail of the standard func
    drawnow;                    %drawing trail of functions
    t1=t;                       %saving old variables for next turn to draw trail
    y1=y;                       %saving old variables for next turn to draw trail
    yf1=yf;                     %saving old variables for next turn to draw trail
endfor